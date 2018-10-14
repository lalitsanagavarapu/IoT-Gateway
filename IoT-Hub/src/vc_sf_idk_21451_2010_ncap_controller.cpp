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
#include <string>
#include <stdlib.h>

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/uriparser-0.8.4/linux/include/uriparser/Uri.h"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/uriparser-0.8.4/raspberry-pi-2/include/uriparser/Uri.h"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
#include "idk/iHubble/uriparser-0.8.4/android-21/armeabi-v7a/include/uriparser/Uri.h"
#endif

#include "vc_sf_idk_logging.h"
#include "vc_sf_idk_21451_2010_ncap_controller.h"
#include "vc_sf_idk_21450_2010_sf_main.h"

//
extern CIdkSfMain* G_SFMAIN;
//

static char ErrorPage[] =
    "<html><body><h1>Hello, It seems there is an Error in the HTTP Request to NCAP Controller!!!</h1></body></html>";
static char postSuccessPage[] = "<html><body><h1>Hello, Your data is accepted. Great!!!</h1></body></html>";

CIdkNcapController::CIdkNcapController(Poco::NotificationQueue* queue,
                                       const std::string& jstrNcapControllerNodeConfig,
                                       const std::string& jstrTransducerDefinitions,
                                       const std::string& jstrProductRules,
                                       const std::string& jstrAssets,
                                       const std::string& jstrErpNode,
                                       const std::string& jstrOpcNode)

{

    m_daemon = NULL;
    m_0mqContext = NULL;
    m_0mqNcapControlerBroadcaster = NULL;

    m_queue = queue;

    m_jstrNcapControllerNodeConfig = jstrNcapControllerNodeConfig;
    m_jstrTransducerDefinitions = jstrTransducerDefinitions;

    m_jstrProductRules = jstrProductRules;
    m_jstrAssets = jstrAssets;

    m_jstrErpNode = jstrErpNode;
    m_jstrOpcNode = jstrOpcNode;

    m_config_node = "ncap_config_node";
    m_bIsValidNcapConfig = false;

    std::string err;
    json11::Json ncapConfig = json11::Json::parse(jstrNcapControllerNodeConfig, err);
    if (!err.empty()) {
        m_bIsValidNcapConfig = false;
    } else {
        m_bIsValidNcapConfig = true;

        m_site_id = ncapConfig[m_config_node.c_str()]["site_id"].number_value();
        m_port = ncapConfig[m_config_node.c_str()]["port"].number_value();
        m_address = ncapConfig[m_config_node.c_str()]["address"].string_value();
        m_scheme = ncapConfig[m_config_node.c_str()]["scheme"].string_value();
        ;
        m_get_config_change_api = ncapConfig[m_config_node.c_str()]["get_config_change_api"].string_value();
        m_get_config_api = ncapConfig[m_config_node.c_str()]["get_config_api"].string_value();
        m_post_config_api = ncapConfig[m_config_node.c_str()]["post_config_api"].string_value();

        // Cyber Physical APIs
        m_get_cyber_physical_config_api =
            ncapConfig[m_config_node.c_str()]["get_cyber_physical_config_api"].string_value();
        m_post_cyber_physical_config_api =
            ncapConfig[m_config_node.c_str()]["post_cyber_physical_config_api"].string_value();
        m_get_new_cyber_physical_config_api =
            ncapConfig[m_config_node.c_str()]["get_new_cyber_physical_config_api"].string_value();
        m_post_new_cyber_physical_config_key =
            ncapConfig[m_config_node.c_str()]["post_new_cyber_physical_config_key"].string_value();

        // Transducer APIs
        m_get_transducer_defs_api = ncapConfig[m_config_node.c_str()]["get_transducer_defs_api"].string_value();
        m_post_transducer_defs_api = ncapConfig[m_config_node.c_str()]["post_transducer_defs_api"].string_value();
        m_get_new_transducer_defs_api = ncapConfig[m_config_node.c_str()]["get_new_transducer_defs_api"].string_value();
        m_post_new_transducer_defs_key =
            ncapConfig[m_config_node.c_str()]["post_new_transducer_defs_key"].string_value();

        // NCAP Broadcaster [PUBLISHER]
        m_broadcaster_port = ncapConfig[m_config_node.c_str()]["ncap_controller_broadcaster_port"].number_value();
        m_broadcaster_address = ncapConfig[m_config_node.c_str()]["ncap_controller_broadcaster_address"].string_value();
        m_broadcaster_scheme = ncapConfig[m_config_node.c_str()]["ncap_controller_broadcaster_scheme"].string_value();

        // Product Rule Engine APIs
        m_get_product_rules_api = ncapConfig[m_config_node.c_str()]["get_product_rules_api"].string_value();
        m_post_product_rules_api = ncapConfig[m_config_node.c_str()]["post_product_rules_api"].string_value();
        m_get_new_product_rules_api = ncapConfig[m_config_node.c_str()]["get_new_product_rules_api"].string_value();
        m_post_new_product_rules_key = ncapConfig[m_config_node.c_str()]["post_new_product_rules_key"].string_value();

        // Asset APIs
        m_get_assets_api = ncapConfig[m_config_node.c_str()]["get_assets_api"].string_value();
        m_post_assets_api = ncapConfig[m_config_node.c_str()]["post_assets_api"].string_value();
        m_get_new_assets_api = ncapConfig[m_config_node.c_str()]["get_new_assets_api"].string_value();
        m_post_new_assets_key = ncapConfig[m_config_node.c_str()]["post_new_assets_key"].string_value();

        // Library APIs
        m_get_transducer_library_api = ncapConfig[m_config_node.c_str()]["get_transducer_library_api"].string_value();
        m_get_product_library_api = ncapConfig[m_config_node.c_str()]["get_product_library_api"].string_value();
        m_get_assets_library_api = ncapConfig[m_config_node.c_str()]["get_assets_library_api"].string_value();
        m_get_preset_library_api = ncapConfig[m_config_node.c_str()]["get_preset_library_api"].string_value();
        m_get_erp_library_api = ncapConfig[m_config_node.c_str()]["get_erp_library_api"].string_value();
        m_get_opc_library_api = ncapConfig[m_config_node.c_str()]["get_opc_library_api"].string_value();

        // ERP Node API
        m_get_erp_node_api = ncapConfig[m_config_node.c_str()]["get_erp_node_api"].string_value();
        m_get_new_erp_node_api = ncapConfig[m_config_node.c_str()]["get_new_erp_node_api"].string_value();
        m_post_erp_node_api = ncapConfig[m_config_node.c_str()]["post_erp_node_api"].string_value();
        m_post_new_erp_node_key = ncapConfig[m_config_node.c_str()]["post_new_erp_node_key"].string_value();

        // OPC Node API
        m_get_opc_node_api = ncapConfig[m_config_node.c_str()]["get_opc_node_api"].string_value();
        m_get_new_opc_node_api = ncapConfig[m_config_node.c_str()]["get_new_opc_node_api"].string_value();
        m_post_opc_node_api = ncapConfig[m_config_node.c_str()]["post_opc_node_api"].string_value();
        m_post_new_opc_node_key = ncapConfig[m_config_node.c_str()]["post_new_opc_node_key"].string_value();

        // NCAP Broadcast Messages
        m_transducer_defs_update_broadcast_message =
            ncapConfig[m_config_node.c_str()]["ncap_transducer_defs_update_broadcast_message"].string_value();
        m_product_rules_update_broadcast_message =
            ncapConfig[m_config_node.c_str()]["ncap_product_rules_update_broadcast_message"].string_value();
        m_assets_update_broadcast_message =
            ncapConfig[m_config_node.c_str()]["ncap_assets_update_broadcast_message"].string_value();
        m_cyber_physical_update_broadcast_message =
            ncapConfig[m_config_node.c_str()]["ncap_cyber_physical_update_broadcast_message"].string_value();
        m_erp_node_update_broadcast_message =
            ncapConfig[m_config_node.c_str()]["ncap_erp_node_update_broadcast_message"].string_value();
        m_opc_node_update_broadcast_message =
            ncapConfig[m_config_node.c_str()]["ncap_opc_node_update_broadcast_message"].string_value();
    }
}

