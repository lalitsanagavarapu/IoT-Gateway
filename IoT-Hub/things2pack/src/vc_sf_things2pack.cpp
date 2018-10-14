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

#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cassert>
#include <list>
#include <set>
#include <unordered_map>
#include <unistd.h>

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/linux/include/json11.hpp"

#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Net/HTTPRequest.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Net/HTTPResponse.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Net/HTTPMessage.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Net/WebSocket.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Net/HTTPClientSession.h"

#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/raspberry-pi-2/include/json11.hpp"

#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Net/HTTPRequest.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Net/HTTPResponse.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Net/HTTPMessage.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Net/WebSocket.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Net/HTTPClientSession.h"

#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/android-21/armeabi-v7a/include/json11.hpp"

#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Net/HTTPRequest.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Net/HTTPResponse.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Net/HTTPMessage.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Net/WebSocket.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Net/HTTPClientSession.h"

#endif

#include "vc_sf_idk_utils.h"
#include "vc_sf_idk_logging.h"
#include "vc_sf_idk_21450_2010_types.h"
#include "vc_sf_idk_21450_2010_transducer_service_apis.h"
#include "vc_sf_idk_21451_2010_ncap_controller.h"
#include "vc_sf_idk_21450_2010_ncap_services.h"
#include "vc_sf_idk_21450_2010_tim_services.h"
#include "vc_sf_idk_21451_X_2010_tim_comm_module.h"
#include "vc_sf_idk_21451_X_2010_ncap_comm_module.h"
#include "vc_sf_idk_21450_2010_sf_main.h"

#include "vc_sf_liquid_milk_rule_engine.h"
#include "vc_sf_liquid_oil_rule_engine.h"
#include "vc_sf_things2pack.h"
#include "vc_sf_things2pack_recorder.h"

#include "db/redis/vc_sf_redis_client_factory.h"
#include "foundation/qlib/vc_sf_reliable_redis_q.h"


// Global Object.
CVCRedisClientFactory*  G_RELIABLE_REDIS_WSN_Q_FACTORY;

#if defined(IDK_PLATFORM_ARM_RPI) || defined(IDK_PLATFORM_LINUX)

#endif

#define SF_OBJECT_LIBRARY_PATH                  "../object-library"
#define SF_ERP_LIBRARY_OBJECTS                  "library_of_erp_objects.json"
#define SF_PHYSICAL_LIBRARY_OBJECTS             "library_of_physical_objects.json"
#define SF_OPC_LIBRARY_OBJECTS                  "library_of_opc_objects.json"
#define SF_PRODUCT_RULE_ENGINE_OBJECTS          "library_of_product_rule_engine_objects.json"
#define SF_TRANSDUCER_OBJECTS                   "library_of_transducer_objects.json"

#define SF_CONFIGURATION_PATH                   "../config"
#define SF_CONFIG_ERP_NODE                      "configured_erp_node.json"
#define SF_CONFIG_ERP_RULES                     "configured_erp_rules.json"
#define SF_CONFIG_FACTORY_PHYSICAL_ASSETS_TREE  "configured_factory_physical_assets_tree.json"
#define SF_CONFIG_OPC_NODE                      "configured_opc_node.json"
#define SF_CONFIG_OPC_RULES                     "configured_opc_rules.json"
#define SF_CONFIG_PRODUCT_RULES                 "configured_product_rules.json"
#define SF_CONFIG_TRANSDUCERS                   "configured_transducers.json"


CSFThings2Pack::CSFThings2Pack()
{
}
CSFThings2Pack::~CSFThings2Pack()
{
}

