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

#include "vc_sf_idk_21450_2010_pressure_transducer.h"
#include "vc_sf_idk_21450_2010_length_transducer.h"
#include "vc_sf_idk_21450_2010_mass_transducer.h"
#include "vc_sf_idk_21450_2010_thickness_transducer.h"
#include "vc_sf_idk_21450_2010_vision_transducer.h"

#include "vc_sf_idk_21450_2010_tim_controller.h"

CIdkTimController::CIdkTimController()
{
    m_jstrTransducerDefinitions.clear();
    m_jstrProductRules.clear();
    m_jstrAssets.clear();
}
CIdkTimController::~CIdkTimController()
{
}

int CIdkTimController::createTransducerObjects(const std::string& jstrTransducerDefinitions,
                                               const std::string& jstrProductRules,
                                               const std::string& jstrAssets)
{
    // Caller MUST ensure the correctness of the JSON strings.
    // I cannot check for all errors!

    m_jstrTransducerDefinitions = jstrTransducerDefinitions;
    m_jstrProductRules = jstrProductRules;
    m_jstrAssets = jstrAssets;

    std::string err;
    m_jTransducerDefinitions = json11::Json::parse(m_jstrTransducerDefinitions, err);
    if (!err.empty()) {
        return VC_SF_ERROR_UNKNOWN_ERROR;
    }

    err.clear();
    m_jProductRules = json11::Json::parse(m_jstrProductRules, err);
    if (!err.empty()) {
        return VC_SF_ERROR_UNKNOWN_ERROR;
    }

    err.clear();
    m_jAssets = json11::Json::parse(m_jstrAssets, err);
    if (!err.empty()) {
        return VC_SF_ERROR_UNKNOWN_ERROR;
    }

    // Erase the existing Transducer objects from the map.
    // Due to security reasons, we will have ALL or NONE approach
    // when updting the Transducer objects.
    m_siteTransducers.erase(m_siteTransducers.begin(), m_siteTransducers.end());

    for (UInt32 i = 0; i < m_jTransducerDefinitions.array_items().size(); i++) {
        std::string teds = m_jTransducerDefinitions.array_items()[i].dump();

        std::string type = m_jTransducerDefinitions.array_items()[i]["Meta-TEDS"]["type"].string_value();
        
        if (type.compare("pressure") == 0) {
            int n = m_jTransducerDefinitions.array_items()[i]["implementation"]["UUID"]["UID"].number_value();
            std::shared_ptr<CIdkTransducer> transducer(new CIdkPressureTransducer(teds), CIdkTransducerDeleter());
            m_siteTransducers.insert({ n, transducer });
            
        } else if (type.compare("vision") == 0) {
            int n = m_jTransducerDefinitions.array_items()[i]["implementation"]["UUID"]["UID"].number_value();
            std::shared_ptr<CIdkTransducer> transducer(new CIdkVisionTransducer(teds), CIdkTransducerDeleter());
            m_siteTransducers.insert({ n, transducer });
            
        } else if (type.compare("thickness") == 0) {
            int n = m_jTransducerDefinitions.array_items()[i]["implementation"]["UUID"]["UID"].number_value();
            std::shared_ptr<CIdkTransducer> transducer(new CIdkThicknessTransducer(teds), CIdkTransducerDeleter());
            m_siteTransducers.insert({ n, transducer });
            
        } else if (type.compare("length") == 0) {
            int n = m_jTransducerDefinitions.array_items()[i]["implementation"]["UUID"]["UID"].number_value();
            std::shared_ptr<CIdkTransducer> transducer(new CIdkLengthTransducer(teds), CIdkTransducerDeleter());
            m_siteTransducers.insert({ n, transducer });
            
        } else if (type.compare("mass") == 0) {
            int n = m_jTransducerDefinitions.array_items()[i]["implementation"]["UUID"]["UID"].number_value();
            std::shared_ptr<CIdkTransducer> transducer(new CIdkMassTransducer(teds), CIdkTransducerDeleter());
            m_siteTransducers.insert({ n, transducer });

        } else {
            // Do nothing.
            // We do not support the Transducer Type requested!
            std::cout << "TRANSDUCER NOT RECOGNIZED -> " << type << std::endl;
        }
    }

    return VC_SF_ERROR_NO_ERROR;
}

// Caller will free the std::string*
std::string* CIdkTimController::readAllSensors()
{
    std::string* psensorOutput = new std::string();

    // Prepare arrary of sensor responses in a JSON
    // JSON Header
    psensorOutput->append("{\"IoT-Transducer-Response\":");
    psensorOutput->append("[");

    int numTransducers = m_siteTransducers.size();
    
    for (const auto& mySensors : m_siteTransducers) {
        /*
        auto p = mySensors.second;

        std::string *pMeasurement = p->readMeasurementString();
        psensorOutput->append(*pMeasurement);

        // We need to free the resources received from readMesurementString().
        delete pMeasurement;
        pMeasurement = NULL;
        */

        auto n = mySensors.first;

        std::string* pMeasurement = readSensorById(n);
        psensorOutput->append(*pMeasurement);

        // We need to free the resources received from readMesurementString().
        delete pMeasurement;
        pMeasurement = NULL;

        numTransducers--;

        if (numTransducers >= 1) {
            psensorOutput->append(",");
        }
    }

    // Close the JSON Array of transducer responses
    psensorOutput->append("]}");
    return psensorOutput;
}

// Caller will free the std::string*
// id => transducer["implementation"]["UUID"]["UID"]
std::string* CIdkTimController::readSensorById(UInt32 id)
{
    std::string* psensorOutput = new std::string();
    psensorOutput->clear();

    int numTransducers = m_siteTransducers.size();
    if (numTransducers > 0) {
        const auto myTransducer = m_siteTransducers.find(id);
        if (myTransducer == m_siteTransducers.end()) {
            // We did not find the Transducer requeste for.
            // Just return empty response.
            psensorOutput->append("{\"IoT-Transducer-Response\":[]}");
        } else // We found the Transducer.
        {
            auto p = myTransducer->second;

            std::string* pMeasurement = p->readMeasurementString();
            psensorOutput->append(*pMeasurement);

            // We need to free the resources received from readMesurementString().
            delete pMeasurement;
            pMeasurement = NULL;
        }
    } else // Something wrong. Why someone is asking to read a transducer when nothing is provisioned?
    {
        psensorOutput->append("{\"IoT-Transducer-Response\":[]}");
    }

    return psensorOutput;
}