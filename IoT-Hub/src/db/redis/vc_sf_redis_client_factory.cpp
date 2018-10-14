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

#include <iostream>

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/hiredis-0.13.3/linux/include/hiredis/hiredis.h"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/hiredis-0.13.3/raspberry-pi-2/include/hiredis/hiredis.h"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
// Not supported. 
#endif

#include "db/redis/vc_sf_redis_client_factory.h"

CVCRedisClientFactory::CVCRedisClientFactory(const std::string& host
                                         , int port
                                         , const std::string& user
                                         , const std::string& passwd
                                         , const std::string& database
                                         , unsigned int dbNum
                                      )
                                      : m_mutex(new std::mutex)
                                      , m_dbNumber((dbNum > 15 ? 0 : dbNum))
                                      , m_dbConnection(nullptr){
  m_dbHost             = host;
  m_dbNetworkPort      = port;
  m_dbAccessUser       = user;
  m_dbAccessPassword   = passwd;
  m_databaseSchemaName = database;
}

CVCRedisClientFactory::~CVCRedisClientFactory() {
  if (m_dbConnection) {
      redisFree(m_dbConnection);
      m_dbConnection = nullptr;
  }
}

// The API should free the DB Session.
CVCRedisClientSession* CVCRedisClientFactory::instantiate()
{
  redisContext* c = nullptr;
  
  // TBD Config paramter for redis connection timeout.
  struct timeval timeout = { 1, 500000 }; // 1.5 seconds
  {
    std::unique_lock<std::mutex> l(*m_mutex);
    c = (redisContext*) redisConnectWithTimeout(m_dbHost.c_str(), m_dbNetworkPort, timeout);
    if (c == NULL || c->err) {
      if (c) {
          redisFree(c);
      } else {
  
      }
      return nullptr;
    }
    else {
      redisReply* rr = (redisReply *) redisCommand(c, "SELECT %d", m_dbNumber);
      if(rr != NULL && rr->type == REDIS_REPLY_ERROR ){
        // Redis client is instantiated successfully.
        if (rr) {
          freeReplyObject(rr);
          rr = nullptr;
        }
        if (c) {
          redisFree(c);
          c = nullptr;
        }
        return nullptr;
      }
      
      // Redis client is instantiated successfully.
      if (rr) {
        freeReplyObject(rr);
        rr = nullptr;
      }
    }
  }
  CVCRedisClientSession* res = new CVCRedisClientSession();
  
  // Critical Block +++> Successfully created Redis Client Object
  if (res) {
    res->m_dbConnection = c;
    return res;
  }
  //<--- Critical Block Successfully created Redis Client Object
  
  if (c) {
    redisFree(c);
  }
  return nullptr;
}


//-------NEW CLASS DEFINITION------------
void CVCRedisClientSession::printRedisResultObject(const std::string& command
                                                  , const redisReply *reply) {

  if (reply) {
    
    unsigned int j = 0;  
    switch (reply->type) {
      case REDIS_REPLY_STATUS: 
      case REDIS_REPLY_ERROR: {
        // TBD Log
        break;
      }
      case REDIS_REPLY_INTEGER: {
        break;
      }
      case REDIS_REPLY_NIL: {
        break;
      }
      case REDIS_REPLY_ARRAY: {
        for (j = 0; j < reply->elements; j++) {
          // TBD Log
        }
        break;
      }
      default:
        break;
    }
  }
  
  return;
}