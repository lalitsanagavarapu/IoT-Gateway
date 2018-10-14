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

#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/raspberry-pi-2/include/json11.hpp"

#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/android-21/armeabi-v7a/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/android-21/armeabi-v7a/include/json11.hpp"
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

#include "vc_sf_things2pack.h"

json11::Json jTransducerLibrary = json11::Json::array{
    json11::Json::object // 1
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xABCD }, { "type", "vision" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  12345 },   // Something like part number.
                                                                { "UID", 1 } // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xABCD },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xABCD },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xABCD },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xABCD },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xABCD },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xABCD },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xABCD },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xABCD },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xABCD },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 2
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xABCE }, { "type", "thickness" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  5678 },    // Something like part number.
                                                                { "UID", 2 } // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xABCE },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xABCE },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xABCE },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xABCE },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xABCE },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xABCE },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xABCE },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xABCE },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xABCE },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 3
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xABCF }, { "type", "mass" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  23456 },   // Something like part number.
                                                                { "UID", 3 } // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xABCF },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xABCF },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xABCF },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xABCF },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xABCF },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xABCF },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xABCF },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xABCF },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xABCF },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 4
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xABBA }, { "type", "length" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  23456 },   // Something like part number.
                                                                { "UID", 4 } // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xABBA },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xABBA },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xABBA },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xABBA },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xABBA },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xABBA },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xABBA },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xABBA },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xABBA },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    
    /////////////////////////////////////////////////////////////////////////////////////////
    
    json11::Json::object // 5
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAAAA }, { "type", "vision" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  123456 },   // Something like part number.
                                                                { "UID", 5 }  // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAAAA },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAAAA },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAAAA },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAAAA },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAAAA },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAAAA },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAAAA },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAAAA },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAAAA },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 6
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAAAB }, { "type", "thickness" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  567890 },    // Something like part number.
                                                                { "UID", 6 }   // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAAAB },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAAAB },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAAAB },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAAAB },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAAAB },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAAAB },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAAAB },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAAAB },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAAAB },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 7
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAAAC }, { "type", "mass" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  2345678 },   // Something like part number.
                                                                { "UID", 7 }   // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAAAC },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAAAC },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAAAC },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAAAC },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAAAC },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAAAC },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAAAC },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAAAC },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAAAC },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 8
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAAAD }, { "type", "length" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  3456789 },   // Something like part number.
                                                                { "UID", 8 } // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAAAD },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAAAD },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAAAD },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAAAD },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAAAD },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAAAD },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAAAD },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAAAD },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAAAD },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    
    
    /////////////////////////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////////
    
    json11::Json::object // 9
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAABA }, { "type", "vision" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  923456 },   // Something like part number.
                                                                { "UID", 9 }  // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAABA },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAABA },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAABA },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAABA },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAABA },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAABA },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAABA },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAABA },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAABA },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 10
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAABB }, { "type", "thickness" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  967898 },    // Something like part number.
                                                                { "UID", 10 }  // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAABB },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAABB },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAABB },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAABB },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAABB },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAABB },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAABB },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAABB },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAABB },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 11
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAABC }, { "type", "mass" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  9345677 },   // Something like part number.
                                                                { "UID", 11 }  // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAABC },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAABC },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAABC },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAABC },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAABC },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAABC },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAABC },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAABC },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAABC },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 12
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAABD }, { "type", "length" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  1456789 },   // Something like part number.
                                                                { "UID", 12 }  // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAABD },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAABD },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAABD },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAABD },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAABD },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAABD },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAABD },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAABD },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAABD },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    
    
    /////////////////////////////////////////////////////////////////////////////////////////
    
    /////////////////////////////////////////////////////////////////////////////////////////
    
    json11::Json::object // 13
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAACA }, { "type", "vision" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  723458 },    // Something like part number.
                                                                { "UID", 13 }  // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAACA },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAACA },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAACA },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAACA },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAACA },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAACA },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAACA },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAACA },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAACA },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 14
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAACB }, { "type", "thickness" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  467898 },     // Something like part number.
                                                                { "UID", 14 }   // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAACB },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAACB },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAACB },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAACB },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAACB },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAACB },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAACB },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAACB },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAACB },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 15
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAACC }, { "type", "mass" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  3345677 },    // Something like part number.
                                                                { "UID", 15 }   // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAACC },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAACC },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAACC },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAACC },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAACC },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAACC },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAACC },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAACC },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAACC },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    json11::Json::object // 16
    {
        // TED sections are sourced from the transducer manufacturer data sheets.
        { "Meta-TEDS",
          json11::Json::object{ { "description", "Meta TEDS" }, { "TEDSID", 0xAACD }, { "type", "length" },

                                // Globally Unique Identifier for Transducer
                                // Usually it is supplied by the manufacturer.
                                { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                                { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                                { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                                { "Year", 2017 },
                                                                { "Date/Sequence",
                                                                  8456789 },    // Something like part number.
                                                                { "UID", 16 }   // Instance ID in our application.
                                          } },
                                { "version",
                                  json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                        { "version_tag", "Some Tag" } // "," separated string.
                                  } },
                                { "TEDs-Specification", "Other Meta TEDS data" } } },
        { "TransducerChannel-TEDS",
          json11::Json::object{
              { "description", "TransducerChannel TEDS" }, { "TEDSID", 0xAACD },
              { "TEDs-Specification", "Other TransducerChannel TEDS data" },

              // The response packet of transducer measurement.
              { "Meta-TransducerChannel-Envelope",
                json11::Json::object{ { "name", "Transducer-Channel-Envelope" }, { "type", "s_int" }, // Envelope Type
                                      { "length", 1 }, // The Transducer Modules fill the data read.
                                      { "response",
                                        "Transducer Measurement" }, // The Transducer Modules build response packet.
                } },
          } },
        { "Calibration-TEDS", json11::Json::object{ { "description", "Calibration TEDS" }, { "TEDSID", 0xAACD },
                                                    { "TEDs-Specification", "Other Calibration TEDS data" } } },
        { "Frequency-Response-TEDS",
          json11::Json::object{ { "description", "Frequency Response TEDS" }, { "TEDSID", 0xAACD },
                                { "TEDs-Specification", "Other Frequency Response TEDS data" } } },
        { "Transfer-Function-TEDS",
          json11::Json::object{ { "description", "Transfer Function TEDS" }, { "TEDSID", 0xAACD },
                                { "TEDs-Specification", "Other Transfer Function TEDS data" } } },
        { "Text-based-TEDS", json11::Json::object{ { "description", "Text-based TEDS" }, { "TEDSID", 0xAACD },
                                                   { "TEDs-Specification", "Other Text-based TEDS data" } } },
        { "End-User-Application-Specific-TEDS",
          json11::Json::object{ { "description", "End User Application Specific TEDS" }, { "TEDSID", 0xAACD },
                                { "TEDs-Specification", "Other End User Application Specific TEDS data" } } },
        { "User-Transducer-Name-TEDS",
          json11::Json::object{ { "description", "User's Transducer Name TEDS" }, { "TEDSID", 0xAACD },
                                { "TEDs-Specification", "Other User's Transducer Name TEDS data" } } },
        { "Manufacturer-defined-TEDS",
          json11::Json::object{ { "description", "Manufacturer-defined TEDS" }, { "TEDSID", 0xAACD },
                                { "TEDs-Specification", "Other Manufacturer-defined TEDS data" } } },
        { "PHY-TEDS", json11::Json::object{ { "description", "PHY TEDS" }, { "TEDSID", 0xAACD },
                                            { "TEDs-Specification", "Other PHY TEDS data" } } },
        // This section should be populated from application
        // For example, Things2Pack.
        // This is the section that links the sensors and application
        { "simulation",
          json11::Json::object{ { "description", "Details of transducer reading simulation" },
                                { "generators", "linear_congruential_engine" },
                                { "distributors", "none" },
                                { "capabilities", 0x000A }, // Usually an ENUM / BIT MAP of the simulation objectives.
                                { "max_history_size", 1800 } } },
    },
    
    
    /////////////////////////////////////////////////////////////////////////////////////////
    
};
