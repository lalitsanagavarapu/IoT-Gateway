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

#ifndef _VC_SF_THINGS2PACK_H_
#define _VC_SF_THINGS2PACK_H_

#include "vc_sf_idk_21450_2010_types.h"
#include "vc_sf_idk_21450_2010_errors.h"
#include "vc_sf_idk_21450_2010_sf_main.h"

/* Begin of the 'extern "C"' block */
#ifdef __cplusplus
extern "C" {
#endif

class CSFThings2Pack : public CIdkSfMain
{
    std::string m_jstrTransducerDefs;
    std::string m_jstrProductRules;
    std::string m_jstrAssets;
    std::string m_jstrErpNode;
    std::string m_jstrOpcNode;

    json11::Json m_jTransducersDefs;
    json11::Json m_jProductRules;
    json11::Json m_jAssets;
    json11::Json m_jErpNode;
    json11::Json m_jOpcNode;

    // Library Copy
    // Load Library Objects.
    json11::Json m_jSFFactoryAssetsLibrary;
    json11::Json m_jSFProductLibrary;
    json11::Json m_jSFTransducerLibrary;
    json11::Json m_jSFErpLibrary;
    json11::Json m_jSFOpcLibrary;
    
    // Configured Objects
    // Load Configured Objects.
    // Default / Preset Cyber-Physical Configuration Implementation
    json11::Json m_jSFAssets_preset;
    json11::Json m_jSFProductRules_preset;
    json11::Json m_jSFErpRules_preset;
    json11::Json m_jSFErpNode_preset;
    json11::Json m_jSFOpcNode_preset;
    json11::Json m_jSFOpcRules_preset;
    json11::Json m_jSFTransducerDefinitions_preset;

public:
    CSFThings2Pack();
    virtual ~CSFThings2Pack();
    virtual int sfMain();
    virtual bool sfsetCyberPhysicalConfig(const std::string& jstrCyberPhysicalConfig);
    virtual int sfProductModelProcessingObjects(/*OUT*/ std::vector<std::shared_ptr<CIdkNcapProductModelProcessor> >& products);

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

#endif /* _VC_SF_THINGS2PACK_H_ */
