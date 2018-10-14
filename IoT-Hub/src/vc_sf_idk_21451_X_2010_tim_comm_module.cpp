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
#include "vc_sf_idk_21451_X_2010_tim_comm_module.h"

CIdkTimWebServer::CIdkTimWebServer(const std::string& jstrTimWebServer, const std::string& jstrNcapControllerClient)
    : m_ncapControllerClient(jstrNcapControllerClient)
{
    // Application can specify the port for TIM Webserver

    m_jstrNcapControllerClient = jstrNcapControllerClient;

    initConfig(jstrTimWebServer);

    m_daemon = NULL;
}

bool CIdkTimWebServer::initConfig(const std::string& jstrTimWebServer)
{
    m_tim_ws_node = "tim_webserver_node";
    m_bIsValidConfig = false;

    std::string err;
    json11::Json jtimWsNode = json11::Json::parse(jstrTimWebServer, err);
    if (!err.empty()) {
        m_bIsValidConfig = false;
    } else {
        m_jstrTimWebServer = jstrTimWebServer;
        m_bIsValidConfig = true;

        m_site_id = jtimWsNode[m_tim_ws_node.c_str()]["site_id"].number_value();
        m_port = jtimWsNode[m_tim_ws_node.c_str()]["port"].number_value();
        m_address = jtimWsNode[m_tim_ws_node.c_str()]["address"].string_value();
        m_scheme = jtimWsNode[m_tim_ws_node.c_str()]["scheme"].string_value();

        m_get_and_reload_transducer_defs_api =
            jtimWsNode[m_tim_ws_node.c_str()]["get_and_reload_transducer_defs_api"].string_value();
        m_get_and_reload_product_rules_api =
            jtimWsNode[m_tim_ws_node.c_str()]["get_and_reload_product_rules_api"].string_value();
        m_get_and_reload_assets_api = jtimWsNode[m_tim_ws_node.c_str()]["get_and_reload_assets_api"].string_value();
        m_get_and_reload_cyber_physical_config_api =
            jtimWsNode[m_tim_ws_node.c_str()]["get_and_reload_transducer_defs_api"].string_value();

        m_get_and_reload_erp_node_api = jtimWsNode[m_tim_ws_node.c_str()]["get_and_reload_erp_node_api"].string_value();
        m_get_and_reload_opc_node_api = jtimWsNode[m_tim_ws_node.c_str()]["get_and_reload_opc_node_api"].string_value();

        m_get_iot_api = jtimWsNode[m_tim_ws_node.c_str()]["get_iot_api"].string_value();
        m_get_erp_api = jtimWsNode[m_tim_ws_node.c_str()]["get_erp_api"].string_value();
        m_get_opc_api = jtimWsNode[m_tim_ws_node.c_str()]["get_opc_api"].string_value();
        m_get_default_api = jtimWsNode[m_tim_ws_node.c_str()]["get_default_api"].string_value();

        // NCAP Broadcaster
        m_ncap_controller_broadcaster_port =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_controller_broadcaster_port"].number_value();
        m_ncap_controller_broadcaster_address =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_controller_broadcaster_address"].string_value();
        m_ncap_controller_broadcaster_scheme =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_controller_broadcaster_scheme"].string_value();

        // NCAP Broadcast Messages
        m_transducer_defs_update_broadcast_message =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_transducer_defs_update_broadcast_message"].string_value();
        m_product_rules_update_broadcast_message =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_product_rules_update_broadcast_message"].string_value();
        m_assets_update_broadcast_message =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_assets_update_broadcast_message"].string_value();
        m_cyber_physical_update_broadcast_message =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_cyber_physical_update_broadcast_message"].string_value();

        m_erp_node_update_broadcast_message =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_erp_node_update_broadcast_message"].string_value();
        m_opc_node_update_broadcast_message =
            jtimWsNode[m_tim_ws_node.c_str()]["ncap_opc_node_update_broadcast_message"].string_value();
    }
    return m_bIsValidConfig;
}

