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

#ifndef _VC_SF_IDK_21451_2010_NCAP_CONTROLLER_H_
#define _VC_SF_IDK_21451_2010_NCAP_CONTROLLER_H_

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

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/libmicrohttpd-0.9.55/linux/include/microhttpd.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/linux/include/json11.hpp"
#include "idk/iHubble/curl-7.55.1/linux/include/curl/curl.h"
#include "idk/iHubble/zeromq-4.2.2/linux/include/zmq.hpp"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/libmicrohttpd-0.9.55/raspberry-pi-2/include/microhttpd.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/raspberry-pi-2/include/json11.hpp"
#include "idk/iHubble/curl-7.55.1/raspberry-pi-2/include/curl/curl.h"
#include "idk/iHubble/zeromq-4.2.2/raspberry-pi-2/include/zmq.hpp"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A
#include "idk/iHubble/libmicrohttpd-0.9.55/android-21/armeabi-v7a/include/microhttpd.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/android-21/armeabi-v7a/include/json11.hpp"
#include "idk/iHubble/curl-7.55.1/android-21/armeabi-v7a/include/curl/curl.h"
#include "idk/iHubble/zeromq-4.2.2/android-21/armeabi-v7a/include/zmq.hpp"
#endif

#include "vc_sf_idk_21450_2010_types.h"
#include "vc_sf_idk_21450_2010_errors.h"

