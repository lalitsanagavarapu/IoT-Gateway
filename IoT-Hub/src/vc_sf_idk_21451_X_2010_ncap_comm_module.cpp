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
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <dlfcn.h>

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/uriparser-0.8.4/linux/include/uriparser/Uri.h"
#include "idk/iHubble/zeromq-4.2.2/linux/include/zmq.hpp"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/uriparser-0.8.4/raspberry-pi-2/include/uriparser/Uri.h"
#include "idk/iHubble/zeromq-4.2.2/raspberry-pi-2/include/zmq.hpp"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
#include "idk/iHubble/uriparser-0.8.4/android-21/armeabi-v7a/include/uriparser/Uri.h"
#include "idk/iHubble/zeromq-4.2.2/android-21/armeabi-v7a/include/zmq.hpp"
#endif

#include "vc_sf_idk_utils.h"
#include "vc_sf_idk_logging.h"
#include "vc_sf_idk_21451_X_2010_ncap_comm_module.h"

CIdkNcapIoTClient::CIdkNcapIoTClient(const std::string& jstrTimWs,
                                     const std::string& primayAPI,
                                     const std::string& jstrModelProcessorCommunicator)
{
    m_jstrTimWs = jstrTimWs;
    m_timSerivcesAPI = primayAPI;
    initConfig(jstrModelProcessorCommunicator);
}

bool CIdkNcapIoTClient::initConfig(const std::string& jstrModelProcessorCommunicator)
{
    m_ncap_processor_communicator_node = "ncap_model_processor_communicator";

    m_jstrModelProcessorCommunicator.clear();

    m_bIsValidNcapCommunicator = false;

    std::string err;
    json11::Json jncapCommunicatorNode = json11::Json::parse(jstrModelProcessorCommunicator, err);
    if (!err.empty()) {
        m_bIsValidNcapCommunicator = false;
    } else {
        m_jstrModelProcessorCommunicator = jstrModelProcessorCommunicator;
        m_bIsValidNcapCommunicator = true;

        m_site_id = jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]["site_id"].number_value();
        m_ncap_processor_communicator_port =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]["ncap_model_processor_communicator_port"]
                .number_value();
        m_ncap_processor_communicator_address =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]
                                 ["ncap_model_processor_communicator_address"].string_value();
        m_ncap_processor_communicator_scheme =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]
                                 ["ncap_model_processor_communicator_scheme"].string_value();
    }
    return m_bIsValidNcapCommunicator;
}

CIdkNcapIoTClient::~CIdkNcapIoTClient()
{
}

void CIdkNcapIoTClient::run()
{
    //  Prepare context and socket
    zmq::context_t context(1);
    zmq::socket_t modelProcessor(context, ZMQ_PUSH);

    std::string pushmq;
    pushmq.clear();
    pushmq.append(m_ncap_processor_communicator_scheme);
    pushmq.append("://");
    pushmq.append(m_ncap_processor_communicator_address);
    pushmq.append(":");
    char buff[33] = {};
    snprintf(buff, sizeof(buff), "%d", m_ncap_processor_communicator_port);
    pushmq.append(buff);

    modelProcessor.connect(pushmq.c_str());

    CIdkTimClient tc(m_jstrTimWs);

    while (1) {
      
        /*
        // Print Timestamp for each loop:
        long long milliseconds_since_epoch_start = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        */
      
        std::string* pTimApiResponse = NULL;
        pTimApiResponse = tc.doTimSerivcesAPI(m_timSerivcesAPI);

        if (pTimApiResponse->compare("") == 0) {
            // Empty response is an indication of some
            // communication / device / transducer error
            // Log it.
            
            std::cout << "GOT EMPTY IOT RESPONSE for " << m_timSerivcesAPI << std::endl;
        }
        
        // By now we have the transducer data received from TIM in buffer.
        // PUSH this data to the Cloud Server.
        zmq::message_t message(pTimApiResponse->length() + 1);
        memset((char*)message.data(), 0, pTimApiResponse->length() + 1);
        memcpy((char*)message.data(), pTimApiResponse->c_str(), pTimApiResponse->length());

        modelProcessor.send(message);

        delete pTimApiResponse;
        pTimApiResponse = NULL;

        /*
        long long milliseconds_since_epoch_end = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        
        std::cout << "Read IoT Data in " 
                  << milliseconds_since_epoch_end - milliseconds_since_epoch_start 
                  << " ms." << std::flush;
         */

#ifdef IDK_PLATFORM_LINUX
        Poco::Thread::sleep(3000);
 
#elif IDK_PLATFORM_ARM_RPI
        Poco::Thread::sleep(3000);
        
#elif IDK_PLATFORM_ANDROID_21_ARMEABI_V7A
        Poco::Thread::sleep(3000);
#endif
    }
}

//++++++++++++++++++NEW CLASS DEFINITION+++++++++++++++++++

CIdkNcapOPCClient::CIdkNcapOPCClient(const std::string& jstrTimWs,
                                     const std::string& primayAPI,
                                     const std::string& jstrModelProcessorCommunicator)
{
    m_jstrTimWs = jstrTimWs;
    m_timSerivcesAPI = primayAPI;
    initConfig(jstrModelProcessorCommunicator);
}