bool CSFThings2Pack::sfsetCyberPhysicalConfig(const std::string& jstrCyberPhysicalConfig)
{
    std::string jerr;
    jerr.clear();

    json11::Json jtap = json11::Json::parse(jstrCyberPhysicalConfig, jerr);

    m_jstrTransducerDefs = jtap["transducer_definitions"].dump();
    m_jstrProductRules = jtap["product_rules"].dump();
    m_jstrAssets = jtap["assets"].dump();
    m_jstrErpNode = jtap["erp_node"].dump();
    m_jstrOpcNode = jtap["opc_node"].dump();

    // Note>> We need convert to string and then to JSON..
    // Test if a simple assignment of JSON will do?
    // m_jTransducers = jtap["transducer_definitions"];

    jerr.clear();
    m_jTransducersDefs = json11::Json::parse(m_jstrTransducerDefs, jerr);

    jerr.clear();
    m_jProductRules = json11::Json::parse(m_jstrProductRules, jerr);

    jerr.clear();
    m_jAssets = json11::Json::parse(m_jstrAssets, jerr);

    jerr.clear();
    m_jErpNode = json11::Json::parse(m_jstrErpNode, jerr);

    jerr.clear();
    m_jOpcNode = json11::Json::parse(m_jstrOpcNode, jerr);

    return true;
}

int CSFThings2Pack::sfProductModelProcessingObjects(
    /*OUT*/ std::vector<std::shared_ptr<CIdkNcapProductModelProcessor> >& products)
{
    // In 0x0A of IDK, we support fixed number of products
    // In 0x0B of IDK, we develop some sort of configurator to configure products from APP (Android/Mobile).

    products.erase(products.begin(), products.end());

    for (UInt32 i = 0; i < m_jProductRules.array_items().size(); i++) {
        int product_id = m_jProductRules.array_items()[i]["Meta-Product-Rules-Key"]["product_id"].number_value();
        std::string product_name =
            m_jProductRules.array_items()[i]["Meta-Product-Rules-Key"]["product_name"].string_value();

        if ((product_id == 1) && (product_name.compare("milk") == 0)) {

            UInt32 opc = 0;
            json11::Json jOpc;
            for (opc = 0; opc < m_jSFOpcLibrary.array_items().size(); opc++) {
                int opc_product_id = m_jSFOpcLibrary[opc]["Meta-Opc-Rules"]["UUID"]["UID"].number_value();

                std::string opc_product_name = m_jSFOpcLibrary[opc]["Meta-Opc-Rules"]["UUID"]["UNAME"].string_value();

                if ((opc_product_id == product_id) && (opc_product_name.compare(product_name) == 0)) {
                    jOpc = m_jSFOpcLibrary[opc];
                    break;
                }
            }

            UInt32 erp = 0;
            json11::Json jErp;
            for (erp = 0; erp < m_jSFErpLibrary.array_items().size(); erp++) {
                int erp_product_id = m_jSFErpLibrary[opc]["Meta-Erp-Rules"]["UUID"]["UID"].number_value();

                std::string erp_product_name = m_jSFErpLibrary[erp]["Meta-Erp-Rules"]["UUID"]["UNAME"].string_value();

                if ((erp_product_id == product_id) && (erp_product_name.compare(product_name) == 0)) {
                    jErp = m_jSFErpLibrary[erp];
                    break;
                }
            }

            // Milk
            std::shared_ptr<CIdkNcapProductModelProcessor> milkModel(
                new CSFMilkProduct(m_jstrTransducerDefs,
                                   m_jProductRules.array_items()[i].dump(),
                                   m_jstrAssets,
                                   m_jSFTransducerLibrary.dump(),
                                   m_jSFProductLibrary.dump(),
                                   m_jSFFactoryAssetsLibrary.dump(),
                                   jErp.dump(),
                                   jOpc.dump()),
                CIdkNcapProductModelProcessorDeleter());

            products.push_back(milkModel);
        } else if ((product_id == 2) && (product_name.compare("oil") == 0)) {
            // Oil

            UInt32 opc = 0;
            json11::Json jOpc;
            for (opc = 0; opc < m_jSFOpcLibrary.array_items().size(); opc++) {
                int opc_product_id = m_jSFOpcLibrary[opc]["Meta-Opc-Rules"]["UUID"]["UID"].number_value();

                std::string opc_product_name = m_jSFOpcLibrary[opc]["Meta-Opc-Rules"]["UUID"]["UNAME"].string_value();

                if ((opc_product_id == product_id) && (opc_product_name.compare(product_name) == 0)) {
                    jOpc = m_jSFOpcLibrary[opc];
                    break;
                }
            }

            UInt32 erp = 0;
            json11::Json jErp;
            for (erp = 0; erp < m_jSFErpLibrary.array_items().size(); erp++) {
                int erp_product_id = m_jSFErpLibrary[erp]["Meta-Erp-Rules"]["UUID"]["UID"].number_value();

                std::string erp_product_name = m_jSFErpLibrary[erp]["Meta-Erp-Rules"]["UUID"]["UNAME"].string_value();

                if ((erp_product_id == product_id) && (erp_product_name.compare(product_name) == 0)) {
                    jErp = m_jSFErpLibrary[erp];
                    break;
                }
            }

            std::shared_ptr<CIdkNcapProductModelProcessor> oilModel(
                new CSFOilProduct(m_jstrTransducerDefs,
                                  m_jProductRules.array_items()[i].dump(),
                                  m_jstrAssets,
                                  m_jSFTransducerLibrary.dump(),
                                  m_jSFProductLibrary.dump(),
                                  m_jSFFactoryAssetsLibrary.dump(),
                                  jErp.dump(),
                                  jOpc.dump()),
                CIdkNcapProductModelProcessorDeleter());

            products.push_back(oilModel);

        } else {
            // NOP ..? Just Log.
        }
    }

    return VC_SF_ERROR_NO_ERROR;
}

