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
#include <stdlib.h>
#include <iostream>

#include "vc_sf_idk_erp_client.h"

// CIdkNcapERPClient Calls/has CIdkErpClient

CIdkErpClientProxy::CIdkErpClientProxy(const std::string& strErpNodeDetails, const std::string& strErpLib)
{
    m_jstrErpNodeDetails = strErpNodeDetails;
    std::string err;
    err.clear();

    m_jErpLib = json11::Json::parse(strErpLib, err);
}

CIdkErpClientProxy::~CIdkErpClientProxy()
{
}

// Caller MUST free the memory
std::string* CIdkErpClientProxy::readErp()
{
    std::string* pErpRecord = new std::string;

    // Get the timestamp.
    double milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    json11::Json erpResp = json11::Json::object{
        { "implementation", m_jErpLib["Meta-Erp-Node-Key"] },
        { "measurement",
          json11::Json::object{
              { "Erps-Channel-Envelope",
                json11::Json::object{ { "type", "json" },             // Envelope Type
                                      { "length", json11::Json(1) },  // The Transducer Modules fill the data read.
                                      { "response", "ERP RESPONSE" }, // The Transducer Modules build response packet.
                } },
              { "status", json11::Json(0) }, // Success = 0, Error is negative number.
              { "time_instance", json11::Json(milliseconds_since_epoch) }, { "time_units", "milliseconds" }
          } }
    };

    pErpRecord->append(erpResp.dump());

    return pErpRecord;
}

CIdkErpClient::CIdkErpClient()
{
}
CIdkErpClient::~CIdkErpClient()
{
}

int CIdkErpClient::createErpClient(const std::string& strOpcNodeDetails, const std::string& jstrNcapControllerClient)
{
    // Caller MUST ensure the correctness of the JSON strings.
    // I cannot check for all errors!
    m_jstrNcapControllerClient = jstrNcapControllerClient;
    m_jstrErpNodeDetails = strOpcNodeDetails;

    std::string err;
    m_jerpNodeDetails = json11::Json::parse(m_jstrErpNodeDetails, err);
    if (!err.empty()) {
        return VC_SF_ERROR_UNKNOWN_ERROR;
    }

    err.clear();

    m_erpClientProxies.erase(m_erpClientProxies.begin(), m_erpClientProxies.end());

    CIdkNcapControllerClient ncapClient(jstrNcapControllerClient);
    std::string* pErpLib = ncapClient.getErpLibrary();

    std::string* pstrProds = ncapClient.getProductRules();

    json11::Json jProds = json11::Json::parse(*pstrProds, err);

    for (UInt32 i = 0; i < jProds.array_items().size(); i++) {
        int product_id = jProds.array_items()[i]["Meta-Product-Rules-Key"]["product_id"].number_value();
        std::string product_name = jProds.array_items()[i]["Meta-Product-Rules-Key"]["product_name"].string_value();

        err.clear();
        json11::Json jErpLib = json11::Json::parse(*pErpLib, err);

        UInt32 erp = 0;
        json11::Json jErp;
        for (erp = 0; erp < jErpLib.array_items().size(); erp++) {
            int erp_product_id = jErpLib[erp]["Meta-Erp-Rules"]["UUID"]["UID"].number_value();

            std::string erp_product_name = jErpLib[erp]["Meta-Erp-Rules"]["UUID"]["UNAME"].string_value();

            if ((erp_product_id == product_id) && (erp_product_name.compare(product_name) == 0)) {
                jErp = jErpLib[erp];

                std::shared_ptr<CIdkErpClientProxy> erpProxy(new CIdkErpClientProxy(m_jstrErpNodeDetails, jErp.dump()),
                                                             CIdkErpClientProxyDeleter());

                m_erpClientProxies.insert({ erp_product_id, erpProxy });
            }
        }
    }
    delete pErpLib;
    delete pstrProds;

    return VC_SF_ERROR_NO_ERROR;
}

// Caller will free the std::string*
std::string* CIdkErpClient::readErp()
{
    std::string* perpOutput = new std::string();

    // Prepare arrary of opc responses in a JSON
    // JSON Header
    perpOutput->append("{\"ERP-Response\":");
    perpOutput->append("[");

    // TBD
    // Read OPC server here.
    // Do data transformation of the OPC
    // PACKML tags needs to be processed here.

    int numErpClients = m_erpClientProxies.size();
    for (const auto& myErp : m_erpClientProxies) {

        auto p = myErp.second;

        std::string* pErpResp = p->readErp();
        perpOutput->append(*pErpResp);

        // We need to free the resources received from readMesurementString().
        delete pErpResp;
        pErpResp = NULL;

        numErpClients--;

        if (numErpClients >= 1) {
            perpOutput->append(",");
        }
    }

    // Close the JSON Array of transducer responses
    perpOutput->append("]}");
    return perpOutput;
}
