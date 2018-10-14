/*==========================LICENSE NOTICE==========================*/
/*
Copyright (c) 2009-2017 Vidcentum R&D Pvt Ltd. All Rights Reserved.
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

#ifndef _VC_SF_IDK_LOGGING_H_
#define _VC_SF_IDK_LOGGING_H_

#include "vc_sf_idk_21450_2010_types.h"
#include "vc_sf_idk_21450_2010_errors.h"

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A
#include <android/log.h>
#define LOG_TAG "picominer.things2pack.services"
#define LOG_LEVEL 9

#define LOGU(level, ...)                                                \
    if (level <= LOG_LEVEL) {                                           \
        __android_log_print(ANDROID_LOG_UNKNOWN, LOG_TAG, __VA_ARGS__); \
    }
#define LOGD(level, ...)                                                \
    if (level <= LOG_LEVEL) {                                           \
        __android_log_print(ANDROID_LOG_DEFAULT, LOG_TAG, __VA_ARGS__); \
    }
#define LOGV(level, ...)                                                \
    if (level <= LOG_LEVEL) {                                           \
        __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__); \
    }
#define LOGDE(level, ...)                                             \
    if (level <= LOG_LEVEL) {                                         \
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__); \
    }
#define LOGI(level, ...)                                             \
    if (level <= LOG_LEVEL) {                                        \
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__); \
    }
#define LOGW(level, ...)                                             \
    if (level <= LOG_LEVEL) {                                        \
        __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__); \
    }
#define LOGE(level, ...)                                              \
    if (level <= LOG_LEVEL) {                                         \
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__); \
    }
#define LOGF(level, ...)                                              \
    if (level <= LOG_LEVEL) {                                         \
        __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__); \
    }
#define LOGS(level, ...)                                               \
    if (level <= LOG_LEVEL) {                                          \
        __android_log_print(ANDROID_LOG_SILENT, LOG_TAG, __VA_ARGS__); \
    }
#endif
/* Begin of the 'extern "C"' block */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} /* end of the 'extern "C"' block */
#endif

#endif /* _VC_SF_IDK_LOGGING_H_ */