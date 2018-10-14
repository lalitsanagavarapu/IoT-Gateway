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

#ifndef _VC_SF_ES_ERRORS_H_
#define _VC_SF_ES_ERRORS_H_

/* Standard C++ includes */

#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>

extern std::unordered_map<int, std::string> G_ES_ERROR_MAP;


// Error Codes of the ES starts from 100-199
// Success is always 0 across all components.
#define ES_SUCCESS                                           (0)
#define ES_EMPTY_STRING                                      (0)
#define ES_EMPTY_JSON_STRING                                 "{}"

// MySQL Errors 100-109
#define ES_ERROR_MYSQL_DB_FACTORY_IS_NOT_RUNNING             (100)
#define ES_ERROR_MYSQL_DB_SERVICE_IS_NOT_RUNNING             (101)
#define ES_ERROR_MYSQL_DB_STATEMENT_EXECUTION                (102)

// Redis Errors 110-119
#define ES_ERROR_REDIS_DB_FACTORY_IS_NOT_RUNNING             (110)
#define ES_ERROR_REDIS_DB_SERVICE_IS_NOT_RUNNING             (111)
#define ES_ERROR_REDIS_DB_STATEMENT_EXECUTION                (112)

// User Errors  120-129
#define ES_ERROR_USER_DUPLICATE_EMAIL                        (120)
#define ES_ERROR_USER_DUPLICATE_MOBILE                       (121)
#define ES_ERROR_PRE_SIGNUP_USER_DUPLICATE_EMAIL             (122)
#define ES_ERROR_PRE_SIGNUP_USER_DUPLICATE_MOBILE            (123)
#define ES_ERROR_PRE_SIGNUP_USER_HAS_RESTRICTED_EMAIL        (124)
#define ES_ERROR_PRE_SIGNUP_USER_HAS_RESTRICTED_MOBILE       (125)
// Signup Errors.
#define ES_ERROR_SIGNUP_VERIFICATION_CODE_EXPIRED            (126)
#define ES_ERROR_SIGNUP_VERIFICATION_FAILED                  (127)

// Error Chain (upstream - downstream error codes)
#define ES_ERROR_CHAIN_UPSTREAM_EXECUTION                    (130)
#define ES_ERROR_CHAIN_DOWNSTREAM_EXECUTION                  (131)

// Parameter validations errors
#define ES_ERROR_PARAMS_INVALID_EMAIL                        (140)
#define ES_ERROR_PARAMS_INVALID_MOBILE                       (141)
#define ES_ERROR_PARAMS_INVALID_LOGIN_NAME                   (142)
#define ES_ERROR_PARAMS_INVALID_COUNTRY_CODE                 (143)
#define ES_ERROR_PARAMS_INVALID_PASSWORD                     (144)
#define ES_ERROR_PARAMS_INVALID_VERIFICATION_CODE            (145)
#define ES_ERROR_PARAMS_INVALID_ROLE                         (146)


// Environment variables
#define ES_ERROR_INVALID_ENVIRONMENT_VARIABLE                (150)

// SMTP ERRORS
#define ES_ERROR_SMTP_SEND_MAIL                              (160)

#define ES_ERROR_USER_ACCOUNT_NOT_FOUND                      (170)

#define ES_ERROR_SERVICE_REQUEST_ATTEMPTS_EXCEEDED           (180)
#define ES_ERROR_FORGOT_PASSWORD_SERVICE_ATTEMPTS_EXCEEDED   (181)

// User Session and Security
#define ES_ERROR_INVALID_LOGIN_SESSION                       (400)
#define ES_ERROR_EXPITED_LOGIN_SESSION                       (401)


#endif /* _VC_SF_ES_ERRORS_H_ */