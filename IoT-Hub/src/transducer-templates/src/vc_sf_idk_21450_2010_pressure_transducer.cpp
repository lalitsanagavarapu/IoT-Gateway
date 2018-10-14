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

#include "vc_sf_idk_21450_2010_pressure_transducer.h"

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkPressureTransducerMeasurement::CIdkPressureTransducerMeasurement()
{
}

CIdkPressureTransducerMeasurement::CIdkPressureTransducerMeasurement(const std::string& jstrTeds)
    : CIdkTransducerMeasurement(jstrTeds)
{
    m_jstrTeds = jstrTeds;
}

CIdkPressureTransducerMeasurement::~CIdkPressureTransducerMeasurement()
{
}

int CIdkPressureTransducerMeasurement::initTransducer()
{
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkPressureTransducerMeasurement::readTransducerMeasurement()
{
    return 0;
}

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkPressureTransducerMeasurementSimulator::CIdkPressureTransducerMeasurementSimulator(const std::string& jstrTeds)
    : CIdkTransducerMeasurement(jstrTeds)
{
    m_jstrTeds = jstrTeds;
    m_pressureHistory.erase(m_pressureHistory.begin(), m_pressureHistory.end());
    m_currentResponseIndex = 0;
    m_maxHistorySize = m_pressureHistory.size();
}

CIdkPressureTransducerMeasurementSimulator::CIdkPressureTransducerMeasurementSimulator()
{
}

int CIdkPressureTransducerMeasurementSimulator::initTransducer()
{
    m_currentResponseIndex = 0;

    // Use base class methods to simulate sensor data.
    CIdkTransducerMeasurement::simulate(m_pressureHistory);

    m_maxHistorySize = m_pressureHistory.size();

    return VC_SF_ERROR_NO_ERROR;
}

CIdkPressureTransducerMeasurementSimulator::~CIdkPressureTransducerMeasurementSimulator()
{
}

int CIdkPressureTransducerMeasurementSimulator::readTransducerMeasurement()
{
    // We will start with m_currentResponseIndex = 0, reach max history size
    // and warp to m_currentResponseIndex = 0 again.
    int s = 0;

    if (m_pressureHistory.size() != 0) {
        s = m_pressureHistory[m_currentResponseIndex];
        m_currentResponseIndex++;
        if (m_currentResponseIndex >= m_maxHistorySize) {
            m_currentResponseIndex = 0;
            m_maxHistorySize = 0;

            // Populate the samples space with new datasets.
            initTransducer();
        }
    } else {
        // Populate the samples space with new datasets.
        initTransducer();

        s = m_pressureHistory[m_currentResponseIndex];
    }
    return s;
}

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkPressureTransducer::CIdkPressureTransducer()
{
    // Do NOT Use this constructor.
    m_pressure = NULL;
    m_httpHandler = NULL;
    m_TEDSHandler = NULL;
}

CIdkPressureTransducer::~CIdkPressureTransducer()
{
    if (NULL != m_pressure)
        delete m_pressure;

    if (NULL != m_httpHandler)
        delete m_httpHandler;

    if (NULL != m_TEDSHandler)
        delete m_TEDSHandler;
}

CIdkPressureTransducer::CIdkPressureTransducer(const std::string& jstrTeds)
{
    // Make all pointer variable to NULL.
    m_pressure = NULL;
    m_httpHandler = NULL;
    m_TEDSHandler = NULL;

    m_jstrTEDS = jstrTeds;

    std::string err;
    m_jTEDS = json11::Json::parse(m_jstrTEDS, err);

    std::string op = m_jTEDS["implementation"]["operation"].string_value();

    if (op.compare("simulation") == 0) {
        m_pressure = new CIdkPressureTransducerMeasurementSimulator(jstrTeds);
    } else {
        m_pressure = new CIdkPressureTransducerMeasurement(jstrTeds);
    }

    if (m_pressure) {
        m_pressure->initTransducer();
    }
}

// The caller is responsible to format the output.
int CIdkPressureTransducer::readMeasurement()
{
    int s = 0;
    if (m_pressure) {
        s = m_pressure->readTransducerMeasurement();
    }

    return s;
}

// Caller will free the memory.
std::string* CIdkPressureTransducer::readMeasurementString()
{
    std::string* pMeasurement = new std::string;
    int s = 0;

    if (m_pressure) {
        s = m_pressure->readTransducerMeasurement();
        // TBD. Transducer Error Injection test.
        int errorInject = m_jTEDS["implementation"]["inject_transducer_errors"]["status"].number_value();
        int lle = 0;
        int ule = 0;
        if (errorInject != 0) {
          
           lle = m_jTEDS["implementation"]["inject_transducer_errors"]["lower_limit_errors"].number_value();
           ule = m_jTEDS["implementation"]["inject_transducer_errors"]["upper_limit_errors"].number_value();
          
        }
        if (lle != 0){
          if (s < 1500) { // For count < 1500... it should be configuration parameter.
            s = 0;    // Error was injected into the transducer reading.         
          }
        }
        if (ule != 0){
          if (s > 3000 && s <= 3750) { // It should be configuration parameter.
            s = 3750;    // Error was injected into the transducer reading.         
          }
        }
    }

    // Get the timestamp.
    double milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    json11::Json pressureResp = json11::Json::object{
        { "implementation", m_jTEDS["implementation"] },
        { "measurement",
          json11::Json::object{
              { "Transducer-Channel-Envelope",
                json11::Json::object{ { "type", "s_int" },             // Envelope Type
                                      { "length", 1 },                 // The Transducer Modules fill the data read.
                                      { "response", json11::Json(s) }, // The Transducer Modules build response packet.
                } },
              { "status", json11::Json(0) }, // Success = 0, Error is negative number.
              { "time_instance", json11::Json(milliseconds_since_epoch) }, { "time_units", "milliseconds" }
          } }
    };
    pMeasurement->append(pressureResp.dump());

    return pMeasurement;
}