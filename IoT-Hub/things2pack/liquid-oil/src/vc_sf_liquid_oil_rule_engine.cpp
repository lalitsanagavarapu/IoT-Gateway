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

#include "vc_sf_liquid_oil_rule_engine.h"

CSFOilProduct::CSFOilProduct()
{
}

CSFOilProduct::CSFOilProduct(const std::string& jstrTransducerDefs,
                             const std::string& jstrProductRules,
                             const std::string& jstrAssets,
                             const std::string& jstrTransducerLib,
                             const std::string& jstrProductsLib,
                             const std::string& jstrAssetsLib,
                             const std::string& jstrErpLib,
                             const std::string& jstrOpcLib)
{
    m_jstrAssets = jstrAssets;
    m_jstrProductRules = jstrProductRules;
    m_jstrTransducerDefs = jstrTransducerDefs;
    m_jstrTransducerLib = jstrTransducerLib;
    m_jstrProductsLib = jstrProductsLib;
    m_jstrAssetsLib = jstrAssetsLib;
    m_jstrErpLib = jstrErpLib;
    m_jstrOpcLib = jstrOpcLib;

    // OK... Let's store JSON objects as well.
    // TBD. We need to optimize the memory usage. We need to store only
    // one version of the libraries (JSON objects). Let' keep both versions till
    // next release.

    std::string err;
    m_jTransducers = json11::Json::parse(m_jstrTransducerDefs, err);
    if (!err.empty()) {
        // Log or Assert.
        return;
    }

    err.clear();
    m_jProductRules = json11::Json::parse(m_jstrProductRules, err);
    if (!err.empty()) {
        // Log or Assert.
        return;
    }

    err.clear();
    m_jAssets = json11::Json::parse(m_jstrAssets, err);
    if (!err.empty()) {
        // Log or Assert.
        return;
    }

    err.clear();
    m_jTransducerLib = json11::Json::parse(m_jstrTransducerLib, err);
    if (!err.empty()) {
        // Log or Assert.
        return;
    }

    err.clear();
    m_jProductsLib = json11::Json::parse(m_jstrProductsLib, err);
    if (!err.empty()) {
        // Log or Assert.
        return;
    }

    err.clear();
    m_jAssetsLib = json11::Json::parse(m_jstrAssetsLib, err);
    if (!err.empty()) {
        // Log or Assert.
        return;
    }

    err.clear();
    m_jOpcLib = json11::Json::parse(m_jstrOpcLib, err);
    if (!err.empty()) {
        // Log or Assert.
        return;
    }

    err.clear();
    m_jErpLib = json11::Json::parse(m_jstrErpLib, err);
    if (!err.empty()) {
        // Log or Assert.
        return;
    }

    m_rstats.erase(m_rstats.begin(), m_rstats.end());
}
CSFOilProduct::~CSFOilProduct()
{
    m_rstats.erase(m_rstats.begin(), m_rstats.end());
}

int CSFOilProduct::doProductModelProcessing(/*IN*/ const std::string& jstrTransducerMeasurement,
                                            /*IN/OUT*/ std::string& jstrPreprocessedMeasurement)
{
    jstrPreprocessedMeasurement.clear();
    jstrPreprocessedMeasurement.append(jstrTransducerMeasurement);

    // Parse the IoT, ERP and OPC data and build stats objects.
    std::string err;
    std::string transducerType;
    std::string productName;

    int factoryId;
    int siteId;
    int areaId;
    int workCenterId;
    int machineId;
    int equipmentModuleId;
    int controlModuleId;
    int shelfId;
    int slotId;

    int transducerUid;
    int capabilities;
    int trStatus;
    int trAlarms;

    double timeInstance = 0;
    int transducerResponse = 0;

    json11::Json sfModelProcessingOutput;
    json11::Json sfMsgRootArray;

    err.clear();
    sfModelProcessingOutput = json11::Json::parse(jstrTransducerMeasurement, err);
    if (!err.empty()) {
        // TBD Log
        // There is some error in the response packet.
        // Dump the response packet into error dataset.
    }

    sfMsgRootArray = sfModelProcessingOutput["IoT-Transducer-Response"];

    // Iterate the jsonArray and print the info of JSONObjects
    for (unsigned int j = 0; j < sfMsgRootArray.array_items().size(); j++) {
        json11::Json jTransducerObj = sfMsgRootArray.array_items()[j];

        transducerType = jTransducerObj["implementation"]["Meta-TEDS"]["type"].string_value();

        // TBD This is a temp. fix.
        // Pick up supported transducers from a global object.
        std::vector<std::string> transducers = { "thickness", "length", "mass", "vision", "pressure" };

        for (unsigned int k = 0; k < transducers.size(); k++) {
            if (transducerType.compare(transducers[k]) == 0) {

                // Assets Segment in the Group Path
                factoryId = jTransducerObj["implementation"]["Meta-Assets-Key"]["factory_id"].number_value();
                siteId = jTransducerObj["implementation"]["Meta-Assets-Key"]["site_id"].number_value();
                areaId = jTransducerObj["implementation"]["Meta-Assets-Key"]["area_id"].number_value();
                workCenterId = jTransducerObj["implementation"]["Meta-Assets-Key"]["work_center_id"].number_value();
                machineId = jTransducerObj["implementation"]["Meta-Assets-Key"]["machine_id"].number_value();
                equipmentModuleId =
                    jTransducerObj["implementation"]["Meta-Assets-Key"]["equipment_module_id"].number_value();
                controlModuleId =
                    jTransducerObj["implementation"]["Meta-Assets-Key"]["control_module_id"].number_value();
                shelfId = jTransducerObj["implementation"]["Meta-Assets-Key"]["shelf_id"].number_value();
                slotId = jTransducerObj["implementation"]["Meta-Assets-Key"]["slot_id"].number_value();

                // Product Segment in the Group Path
                productName = jTransducerObj["implementation"]["Meta-Product-Rules-Key"]["product_name"].string_value();

                transducerUid = jTransducerObj["implementation"]["UUID"]["UID"].number_value();

                std::ostringstream datasetHashStream;

                // Asset Segment
                datasetHashStream << factoryId << "." << siteId << "." << areaId << "." << workCenterId << "."
                                  << machineId << "." << equipmentModuleId << "." << controlModuleId << "." << shelfId
                                  << "." << slotId

                    // Product Segment
                                  << "." << productName

                    // Transducer Segment.
                                  << "." << transducerUid;

                // Check if the dataset is present in the mapper.
                auto myrStats = m_rstats.find(datasetHashStream.str());
                if (myrStats == m_rstats.end()) {
                    std::shared_ptr<CSFThings2PackRStats> rStatsObj(new CSFThings2PackRStats(),
                                                                    CSFThings2PackRStatsDeleter());
                    m_rstats.insert({ datasetHashStream.str(), rStatsObj });
                    myrStats = m_rstats.find(datasetHashStream.str());
                }
                auto statsObj = myrStats->second;

                timeInstance = jTransducerObj["measurement"]["time_instance"].number_value();

                transducerResponse =
                    jTransducerObj["measurement"]["Transducer-Channel-Envelope"]["response"].number_value();
                trStatus = jTransducerObj["measurement"]["Transducer-Channel-Envelope"]["status"].number_value();
                // TBD
                // Alarm management will be introduced soon.
                trAlarms = 0;

                capabilities = jTransducerObj["implementation"]["capabilities"].number_value();

                statsObj->add(transducerResponse);

            } else {
                // NOP
            }
        }
    }

    return 0;
}
