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

/* Standard C++ includes */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>

#include "system/global/wsn/vc_sf_es_errors.h"

// ES Errors
// Remember ES is the Application Domain identifier for Enterprise Systems
std::unordered_map<int, std::string> G_ES_ERROR_MAP
  = {
      { // 0 Success
        ES_SUCCESS
          , ""
      },
      { // 0 Empty String. Never change this convention.
        ES_EMPTY_STRING
          , ""
      },
      // MySQL Errors 110-119
      { // 100
        ES_ERROR_MYSQL_DB_FACTORY_IS_NOT_RUNNING
          , "Error (100). Database factory is not available. Try later."
      },
      { // 101
        ES_ERROR_MYSQL_DB_SERVICE_IS_NOT_RUNNING
          , "Error (101). Database service is not available. Try later."
      },
      { // 102
        ES_ERROR_MYSQL_DB_STATEMENT_EXECUTION
          , "Error (102). Database statement execution failed."
      },
      // Redis Errors 110-119
      { // 110
        ES_ERROR_REDIS_DB_FACTORY_IS_NOT_RUNNING
          , "Error (110). Database factory is not available. Try later."
      },
      { // 111
        ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING
          , "Error (111). Database service is not available. Try later."
      },
      { // 112
        ES_ERROR_REDIS_DB_STATEMENT_EXECUTION
          , "Error (112). Database statement execution failed."
      },
      
      // User Profile Errors
      { // 120
        ES_ERROR_USER_DUPLICATE_EMAIL
          , "Error (120). Another user is already in the system using the same e-mail id."
      },
      { // 121
        ES_ERROR_USER_DUPLICATE_MOBILE
          , "Error (121). Another user is already in the system using the same mobile number."
      },
      { // 122
        ES_ERROR_PRE_SIGNUP_USER_DUPLICATE_EMAIL
          , "Error (122). Another user is already in the system using the same e-mail id."
      },
      { // 123
        ES_ERROR_PRE_SIGNUP_USER_DUPLICATE_MOBILE
          , "Error (123). Another user is already in the system using the same mobile number."
      },
      { // 124
        ES_ERROR_PRE_SIGNUP_USER_HAS_RESTRICTED_EMAIL
          , "Error (124). System is not accepting the E-Mail id. Contact the support team."
      },
      { // 125
        ES_ERROR_PRE_SIGNUP_USER_HAS_RESTRICTED_MOBILE
          , "Error (125). System is not accepting the Mobile number. Contact the support team."
      },
      // Signup Errors.
      { // 126
        ES_ERROR_SIGNUP_VERIFICATION_CODE_EXPIRED
          , "Error (126). Verification Code has expired. Contact the support team."
      },
      { // 127
        ES_ERROR_SIGNUP_VERIFICATION_FAILED
          , "Error (127). User verification failed. Contact the support team."
      },
      { // Upstream Errors 130
        ES_ERROR_CHAIN_UPSTREAM_EXECUTION
          , "Error (130). Upstream function execution encountered soft errors."
      },
      { // Upstream Errors 131
        ES_ERROR_CHAIN_DOWNSTREAM_EXECUTION
          , "Error (131). Downstream function execution encountered soft errors."
      },
      { // Invalid E-Mail parameter 140
        ES_ERROR_PARAMS_INVALID_EMAIL
          , "Error (140). Invalid email. Currently we do not support non ASCII characters in the e-mails."
      },
      { // Invalid Mobile parameter 141
        ES_ERROR_PARAMS_INVALID_MOBILE
          , "Error (141). Invalid nobile number."
      },
      { // Invalid Login parameter 142
        ES_ERROR_PARAMS_INVALID_LOGIN_NAME
          , "Error (142). Invalid login name."
      },
      { // Invalid Country  143
        ES_ERROR_PARAMS_INVALID_COUNTRY_CODE
          , "Error (143). Invalid country code."
      },
      { // Invalid Password  144
        ES_ERROR_PARAMS_INVALID_PASSWORD
          , "Error (144). Invalid password / e-mail / verification credentials."
      },
      { // Invalid Password  145
        ES_ERROR_PARAMS_INVALID_VERIFICATION_CODE
          , "Error (145). Invalid password / e-mail / verification credentials."
      },
      { // Invalid Role 146
        ES_ERROR_PARAMS_INVALID_ROLE
          , "Error (146). Invalid password / e-mail / role / verification credentials."
      },
      { // Invalid Environment Variable 150
        ES_ERROR_INVALID_ENVIRONMENT_VARIABLE
          , "Error (150). Invalid Environment Variable."
      },      
      { // Error while sending E-Mail 160
        ES_ERROR_SMTP_SEND_MAIL
          , "Error (160). Error while sending E-Mail"
      },
      { // User is not found 170
        ES_ERROR_USER_ACCOUNT_NOT_FOUND
          , "Error (170). User is not found."
      },

      { // Exceeding number of service requests. 180
        ES_ERROR_SERVICE_REQUEST_ATTEMPTS_EXCEEDED
          , "Error (180). Exceeding number of service requests. Try later."
      },

      { // Exceeding number of forgot password service requests. 181
        ES_ERROR_FORGOT_PASSWORD_SERVICE_ATTEMPTS_EXCEEDED
          , "Error (180). Exceeding number of forgot password service requests. Try later."
      },
      
      // User Session and Security  (400)
      { // User either did not login or the session expired.
        ES_ERROR_INVALID_LOGIN_SESSION
          , "Error (400). Your either did not login (1) or your session expired. Login to continue."
      },
      { // User either did not login or the session expired.
        ES_ERROR_EXPITED_LOGIN_SESSION
          , "Error (401). Your either did not login or your session expired (2). Login to continue."
      }
      
    };
  