/* Begin of the 'extern "C"' block */
#ifdef __cplusplus
extern "C" {
#endif

//
// NCAP Controller binds the Application with Smart Factory IDK
// Please NOTE for security and data integrity reasons, only one
// connection is allowed at any point of time.
// The requests are accepted from local IP addresses only.
// Currently, we support IPv4 and let's plan IPv6 in later releases.
//

class CIdkNcapController;
typedef struct NcapControllerConnectionInfo NcapControllerConnectionInfo;
struct NcapControllerConnectionInfo
{
    int connType;
    char* reply;
    int replyCode;
    struct MHD_PostProcessor* postProcessor;
    CIdkNcapController* ncapController;
    std::string postAPI;
};

class CIdkNcapNotification : public Poco::Notification
{
public:
    CIdkNcapNotification(const std::string& data) : _data(data)
    {
    }
    const std::string& data() const
    {
        return _data;
    }

private:
    std::string _data;
};

class CIdkNcapController : public Poco::Runnable
{
private:
    int m_port;
    std::string m_address;
    std::string m_scheme;
    int m_site_id;
    std::string m_config_node;
    std::string m_get_config_change_api;
    std::string m_get_config_api;
    std::string m_post_config_api;

    // Cyber-Physical Config
    std::string m_get_cyber_physical_config_api;
    std::string m_get_new_cyber_physical_config_api;
    std::string m_post_cyber_physical_config_api;
    std::string m_post_new_cyber_physical_config_key;

    // Transducer APIs
    std::string m_get_transducer_defs_api;
    std::string m_get_new_transducer_defs_api;
    std::string m_post_transducer_defs_api;
    std::string m_post_new_transducer_defs_key;

    // Product Rule Engine APIs
    std::string m_get_product_rules_api;
    std::string m_get_new_product_rules_api;
    std::string m_post_product_rules_api;
    std::string m_post_new_product_rules_key;

    // Asset Management APIs
    std::string m_get_assets_api;
    std::string m_get_new_assets_api;
    std::string m_post_assets_api;
    std::string m_post_new_assets_key;

    // Library Management APIs
    std::string m_get_transducer_library_api;
    std::string m_get_product_library_api;
    std::string m_get_assets_library_api;
    std::string m_get_erp_library_api;
    std::string m_get_opc_library_api;

    // ERP Node API
    std::string m_get_erp_node_api;
    std::string m_get_new_erp_node_api;

    std::string m_post_erp_node_api;
    std::string m_post_new_erp_node_key;

    // OPC Node API
    std::string m_get_opc_node_api;
    std::string m_get_new_opc_node_api;

    std::string m_post_opc_node_api;
    std::string m_post_new_opc_node_key;

    // Pre configured system
    std::string m_get_preset_library_api;

    // NCAP Broadcaster [PUBLISHER]
    int m_broadcaster_port;
    std::string m_broadcaster_address;
    std::string m_broadcaster_scheme;

    std::string m_transducer_defs_update_broadcast_message;
    std::string m_product_rules_update_broadcast_message;
    std::string m_assets_update_broadcast_message;
    std::string m_cyber_physical_update_broadcast_message;
    std::string m_erp_node_update_broadcast_message;
    std::string m_opc_node_update_broadcast_message;

    bool m_bIsValidNcapConfig;

    struct MHD_Daemon* m_daemon;
    std::string m_jstrNcapControllerNodeConfig;

    // This object has valid and working set of transducer definitions.
    std::string m_jstrTransducerDefinitions;

    // This object has new set of transducer definitions.
    // This object SHOULD be copied to m_jstrTransducerDefinitions
    // only if the transducer defintions are valid.
    // Usually, we receive the transducer definitions from a POST request.

    std::string m_jstrNewTransducerDefinitionsPosted;

    std::string m_jstrProductRules;
    std::string m_jstrNewProductRules;

    std::string m_jstrAssets;
    std::string m_jstrNewAssets;

    std::string m_jstrCyberPhysicalConfig;
    std::string m_jstrNewCyberPhysicalConfig;

    std::string m_jstrErpNode;
    std::string m_jstrNewErpNode;

    std::string m_jstrOpcNode;
    std::string m_jstrNewOpcNode;

    // Boardcast Config Update.
    // Prepare our context and socket
    zmq::context_t* m_0mqContext;
    zmq::socket_t* m_0mqNcapControlerBroadcaster;

    // Notification Q
    Poco::NotificationQueue* m_queue;

public:
    virtual ~CIdkNcapController();
    CIdkNcapController(Poco::NotificationQueue* queue,
                       const std::string& jstrNcapControllerNodeConfig,
                       const std::string& jstrTransducerDefinitions,
                       const std::string& jstrProductRules,
                       const std::string& jstrAssets,
                       const std::string& jstrErpNode,
                       const std::string& jstrOpcNode);

    int start();
    static int ncapControllerService(void* cls,
                                     struct MHD_Connection* connection,
                                     const char* url,
                                     const char* method,
                                     const char* version,
                                     const char* upload_data,
                                     size_t* upload_data_size,
                                     void** con_cls);
    static void postRequestCompletedCb(void* cls,
                                       struct MHD_Connection* connection,
                                       void** con_cls,
                                       enum MHD_RequestTerminationCode tcode);
    static int iteratePostCb(void* coninfo_cls,
                             enum MHD_ValueKind kind,
                             const char* key,
                             const char* filename,
                             const char* content_type,
                             const char* transfer_encoding,
                             const char* data,
                             uint64_t off,
                             size_t size);

    int broadcastTransducerDefsUpdate();
    int broadcastProductRulesUpdate();
    int broadcastAssetsUpdate();
    int broadcastCyberPhysicalConfigUpdate();
    int broadcastErpNodeUpdate();
    int broadcastOpcNodeUpdate();

    virtual void run();
};

//
// Applications derive from CIdkNcapControllerClient
// BECAREFUL WHILE SHARING THIS CLASS OBJECTS ACROSS THE THREADS
//
class CIdkNcapControllerClient
{
private:
    int m_port;
    std::string m_address;
    std::string m_scheme;
    int m_site_id;
    std::string m_config_node;
    std::string m_get_config_change_api;
    std::string m_get_config_api;
    std::string m_post_config_api;

    // Cyber-Physical Config
    std::string m_get_cyber_physical_config_api;

    // Transducer APIs
    std::string m_get_transducer_defs_api;
    std::string m_get_new_transducer_defs_api;
    std::string m_post_transducer_defs_api;
    std::string m_post_new_transducer_defs_key;

    // Product Rule Engine APIs
    std::string m_get_product_rules_api;
    std::string m_get_new_product_rules_api;
    std::string m_post_product_rules_api;
    std::string m_post_new_product_rules_key;

    // Asset Management APIs
    std::string m_get_assets_api;
    std::string m_get_new_assets_api;
    std::string m_post_assets_api;
    std::string m_post_new_assets_key;

    // Library Management APIs
    std::string m_get_transducer_library_api;
    std::string m_get_product_library_api;
    std::string m_get_assets_library_api;
    std::string m_get_preset_library_api;

    std::string m_get_erp_library_api;
    std::string m_get_opc_library_api;

    // ERP Node API
    std::string m_get_erp_node_api;
    std::string m_get_new_erp_node_api;

    std::string m_post_erp_node_api;
    std::string m_post_new_erp_node_key;

    // OPC Node API
    std::string m_get_opc_node_api;
    std::string m_get_new_opc_node_api;

    std::string m_post_opc_node_api;
    std::string m_post_new_opc_node_key;

    bool m_bIsValidNcapConfig;

    std::string m_jstrNcapController;

    bool clientInit(CURL*& conn, const char* url, char* errorBuffer, std::string* dataBuffer);

    bool initConfig(const std::string& jstrNcapController);

public:
    CIdkNcapControllerClient();
    CIdkNcapControllerClient(const std::string& jstrNcapController);
    virtual ~CIdkNcapControllerClient();

    static int ncapControllerServiceCb(char* data, size_t size, size_t nmemb, std::string* dataBuffer);

    // Base class functionality
    // CALLER MUST FREE THE std::string*
    std::string* getConfig();
    std::string* getConfigChange();
    std::string* getTransducerDefs();
    std::string* getNewTransducerDefs();
    std::string* getProductRules();
    std::string* getNewProductRules();
    std::string* getAssets();
    std::string* getNewAssets();
    std::string* getCyberPhysicalConfig();
    std::string* getErpNode();
    std::string* getNewErpNode();
    std::string* getOpcNode();
    std::string* getNewOpcNode();

    // Library APIs
    std::string* getTransducerLibrary();
    std::string* getProductLibrary();
    std::string* getAssetsLibrary();
    std::string* getPresetLibrary();
    std::string* getErpLibrary();
    std::string* getOpcLibrary();

    bool reInitConfig(const std::string& jstrNcapController);
};

#ifdef __cplusplus
} /* end of the 'extern "C"' block */
#endif

#endif /* _VC_SF_IDK_21451_2010_NCAP_CONTROLLER_H_ */