CIdkNcapController::~CIdkNcapController()
{
    if (m_0mqNcapControlerBroadcaster) {
        delete m_0mqNcapControlerBroadcaster;
        m_0mqNcapControlerBroadcaster = NULL;
    }

    if (m_0mqContext) {
        delete m_0mqContext;
        m_0mqContext = NULL;
    }
}

void CIdkNcapController::postRequestCompletedCb(void* cls,
                                                struct MHD_Connection* connection,
                                                void** con_cls,
                                                enum MHD_RequestTerminationCode tcode)
{

    NcapControllerConnectionInfo* con_info = (NcapControllerConnectionInfo*)*con_cls;

    if (NULL == con_info) {
        return;
    }

    if (con_info->connType == VC_SF_HTTP_POST) {
        if (NULL != con_info->postProcessor) {
            MHD_destroy_post_processor(con_info->postProcessor);
        }
    }

    if (con_info->postAPI.compare(con_info->ncapController->m_post_transducer_defs_api) == 0) {
        // Let's tell the world that there is some change in the transducer definitions.
        con_info->ncapController->broadcastTransducerDefsUpdate();

    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_product_rules_api) == 0) {
        // Let's tell the world that there is some change in the Product Rules.
        con_info->ncapController->broadcastProductRulesUpdate();
    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_assets_api) == 0) {
        // Let's tell the world that there is some change in the Assets.
        con_info->ncapController->broadcastAssetsUpdate();
    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_cyber_physical_config_api) == 0) {
        // Let's tell the world that there is some change in the Assets.
        con_info->ncapController->broadcastCyberPhysicalConfigUpdate();
    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_erp_node_api) == 0) {
        // Let's tell the world that there is some change in the ERP Node.
        con_info->ncapController->broadcastErpNodeUpdate();
    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_opc_node_api) == 0) {
        // Let's tell the world that there is some change in the OPC Node.
        con_info->ncapController->broadcastOpcNodeUpdate();
    }
    delete (con_info);
    *con_cls = NULL;

    return;
}

