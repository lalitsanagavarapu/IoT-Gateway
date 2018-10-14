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

#ifndef _VC_SF_IDK_21450_2010_ERRORS_H_
#define _VC_SF_IDK_21450_2010_ERRORS_H_

#include <string>
#include <vector>
#include <string>

#include "vc_sf_idk_21450_2010_types.h"

/* Begin of the 'extern "C"' block */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Clause 9.3.1.2 Error codes of ISO_IEC_IEEE_21450_2010
 */
/* All error codes are represented as UInt16 quantities.
 * Five entities are involved in a communication transaction:
 * 1) the local IEEE 1451.0 layer,
 * 2) the local IEEE 1451.X layer,
 * 3) the remote IEEE 1451.X layer,
 * 4) the remote IEEE 1451.0 layer,
 * 5) and the remote application layer.
 *
 * The error code source is encoded in the upper 3 bits.
 * Error code source enumeration
 * 0 Error from the local IEEE 1451.0 layer
 * 1 Error from the local IEEE 1451.X layer
 * 2 Error from the remote IEEE 1451.X layer
 * 3 Error from the remote IEEE 1451.0 layer
 * 4 Error from the remote application layer
 * 5 Reserved
 * 6 Reserved
 * 7 Open to manufacturers
 *
 * The error code enumeration is encoded in the lower bits.
 */

#define VC_SF_ERROR_FROM_LOCAL_1451_0 (0)
#define VC_SF_ERROR_FROM_LOCAL_1451_X (1) // X varies as the implementation of standard.
#define VC_SF_ERROR_FROM_REMOTE_1451_X (2)
#define VC_SF_ERROR_FROM_REMOTE_1451_0 (3)
#define VC_SF_ERROR_FROM_REMOTE_APP (4)

#define VC_SF_ERROR_UNKNOWN_ERROR (-1)
#define VC_SF_ERROR_NO_ERROR (0)
#define VC_SF_ERROR_INVALID_COMMID (1)
#define VC_SF_ERROR_UNKNOWN_DESTID (2)
#define VC_SF_ERROR_TIMEOUT (3)
#define VC_SF_ERROR_NETWORK_FAILURE (4)
#define VC_SF_ERROR_NETWORK_CORRUPTION (5)
#define VC_SF_ERROR_MEMORY (6)
#define VC_SF_ERROR_QOS_FAILURE (7)
#define VC_SF_ERROR_MCAST_NOT_SUPPORTED (8)
#define VC_SF_ERROR_UNKNOWN_GROUPID (9)
#define VC_SF_ERROR_UNKNOWN_MODULEID (10)
#define VC_SF_ERROR_UNKNOWN_MSGID (11)
#define VC_SF_ERROR_NOT_GROUP_MEMBER (12)
#define VC_SF_ERROR_ILLEGAL_MODE (13)
#define VC_SF_ERROR_LOCKED_RESOURCE (14)
#define VC_SF_ERROR_FATAL_TEDS_ERROR (15)
#define VC_SF_ERROR_NON_FATAL_TEDS_ERROR (16)
#define VC_SF_ERROR_CLOSE_ON_LOCKED_RESOURCE (17)
#define VC_SF_ERROR_LOCK_BROKEN (18)
#define VC_SF_ERROR_NETWORK_RESOURCE_EXCEEDED (19)
#define VC_SF_ERROR_MEMORY_RESOURCE_EXCEEDED (20)

typedef struct
{
    UInt16 error;
    _String description;
} IEEE1451Dot0ErrorCodesDef;

extern IEEE1451Dot0ErrorCodesDef IEEE1451Dot0ErrorCodes[];

#ifdef __cplusplus
} /* end of the 'extern "C"' block */
#endif

#endif /* _VC_SF_IDK_21450_2010_ERRORS_H_ */