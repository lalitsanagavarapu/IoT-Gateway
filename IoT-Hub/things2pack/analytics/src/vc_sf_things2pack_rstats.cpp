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

#include <iostream>
#include <sstream>
#include <time.h>
#include <sys/time.h>
#include <chrono>

#ifdef IDK_PLATFORM_LINUX

#endif

#ifdef IDK_PLATFORM_ARM_RPI

#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK

#endif

#include "vc_sf_things2pack_rstats.h"

CSFThings2PackRStats::CSFThings2PackRStats()
{
    init();
}

CSFThings2PackRStats::~CSFThings2PackRStats()
{
    if (m_rsWorkspace) {
        gsl_rstat_free(m_rsWorkspace);
    }
}

int CSFThings2PackRStats::init()
{
    // Let's catch library errors with status value and
    // continue the execution of the program.
    gsl_set_error_handler_off();

    m_rsWorkspace = gsl_rstat_alloc();
    
    // Time interval between 1 and last sample.
    milliseconds_since_epoch_at_1_sample = 0L;
    milliseconds_since_epoch_at_last_sample = 0L;

    return VC_SF_ERROR_NO_ERROR;
}

int CSFThings2PackRStats::reset()
{
    // Let's catch library errors with status value and
    // continue the execution of the program.
    gsl_set_error_handler_off();

    if (m_rsWorkspace) {
        gsl_rstat_reset(m_rsWorkspace);
    }

    milliseconds_since_epoch_at_1_sample = 0L;
    milliseconds_since_epoch_at_last_sample = 0L;

    return VC_SF_ERROR_NO_ERROR;
}

// Add Samples
int CSFThings2PackRStats::add(const double x)
{
    if (size() >= VC_SF_MAX_DATASET_SIZE_FOR_RSTATS) {
        printStats();
        reset();
        
        // Start a new time window.
        // Store timestamp of 1st sample after a reset.
        milliseconds_since_epoch_at_1_sample = std::chrono::duration_cast<std::chrono::milliseconds>
                    (
                      std::chrono::system_clock::now().time_since_epoch()
                    ).count();
    }
    // Store timestamp of last added sample.
    milliseconds_since_epoch_at_last_sample = std::chrono::duration_cast<std::chrono::milliseconds>
                (
                  std::chrono::system_clock::now().time_since_epoch()
                ).count();
    return gsl_rstat_add(x, m_rsWorkspace);
}

// Size of the data added to the workspace.
double CSFThings2PackRStats::size()
{
    return gsl_rstat_n(m_rsWorkspace);
}

double CSFThings2PackRStats::min()
{
    return gsl_rstat_min(m_rsWorkspace);
}

double CSFThings2PackRStats::max()
{
    return gsl_rstat_max(m_rsWorkspace);
}

double CSFThings2PackRStats::mean()
{
    return gsl_rstat_mean(m_rsWorkspace);
}

double CSFThings2PackRStats::variance()
{
    return gsl_rstat_variance(m_rsWorkspace);
}

double CSFThings2PackRStats::sd()
{
    return gsl_rstat_sd(m_rsWorkspace);
}

double CSFThings2PackRStats::skew()
{
    return gsl_rstat_skew(m_rsWorkspace);
}

double CSFThings2PackRStats::kurtosis()
{
    return gsl_rstat_kurtosis(m_rsWorkspace);
}

double CSFThings2PackRStats::median()
{
    return gsl_rstat_median(m_rsWorkspace);
}

double CSFThings2PackRStats::getStatsDuration()
{
  return milliseconds_since_epoch_at_last_sample - milliseconds_since_epoch_at_1_sample;
}

// Monotor
int CSFThings2PackRStats::printStats()
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << "DATA SIZE : " << size() << std::endl;
    std::cout << "MIN       : " << min() << std::endl;
    std::cout << "MAX       : " << max() << std::endl;
    std::cout << "MEAN      : " << mean() << std::endl;
    std::cout << "VARIANCE  : " << variance() << std::endl;
    std::cout << "STD. DEV  : " << sd() << std::endl;
    std::cout << "SKEW      : " << skew() << std::endl;
    std::cout << "KURTOSIS  : " << kurtosis() << std::endl;
    std::cout << "MEDIAN    : " << median() << std::endl;
    std::cout << "------------------------------------" << std::endl;

    return VC_SF_ERROR_NO_ERROR;
}