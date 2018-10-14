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

// Errors
#include "system/global/wsn/vc_sf_es_errors.h"
#include "system/global/security/vc_sf_security_errors.h"
#include "db/redis/vc_sf_redis_client_factory.h"
#include "foundation/qlib/vc_sf_reliable_redis_q.h"


CVCSfIoTHubIngressWsnReliableRedisQ::CVCSfIoTHubIngressWsnReliableRedisQ ( CVCRedisClientFactory*  redisClientFactory
                                                                             , const std::string&        domain
                                                                             , const std::string&        q_name
                                                                         )
                                                                         : m_redisClientFactory(redisClientFactory)
                                                                           , m_domainName(domain)
                                                                           , m_qName(q_name)
                                                                         {
                          
}
                 
CVCSfIoTHubIngressWsnReliableRedisQ::~CVCSfIoTHubIngressWsnReliableRedisQ(){
  
}
    
int CVCSfIoTHubIngressWsnReliableRedisQ::push(const std::string& q_element){
  if (m_redisClientFactory){
    std::unique_ptr<CVCRedisClientSession> rdb(m_redisClientFactory->instantiate());
    
    if (rdb == nullptr || !rdb->m_dbConnection){
      // TBD (Log and return error)
      return ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING;
    }
    redisReply* rr = (redisReply *) redisCommand(
                                                  rdb->m_dbConnection
                                                    , "RPUSH %s:%s %s"
                                                    , m_domainName.c_str()
                                                    , m_qName.c_str()
                                                    , q_element.c_str()
                                                );
    rdb->printRedisResultObject("RPUSH", rr);
    if(rr){
      int res = (rr->type == REDIS_REPLY_ERROR) ? ES_ERROR_REDIS_DB_STATEMENT_EXECUTION : ES_SUCCESS;
      
      freeReplyObject(rr);
      
      return res;
    }
    return ES_ERROR_REDIS_DB_STATEMENT_EXECUTION;    
  }
  
  // TDB (Log and return error)
  return ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING;
}


int CVCSfIoTHubIngressWsnReliableRedisQ::pushToThisQ(const std::string& q_domain         // Appliction ID (WSN:EGRESS)
                                                       , const std::string& q_name       // Q Names
                                                       , const std::string& q_element){
  if (m_redisClientFactory){
    std::unique_ptr<CVCRedisClientSession> rdb(m_redisClientFactory->instantiate());
    
    if (rdb == nullptr || !rdb->m_dbConnection){
      // TBD (Log and return error)
      return ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING;
    }
    redisReply* rr = (redisReply *) redisCommand(
                                                  rdb->m_dbConnection
                                                    , "RPUSH %s:%s %s"
                                                    , q_domain.c_str()
                                                    , q_name.c_str()
                                                    , q_element.c_str()
                                                );
    rdb->printRedisResultObject("RPUSH", rr);
    if(rr){
      int res = (rr->type == REDIS_REPLY_ERROR) ? ES_ERROR_REDIS_DB_STATEMENT_EXECUTION : ES_SUCCESS;
      
      freeReplyObject(rr);
      
      return res;
    }
    return ES_ERROR_REDIS_DB_STATEMENT_EXECUTION;    
  }
  
  // TDB (Log and return error)
  return ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING;
}
    
/*
  count > 0: Remove elements equal to value (q_element) moving from head to tail.
  count < 0: Remove elements equal to value (q_element) moving from tail to head.
  count = 0: Remove all elements equal to value (q_element).
*/
int CVCSfIoTHubIngressWsnReliableRedisQ::remove(const std::string& q_element, int count){
  
  // TBD Not implemented.
  return ES_SUCCESS;
}

int CVCSfIoTHubIngressWsnReliableRedisQ::removeFromThisQ(const std::string& q_domain         // Appliction ID (WSN:EGRESS)
                                                           , const std::string& q_name       // Q Names
                                                           , const std::string& q_element
                                                           , int count
                                                        )
{
  
  // TBD Not implemented.
  return ES_SUCCESS;
 
}

