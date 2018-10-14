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

#ifndef _VC_SF_IDK_21450_2010_SF_MAIN_H_
#define _VC_SF_IDK_21450_2010_SF_MAIN_H_

#include "vc_sf_idk_21450_2010_types.h"
#include "vc_sf_idk_21450_2010_errors.h"

#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cassert>
#include <list>
#include <set>
#include <unordered_map>
#include <memory>

#include "Poco/SingletonHolder.h"
#include "vc_sf_idk_21450_2010_ncap_services.h"

/* Begin of the 'extern "C"' block */
#ifdef __cplusplus
extern "C" {
#endif

//
// GLOBAL SMART FACTORY MAIN OBJECT.
// YES... WE "KNOW" THIS APPROACH IS NOT VERY ELEGANT.
// WE WILL FIND SOMEWAY TO USE SINGLETON OBJECT.
// THE CLIENTS OF THIS CLASS + GLOBAL OBJECT ARE REQUIRED
// KEEP THIS OBJ ONLY FOR DESIGNED USAGE.
//
// THIS IS THE FIRST OBJECT CREATED IN THE PROGRAM MAIN
// OR IN THE LIBRAY INTERFACES.
//

class CIdkSfMain;
extern CIdkSfMain* G_SFMAIN;

class CIdkTransducerFactory
{
public:
    CIdkTransducerFactory();
    virtual ~CIdkTransducerFactory();

    // Transducer Definition interface for Smart Factory Apps

    // Returns platform supported transducers
    // transducer-templates/ has a set of platform supported transducers.
    // Of which, only a sub-set of transducer-templates are needed
    // for given Smart Factory Apps.
    // For example, length, mass, and pressure transducers are supported
    // for Packaging application.
    // Derived classes (CIdkSfMain and its sub classes) override to implement
    // application specific transducer library.
    // Returns a JSON array - Follow the below JSON structure.
    /*
    json11::Json jPlatformMetatransducerDefinitions = json11::Json::array
    {
        json11::Json::object
        {
            {"Platfrom-Transducer-Library", json11::Json::object
                {
                    {"name", <some name of the transducer>},
                    {"type", <length | mass | <type of the transducer>>},
                    {"transducers", json11::Json::array
                        {
                            json11::Json::object // 1 Transducer TEDS of Type "A"
                            {
                                // TED sections are sourced from the transducer manufacturer data sheets.
                                {"Meta-TEDS", json11::Json::object
                                    ...
                                },
                            },
                            json11::Json::object // 2 Transducer TEDS of Type "A"
                            {
                                // TED sections are sourced from the transducer manufacturer data sheets.
                                {"Meta-TEDS", json11::Json::object
                                    ...
                                },
                            }
                        }
                    }
                }
            }

        },
        // 2nd Type of Transducer and its supported Library
    };
    */
    //
    virtual std::string* getPlatformMetaTransducerLibrary();
};

class CIdkProductFactory
{
public:
    CIdkProductFactory();
    virtual ~CIdkProductFactory();

    // Product Definition interface for Smart Factory Apps

    // Returns platform supported Products
    // <Product Family>/ has a set of platform supported products.
    // Of which, only a sub-set of products are licensed
    // for given Smart Factory Apps.
    // For example, milk, oil, are supported product line for Packaging application.

    // Derived classes (CIdkSfMain and its sub classes) override to implement
    // application specific product library.
    // Returns a JSON array - Follow the below JSON structure.
    /*
    json11::Json jPlatformMetaProducts = json11::Json::array
    {
        json11::Json::object // Product #1
        {
            {"Meta-Product-Rules", json11::Json::object
                {
                   ...
                }
            }
        },
        // Product #2
    };
    */
    //
    virtual std::string* getPlatformMetaProductLibrary();
};

class CIdkAssetsFactory
{
public:
    CIdkAssetsFactory();
    virtual ~CIdkAssetsFactory();

    // Assets configuration for Smart Factory Apps
    // Returns the Facory assets configure.
    virtual std::string* getPlatformMetaAssetsLibrary();
};

class CIdkPresetSmartFactory
{
public:
    CIdkPresetSmartFactory();
    virtual ~CIdkPresetSmartFactory();

    // Returns a JSON array - Follow the below JSON structure.
    // Returns a preset of product(s), transducer(s) and assets
    /*
    json11::Json jPresetSmartFactory = json11::Json::array
    {
        json11::Json::object // Preset #1
        {
            {"transducer_definitions", json11::Json::object
                {
                   ...
                }
            },
            {"product_rules", json11::Json::object
                {
                   ...
                }
            },
            {"assets", json11::Json::object
                {
                   ...
                }
            }

        },
        // Preset #2
    };
    */
    //
    virtual std::string* getPresetSmartFactoryLibrary();
};

class CIdkErpFactory
{
public:
    CIdkErpFactory();
    virtual ~CIdkErpFactory();

    // Assets configuration for Smart Factory Apps
    // Returns the Facory assets configure.
    virtual std::string* getPlatformMetaErpLibrary();
};

class CIdkOpcFactory
{
public:
    CIdkOpcFactory();
    virtual ~CIdkOpcFactory();

    // Assets configuration for Smart Factory Apps
    // Returns the Facory assets configure.
    virtual std::string* getPlatformMetaOpcLibrary();
};

class CIdkSfMain : public CIdkTransducerFactory,
                   public CIdkProductFactory,
                   public CIdkAssetsFactory,
                   public CIdkPresetSmartFactory,
                   public CIdkErpFactory,
                   public CIdkOpcFactory
{
public:
    CIdkSfMain();
    virtual ~CIdkSfMain();
    virtual int sfMain();

    // Derived FAMILY of Products MUST override this to verify the
    // given Cyber-Physical configuration.
    virtual bool sfsetCyberPhysicalConfig(const std::string& jstrCyberPhysicalConfig);
    virtual int
    sfProductModelProcessingObjects(/*OUT*/ std::vector<std::shared_ptr<CIdkNcapProductModelProcessor> >& products);

    // Cyber-Physical Config factory overrides
    virtual std::string* getPlatformMetaTransducerLibrary();
    virtual std::string* getPlatformMetaProductLibrary();
    virtual std::string* getPresetSmartFactoryLibrary();
    virtual std::string* getPlatformMetaAssetsLibrary();
    virtual std::string* getPlatformMetaErpLibrary();
    virtual std::string* getPlatformMetaOpcLibrary();
};

#ifdef __cplusplus
} /* end of the 'extern "C"' block */
#endif

#endif /* _VC_SF_IDK_21450_2010_SF_MAIN_H_ */