// POST APIs are handled in the callback method.
int CIdkNcapController::iteratePostCb(void* coninfo_cls,
                                      enum MHD_ValueKind kind,
                                      const char* key,
                                      const char* filename,
                                      const char* content_type,
                                      const char* transfer_encoding,
                                      const char* data,
                                      uint64_t off,
                                      size_t size)
{
    NcapControllerConnectionInfo* con_info = (NcapControllerConnectionInfo*)coninfo_cls;

    con_info->reply = ErrorPage;
    con_info->replyCode = MHD_HTTP_INTERNAL_SERVER_ERROR;

    if (con_info->postAPI.compare(con_info->ncapController->m_post_transducer_defs_api) == 0) {
        if (0 != strcmp(key, con_info->ncapController->m_post_new_transducer_defs_key.c_str())) {
            return MHD_NO;
        }
        if (size > 0) {
            con_info->ncapController->m_jstrNewTransducerDefinitionsPosted.append(data, (sizeof(char) * size));
        }

    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_product_rules_api) == 0) {
        if (0 != strcmp(key, con_info->ncapController->m_post_new_product_rules_key.c_str())) {
            return MHD_NO;
        }
        if (size > 0) {
            con_info->ncapController->m_jstrNewProductRules.append(data, (sizeof(char) * size));
        }
    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_assets_api) == 0) {
        if (0 != strcmp(key, con_info->ncapController->m_post_new_assets_key.c_str())) {
            return MHD_NO;
        }
        if (size > 0) {
            con_info->ncapController->m_jstrNewAssets.append(data, (sizeof(char) * size));
        }
    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_cyber_physical_config_api) == 0) {
        if (0 != strcmp(key, con_info->ncapController->m_post_new_cyber_physical_config_key.c_str())) {
            return MHD_NO;
        }
        if (size > 0) {
            con_info->ncapController->m_jstrNewCyberPhysicalConfig.append(data, (sizeof(char) * size));
        }
    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_erp_node_api) == 0) {
        if (0 != strcmp(key, con_info->ncapController->m_post_new_erp_node_key.c_str())) {
            return MHD_NO;
        }
        if (size > 0) {
            con_info->ncapController->m_jstrNewErpNode.append(data, (sizeof(char) * size));
        }
    } else if (con_info->postAPI.compare(con_info->ncapController->m_post_opc_node_api) == 0) {
        if (0 != strcmp(key, con_info->ncapController->m_post_new_opc_node_key.c_str())) {
            return MHD_NO;
        }
        if (size > 0) {
            con_info->ncapController->m_jstrNewOpcNode.append(data, (sizeof(char) * size));
        }
    } else {
        return MHD_NO;
    }

    con_info->reply = postSuccessPage;
    con_info->replyCode = MHD_HTTP_OK;

    return MHD_YES;
}

