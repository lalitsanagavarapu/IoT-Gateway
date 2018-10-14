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

#include <stdio.h>
#include "vc_sf_idk_21450_2010_types.h"
#include "vc_sf_idk_21450_2010_errors.h"

IEEE1451Dot0ErrorCodesDef IEEE1451Dot0ErrorCodes[] = {
    { VC_SF_ERROR_NO_ERROR, //     (0)
      "No error, operation successful" },
    { VC_SF_ERROR_INVALID_COMMID, //     (1)
      "Invalid commId" },
    { VC_SF_ERROR_UNKNOWN_DESTID, //     (2)
      "Unknown destId" },
    { VC_SF_ERROR_TIMEOUT, //     (3)
      "Operation time-out" },
    { VC_SF_ERROR_NETWORK_FAILURE, //     (4)
      "Destination unreachable network failure" },
    { VC_SF_ERROR_NETWORK_CORRUPTION, //     (5)
      "Corrupt communication network failure" },
    { VC_SF_ERROR_MEMORY, //     (6)
      "Local out-of-memory error" },
    { VC_SF_ERROR_QOS_FAILURE, //     (7)
      "Network quality-of-service violation" },
    { VC_SF_ERROR_MCAST_NOT_SUPPORTED, //     (8)
      "Multicast not supported or operation invalid for multicast" },
    { VC_SF_ERROR_UNKNOWN_GROUPID, //     (9)
      "Unknown groupId" },
    { VC_SF_ERROR_UNKNOWN_MODULEID, //     (10)
      "Unknown moduleId" },
    { VC_SF_ERROR_UNKNOWN_MSGID, //     (11)
      "Unknown msgId" },
    { VC_SF_ERROR_NOT_GROUP_MEMBER, //     (12)
      "destId not in the group" },
    { VC_SF_ERROR_ILLEGAL_MODE, //     (13)
      "The mode parameter is not valid" },
    { VC_SF_ERROR_LOCKED_RESOURCE, //     (14)
      "The resource being accessed is locked" },
    { VC_SF_ERROR_FATAL_TEDS_ERROR, //     (15)
      "An error in the TEDS makes the device unusable" },
    { VC_SF_ERROR_NON_FATAL_TEDS_ERROR, //     (16)
      "The value in a field in the TEDS is unusable, but the device will still function" },
    { VC_SF_ERROR_CLOSE_ON_LOCKED_RESOURCE, //     (17)
      "A warning error code returned to signal that a close on a locked resource was performed" },
    { VC_SF_ERROR_LOCK_BROKEN, //     (18)
      "If a non-blocking read or write, or measurement stream, \
        is in progress, the callback will be invoked with this error code" },
    { VC_SF_ERROR_NETWORK_RESOURCE_EXCEEDED, //     (19)
      "IEEE 1451.X has reached network resource limits" },
    { VC_SF_ERROR_MEMORY_RESOURCE_EXCEEDED, //     (20)
      "IEEE 1451.X has reached memory resource limits" }
};