bool CIdkTimWebServer::checkAndLoadNcapConfigIntoTimController()
{
    // Let's check and ensure the NCAP Controller is ready to server the
    // transducer definiitons (those configured).
    std::string* pCyberPhysicalConfigData = NULL;
    int retries = 3;
    do {
        pCyberPhysicalConfigData = m_ncapControllerClient.getCyberPhysicalConfig();
        if (pCyberPhysicalConfigData->empty()) {
            delete pCyberPhysicalConfigData;
            pCyberPhysicalConfigData = NULL;

            Poco::Thread::sleep(100); // A small nap.
            retries--;
            continue;
        } else {
            // Create the Transducer Objects that this TimWebserver
            // can communicate with.

            // VERIFY THE NEW TRANSDUCER DEFS, PRODUCT RULES AND ASSETS
            std::string err;
            json11::Json jncapConfig = json11::Json::parse(*pCyberPhysicalConfigData, err);

            timController.createTransducerObjects(jncapConfig["transducer_definitions"].dump(),
                                                  jncapConfig["product_rules"].dump(),
                                                  jncapConfig["assets"].dump());

            m_opcClient.createOpcClient(jncapConfig["erp_node"].dump(), m_jstrNcapControllerClient);
            m_erpClient.createErpClient(jncapConfig["opc_node"].dump(), m_jstrNcapControllerClient);

            // Free the pTransducers as we do not need it any more.
            delete pCyberPhysicalConfigData;
            pCyberPhysicalConfigData = NULL;
            return true;
        }
    } while (retries > 0);

    return false;
}