int CIdkNcapController::broadcastCyberPhysicalConfigUpdate()
{

    // IT IS VERY IMPORTANT TO POST ONLY VALID TRANSFER DEFS.
    if (m_jstrNewCyberPhysicalConfig.empty()) {
        // Tit for tat!! You posted invalid data posing as though right data!
        // I honour you and return OK. Don't worry, I remember you posted
        // some wrong data!
        return VC_SF_ERROR_NO_ERROR;
    }
    m_jstrCyberPhysicalConfig = m_jstrNewCyberPhysicalConfig;

    // Get all components of Cyber Physical Configuration
    std::string err;

    json11::Json jcp = json11::Json::parse(m_jstrNewCyberPhysicalConfig, err);

    // Check and Log any json parse error.
    // std::cout << err << std::endl;

    // PLEASE NOTE THAT THE CLIENT MUST ENSURE THE VALID CYBER PHYSICAL CONFIG
    // I AM JUST WORKING IN A SLAVE MODE.
    m_jstrNewAssets = jcp["assets"].dump();
    m_jstrNewProductRules = jcp["product_rules"].dump();
    m_jstrNewTransducerDefinitionsPosted = jcp["transducer_definitions"].dump();

    // DO ANY BASIC VALIDATION ON ALL COMPONENTS OF CYBER PHYSICAL CONFIG
    // ...
    // TBD
    // ...

    // ACTIVATE THE NEW CYBER PHYSICAL CONFIG
    m_jstrAssets = m_jstrNewAssets;
    m_jstrProductRules = m_jstrNewProductRules;
    m_jstrTransducerDefinitions = m_jstrNewTransducerDefinitionsPosted;

    if (m_0mqNcapControlerBroadcaster) {
        zmq::message_t message(m_cyber_physical_update_broadcast_message.length() + 1);
        memset((char*)message.data(), 0, m_cyber_physical_update_broadcast_message.length() + 1);
        memcpy((char*)message.data(),
               m_cyber_physical_update_broadcast_message.c_str(),
               m_cyber_physical_update_broadcast_message.length());

        m_0mqNcapControlerBroadcaster->send(message);
    }
    if (m_queue) {
        CIdkNcapNotification* nobj = new CIdkNcapNotification(m_cyber_physical_update_broadcast_message);

        m_queue->enqueueNotification(nobj);
    }
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkNcapController::broadcastTransducerDefsUpdate()
{

    // IT IS VERY IMPORTANT TO POST ONLY VALID TRANSFER DEFS.
    if (m_jstrNewTransducerDefinitionsPosted.empty()) {
        // Tit for tat!! You posted invalid data posing as though right data!
        // I honour you and return OK. Don't worry, I remember you posted
        // some wrong data!
        return VC_SF_ERROR_NO_ERROR;
    }
    m_jstrTransducerDefinitions = m_jstrNewTransducerDefinitionsPosted;

    if (m_0mqNcapControlerBroadcaster) {
        zmq::message_t message(m_transducer_defs_update_broadcast_message.length() + 1);
        memset((char*)message.data(), 0, m_transducer_defs_update_broadcast_message.length() + 1);
        memcpy((char*)message.data(),
               m_transducer_defs_update_broadcast_message.c_str(),
               m_transducer_defs_update_broadcast_message.length());

        m_0mqNcapControlerBroadcaster->send(message);
    }
    if (m_queue) {
        CIdkNcapNotification* nobj = new CIdkNcapNotification(m_transducer_defs_update_broadcast_message);

        m_queue->enqueueNotification(nobj);
    }
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkNcapController::broadcastProductRulesUpdate()
{

    // IT IS VERY IMPORTANT TO POST ONLY VALID PRODUCT RULES.
    if (m_jstrNewProductRules.empty()) {
        // Tit for tat!! You posted invalid data posing as though right data!
        // I honour you and return OK. Don't worry, I remember you posted
        // some wrong data!
        return VC_SF_ERROR_NO_ERROR;
    }
    m_jstrProductRules = m_jstrNewProductRules;

    if (m_0mqNcapControlerBroadcaster) {
        zmq::message_t message(m_product_rules_update_broadcast_message.length() + 1);
        memset((char*)message.data(), 0, m_product_rules_update_broadcast_message.length() + 1);
        memcpy((char*)message.data(),
               m_product_rules_update_broadcast_message.c_str(),
               m_product_rules_update_broadcast_message.length());

        m_0mqNcapControlerBroadcaster->send(message);
    }
    if (m_queue) {
        CIdkNcapNotification* nobj = new CIdkNcapNotification(m_product_rules_update_broadcast_message);

        m_queue->enqueueNotification(nobj);
    }
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkNcapController::broadcastAssetsUpdate()
{
    // IT IS VERY IMPORTANT TO POST ONLY VALID ASSETS.
    if (m_jstrNewAssets.empty()) {
        // Tit for tat!! You posted invalid data posing as though right data!
        // I honour you and return OK. Don't worry, I remember you posted
        // some wrong data!
        return VC_SF_ERROR_NO_ERROR;
    }
    m_jstrAssets = m_jstrNewAssets;

    if (m_0mqNcapControlerBroadcaster) {
        zmq::message_t message(m_assets_update_broadcast_message.length() + 1);
        memset((char*)message.data(), 0, m_assets_update_broadcast_message.length() + 1);
        memcpy((char*)message.data(),
               m_assets_update_broadcast_message.c_str(),
               m_assets_update_broadcast_message.length());

        m_0mqNcapControlerBroadcaster->send(message);
    }
    if (m_queue) {
        CIdkNcapNotification* nobj = new CIdkNcapNotification(m_assets_update_broadcast_message);

        m_queue->enqueueNotification(nobj);
    }
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkNcapController::broadcastErpNodeUpdate()
{
    // IT IS VERY IMPORTANT TO POST ONLY VALID ERP NODE.
    if (m_jstrNewErpNode.empty()) {
        // Tit for tat!! You posted invalid data posing as though right data!
        // I honour you and return OK. Don't worry, I remember you posted
        // some wrong data!
        return VC_SF_ERROR_NO_ERROR;
    }
    m_jstrErpNode = m_jstrNewErpNode;

    if (m_0mqNcapControlerBroadcaster) {
        zmq::message_t message(m_erp_node_update_broadcast_message.length() + 1);
        memset((char*)message.data(), 0, m_erp_node_update_broadcast_message.length() + 1);
        memcpy((char*)message.data(),
               m_erp_node_update_broadcast_message.c_str(),
               m_erp_node_update_broadcast_message.length());

        m_0mqNcapControlerBroadcaster->send(message);
    }
    if (m_queue) {
        CIdkNcapNotification* nobj = new CIdkNcapNotification(m_erp_node_update_broadcast_message);

        m_queue->enqueueNotification(nobj);
    }
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkNcapController::broadcastOpcNodeUpdate()
{
    // IT IS VERY IMPORTANT TO POST ONLY VALID ERP NODE.
    if (m_jstrNewOpcNode.empty()) {
        // Tit for tat!! You posted invalid data posing as though right data!
        // I honour you and return OK. Don't worry, I remember you posted
        // some wrong data!
        return VC_SF_ERROR_NO_ERROR;
    }
    m_jstrOpcNode = m_jstrNewOpcNode;

    if (m_0mqNcapControlerBroadcaster) {
        zmq::message_t message(m_opc_node_update_broadcast_message.length() + 1);
        memset((char*)message.data(), 0, m_opc_node_update_broadcast_message.length() + 1);
        memcpy((char*)message.data(),
               m_opc_node_update_broadcast_message.c_str(),
               m_opc_node_update_broadcast_message.length());

        m_0mqNcapControlerBroadcaster->send(message);
    }
    if (m_queue) {
        CIdkNcapNotification* nobj = new CIdkNcapNotification(m_opc_node_update_broadcast_message);

        m_queue->enqueueNotification(nobj);
    }
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkNcapController::start()
{
    // Proceed only if we have a valid Node configuration.
    if (!m_bIsValidNcapConfig) {
        return VC_SF_ERROR_UNKNOWN_ERROR;
    }

    // Initialize 0MQ for publishing (broadcasting) NCAP controller events.
    m_0mqContext = new zmq::context_t(1);
    m_0mqNcapControlerBroadcaster = new zmq::socket_t(*m_0mqContext, ZMQ_PUB);

    std::string bmq;
    bmq.clear();
    bmq.append(m_broadcaster_scheme);
    bmq.append("://");
    bmq.append(m_broadcaster_address);
    bmq.append(":");
    char buff[33] = {};
    snprintf(buff, sizeof(buff), "%d", m_broadcaster_port);
    bmq.append(buff);

    m_0mqNcapControlerBroadcaster->bind(bmq.c_str());

    struct sockaddr_in daemon_ip_addr;
    memset(&daemon_ip_addr, 0, sizeof(struct sockaddr_in));
    daemon_ip_addr.sin_family = AF_INET;
    daemon_ip_addr.sin_port = htons(m_port);

    // Let's listen on Local address only.
    inet_pton(AF_INET, m_address.c_str(), &daemon_ip_addr.sin_addr);
    m_daemon = NULL;

    m_daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY | MHD_SUPPRESS_DATE_NO_CLOCK | MHD_USE_EPOLL |
                                    MHD_USE_EPOLL_TURBO,
                                m_port,
                                NULL,
                                NULL,
                                &ncapControllerService,
                                this,
                                MHD_OPTION_NOTIFY_COMPLETED,
                                &postRequestCompletedCb,
                                NULL,
                                MHD_OPTION_SOCK_ADDR,
                                &daemon_ip_addr,
                                MHD_OPTION_CONNECTION_TIMEOUT,
                                (unsigned int)120,
                                MHD_OPTION_THREAD_POOL_SIZE,
                                (unsigned int)4,
                                MHD_OPTION_END);
    if (NULL == m_daemon) {
        // Log Error
        return VC_SF_ERROR_UNKNOWN_ERROR;
    }

    while (1) {
        Poco::Thread::sleep(10000);
    }

    // Hopefully, all set.
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkNcapController::ncapControllerService(void* cls,
                                              struct MHD_Connection* connection,
                                              const char* url,
                                              const char* method,
                                              const char* version,
                                              const char* upload_data,
                                              size_t* upload_data_size,
                                              void** con_cls)
{
    struct MHD_Response* response;
    // static int aptr = 0;
    int ret;

    CIdkNcapController* server = (CIdkNcapController*)cls;

    if ((0 != strcmp(method, "GET")) && (0 != strcmp(method, "POST"))) {
        return MHD_NO; /* unexpected method */
    }

    // if (&aptr != *con_cls)
    // {
    //   /* do never respond on first call */
    //   *con_cls = &aptr;
    //   return MHD_YES;
    // }
    // *con_cls = NULL;                 /* reset when done */

    UriParserStateA uriTimSfstate;
    UriUriA uriSfApi;

    uriTimSfstate.uri = &uriSfApi;

    // API
    if (uriParseUriA(&uriTimSfstate, url) != URI_SUCCESS) {
        /* Failure */

        response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_PERSISTENT);

        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);

        // Free the URI Parser resources
        uriFreeUriMembersA(&uriSfApi);

        return ret;
    }

    // Let's parse URI for API reuested.
    // The FIRST path segment is API. We ignore all other path string.
    std::string api;

    UriPathSegmentA* segment = uriSfApi.pathHead;
    if (segment) {
        UriTextRangeA* text_range = &segment->text;
        if (!text_range || !text_range->first || !text_range->afterLast) {
            return VC_SF_ERROR_UNKNOWN_ERROR;
        }
        api.append(text_range->first, text_range->afterLast - text_range->first);
    }
    // Free the URI Parser resources
    uriFreeUriMembersA(&uriSfApi);

    if (0 == strcmp(method, MHD_HTTP_METHOD_GET)) {
        if (api.compare(server->m_get_config_change_api) == 0) {
            json11::Json confChange = json11::Json::object{
                { "ncap_config_change_response",
                  json11::Json::object{ { "site_id", 1 }, { "response", 0 } // 0 = No change, 1 = Change
                  } }
            };

            std::string rsp = confChange.dump();
            response = MHD_create_response_from_buffer(rsp.length(), (void*)rsp.c_str(), MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_config_api) == 0) {
            response = MHD_create_response_from_buffer(server->m_jstrNcapControllerNodeConfig.length(),
                                                       (void*)server->m_jstrNcapControllerNodeConfig.c_str(),
                                                       MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_transducer_defs_api) == 0) {
            response = MHD_create_response_from_buffer(server->m_jstrTransducerDefinitions.length(),
                                                       (void*)server->m_jstrTransducerDefinitions.c_str(),
                                                       MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_new_transducer_defs_api) == 0) {
            response = MHD_create_response_from_buffer(server->m_jstrNewTransducerDefinitionsPosted.length(),
                                                       (void*)server->m_jstrNewTransducerDefinitionsPosted.c_str(),
                                                       MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_product_rules_api) == 0) {
            response = MHD_create_response_from_buffer(
                server->m_jstrProductRules.length(), (void*)server->m_jstrProductRules.c_str(), MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_new_product_rules_api) == 0) {
            response = MHD_create_response_from_buffer(server->m_jstrNewProductRules.length(),
                                                       (void*)server->m_jstrNewProductRules.c_str(),
                                                       MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_assets_api) == 0) {
            response = MHD_create_response_from_buffer(
                server->m_jstrAssets.length(), (void*)server->m_jstrAssets.c_str(), MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_new_assets_api) == 0) {
            response = MHD_create_response_from_buffer(
                server->m_jstrNewAssets.length(), (void*)server->m_jstrNewAssets.c_str(), MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_new_erp_node_api) == 0) {
            response = MHD_create_response_from_buffer(
                server->m_jstrNewErpNode.length(), (void*)server->m_jstrNewErpNode.c_str(), MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_new_opc_node_api) == 0) {
            response = MHD_create_response_from_buffer(
                server->m_jstrNewOpcNode.length(), (void*)server->m_jstrNewOpcNode.c_str(), MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_erp_node_api) == 0) {
            response = MHD_create_response_from_buffer(
                server->m_jstrErpNode.length(), (void*)server->m_jstrErpNode.c_str(), MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_opc_node_api) == 0) {
            response = MHD_create_response_from_buffer(
                server->m_jstrOpcNode.length(), (void*)server->m_jstrOpcNode.c_str(), MHD_RESPMEM_MUST_COPY);
        } else if (api.compare(server->m_get_cyber_physical_config_api) == 0) {
            std::string cpConfig;
            cpConfig.clear();

            std::string err;

            json11::Json jt = json11::Json::parse(server->m_jstrTransducerDefinitions, err);
            json11::Json jp = json11::Json::parse(server->m_jstrProductRules, err);
            json11::Json ja = json11::Json::parse(server->m_jstrAssets, err);
            json11::Json je = json11::Json::parse(server->m_jstrErpNode, err);
            json11::Json jo = json11::Json::parse(server->m_jstrOpcNode, err);

            json11::Json jtapeo = json11::Json::object{ { "transducer_definitions", jt },
                                                        { "product_rules", jp },
                                                        { "assets", ja },
                                                        { "erp_node", je },
                                                        { "opc_node", jo }, };

            cpConfig = jtapeo.dump();

            response =
                MHD_create_response_from_buffer(cpConfig.length(), (void*)cpConfig.c_str(), MHD_RESPMEM_MUST_COPY);
        }

        // TBD Get rid of Global Smart Factory Object.
        else if (api.compare(server->m_get_assets_library_api) == 0) {
            if (G_SFMAIN) {
                std::string* al = G_SFMAIN->getPlatformMetaAssetsLibrary();
                response = MHD_create_response_from_buffer(al->length(), (void*)al->c_str(), MHD_RESPMEM_MUST_COPY);
                delete al;
            } else {
                response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);
            }
        } else if (api.compare(server->m_get_product_library_api) == 0) {
            if (G_SFMAIN) {
                std::string* pl = G_SFMAIN->getPlatformMetaProductLibrary();
                response = MHD_create_response_from_buffer(pl->length(), (void*)pl->c_str(), MHD_RESPMEM_MUST_COPY);
                delete pl;
            } else {
                response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);
            }
        } else if (api.compare(server->m_get_transducer_library_api) == 0) {
            if (G_SFMAIN) {
                std::string* tl = G_SFMAIN->getPlatformMetaTransducerLibrary();
                response = MHD_create_response_from_buffer(tl->length(), (void*)tl->c_str(), MHD_RESPMEM_MUST_COPY);
                delete tl;
            } else {
                response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);
            }
        } else if (api.compare(server->m_get_preset_library_api) == 0) {
            if (G_SFMAIN) {
                std::string* prl = G_SFMAIN->getPresetSmartFactoryLibrary();
                response = MHD_create_response_from_buffer(prl->length(), (void*)prl->c_str(), MHD_RESPMEM_MUST_COPY);
                delete prl;
            } else {
                response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);
            }
        } else if (api.compare(server->m_get_erp_library_api) == 0) {
            if (G_SFMAIN) {
                std::string* prl = G_SFMAIN->getPlatformMetaErpLibrary();
                response = MHD_create_response_from_buffer(prl->length(), (void*)prl->c_str(), MHD_RESPMEM_MUST_COPY);
                delete prl;
            } else {
                response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);
            }
        } else if (api.compare(server->m_get_opc_library_api) == 0) {
            if (G_SFMAIN) {
                std::string* prl = G_SFMAIN->getPlatformMetaOpcLibrary();
                response = MHD_create_response_from_buffer(prl->length(), (void*)prl->c_str(), MHD_RESPMEM_MUST_COPY);
                delete prl;
            } else {
                response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);
            }
        } else {
            response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);
        }

        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }
    if (0 == strcmp(method, MHD_HTTP_METHOD_POST)) {
        // Currently we support limited POST APIs.
        if ((api.compare(server->m_post_transducer_defs_api) != 0) &&
            (api.compare(server->m_post_product_rules_api) != 0) && (api.compare(server->m_post_assets_api) != 0) &&
            (api.compare(server->m_post_cyber_physical_config_api) != 0) &&
            (api.compare(server->m_post_erp_node_api) != 0) && (api.compare(server->m_post_opc_node_api) != 0)) {

            response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);

            ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);

            return MHD_NO;
        }

        if (NULL == *con_cls) {

            // Let's clear data members for POST.
            // For every POST, we will have unique member object.

            if (api.compare(server->m_post_transducer_defs_api) == 0) {
                server->m_jstrNewTransducerDefinitionsPosted.clear();
            } else if (api.compare(server->m_post_product_rules_api) == 0) {
                server->m_jstrNewProductRules.clear();
            } else if (api.compare(server->m_post_assets_api) == 0) {
                server->m_jstrNewAssets.clear();
            } else if (api.compare(server->m_post_cyber_physical_config_api) == 0) {
                server->m_jstrNewCyberPhysicalConfig.clear();
            } else if (api.compare(server->m_post_erp_node_api) == 0) {
                server->m_jstrNewErpNode.clear();
            } else if (api.compare(server->m_post_opc_node_api) == 0) {
                server->m_jstrNewOpcNode.clear();
            } else {
                response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);

                ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                MHD_destroy_response(response);
                return MHD_NO;
            }
            struct NcapControllerConnectionInfo* con_info;

            con_info = new NcapControllerConnectionInfo();
            if (NULL == con_info) {
                return MHD_NO;
            }
            con_info->ncapController = server;
            con_info->postAPI.append(api);

            con_info->postProcessor =
                MHD_create_post_processor(connection, VC_SF_HTTP_POST_BUFFER_SIZE, &iteratePostCb, (void*)con_info);

            if (NULL == con_info->postProcessor) {
                delete (con_info);

                return MHD_NO;
            }

            con_info->connType = VC_SF_HTTP_POST;
            con_info->replyCode = MHD_HTTP_OK;
            con_info->reply = postSuccessPage;

            *con_cls = (void*)con_info;

            return MHD_YES;
        }

        NcapControllerConnectionInfo* con_info = (NcapControllerConnectionInfo*)*con_cls;

        if (0 != *upload_data_size) {
            MHD_post_process(con_info->postProcessor, upload_data, *upload_data_size);
            *upload_data_size = 0;

            return MHD_YES;
        } else {
            // TBD Validate the Transducer Definitions.

            response =
                MHD_create_response_from_buffer(strlen(postSuccessPage), (void*)postSuccessPage, MHD_RESPMEM_MUST_COPY);
            ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);

            return ret;
        }
    }

    // Control should not reach here if everything goes as designed:-)
    response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);

    ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    MHD_destroy_response(response);

    return ret;
}

