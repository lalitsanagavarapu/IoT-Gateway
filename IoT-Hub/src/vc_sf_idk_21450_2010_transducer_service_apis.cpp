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
#include "vc_sf_idk_21450_2010_transducer_service_apis.h"

//+++++++++++++++NEW CLASS DEFINITION++++++++++++++++

CIdkTimClient::CIdkTimClient()
{
}

bool CIdkTimClient::initConfig(const std::string& jstrTimWebServer)
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
        m_get_iot_api = jtimWsNode[m_tim_ws_node.c_str()]["get_iot_api"].string_value();
        m_get_erp_api = jtimWsNode[m_tim_ws_node.c_str()]["get_erp_api"].string_value();
        m_get_opc_api = jtimWsNode[m_tim_ws_node.c_str()]["get_opc_api"].string_value();
        m_get_default_api = jtimWsNode[m_tim_ws_node.c_str()]["get_default_api"].string_value();
    }
    return m_bIsValidConfig;
}

CIdkTimClient::CIdkTimClient(const std::string& jstrTimWebServer)
{
    initConfig(jstrTimWebServer);
}

bool CIdkTimClient::clientInit(CURL*& conn, const char* url, char* errorBuffer, std::string* dataBuffer)
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
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, CIdkTimClient::timWebServiceCb);
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

CIdkTimClient::~CIdkTimClient()
{
}

int CIdkTimClient::timWebServiceCb(char* data, size_t size, size_t nmemb, std::string* dataBuffer)
{
    if (dataBuffer == NULL) {
        return 0;
    }

    dataBuffer->append(data, size * nmemb);

    return (size * nmemb);
}

bool CIdkTimClient::verifyAPI(const std::string& api)
{
    bool res = false;
    if (m_bIsValidConfig) {
        if ((m_get_and_reload_transducer_defs_api.compare(api) != 0) && (m_get_iot_api.compare(api) != 0) &&
            (m_get_erp_api.compare(api) != 0) && (m_get_opc_api.compare(api) != 0) &&
            (m_get_default_api.compare(api) != 0)) {
            return res;
        } else {
            res = true;
            return res;
        }
    }

    return res;
}

std::string* CIdkTimClient::doTimSerivcesAPI(const std::string& api)
{
    // Must be called in the derived classes.
    std::string* pDataBuffer = new std::string();
    pDataBuffer->clear();
    if (!CIdkTimClient::verifyAPI(api)) {
        return pDataBuffer;
    }

    // Initialize the receive buffer for each cycle.
    CURL* conn = NULL;
    CURLcode code;

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
    strUrl.append(api);

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