int CIdkTimWebServer::start()
{
    // Let's check and ensure the NCAP Controller is ready to server the
    // transducer definiitons (those configured).
    std::string* pCyberPhysicalConfigData = NULL;

    // A small nap. There is no real need! But, I prefer to take a nap:-)
    Poco::Thread::sleep(1000);

    do {
        pCyberPhysicalConfigData = m_ncapControllerClient.getCyberPhysicalConfig();

        if (pCyberPhysicalConfigData->empty()) {
            delete pCyberPhysicalConfigData;
            pCyberPhysicalConfigData = NULL;

            Poco::Thread::sleep(100); // A small nap.
            continue;
        } else {
            // Create the Transducer Objects that this TimWebserver
            // can communicate with.

            // VERIFY THE NEW TRANSDUCER DEFS, PRODUCT RULES AND ASSETS
            std::string err;
            json11::Json jncapConfig = json11::Json::parse(*pCyberPhysicalConfigData, err);

            timController.createTransducerObjects(jncapConfig["transducer_definitions"].dump(),
                                                  jncapConfig["product_rules"].dump(),
                                                  jncapConfig["assets"].dump());

            m_opcClient.createOpcClient(jncapConfig["erp_node"].dump(), m_jstrNcapControllerClient);
            m_erpClient.createErpClient(jncapConfig["opc_node"].dump(), m_jstrNcapControllerClient);

            // Free the pTransducers as we do not need it any more.
            delete pCyberPhysicalConfigData;
            pCyberPhysicalConfigData = NULL;

            // All set to action.
            break;
        }
    } while (1);

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
                                &answer_to_connection,
                                this,
                                MHD_OPTION_SOCK_ADDR,
                                &daemon_ip_addr,
                                MHD_OPTION_CONNECTION_TIMEOUT,
                                (unsigned int)120,
                                MHD_OPTION_THREAD_POOL_SIZE,
                                (unsigned int)4,
                                MHD_OPTION_END);
    if (NULL == m_daemon) {
        // Log Error
        std::cout << "Error while starting CIdkTimWebServer::start" << std::endl;
        return VC_SF_ERROR_UNKNOWN_ERROR;
    }

    // Listen to config change events.
    //  Prepare our context and socket
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);

    std::string smq;
    smq.clear();
    smq.append(m_ncap_controller_broadcaster_scheme);
    smq.append("://");
    smq.append(m_ncap_controller_broadcaster_address);
    smq.append(":");
    char buff[33] = {};
    snprintf(buff, sizeof(buff), "%d", m_ncap_controller_broadcaster_port);
    smq.append(buff);

    subscriber.connect(smq.c_str());
    subscriber.setsockopt(ZMQ_SUBSCRIBE, L"", 0);

    while (1) {
        zmq::message_t ncapEvent;

        //  Wait for next request from client
        subscriber.recv(&ncapEvent);

        // NCAP Broadcast Messages
        std::string rcvdEvent((char*)ncapEvent.data());

        // Currently we reload all Cyber Physical Config
        // Transducers, Product Rules, Assets, ERP Node, OPC Node
        // We will consider modularizing the update in future releases.
        if ((rcvdEvent.compare(m_transducer_defs_update_broadcast_message) == 0) ||
            (rcvdEvent.compare(m_product_rules_update_broadcast_message) == 0) ||
            (rcvdEvent.compare(m_assets_update_broadcast_message) == 0) ||
            (rcvdEvent.compare(m_cyber_physical_update_broadcast_message) == 0) ||
            (rcvdEvent.compare(m_erp_node_update_broadcast_message) == 0) ||
            (rcvdEvent.compare(m_opc_node_update_broadcast_message) == 0)) {

            CIdkTimWebServerClient timWsClient(m_jstrTimWebServer);

            // This is a Network call. It reloads new cyber physical config.
            // This is a trick we played to update the cyber physical config.

            std::string* reply = timWsClient.getAndReloadCyberPhysicalConfig();
            delete reply;
        } else {
        }

        Poco::Thread::sleep(0);
    }

    // Hopefully, all set.
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkTimWebServer::answer_to_connection(void* cls,
                                           struct MHD_Connection* connection,
                                           const char* url,
                                           const char* method,
                                           const char* version,
                                           const char* upload_data,
                                           size_t* upload_data_size,
                                           void** con_cls)
{
    const char* ErrorPage =
        "<html><body><h1>Hello, It seems there is an Error in the HTTP Request!!!</h1></body></html>";
    struct MHD_Response* response;
    static int aptr;
    int ret;

    CIdkTimWebServer* server = (CIdkTimWebServer*)cls;

    if (0 != strcmp(method, "GET")) {
        return MHD_NO; /* unexpected method */
    }

    if (&aptr != *con_cls) {
        /* do never respond on first call */
        *con_cls = &aptr;
        return MHD_YES;
    }
    *con_cls = NULL; /* reset when done */

    // Let's build API support to the TIM webserver.
    // Implement APIs as specified in IEEE 21450, 21451.1
    UriParserStateA uriTimSfstate;
    UriUriA uriSfApi;

    uriTimSfstate.uri = &uriSfApi;

    // API
    if (uriParseUriA(&uriTimSfstate, url) != URI_SUCCESS) {
        /* Failure */

        response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_PERSISTENT);

        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
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

    // Currently, we reload all configuration components.
    // Consider loading individual components if required.
    if ((api.compare(server->m_get_and_reload_transducer_defs_api) == 0) ||
        (api.compare(server->m_get_and_reload_product_rules_api) == 0) ||
        (api.compare(server->m_get_and_reload_assets_api) == 0) ||
        (api.compare(server->m_get_and_reload_erp_node_api) == 0) ||
        (api.compare(server->m_get_and_reload_opc_node_api) == 0) ||
        (api.compare(server->m_get_and_reload_cyber_physical_config_api) == 0)) {
        // Read all the sensors individually, in a group, or all sensors.
        // Transducers, Product Rules and Assets are reloaded.
        if (server->checkAndLoadNcapConfigIntoTimController()) {
            // Get the timestamp.
            double milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();

            json11::Json reload = json11::Json::object{
                { "config-reload",
                  json11::Json::object{ { "status", json11::Json(0) }, // Success = 0, Error is negative number.
                                        { "response",
                                          "New Configuration (Transducers, Product Rules and Assets) is loaded!!" },
                                        { "time_instance", json11::Json(milliseconds_since_epoch) },
                                        { "time_units", "milliseconds" } } }
            };

            std::string reply = reload.dump();
            response = MHD_create_response_from_buffer(reply.length(), (void*)reply.c_str(), MHD_RESPMEM_MUST_COPY);
        } else {
            // Get the timestamp.
            double milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();

            json11::Json reload = json11::Json::object{
                { "config-reload",
                  json11::Json::object{ { "status", json11::Json(-1) }, // Success = 0, Error is negative number.
                                        { "response", "FAILED to load new NCAP Configuration." },
                                        { "time_instance", json11::Json(milliseconds_since_epoch) },
                                        { "time_units", "milliseconds" } } }
            };

            std::string reply = reload.dump();
            response = MHD_create_response_from_buffer(reply.length(), (void*)reply.c_str(), MHD_RESPMEM_MUST_COPY);
        }
    } else if (api.compare(server->m_get_iot_api) == 0) {
        CIdkTimController& tc = server->getTimController();

        std::string* piotSensorsReading = tc.readAllSensors();

        response = MHD_create_response_from_buffer(
            piotSensorsReading->length(), (void*)piotSensorsReading->c_str(), MHD_RESPMEM_MUST_COPY);
        delete piotSensorsReading;
    } else if (api.compare(server->m_get_opc_api) == 0) {

        CIdkOpcClient& oc = server->getOpcClient();

        std::string* popcData = oc.readOpc();

        response = MHD_create_response_from_buffer(popcData->length(), (void*)popcData->c_str(), MHD_RESPMEM_MUST_COPY);
        delete popcData;
    } else if (api.compare(server->m_get_erp_api) == 0) {
        CIdkErpClient& ec = server->getErpClient();

        std::string* perpData = ec.readErp();

        response = MHD_create_response_from_buffer(perpData->length(), (void*)perpData->c_str(), MHD_RESPMEM_MUST_COPY);
        delete perpData;
    } else {
        response = MHD_create_response_from_buffer(strlen(ErrorPage), (void*)ErrorPage, MHD_RESPMEM_MUST_COPY);
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    // Free the URI Parser resources
    uriFreeUriMembersA(&uriSfApi);

    return ret;
}

void CIdkTimWebServer::run()
{
    start();
}

CIdkTimController& CIdkTimWebServer::getTimController()
{
    return timController;
}

CIdkNcapControllerClient& CIdkTimWebServer::getNcapControllerClient()
{
    return m_ncapControllerClient;
}

CIdkOpcClient& CIdkTimWebServer::getOpcClient()
{
    return m_opcClient;
}

CIdkErpClient& CIdkTimWebServer::getErpClient()
{
    return m_erpClient;
}

CIdkTimWebServer::~CIdkTimWebServer()
{
}

//+++++++++++++++NEW CLASS DEFINITION++++++++++++++++

CIdkTimWebServerClient::CIdkTimWebServerClient()
{
}

bool CIdkTimWebServerClient::initConfig(const std::string& jstrTimWebServer)
{
    m_tim_ws_node = "tim_webserver_node";
    m_bIsValidConfig = false;

    std::string err;
    json11::Json jtimWsNode = json11::Json::parse(jstrTimWebServer, err);
    if (!err.empty()) {
        m_bIsValidConfig = false;
    } else {
        m_jstrTimWebServer = jstrTimWebServer;
        m_bIsValidConfig = true;

        m_site_id = jtimWsNode[m_tim_ws_node.c_str()]["site_id"].number_value();
        m_port = jtimWsNode[m_tim_ws_node.c_str()]["port"].number_value();
        m_address = jtimWsNode[m_tim_ws_node.c_str()]["address"].string_value();
        m_scheme = jtimWsNode[m_tim_ws_node.c_str()]["scheme"].string_value();
        m_get_and_reload_cyber_physical_config_api =
            jtimWsNode[m_tim_ws_node.c_str()]["get_and_reload_transducer_defs_api"].string_value();
    }
    return m_bIsValidConfig;
}

CIdkTimWebServerClient::CIdkTimWebServerClient(const std::string& jstrTimWebServer)
{
    initConfig(jstrTimWebServer);
}

bool CIdkTimWebServerClient::clientInit(CURL*& conn, const char* url, char* errorBuffer, std::string* dataBuffer)
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

    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, CIdkTimWebServerClient::timWebServiceCb);
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

CIdkTimWebServerClient::~CIdkTimWebServerClient()
{
}

int CIdkTimWebServerClient::timWebServiceCb(char* data, size_t size, size_t nmemb, std::string* dataBuffer)
{
    if (dataBuffer == NULL) {
        return 0;
    }

    dataBuffer->append(data, size * nmemb);

    return (size * nmemb);
}

std::string* CIdkTimWebServerClient::getAndReloadCyberPhysicalConfig()
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
    strUrl.append(m_get_and_reload_cyber_physical_config_api);

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