void CIdkNcapController::run()
{
    start();
}

//+++++++++NEW CLASS DEFINITION++++++++++++++++++

CIdkNcapControllerClient::CIdkNcapControllerClient()
{
}

CIdkNcapControllerClient::CIdkNcapControllerClient(const std::string& jstrNcapController)
{
    initConfig(jstrNcapController);
}

bool CIdkNcapControllerClient::initConfig(const std::string& jstrNcapController)
{
    m_jstrNcapController = jstrNcapController;

    m_config_node = "ncap_config_node";
    m_bIsValidNcapConfig = false;

    std::string err;
    json11::Json ncapConfig = json11::Json::parse(m_jstrNcapController, err);
    if (!err.empty()) {
        m_bIsValidNcapConfig = false;
    } else {
        m_bIsValidNcapConfig = true;

        m_site_id = ncapConfig[m_config_node.c_str()]["site_id"].number_value();
        m_port = ncapConfig[m_config_node.c_str()]["port"].number_value();
        m_address = ncapConfig[m_config_node.c_str()]["address"].string_value();
        m_scheme = ncapConfig[m_config_node.c_str()]["scheme"].string_value();
        ;
        m_get_config_change_api = ncapConfig[m_config_node.c_str()]["get_config_change_api"].string_value();
        m_get_config_api = ncapConfig[m_config_node.c_str()]["get_config_api"].string_value();
        m_post_config_api = ncapConfig[m_config_node.c_str()]["post_config_api"].string_value();

        // Cyber Physical APIs
        m_get_cyber_physical_config_api =
            ncapConfig[m_config_node.c_str()]["get_cyber_physical_config_api"].string_value();

        //  Transducer APIs
        m_get_transducer_defs_api = ncapConfig[m_config_node.c_str()]["get_transducer_defs_api"].string_value();
        m_post_transducer_defs_api = ncapConfig[m_config_node.c_str()]["post_transducer_defs_api"].string_value();
        m_get_new_transducer_defs_api = ncapConfig[m_config_node.c_str()]["get_new_transducer_defs_api"].string_value();
        m_post_new_transducer_defs_key =
            ncapConfig[m_config_node.c_str()]["post_new_transducer_defs_key"].string_value();

        // Product Rule Engine APIs
        m_get_product_rules_api = ncapConfig[m_config_node.c_str()]["get_product_rules_api"].string_value();
        m_post_product_rules_api = ncapConfig[m_config_node.c_str()]["post_product_rules_api"].string_value();
        m_get_new_product_rules_api = ncapConfig[m_config_node.c_str()]["get_new_product_rules_api"].string_value();
        m_post_new_product_rules_key = ncapConfig[m_config_node.c_str()]["post_new_product_rules_key"].string_value();

        m_get_assets_api = ncapConfig[m_config_node.c_str()]["get_assets_api"].string_value();
        m_post_assets_api = ncapConfig[m_config_node.c_str()]["post_assets_api"].string_value();
        m_get_new_assets_api = ncapConfig[m_config_node.c_str()]["get_new_assets_api"].string_value();
        m_post_new_assets_key = ncapConfig[m_config_node.c_str()]["post_new_assets_key"].string_value();

        // Library APIs
        m_get_transducer_library_api = ncapConfig[m_config_node.c_str()]["get_transducer_library_api"].string_value();
        m_get_product_library_api = ncapConfig[m_config_node.c_str()]["get_product_library_api"].string_value();
        m_get_assets_library_api = ncapConfig[m_config_node.c_str()]["get_assets_library_api"].string_value();
        m_get_preset_library_api = ncapConfig[m_config_node.c_str()]["get_preset_library_api"].string_value();

        m_get_erp_library_api = ncapConfig[m_config_node.c_str()]["get_erp_library_api"].string_value();
        m_get_opc_library_api = ncapConfig[m_config_node.c_str()]["get_opc_library_api"].string_value();

        // ERP Node API
        m_get_erp_node_api = ncapConfig[m_config_node.c_str()]["get_erp_node_api"].string_value();
        m_get_new_erp_node_api = ncapConfig[m_config_node.c_str()]["get_new_erp_node_api"].string_value();
        m_post_erp_node_api = ncapConfig[m_config_node.c_str()]["post_erp_node_api"].string_value();
        m_post_new_erp_node_key = ncapConfig[m_config_node.c_str()]["post_new_erp_node_key"].string_value();

        // OPC Node API
        m_get_opc_node_api = ncapConfig[m_config_node.c_str()]["get_opc_node_api"].string_value();
        m_get_new_opc_node_api = ncapConfig[m_config_node.c_str()]["get_new_opc_node_api"].string_value();
        m_post_opc_node_api = ncapConfig[m_config_node.c_str()]["post_opc_node_api"].string_value();
        m_post_new_opc_node_key = ncapConfig[m_config_node.c_str()]["post_new_opc_node_key"].string_value();
    }
    return m_bIsValidNcapConfig;
}
bool CIdkNcapControllerClient::reInitConfig(const std::string& jstrNcapController)
{
    return initConfig(jstrNcapController);
}

