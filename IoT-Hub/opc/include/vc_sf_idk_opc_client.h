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

#ifndef _VC_SF_IDK_OPC_CLIENT_H_
#define _VC_SF_IDK_OPC_CLIENT_H_

#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cassert>
#include <list>
#include <set>
#include <unordered_map>
#include <memory>

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/json11/linux/include/json11.hpp"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/json11/raspberry-pi-2/include/json11.hpp"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A
#include "idk/iHubble/json11/android-21/armeabi-v7a/include/json11.hpp"
#endif

#include "vc_sf_idk_21450_2010_types.h"
#include "vc_sf_idk_21450_2010_errors.h"
#include "vc_sf_idk_utils.h"

#include "vc_sf_idk_21451_2010_ncap_controller.h"
#include "vc_sf_idk_opc_packml_client.h"

/* Begin of the 'extern "C"' block */
#ifdef __cplusplus
extern "C" {
#endif

class CIdkOpcClientProxy
{
    std::string m_jstrOpcNodeDetails;
    json11::Json m_jopcNodeDetails;

    json11::Json m_jOpcLib;

    std::unordered_map<int, std::shared_ptr<CIdkOpcClientProxyPackmlStatusService> > m_opcPackMlStatusJobs;

public:
    CIdkOpcClientProxy(const std::string& strOpcNodeDetails, const std::string& strOpcLib);
    ~CIdkOpcClientProxy();

    // Caller MUST free the memory
    std::string* readOpc();
};

class CIdkOpcClientProxyDeleter
{
public:
    void operator()(CIdkOpcClientProxy* pe) const
    {
        delete pe;
    }
};

class CIdkOpcClient
{
    std::string m_jstrOpcNodeDetails;
    json11::Json m_jopcNodeDetails;
    std::string m_jstrNcapControllerClient;

    // Product Id is the key
    std::unordered_map<int, std::shared_ptr<CIdkOpcClientProxy> > m_opcClientProxies;

public:
    ~CIdkOpcClient();
    CIdkOpcClient();

    int createOpcClient(const std::string& strOpcNodeDetails, const std::string& jstrNcapControllerClient);

    // Caller MUST free the memory
    std::string* readOpc();
};

#ifdef __cplusplus
} /* end of the 'extern "C"' block */
#endif

#endif /* _VC_SF_IDK_OPC_CLIENT_H_ */
