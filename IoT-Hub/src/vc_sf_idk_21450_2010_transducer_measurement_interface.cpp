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
#include "vc_sf_idk_21450_2010_transducer_measurement_interface.h"

//+++++++++++++++++++A NEW CLASS DEFINITION+++++++++++++++++++
CIdkTransducerMeasurement::CIdkTransducerMeasurement()
{
}

CIdkTransducerMeasurement::CIdkTransducerMeasurement(const std::string& jstrTeds)
{
    m_jstrTeds = jstrTeds;
}

CIdkTransducerMeasurement::~CIdkTransducerMeasurement()
{
}

int CIdkTransducerMeasurement::initTransducer()
{
    // The derived classes MUST override this.
    return VC_SF_ERROR_NO_ERROR;
}

int CIdkTransducerMeasurement::readTransducerMeasurement()
{
    // The derived classes MUST override this.
    return 0;
}

int CIdkTransducerMeasurement::simulate(/*OUT*/ std::vector<int>& samples)
{
    std::string err;
    err.clear();

    json11::Json jteds = json11::Json::parse(m_jstrTeds, err);

    // Let's clear the samples bin.
    samples.erase(samples.begin(), samples.end());

    if (!err.empty()) {
        return VC_SF_ERROR_UNKNOWN_ERROR;
    }

    // Read the TEDS (simulation Section) and do generate appropriate dataset.

    std::string generators = jteds["simulation"]["generators"].string_value();
    std::string distributors = jteds["simulation"]["distributors"].string_value();
    int maxHistorySize = jteds["simulation"]["max_history_size"].number_value();

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(750, 3750);
    for (int i = 0; i < maxHistorySize; ++i) {
        int number = distribution(generator);
        samples.push_back(number);
    }

    return VC_SF_ERROR_NO_ERROR;
}