CIdkNcapControllerClient::~CIdkNcapControllerClient()
{
}

bool CIdkNcapControllerClient::clientInit(CURL*& conn, const char* url, char* errorBuffer, std::string* dataBuffer)
{
    CURLcode code;
    conn = curl_easy_init();

    if (conn == NULL) {
        std::cout << "Failed to create CURL connection\n" << std::endl;
        exit(EXIT_FAILURE);
    }

    curl_easy_setopt(conn, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
    if (code != CURLE_OK) {
        std::cout << "Failed to set error buffer [" << code << "]\n" << std::endl;
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_URL, url);
    if (code != CURLE_OK) {
        std::cout << "Failed to set URL [" << errorBuffer << "]\n" << std::endl;
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
    if (code != CURLE_OK) {
        std::cout << "Failed to set redirect option [" << errorBuffer << "]\n" << std::endl;
        ;
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, CIdkNcapControllerClient::ncapControllerServiceCb);
    if (code != CURLE_OK) {
        std::cout << "Failed to set writer [" << errorBuffer << "]\n" << std::endl;
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, dataBuffer);
    if (code != CURLE_OK) {
        std::cout << "Failed to set write data [" << errorBuffer << "]\n" << std::endl;
        return false;
    }

    return true;
}

int CIdkNcapControllerClient::ncapControllerServiceCb(char* data, size_t size, size_t nmemb, std::string* dataBuffer)
{
    if (dataBuffer == NULL) {
        return 0;
    }

    dataBuffer->append(data, size * nmemb);

    return (size * nmemb);
}

// Base class functionality
std::string* CIdkNcapControllerClient::getConfig()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_config_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}
std::string* CIdkNcapControllerClient::getConfigChange()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_config_change_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}
std::string* CIdkNcapControllerClient::getTransducerDefs()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_transducer_defs_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getNewTransducerDefs()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_new_transducer_defs_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getProductRules()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_product_rules_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getNewProductRules()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_new_product_rules_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getAssets()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_assets_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getNewAssets()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_new_assets_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getCyberPhysicalConfig()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_cyber_physical_config_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

