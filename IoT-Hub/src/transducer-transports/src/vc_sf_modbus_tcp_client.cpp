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
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "vc_sf_idk_21450_2010_types.h"
#include "vc_sf_idk_21450_2010_errors.h"
#include "vc_sf_modbus_tcp_client.h"

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/libmodbus-3.1.4/linux/include/modbus/modbus.h"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/libmodbus-3.1.4/raspberry-pi-2/include/modbus/modbus.h"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
#include "idk/iHubble/libmodbus-3.1.4/android-21/armeabi-v7a/include/modbus/modbus.h"
#endif

CIdkModbusTcpClient::CIdkModbusTcpClient()
{
}
CIdkModbusTcpClient::CIdkModbusTcpClient(const std::string& jstrTeds)
{
    // Get the transport spec from the TEDs.
    std::string err;
    json11::Json jTEDS = json11::Json::parse(jstrTeds, err);

    m_jstrImplementationTeds = jTEDS["implementation"].dump();

    m_modbusTcpServer = jTEDS["implementation"]["field-bus"]["server"].string_value();
    m_modbusTcpPort = jTEDS["implementation"]["field-bus"]["port"].number_value();
    m_measurementInputRegStart =
        jTEDS["implementation"]["field-bus"]["register_map"]["measurement_input_reg_addr_start"].number_value();
    m_measurementInputRegEnd =
        jTEDS["implementation"]["field-bus"]["register_map"]["measurement_input_reg_addr_end"].number_value();

    m_simHistory.erase(m_simHistory.begin(), m_simHistory.end());
    m_currentResponseIndex = 0;
    m_maxHistorySize = m_simHistory.size();

    // Use base class methods to simulate sensor data.
    init();
}

CIdkModbusTcpClient::~CIdkModbusTcpClient()
{
}

int CIdkModbusTcpClient::simulate(/*OUT*/ std::vector<uint16_t>& samples)
{
    // Let's clear the samples bin.
    samples.erase(samples.begin(), samples.end());

    std::default_random_engine generator;
    std::uniform_int_distribution<uint16_t> distribution(700, 3300);

    // Create 1800 samples of simulated data.
    for (int i = 0; i < 1800; ++i) {
        uint16_t number = distribution(generator);
        samples.push_back(number);
    }

    return VC_SF_ERROR_NO_ERROR;
}

int CIdkModbusTcpClient::init()
{
    m_currentResponseIndex = 0;

    // Use base class methods to simulate sensor data.
    simulate(m_simHistory);

    m_maxHistorySize = m_simHistory.size();

    return VC_SF_ERROR_NO_ERROR;
}

int CIdkModbusTcpClient::readMeasurementInputRegisters()
{
    modbus_t* ctx;
    int rc;
    int addr;
    int nb;

    uint16_t* transducer_rq_registers;
    uint16_t* transducer_rp_registers;

    // Modbus TCP
    ctx = modbus_new_tcp(m_modbusTcpServer.c_str(), m_modbusTcpPort);
    if (modbus_connect(ctx) == -1) {
        printf("Connection failed: %s\n", modbus_strerror(errno));

        modbus_free(ctx);

        return 0; // Return an invalid reading of a transducer.
    }

    // Memory initialiation
    addr = m_measurementInputRegStart;
    nb = m_measurementInputRegEnd - m_measurementInputRegStart;

    transducer_rq_registers = (uint16_t*)new uint16_t[nb];
    memset(transducer_rq_registers, 0, nb * sizeof(uint16_t));

    /* Fill Req packet with some Random numbers (short) */
    uint16_t s = 0;
    if (m_simHistory.size() != 0) {
        s = m_simHistory[m_currentResponseIndex];
        m_currentResponseIndex++;
        if (m_currentResponseIndex >= m_maxHistorySize) {
            m_currentResponseIndex = 0;
            m_maxHistorySize = 0;

            // Populate the samples space with new datasets.
            init();
        }
    } else {
        // Populate the samples space with new datasets.
        init();

        s = m_simHistory[m_currentResponseIndex];
    }

    transducer_rq_registers[0] = s;
    transducer_rq_registers[1] = 0;

    // For simulations, write the Modbus registers and read them again.
    rc = modbus_write_registers(ctx, addr, nb, transducer_rq_registers);
    if (rc != nb) {

        printf("ERROR modbus_write_registers (%d)\n", rc);
        printf("Address = %d, nb = %d\n", addr, nb);

        modbus_close(ctx);
        modbus_free(ctx);
        delete[] transducer_rq_registers;
        return 0; // Return an invalid reading of a transducer.
    }

    transducer_rp_registers = (uint16_t*)new uint16_t[nb];
    memset(transducer_rp_registers, 0, nb * sizeof(uint16_t));

    rc = modbus_read_registers(ctx, addr, nb, transducer_rp_registers);
    if (rc != nb) {

        printf("ERROR modbus_read_registers single (%d)\n", rc);
        printf("Address = %d\n", addr);

        modbus_close(ctx);
        modbus_free(ctx);
        delete[] transducer_rq_registers;
        delete[] transducer_rp_registers;

        return 0; // Return an invalid reading of a transducer.
    }

    int resp = 0x0000;
    resp = (resp | transducer_rp_registers[0]);

    // Session clean up.
    modbus_close(ctx);
    modbus_free(ctx);
    delete[] transducer_rq_registers;
    delete[] transducer_rp_registers;

    printf("SUCCESS modbus_read_registers single (%d)\n", resp);

    return resp;
}
