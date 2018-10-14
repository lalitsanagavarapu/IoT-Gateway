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

//
// Make sure the UUID["UID"] && UUID["UNAME"] && class["class_id"] are unique in the
// Product OPC Array.
// Please note that the processing of OPC data changes for each product line.
// So, it is a MUST to define OPC objects per product and add it to the
// appropriate preset.
//

json11::Json jOpcLibrary = json11::Json::array{
    json11::Json::object // 1 Product #1 Milk
    { { "Meta-Opc-Node-Key", json11::Json::object{ { "server", "localhost" }, { "port", 80 }, { "id", 1 },
                                                   // Other ERP Server details.
                             } },
      // TED sections are sourced from the transducer manufacturer data sheets.
      { "Meta-Opc-Rules",
        json11::Json::object{ { "description", "Meta-Opc-Rules" },

                              // Globally Unique Identifier for Product ERP
                              { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                              { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                              { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                              { "Year", 2017 },
                                                              { "Date/Sequence",
                                                                0xABDC }, // Something like part number /UID
                                                              { "UNAME", "milk" },
                                                              { "UID", 1 } } },
                              { "class",
                                json11::Json::object{ { "class_id", 0xFEFE },
                                                      { "class_name", "CSFMilkOpc" }, // Platform supported Product OPC
                                                      { "class_tag", "OPC" }          // "," separated string.
                                } },
                              { "version",
                                json11::Json::object{ { "version_id", 0xFFFF }, { "version_name", "Some Name" },
                                                      { "version_tag", "Some Tag" } // "," separated string.
                                } } } },
      { "Opc-Rules",
        json11::Json::object{
            { "description", "Product specific OPC Rules and details." },
            { "rules", json11::Json::array{ json11::Json::object{ { "id", 0xFEEB }, { "options", 0xFEEB }
                                                                  // Let's define rules....
                                            },
                                            json11::Json::object{ { "id", 0xFEEC }, { "options", 0xFEEC }
                                                                  // Let's define rules....
                                            } } },
            { "packml-status-commands",
              json11::Json::array{
                  json11::Json::object{ { "1", json11::Json::object{ { "id", 0xFEEB }, { "options", 0xFEEB }
                                                                     // Let's define rules....
                                               } } },
                  json11::Json::object{ { "2", json11::Json::object{ { "id", 0xFEEC }, { "options", 0xFEEC }
                                                                     // Let's define rules....
                                               } } },
              } },
        }, },
      { "Upstream-Rules",
        json11::Json::object{ { "description", "Product Product specific OPC Upstream details." },
                              { "rules",
                                json11::Json::array{ json11::Json::object{ { "id", 0xFEED }, { "options", 0xFEED }
                                                                           // Let's define rules....
                                                     },
                                                     json11::Json::object{ { "id", 0xFEEE }, { "options", 0xFEED }
                                                                           // Let's define rules....
                                                     } } } } },
      { "Downstream-Rules",
        json11::Json::object{ { "description", "Product specific OPC Downstream details." },
                              { "rules",
                                json11::Json::array{ json11::Json::object{ { "id", 0xFEEB }, { "options", 0xFEEB }
                                                                           // Let's define rules....
                                                     },
                                                     json11::Json::object{ { "id", 0xFEEC }, { "options", 0xFEEC }
                                                                           // Let's define rules....
                                                     } } } } }, },
    json11::Json::object // 2 Product #2 Oil
    { { "Meta-Opc-Node-Key", json11::Json::object{ { "server", "localhost" }, { "port", 80 }, { "id", 2 },
                                                   // Other ERP Server details.
                             } },

      // TED sections are sourced from the transducer manufacturer data sheets.
      { "Meta-Opc-Rules",
        json11::Json::object{ { "description", "Meta-Opc-Rules" },

                              // Globally Unique Identifier for Product OPC
                              { "UUID", json11::Json::object{ { "N/S", 1 },                            // N = 1, S = 0
                                                              { "Latitude", 17.385044 }, { "E/W", 1 }, // E = 1, W = 0
                                                              { "Longitude", 78.486671 }, { "Manufacturer", 0X000A },
                                                              { "Year", 2017 },
                                                              { "Date/Sequence",
                                                                0xABDC }, // Something like part number /UID
                                                              { "UNAME", "oil" },
                                                              { "UID", 2 } } },
                              { "class",
                                json11::Json::object{ { "class_id", 0xBBBB },
                                                      { "class_name", "CSFOilOpc" }, // Platform supported Product
                                                      { "class_tag", "OPC" }         // "," separated string.
                                } },
                              { "version",
                                json11::Json::object{ { "version_id", 0xBBBB }, { "version_name", "Some Name" },
                                                      { "version_tag", "Some Tag" } // "," separated string.
                                } } } },
      { "Opc-Rules",
        json11::Json::object{
            { "description", "Product specific OPC Rules and details." },
            { "rules", json11::Json::array{ json11::Json::object{ { "id", 0xFEEB }, { "options", 0xFEEB }
                                                                  // Let's define rules....
                                            },
                                            json11::Json::object{ { "id", 0xFEEC }, { "options", 0xFEEC }
                                                                  // Let's define rules....
                                            } } },
            { "packml-status-commands",
              json11::Json::array{
                  json11::Json::object{ { "1", json11::Json::object{ { "id", 0xFEEB }, { "options", 0xFEEB }
                                                                     // Let's define rules....
                                               } } },
                  json11::Json::object{ { "2", json11::Json::object{ { "id", 0xFEEC }, { "options", 0xFEEC }
                                                                     // Let's define rules....
                                               } } },
              } },
        }, },
      { "Upstream-Rules",
        json11::Json::object{ { "description", "Product specific OPC Upstream details." },
                              { "rules",
                                json11::Json::array{ json11::Json::object{ { "id", 0xFEED }, { "options", 0xFEED }
                                                                           // Let's define rules....
                                                     },
                                                     json11::Json::object{ { "id", 0xFEEE }, { "options", 0xFEED }
                                                                           // Let's define rules....
                                                     } } } } },
      { "Downstream-Rules",
        json11::Json::object{ { "description", "Product specific ERP Downstream details." },
                              { "rules",
                                json11::Json::array{ json11::Json::object{ { "id", 0xFEEB }, { "options", 0xFEEB }
                                                                           // Let's define rules....
                                                     },
                                                     json11::Json::object{ { "id", 0xFEEC }, { "options", 0xFEEC }
                                                                           // Let's define rules....
                                                     } } } } }, },
};