// Library APIs
std::string* CIdkNcapControllerClient::getTransducerLibrary()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_transducer_library_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getProductLibrary()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_product_library_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getAssetsLibrary()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_assets_library_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}
std::string* CIdkNcapControllerClient::getPresetLibrary()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_preset_library_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}
////////////////
std::string* CIdkNcapControllerClient::getErpNode()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_erp_node_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getNewErpNode()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_new_erp_node_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

//////////////////////////////////

std::string* CIdkNcapControllerClient::getOpcNode()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_opc_node_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

std::string* CIdkNcapControllerClient::getNewOpcNode()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_new_opc_node_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

//////////////////////////////////
std::string* CIdkNcapControllerClient::getErpLibrary()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_erp_library_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}

//////////////////////////////
std::string* CIdkNcapControllerClient::getOpcLibrary()
{
    CURL* conn = NULL;
    CURLcode code;

    // Initialize the receive buffer for each cycle.
    std::string* pDataBuffer = new std::string();
    char* pErrorBuffer = new char[sizeof(char) * CURL_ERROR_SIZE];

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Get Config API builder //
    std::string strUrl;
    strUrl.append(m_scheme);
    strUrl.append("://");
    strUrl.append(m_address);
    strUrl.append(":");
    char buffer[33] = {};
    snprintf(buffer, sizeof(buffer), "%d", m_port);
    strUrl.append(buffer);
    strUrl.append("/");
    strUrl.append(m_get_opc_library_api);

    // Initialize CURL connection
    if (!clientInit(conn, strUrl.c_str(), pErrorBuffer, pDataBuffer)) {
        std::cout << "Connection initializion failed\n" << std::endl;
        pDataBuffer->clear();

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        return pDataBuffer;
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);

    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        std::cout << "Failed to get" << strUrl << "Error:" << pErrorBuffer << std::endl;

        // Free the Error buffer.
        delete[] pErrorBuffer;

        // Caller must free the memory.
        pDataBuffer->clear();
        return pDataBuffer;
    }
    // Free the Error buffer.
    delete[] pErrorBuffer;

    // Caller must free the memory.
    return pDataBuffer;
}