//////////////////// NEW CLASS DEFINITION /////////////////////

CVCSfIoTHubEgressWsnReliableRedisQ::CVCSfIoTHubEgressWsnReliableRedisQ (CVCRedisClientFactory*  redisClientFactory
                                                                           , const std::string&        domain
                                                                           , const std::string&        q_name
                                                                       )
                                                                       : m_redisClientFactory(redisClientFactory)
                                                                         , m_domainName(domain)
                                                                         , m_qName(q_name)
                                                                       {
                          
}
                 
CVCSfIoTHubEgressWsnReliableRedisQ::~CVCSfIoTHubEgressWsnReliableRedisQ(){
  
}
    
int CVCSfIoTHubEgressWsnReliableRedisQ::push(const std::string& q_element){
  if (m_redisClientFactory){
    std::unique_ptr<CVCRedisClientSession> rdb(m_redisClientFactory->instantiate());
    
    if (rdb == nullptr || !rdb->m_dbConnection){
      // TBD (Log and return error)
      return ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING;
    }
    redisReply* rr = (redisReply *) redisCommand(
                                                  rdb->m_dbConnection
                                                    , "RPUSH %s:%s %s"
                                                    , m_domainName.c_str()
                                                    , m_qName.c_str()
                                                    , q_element.c_str()
                                                );
    rdb->printRedisResultObject("RPUSH", rr);
    if(rr){
      int res = (rr->type == REDIS_REPLY_ERROR) ? ES_ERROR_REDIS_DB_STATEMENT_EXECUTION : ES_SUCCESS;
      
      freeReplyObject(rr);
      
      return res;
    }
    return ES_ERROR_REDIS_DB_STATEMENT_EXECUTION;    
  }
  
  // TDB (Log and return error)
  return ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING;
}
    
int CVCSfIoTHubEgressWsnReliableRedisQ::pushToThisQ(const std::string& q_domain         // Appliction ID (WSN:EGRESS)
                                                      , const std::string& q_name       // Q Names
                                                      , const std::string& q_element){
  if (m_redisClientFactory){
    std::unique_ptr<CVCRedisClientSession> rdb(m_redisClientFactory->instantiate());
    
    if (rdb == nullptr || !rdb->m_dbConnection){
      // TBD (Log and return error)
      return ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING;
    }
    redisReply* rr = (redisReply *) redisCommand(
                                                  rdb->m_dbConnection
                                                    , "RPUSH %s:%s %s"
                                                    , q_domain.c_str()
                                                    , q_name.c_str()
                                                    , q_element.c_str()
                                                );
    rdb->printRedisResultObject("RPUSH", rr);
    if(rr){
      int res = (rr->type == REDIS_REPLY_ERROR) ? ES_ERROR_REDIS_DB_STATEMENT_EXECUTION : ES_SUCCESS;
      
      freeReplyObject(rr);
      
      return res;
    }
    return ES_ERROR_REDIS_DB_STATEMENT_EXECUTION;    
  }
  
  // TDB (Log and return error)
  return ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING;
}

    
/*
  count > 0: Remove elements equal to value (q_element) moving from head to tail.
  count < 0: Remove elements equal to value (q_element) moving from tail to head.
  count = 0: Remove all elements equal to value (q_element).
*/
int CVCSfIoTHubEgressWsnReliableRedisQ::remove(const std::string& q_element, int count){
  
  // TBD Not implemented.
  return ES_SUCCESS;
}

int CVCSfIoTHubEgressWsnReliableRedisQ::removeFromThisQ(const std::string& q_domain         // Appliction ID (WSN:EGRESS)
                                                          , const std::string& q_name       // Q Names
                                                          , const std::string& q_element
                                                          , int count
                                                       )
{
  
  // TBD Not implemented.
  return ES_SUCCESS;
 
}