// Caller MUST Free the Memory
std::string* CSFThings2Pack::getPlatformMetaTransducerLibrary()
{

    std::string* ptl = new std::string();
    ptl->clear();
    ptl->append(m_jSFTransducerLibrary.dump());

    return ptl;
}

// Caller MUST Free the Memory
std::string* CSFThings2Pack::getPlatformMetaProductLibrary()
{

    std::string* ppl = new std::string();
    ppl->clear();
    ppl->append(m_jSFProductLibrary.dump());

    return ppl;
}

std::string* CSFThings2Pack::getPlatformMetaAssetsLibrary()
{
    std::string* ppaf = new std::string();
    ppaf->clear();
    ppaf->append(m_jSFFactoryAssetsLibrary.dump());
    return ppaf;
}

// Caller MUST Free the Memory
std::string* CSFThings2Pack::getPresetSmartFactoryLibrary()
{

    json11::Json jPresetSmartFactory =
        json11::Json::array{ json11::Json::object // Preset #1
                             { { "transducer_definitions", m_jSFTransducerDefinitions_preset},
                               { "product_rules", m_jSFProductRules_preset },
                               { "assets", m_jSFAssets_preset },
                               { "erp_node", m_jSFErpNode_preset },
                               { "opc_node", m_jSFOpcNode_preset } },
                            };
    std::string* ppsf = new std::string();
    ppsf->clear();
    ppsf->append(jPresetSmartFactory.dump());

    return ppsf;
}

std::string* CSFThings2Pack::getPlatformMetaErpLibrary()
{
    std::string* ppel = new std::string();
    ppel->clear();
    ppel->append(m_jSFErpLibrary.dump());
    return ppel;
}
std::string* CSFThings2Pack::getPlatformMetaOpcLibrary()
{
    std::string* ppol = new std::string();
    ppol->clear();
    ppol->append(m_jSFOpcLibrary.dump());
    return ppol;
}

