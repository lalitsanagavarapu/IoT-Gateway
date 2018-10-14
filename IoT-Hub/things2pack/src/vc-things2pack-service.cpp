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

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <list>
#include <set>
#include <unordered_map>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <dlfcn.h>

#include "vc_sf_idk_logging.h"

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/uriparser-0.8.4/linux/include/uriparser/Uri.h"
#include "idk/iHubble/zeromq-4.2.2/linux/include/zmq.hpp"
#include "idk/iHubble/json11/linux/include/json11.hpp"
#include "idk/iHubble/libmicrohttpd-0.9.55/linux/include/microhttpd.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Runnable.h"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/uriparser-0.8.4/raspberry-pi-2/include/uriparser/Uri.h"
#include "idk/iHubble/zeromq-4.2.2/raspberry-pi-2/include/zmq.hpp"
#include "idk/iHubble/json11/raspberry-pi-2/include/json11.hpp"
#include "idk/iHubble/libmicrohttpd-0.9.55/raspberry-pi-2/include/microhttpd.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Runnable.h"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
#include "idk/iHubble/uriparser-0.8.4/android-21/armeabi-v7a/include/uriparser/Uri.h"
#include "idk/iHubble/zeromq-4.2.2/android-21/armeabi-v7a/include/zmq.hpp"
#include "idk/iHubble/json11/android-21/armeabi-v7a/include/json11.hpp"
#include "idk/iHubble/libmicrohttpd-0.9.55/android-21/armeabi-v7a/include/microhttpd.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Runnable.h"
#endif

#include "vc_sf_idk_21450_2010_sf_main.h"
#include "vc-things2pack-service.h"

#include "vc_sf_things2pack.h"

// Check that Json has the properties we want.
#include <type_traits>
#define CHECK_TRAIT(x) static_assert(std::x::value, #x)
CHECK_TRAIT(is_nothrow_constructible<json11::Json>);
CHECK_TRAIT(is_nothrow_default_constructible<json11::Json>);
CHECK_TRAIT(is_copy_constructible<json11::Json>);
CHECK_TRAIT(is_nothrow_move_constructible<json11::Json>);
CHECK_TRAIT(is_copy_assignable<json11::Json>);
CHECK_TRAIT(is_nothrow_move_assignable<json11::Json>);
CHECK_TRAIT(is_nothrow_destructible<json11::Json>);

void parse_from_stdin()
{
    std::string buf;
    std::string line;
    while (std::getline(std::cin, line)) {
        buf += line + "\n";
    }

    std::string err;
    auto json = json11::Json::parse(buf, err);
    if (!err.empty()) {
        printf("Failed: %s\n", err.c_str());
    } else {
        printf("Result: %s\n", json.dump().c_str());
    }
}

void startVcThings2PackSFServices()
{
#if defined(IDK_PLATFORM_FAMILY_THINGS2PACK)
    CSFThings2Pack* sf = new CSFThings2Pack();

    // STORE THE SMART FACTORY GLOBAL OBJECT
    G_SFMAIN = sf;
    sf->sfMain();
#endif
    return;
}

void startVcThings2PackNCAP2UIServices()
{
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://127.0.0.1:5555");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, L"", 0);

    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://0.0.0.0:6666");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        subscriber.recv(&request);

        // Do some 'work'.
        // Usually, Business specific parameters are applied.
        sleep(0);

        //  Send the processed data onto publisher channel
        publisher.send(request);
        
    }
    // Hopefully, all set.
    return;
}