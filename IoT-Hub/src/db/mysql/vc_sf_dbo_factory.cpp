/*==========================LICENSE NOTICE==========================*/
/*
Copyright (c) 2009-#### Vidcentum R&D Pvt Ltd. All Rights Reserved.
Author: Vidcentum R&D (research@vidcentum.com)
*/

/*
The software and services are confidential and proprietary of Vidcentum R&D Pvt Ltd. 
You shall not disclose such Confidential Information and shall use it only in 
accordance with the terms of the license agreement you entered with Vidcentum R&D.
Vidcentum R&D acknowledges and honours the opensource software modules and
respective licenses. 

The software is distributed with source to its users / customers / stakeholders. 

Please see the TERMS OF USE OF THE SOFTWARE below before using this software.

Type of Software: Application
External Libraries: This software uses external libraries with licenses MIT, GPL, Apache etc.
The software is distributed with source to its users / customers as part of its
service contract. It will comply with all or most of licenses of external libraries.
*/

/* 
TERMS OF USE OF THE SOFTWARE by Vidcentum R&D Pvt Ltd
======================================================
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

Ref: https://www.gnu.org/copyleft/gpl.html Sections 15, 16 and 17.

A Disclaimer of Warranty.
=========================
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. 
EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER 
PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED 
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE 
OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST 
OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

B Limitation of Liability.
==========================
IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY 
COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS THE PROGRAM AS 
PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL, 
INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE 
THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED 
INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM 
TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN 
ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

C Interpretation of Sections A and B.
=====================================
If the disclaimer of warranty and limitation of liability provided above cannot be 
given local legal effect according to their terms, reviewing courts shall apply local 
law that most closely approximates an absolute waiver of all civil liability in connection 
with the Program, unless a warranty or assumption of liability accompanies a copy of 
the Program in return for a fee.
*/
/*==========================END LICENSE NOTICE==========================*/  


#include "db/mysql/vc_sf_mysql_dbo_factory.h"

MySQLDboFactory::MySQLDboFactory(const std::string& host
                                   , int port
                                   , const std::string& user
                                   , const std::string& passwd
                                   , const std::string& database
                                )
                : m_mutex(new std::mutex)
                   , m_dbDriver(nullptr)
                   , m_dbConnection(nullptr){
  m_dbHost             = host;
  m_dbNetworkPort      = port;
  m_dbAccessUser       = user;
  m_dbAccessPassword   = passwd;
  m_databaseSchemaName = database;
  
  std::stringstream ss;
  ss << "tcp://" << m_dbHost << ":" << m_dbNetworkPort;
  
  m_dbHostFQN = ss.str();
  
  try
	{
		/* Create a connection */
    m_dbDriver = get_driver_instance();
	}
	catch (sql::SQLException& e)
	{
		std::cout << "Could not get a database driver. Error message: " << e.what() << std::endl;
		m_dbDriver = nullptr;
	}
  
}

MySQLDboFactory::~MySQLDboFactory() {
  if (m_dbConnection){
    delete m_dbConnection;
    m_dbConnection = nullptr; 
  }
}

// The API should free the DB Session.
MySQLDboSession* MySQLDboFactory::instantiate()
{
  try {
    MySQLDboSession* res = new MySQLDboSession(); 
    assert(res != nullptr);
    {
      std::unique_lock<std::mutex> l(*m_mutex);
      
      // Stop. Look. Proceed. 
      sleep(0);
      
      if (m_dbDriver) {
        sql::Connection* con = m_dbDriver->connect(m_dbHostFQN.c_str(), m_dbAccessUser.c_str(), m_dbAccessPassword.c_str());
        
        if (con) {
          /* Connect to the MySQL test database */
          con->setSchema(m_databaseSchemaName.c_str());
          res->m_dbConnection = con;
          
          return res;
        }
      }
    }
    // Unable to instantiate a DB connection.
    delete res;
    return nullptr;
  } 
  catch (sql::SQLException &e) {
    // TBD - Logging
    std::cout << "# ERR: SQLException in " << __FILE__;
    std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
    std::cout << "# ERR: " << e.what();
    std::cout << " (MySQL error code: " << e.getErrorCode();
    std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return nullptr;
  }
 
  return nullptr;
}