bool CIdkNcapOPCClient::initConfig(const std::string& jstrModelProcessorCommunicator)
{
    m_ncap_processor_communicator_node = "ncap_model_processor_communicator";

    m_jstrModelProcessorCommunicator.clear();

    m_bIsValidNcapCommunicator = false;

    std::string err;
    json11::Json jncapCommunicatorNode = json11::Json::parse(jstrModelProcessorCommunicator, err);
    if (!err.empty()) {
        m_bIsValidNcapCommunicator = false;
    } else {
        m_jstrModelProcessorCommunicator = jstrModelProcessorCommunicator;
        m_bIsValidNcapCommunicator = true;

        m_site_id = jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]["site_id"].number_value();
        m_ncap_processor_communicator_port =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]["ncap_model_processor_communicator_port"]
                .number_value();
        m_ncap_processor_communicator_address =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]
                                 ["ncap_model_processor_communicator_address"].string_value();
        m_ncap_processor_communicator_scheme =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]
                                 ["ncap_model_processor_communicator_scheme"].string_value();
    }
    return m_bIsValidNcapCommunicator;
}

CIdkNcapOPCClient::~CIdkNcapOPCClient()
{
}

void CIdkNcapOPCClient::run()
{
    //  Prepare context and socket
    zmq::context_t context(1);
    zmq::socket_t modelProcessor(context, ZMQ_PUSH);

    std::string pushmq;
    pushmq.clear();
    pushmq.append(m_ncap_processor_communicator_scheme);
    pushmq.append("://");
    pushmq.append(m_ncap_processor_communicator_address);
    pushmq.append(":");
    char buff[33] = {};
    snprintf(buff, sizeof(buff), "%d", m_ncap_processor_communicator_port);
    pushmq.append(buff);

    modelProcessor.connect(pushmq.c_str());

    CIdkTimClient tc(m_jstrTimWs);

    while (1) {
        std::string* pTimApiResponse = NULL;
        pTimApiResponse = tc.doTimSerivcesAPI(m_timSerivcesAPI);

        // By now we have the transducer data received from OPC in a buffer.
        // PUSH this data to the Cloud Server.
        // PUSH the data to "Packaging Model Preprocessors" or any
        // other application specific preprocessors.

        zmq::message_t message(pTimApiResponse->length() + 1);
        memset((char*)message.data(), 0, pTimApiResponse->length() + 1);
        memcpy((char*)message.data(), pTimApiResponse->c_str(), pTimApiResponse->length());

        modelProcessor.send(message);

        delete pTimApiResponse;
        pTimApiResponse = NULL;

#ifdef IDK_PLATFORM_LINUX
        Poco::Thread::sleep(3000);
 
#elif IDK_PLATFORM_ARM_RPI
        Poco::Thread::sleep(3000);
        
#elif IDK_PLATFORM_ANDROID_21_ARMEABI_V7A
        Poco::Thread::sleep(3000);
#endif

    }
}

//++++++++++++++++++NEW CLASS DEFINITION+++++++++++++++++++

CIdkNcapERPClient::CIdkNcapERPClient(const std::string& jstrTimWs,
                                     const std::string& primayAPI,
                                     const std::string& jstrModelProcessorCommunicator)
{
    m_jstrTimWs = jstrTimWs;
    m_timSerivcesAPI = primayAPI;
    initConfig(jstrModelProcessorCommunicator);
}

bool CIdkNcapERPClient::initConfig(const std::string& jstrModelProcessorCommunicator)
{
    m_ncap_processor_communicator_node = "ncap_model_processor_communicator";

    m_jstrModelProcessorCommunicator.clear();

    m_bIsValidNcapCommunicator = false;

    std::string err;
    json11::Json jncapCommunicatorNode = json11::Json::parse(jstrModelProcessorCommunicator, err);
    if (!err.empty()) {
        m_bIsValidNcapCommunicator = false;
    } else {
        m_jstrModelProcessorCommunicator = jstrModelProcessorCommunicator;
        m_bIsValidNcapCommunicator = true;

        m_site_id = jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]["site_id"].number_value();
        m_ncap_processor_communicator_port =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]["ncap_model_processor_communicator_port"]
                .number_value();
        m_ncap_processor_communicator_address =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]
                                 ["ncap_model_processor_communicator_address"].string_value();
        m_ncap_processor_communicator_scheme =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]
                                 ["ncap_model_processor_communicator_scheme"].string_value();
    }
    return m_bIsValidNcapCommunicator;
}

CIdkNcapERPClient::~CIdkNcapERPClient()
{
}

void CIdkNcapERPClient::run()
{
    //  Prepare context and socket
    zmq::context_t context(1);
    zmq::socket_t modelProcessor(context, ZMQ_PUSH);

    std::string pushmq;
    pushmq.clear();
    pushmq.append(m_ncap_processor_communicator_scheme);
    pushmq.append("://");
    pushmq.append(m_ncap_processor_communicator_address);
    pushmq.append(":");
    char buff[33] = {};
    snprintf(buff, sizeof(buff), "%d", m_ncap_processor_communicator_port);
    pushmq.append(buff);

    modelProcessor.connect(pushmq.c_str());

    CIdkTimClient tc(m_jstrTimWs);

    while (1) {
        std::string* pTimApiResponse = NULL;
        pTimApiResponse = tc.doTimSerivcesAPI(m_timSerivcesAPI);

        // By now we have the transducer data received from ERP in a buffer.
        // PUSH this data to the Cloud Server.
        // PUSH the data to "Packaging Model Preprocessors" or any
        // other application specific preprocessors.

        zmq::message_t message(pTimApiResponse->length() + 1);
        memset((char*)message.data(), 0, pTimApiResponse->length() + 1);
        memcpy((char*)message.data(), pTimApiResponse->c_str(), pTimApiResponse->length());

        modelProcessor.send(message);

        delete pTimApiResponse;
        pTimApiResponse = NULL;

#ifdef IDK_PLATFORM_LINUX
        Poco::Thread::sleep(3000);
 
#elif IDK_PLATFORM_ARM_RPI
        Poco::Thread::sleep(3000);
        
#elif IDK_PLATFORM_ANDROID_21_ARMEABI_V7A
        Poco::Thread::sleep(3000);
#endif
    }
}