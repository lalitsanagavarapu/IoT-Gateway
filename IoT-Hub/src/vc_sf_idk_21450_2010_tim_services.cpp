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
#include <unistd.h>
#include <iostream>

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/libmodbus-3.1.4/linux/include/modbus/modbus.h"
#include "idk/iHubble/uriparser-0.8.4/linux/include/uriparser/Uri.h"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/libmodbus-3.1.4/raspberry-pi-2/include/modbus/modbus.h"
#include "idk/iHubble/uriparser-0.8.4/raspberry-pi-2/include/uriparser/Uri.h"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
#include "idk/iHubble/libmodbus-3.1.4/android-21/armeabi-v7a/include/modbus/modbus.h"
#include "idk/iHubble/uriparser-0.8.4/android-21/armeabi-v7a/include/uriparser/Uri.h"
#endif

#include "vc_sf_idk_21450_2010_tim_services.h"

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkTimServices::CIdkTimServices()
{
}

CIdkTimServices::~CIdkTimServices()
{
}

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkTimServicesHttpHandler::CIdkTimServicesHttpHandler()
{
}

CIdkTimServicesHttpHandler::~CIdkTimServicesHttpHandler()
{
}

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkTimServicesTEDHandler::CIdkTimServicesTEDHandler()
{
}

CIdkTimServicesTEDHandler::~CIdkTimServicesTEDHandler()
{
}

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkTimServicesModbusClient::CIdkTimServicesModbusClient()
{
}

CIdkTimServicesModbusClient::~CIdkTimServicesModbusClient()
{
}

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkTimServicesModbusServer::CIdkTimServicesModbusServer()
{
}

CIdkTimServicesModbusServer::~CIdkTimServicesModbusServer()
{
}

void CIdkTimServicesModbusServer::run()
{
    // In the current release we accept one client connection.
    // Let's plan for more client connections in later releases.
    // Further, the modbus server is used for testing the protocol
    // stack.

    // It is a very simple Modbus Server just echo the client message.
    // Only one client can connect to the server.
    
    for (;;)
    {
      
        modbus_t* ctx;
        ctx = modbus_new_tcp("0.0.0.0", 1502);
        /* modbus_set_debug(ctx, TRUE); */
        
        modbus_mapping_t* mb_mapping;

        mb_mapping = modbus_mapping_new(500, 500, 500, 500);
        if (mb_mapping == NULL) {
            // std::cout << "Failed to allocate the mapping: %s\n" << modbus_strerror(errno) << std::endl;
            modbus_close(ctx);
            modbus_free(ctx);
            return;
        }
      
        int s = -1;
        
        s = modbus_tcp_listen(ctx, 1);
        modbus_tcp_accept(ctx, &s);

        for (;;) {
            uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
            int rc;

            rc = modbus_receive(ctx, query);
            if (rc > 0) {
                
                printf ("Received Req...\n");
                
                /* rc is the query size */
                modbus_reply(ctx, query, rc, mb_mapping);
                
            } else if (rc == -1) {
                /* Connection closed by the client or error */
                // std::cout << "Quit the loop: %s\n" << modbus_strerror(errno) << std::endl;
                Poco::Thread::sleep(0);

                // Free All the old context and registers.
                if (s != -1) {
                    close(s);
                }
                // Free All the old context and registers.
                modbus_mapping_free(mb_mapping);
                modbus_close(ctx);
                modbus_free(ctx);
                break;
            }
        }

    }
    
    return;
}