int CSFThings2Pack::sfMain()
{
    
    {
      std::string fname = SF_OBJECT_LIBRARY_PATH
                          "/"
                          SF_PHYSICAL_LIBRARY_OBJECTS;
      std::ifstream file (fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::stringstream ss;
      ss << file.rdbuf();
      std::string err;
      err.clear();
      m_jSFFactoryAssetsLibrary = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          std::cout << err << std::endl;
          exit (0);
      }
    }
    {
      std::string fname = SF_OBJECT_LIBRARY_PATH
                          "/" 
                          SF_ERP_LIBRARY_OBJECTS;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFErpLibrary = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_OBJECT_LIBRARY_PATH
                          "/" 
                          SF_OPC_LIBRARY_OBJECTS;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFOpcLibrary = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_OBJECT_LIBRARY_PATH
                          "/"
                          SF_PRODUCT_RULE_ENGINE_OBJECTS;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFProductLibrary = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_OBJECT_LIBRARY_PATH
                          "/"
                          SF_TRANSDUCER_OBJECTS;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFTransducerLibrary = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    
    // Load Configured Objects.
    {
      std::string fname = SF_CONFIGURATION_PATH
                          "/"
                          SF_CONFIG_ERP_NODE;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFErpNode_preset = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_CONFIGURATION_PATH
                          "/"
                          SF_CONFIG_ERP_RULES;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFErpRules_preset = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_CONFIGURATION_PATH
                          "/"
                          SF_CONFIG_FACTORY_PHYSICAL_ASSETS_TREE;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFAssets_preset = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_CONFIGURATION_PATH
                          "/"
                          SF_CONFIG_OPC_NODE;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFOpcNode_preset = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_CONFIGURATION_PATH
                          "/"
                          SF_CONFIG_OPC_RULES;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFOpcRules_preset = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_CONFIGURATION_PATH
                          "/"
                          SF_CONFIG_PRODUCT_RULES;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFProductRules_preset = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    {
      std::string fname = SF_CONFIGURATION_PATH
                          "/"
                          SF_CONFIG_TRANSDUCERS;
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      m_jSFTransducerDefinitions_preset = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
    }
    
    // Testing of Libwebsockets

    // Let's initialize the 21450-21451 smart factory stack.
    // Let's have a NcapControllerClient object for each thread.
    // Global Object

    json11::Json jNcapBroadcaster = json11::Json::object{
        // NCAP Broadcaster [PUBLISHER]
        { "ncap_controller_broadcaster_port", 7778 },
        { "ncap_controller_broadcaster_address", "127.0.0.1" },
        { "ncap_controller_broadcaster_scheme", "tcp" },

        // NCAP Broadcast Messages
        { "ncap_transducer_defs_update_broadcast_message", "NCAP_CONTROLLER_TRANSDUCER_DEFS_BROADCAST_EVENT" },
        { "ncap_product_rules_update_broadcast_message", "NCAP_CONTROLLER_PRODUCT_RULES_BROADCAST_EVENT" },
        { "ncap_assets_update_broadcast_message", "NCAP_CONTROLLER_ASSETS_BROADCAST_EVENT" },
        { "ncap_cyber_physical_update_broadcast_message", "NCAP_CONTROLLER_CYBER_PHYSICAL_BROADCAST_EVENT" }
    };

    json11::Json jNcapController =
        json11::Json::object{
            { "ncap_config_node",
              json11::Json::object{
                  { "site_id", 0 }, { "address", "127.0.0.1" }, { "port", 7777 }, { "scheme", "http" },
                  { "get_config_change_api", "get-config-change" }, { "get_config_api", "get-config" },
                  { "post_config_api", "set-config" },

                  // Cyber Physical Configuration
                  { "get_cyber_physical_config_api", "get-cyber-physical-config" },
                  { "get_new_cyber_physical_config_api", "get-new-cyber-physical-config" },
                  { "post_cyber_physical_config_api", "post-cyber-physical-config" },
                  { "post_new_cyber_physical_config_key", "cyber-physical-config" },

                  // Transducer Definitions
                  { "get_transducer_defs_api", "get-transducer-defs" },
                  { "get_new_transducer_defs_api", "get-new-transducer-defs" },
                  { "post_transducer_defs_api", "post-transducer-defs" },
                  { "post_new_transducer_defs_key", "transducer-defs" },

                  // Product Rule Engine APIs
                  { "get_product_rules_api", "get-product-rules" },
                  { "get_new_product_rules_api", "get-new-product-rules" },
                  { "post_product_rules_api", "post-product-rules" }, { "post_new_product_rules_key", "product-rules" },

                  // Asset Management APIs
                  { "get_assets_api", "get-assets" }, { "get_new_assets_api", "get-new-assets" },
                  { "post_assets_api", "post-assets" }, { "post_new_assets_key", "assets" },

                  // ERP Node API
                  { "get_erp_node_api", "get-erp-node" }, { "get_new_erp_node_api", "get-new-erp-node" },
                  { "post_erp_node_api", "post-erp-node" }, { "post_new_erp_node_key", "erp-node" },

                  // OPC Node API
                  { "get_opc_node_api", "get-opc-node" }, { "get_new_opc_node_api", "get-new-opc-node" },
                  { "post_opc_node_api", "post-opc-node" }, { "post_new_opc_node_key", "opc-node" },

                  // Library Management APIs
                  { "get_transducer_library_api", "get-transducer-library" },
                  { "get_product_library_api", "get-product-library" },
                  { "get_assets_library_api", "get-assets-library" },
                  { "get_preset_library_api", "get-preset-library" }, { "get_erp_library_api", "get-erp-library" },
                  { "get_opc_library_api", "get-opc-library" },

                  // NCAP Broadcaster [PUBLISHER]
                  { "ncap_controller_broadcaster_port", 7778 }, { "ncap_controller_broadcaster_address", "127.0.0.1" },
                  { "ncap_controller_broadcaster_scheme", "tcp" },

                  // NCAP Broadcast Messages
                  { "ncap_transducer_defs_update_broadcast_message",
                    "NCAP_CONTROLLER_TRANSDUCER_DEFS_BROADCAST_EVENT" },
                  { "ncap_product_rules_update_broadcast_message", "NCAP_CONTROLLER_PRODUCT_RULES_BROADCAST_EVENT" },
                  { "ncap_assets_update_broadcast_message", "NCAP_CONTROLLER_ASSETS_BROADCAST_EVENT" },
                  { "ncap_cyber_physical_update_broadcast_message", "NCAP_CONTROLLER_CYBER_PHYSICAL_BROADCAST_EVENT" },
                  { "ncap_erp_node_update_broadcast_message", "NCAP_CONTROLLER_ERP_NODE_BROADCAST_EVENT" },
                  { "ncap_opc_node_update_broadcast_message", "NCAP_CONTROLLER_OPC_NODE_BROADCAST_EVENT" }
              } }
        };
    // Global Object
    json11::Json jTimWs =
        json11::Json::object{
            { "tim_webserver_node",
              json11::Json::object{
                  { "site_id", 0 }, { "address", "0.0.0.0" }, { "port", 8888 }, { "scheme", "http" },

                  // APIs exposed by the TimWebServer.
                  { "get_and_reload_transducer_defs_api", "get-reload-transducer-defs" },
                  { "get_and_reload_product_rules_api", "get-reload-product-rules" },
                  { "get_and_reload_assets_api", "get-reload-assets" },
                  { "get_and_reload_erp_node_api", "get-reload-erp-node" },
                  { "get_and_reload_opc_node_api", "get-reload-opc-node" },
                  { "get_and_reload_cyber_physical_config_api", "get-reload-cyber-physical-config-api" },
                  { "get_iot_api", "iot" }, { "get_erp_api", "erp" }, { "get_opc_api", "opc" },
                  { "get_default_api", "" },

                  // NCAP Broadcaster [PUBLISHER]
                  // tim_webserver_node is a SUBSCRIBER.
                  // NCAP Broadcaster [PUBLISHER]
                  { "ncap_controller_broadcaster_port", 7778 }, { "ncap_controller_broadcaster_address", "127.0.0.1" },
                  { "ncap_controller_broadcaster_scheme", "tcp" },

                  // NCAP Broadcast Messages
                  { "ncap_transducer_defs_update_broadcast_message",
                    "NCAP_CONTROLLER_TRANSDUCER_DEFS_BROADCAST_EVENT" },
                  { "ncap_product_rules_update_broadcast_message", "NCAP_CONTROLLER_PRODUCT_RULES_BROADCAST_EVENT" },
                  { "ncap_assets_update_broadcast_message", "NCAP_CONTROLLER_ASSETS_BROADCAST_EVENT" },
                  { "ncap_cyber_physical_update_broadcast_message", "NCAP_CONTROLLER_CYBER_PHYSICAL_BROADCAST_EVENT" },
                  { "ncap_erp_node_update_broadcast_message", "NCAP_CONTROLLER_ERP_NODE_BROADCAST_EVENT" },
                  { "ncap_opc_node_update_broadcast_message", "NCAP_CONTROLLER_OPC_NODE_BROADCAST_EVENT" }
              } }
        };

    // Here, we fill some more recorder configurations as well.
    
    // Further, in certain deployment scenarios, saving a file (HDF5) locally may not
    // be a right option. So, network recorders are used instead.
    // Push the recording to some external server.
    int hdf5HistorianStatus = 0;  // 0 - disabled, 1 enabled.
    json11::Json sfDigitalTwinConfig;
    {
      std::string fname = "../config/digital_twin_config.json";
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      sfDigitalTwinConfig = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
      
      hdf5HistorianStatus = sfDigitalTwinConfig["hdf5_historian"].number_value();
      
      // Let's create the Redis DB client for WSN functionality.
      G_RELIABLE_REDIS_WSN_Q_FACTORY = new CVCRedisClientFactory(sfDigitalTwinConfig["wsn"]["remote-node"]["remote_wsn_server"].string_value()
                                                                    , sfDigitalTwinConfig["wsn"]["remote-node"]["remote_wsn_port"].number_value()
                                                                    , sfDigitalTwinConfig["wsn"]["remote-node"]["remote_wsn_user"].string_value()
                                                                    , sfDigitalTwinConfig["wsn"]["remote-node"]["remote_wsn_password"].string_value()
                                                                    , ""
                                                                    , sfDigitalTwinConfig["wsn"]["remote-node"]["remote_wsn_db"].number_value()
                                                                );
       
    }

    // Global Object
    json11::Json jModelProcessorCommunicator = json11::Json::object{
        { "ncap_model_processor_communicator",
          json11::Json::object{
              { "site_id", 0 },
              { "ncap_model_processor_communicator_address", "127.0.0.1" },
              { "ncap_model_processor_communicator_port", 6664 },
              { "ncap_model_processor_communicator_scheme", "tcp" },

              // NCAP Broadcast Messages
              { "ncap_transducer_defs_update_broadcast_message", "NCAP_CONTROLLER_TRANSDUCER_DEFS_BROADCAST_EVENT" },
              { "ncap_product_rules_update_broadcast_message", "NCAP_CONTROLLER_PRODUCT_RULES_BROADCAST_EVENT" },
              { "ncap_assets_update_broadcast_message", "NCAP_CONTROLLER_ASSETD_BROADCAST_EVENT" }
          } },

        // Please note that the RECORDER subscribes to this publisher.
        { "ncap_model_processor_publisher",
          json11::Json::object{ { "site_id", 0 },
                                { "ncap_model_processor_publisher_address", "0.0.0.0" },
                                { "ncap_model_processor_publisher_port", 5555 },
                                { "ncap_model_processor_publisher_scheme", "tcp" } } },
        
        // Recorder config read from the digital_twin configuration.
        { "digital_twin_config",
          json11::Json::object{ 
                                { "influx-server-url", sfDigitalTwinConfig["influx-server-url"] },
                                { "hdf5_historian", hdf5HistorianStatus },
                                { "wsn", sfDigitalTwinConfig["wsn"]} 
                              } 
        }
    };

    std::string jstrNcapControllerNode = jNcapController.dump();
    std::string jstrtransducerDefinitions = m_jSFTransducerDefinitions_preset.dump();
    std::string jstrProductRules = m_jSFProductRules_preset.dump();
    std::string jstrAssets = m_jSFAssets_preset.dump();
    std::string jstrErpNode = m_jSFErpNode_preset.dump();
    std::string jstrOpcNode = m_jSFOpcNode_preset.dump();

    // Let's windup the stack and free some memory
    {
        // Populate the Smart Factory initial data structures.
        json11::Json jPresetSmartFactory_1 // Preset #1
            { { { "transducer_definitions", m_jSFTransducerDefinitions_preset },
                { "product_rules", m_jSFProductRules_preset },
                { "assets", m_jSFAssets_preset },
                { "erp_node", m_jSFErpNode_preset },
                { "opc_node", m_jSFOpcNode_preset } } };

        this->sfsetCyberPhysicalConfig(jPresetSmartFactory_1.dump());
    }

    Poco::NotificationQueue* queue = new Poco::NotificationQueue();

    CIdkNcapControllerClient ncapCtrlClient(jstrNcapControllerNode);

    std::string jstrTimWs = jTimWs.dump();

    CIdkTimWebServer ws(jstrTimWs, jstrNcapControllerNode);

    CIdkNcapController nc(queue,
                          jstrNcapControllerNode,
                          jstrtransducerDefinitions,
                          jstrProductRules,
                          jstrAssets,
                          jstrErpNode,
                          jstrOpcNode);

    // These clients access TIM communication module (Tim Webserver)
    // to read sensor (IoT), ERP, OPC data.
    // We can think of adding a set of APIs (std::vector<std::string>& supplimentryAPIs)
    std::string jstrModelProcessorCommunicator = jModelProcessorCommunicator.dump();

    // Let's initialize the 21450-21451 smart factory stack.
    // Let's have a NcapControllerClient object for each thread.
    CIdkNcapModelProcessor mp(queue,
                              jstrNcapControllerNode,
                              jstrModelProcessorCommunicator,
                              jstrProductRules,
                              jstrAssets,
                              jstrErpNode,
                              jstrOpcNode);

    CIdkNcapIoTClient ic(jstrTimWs, "iot", jstrModelProcessorCommunicator); // iot is the primary API to query.
    CIdkNcapOPCClient oc(jstrTimWs, "opc", jstrModelProcessorCommunicator);
    CIdkNcapERPClient ec(jstrTimWs, "erp", jstrModelProcessorCommunicator);

    // Modbus Server
    CIdkTimServicesModbusServer ms;

    Poco::ThreadPool::defaultPool().start(nc);
    Poco::ThreadPool::defaultPool().start(mp);
    Poco::ThreadPool::defaultPool().start(ms);
    Poco::ThreadPool::defaultPool().start(ws);

    Poco::ThreadPool::defaultPool().start(ic);
// Poco::ThreadPool::defaultPool().start(oc);
// Poco::ThreadPool::defaultPool().start(ec);

#if defined(IDK_PLATFORM_ARM_RPI) || defined(IDK_PLATFORM_LINUX)
    //
    // RECORDER Thread. This is NOT available on Android Platforms.
    //
    
    CSFThings2PackRecorder recorder(jstrModelProcessorCommunicator, jstrNcapControllerNode);

    Poco::ThreadPool::defaultPool().start(recorder);

#endif

    Poco::ThreadPool::defaultPool().joinAll();

    return VC_SF_ERROR_NO_ERROR;
}

#if defined(IDK_PLATFORM_ARM_RPI) || defined(IDK_PLATFORM_LINUX)
int main(int argc, char* argv[])
{

/*
// We will be using Websockets soon in the IoT App. This is a Test program.

Poco::Net::HTTPClientSession cs("localhost:7681");
Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, "/",Poco::Net::HTTPMessage::HTTP_1_1);
request.set("origin", "ws://localhost:7681");
Poco::Net::HTTPResponse response;

try
{
    Poco::Net::WebSocket* m_psock = new Poco::Net::WebSocket(cs, request, response);

    std::ostringstream strs;
    while(true)
    {
        char rcv[1024];
        int flags=0;
        m_psock->receiveFrame(rcv, 1024, flags);

        std::cout << rcv << std::endl;
    }
    m_psock->close();
}
catch (std::exception &e)
{
    std::cout << "Exception " << e.what();
}
*/

#if defined(IDK_PLATFORM_FAMILY_THINGS2PACK)

    CSFThings2Pack* sf = new CSFThings2Pack();
    
    // STORE THE SMART FACTORY GLOBAL OBJECT
    G_SFMAIN = sf;
    return sf->sfMain();
#endif
    return 0;
}
#endif
