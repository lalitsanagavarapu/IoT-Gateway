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
#include <time.h>
#include <sys/time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <unordered_map>
#include <chrono>

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/curl-7.55.1/linux/include/curl/curl.h"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/curl-7.55.1/raspberry-pi-2/include/curl/curl.h"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
#include "idk/iHubble/curl-7.55.1/android-21/armeabi-v7a/include/curl/curl.h"
#endif

#include "vc_sf_things2pack_rstats.h"

#include "vc_sf_idk_21450_2010_ncap_services.h"
#include "vc_sf_idk_21451_2010_ncap_controller.h"

#include "vc_sf_idk_21450_2010_sf_main.h"

#include "db/redis/vc_sf_redis_client_factory.h"
#include "foundation/qlib/vc_sf_reliable_redis_q.h"


extern CVCRedisClientFactory*  G_RELIABLE_REDIS_WSN_Q_FACTORY;

// Interface class to Product specific Rule Engine.
CIdkNcapProductModelProcessor::CIdkNcapProductModelProcessor()
{
}

CIdkNcapProductModelProcessor::~CIdkNcapProductModelProcessor()
{
}

int CIdkNcapProductModelProcessor::doProductModelProcessing(/*IN*/ const std::string& jstrTransducerMeasurement,
                                                            /*IN/OUT*/ std::string& jstrPreprocessedMeasurement)
{
    return VC_SF_ERROR_NO_ERROR;
}

//+++++++++++++++NEW CLASS DEFINITION+++++++++++++++++++++
CIdkNcapModelProcessor::CIdkNcapModelProcessor(Poco::NotificationQueue* queue,
                                               const std::string& jstrNcapControllerClient,
                                               const std::string& jstrModelProcessorCommunicator,
                                               const std::string& jstrProductRules,
                                               const std::string& jstrAssets,
                                               const std::string& jstrErpNode,
                                               const std::string& jstrOpcNode)
    : m_ncapControllerClient(jstrNcapControllerClient)
{
    m_queue = queue;
    m_jstrProductRules = jstrProductRules;
    m_jstrAssets = jstrAssets;
    m_jstrErpNode = jstrErpNode;
    m_jstrOpcNode = jstrOpcNode;
    initConfig(jstrModelProcessorCommunicator);
}
CIdkNcapModelProcessor::~CIdkNcapModelProcessor()
{
}

bool CIdkNcapModelProcessor::initConfig(const std::string& jstrModelProcessorCommunicator)
{
    m_ncap_processor_communicator_node = "ncap_model_processor_communicator";
    m_ncap_processor_publisher_node = "ncap_model_processor_publisher";
    m_jstrModelProcessorCommunicator.clear();

    m_bIsValidNcapCommunicator = false;

    std::string err;
    json11::Json jncapCommunicatorNode = json11::Json::parse(jstrModelProcessorCommunicator, err);
    if (!err.empty()) {
        m_bIsValidNcapCommunicator = false;
    } else {
        m_jstrModelProcessorCommunicator = jstrModelProcessorCommunicator;
        m_bIsValidNcapCommunicator = true;

        m_site_id = jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]["site_id"].number_value();

        m_ncap_processor_communicator_port =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]["ncap_model_processor_communicator_port"]
                .number_value();
        m_ncap_processor_communicator_address =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]
                                 ["ncap_model_processor_communicator_address"].string_value();
        m_ncap_processor_communicator_scheme =
            jncapCommunicatorNode[m_ncap_processor_communicator_node.c_str()]
                                 ["ncap_model_processor_communicator_scheme"].string_value();

        m_ncap_processor_publisher_port =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]["ncap_model_processor_publisher_port"]
                .number_value();
        m_ncap_processor_publisher_address =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]["ncap_model_processor_publisher_address"]
                .string_value();
        m_ncap_processor_publisher_scheme =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]["ncap_model_processor_publisher_scheme"]
                .string_value();

        // NCAP Broadcast Messages
        m_transducer_defs_update_broadcast_message =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]
                                 ["ncap_transducer_defs_update_broadcast_message"].string_value();
        m_product_rules_update_broadcast_message =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]
                                 ["ncap_product_rules_update_broadcast_message"].string_value();
        m_assets_update_broadcast_message =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]["ncap_assets_update_broadcast_message"]
                .string_value();
        m_cyber_physical_update_broadcast_message =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]
                                 ["ncap_cyber_physical_update_broadcast_message"].string_value();

        m_erp_node_update_broadcast_message =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]["ncap_erp_node_update_broadcast_message"]
                .string_value();

        m_opc_node_update_broadcast_message =
            jncapCommunicatorNode[m_ncap_processor_publisher_node.c_str()]["ncap_opc_node_update_broadcast_message"]
                .string_value();
                
        m_digital_twin_config = jncapCommunicatorNode["digital_twin_config"];
    }
    return m_bIsValidNcapCommunicator;
}

void CIdkNcapModelProcessor::run()
{
    // Collect IIoT, OPC and ERP data into a preprocessor

    //  Prepare context and socket
    zmq::context_t context(1);
    zmq::socket_t modelProcessor(context, ZMQ_PULL);

    std::string pullmq;
    pullmq.clear();
    pullmq.append(m_ncap_processor_communicator_scheme);
    pullmq.append("://");
    pullmq.append(m_ncap_processor_communicator_address);
    pullmq.append(":");
    // Just a local block ... some memory may be saved.
    {
        char buff[33] = {};
        snprintf(buff, sizeof(buff), "%d", m_ncap_processor_communicator_port);
        pullmq.append(buff);
    }
    modelProcessor.bind(pullmq.c_str());

    // Publish the results to Measurement APP.
    zmq::socket_t publisher(context, ZMQ_PUB);

    std::string pubmq;
    pubmq.clear();
    pubmq.append(m_ncap_processor_publisher_scheme);
    pubmq.append("://");
    pubmq.append(m_ncap_processor_publisher_address);
    pubmq.append(":");

    // Just a local block ... some memory may be saved.
    {
        char buff2[33] = {};
        snprintf(buff2, sizeof(buff2), "%d", m_ncap_processor_publisher_port);
        pubmq.append(buff2);
    }

    publisher.bind(pubmq.c_str());

    std::vector<std::shared_ptr<CIdkNcapProductModelProcessor> > products;

    if (G_SFMAIN) {
        G_SFMAIN->sfProductModelProcessingObjects(products);
    }
    
    // Read the Digital Twin Configuration
    std::string influxDbServerUrl = m_digital_twin_config["influx-server-url"].string_value();
    
    // To be deleted after testing.
    /*
    {
      std::string fname = "../config/digital_twin_config.json";
      std::stringstream ss;
      std::ifstream file(fname);
      if (!file.is_open()){
        std::cout << "File Open Error :: " << fname << std::endl;
        exit(0);
      }
      std::string err;
      err.clear();
      ss << file.rdbuf();
      json11::Json sfDigitalTwinConfig = json11::Json::parse(ss.str(), err);
      if (!err.empty()) {
          // TBD Log
          exit (0);
      }
      // 
      // {
      //    "influx-server-url": "http://localhost:8086/write?db=things2pack&u=picominer&p=vc1004influxdb123!"
      // }
      
      influxDbServerUrl = sfDigitalTwinConfig["influx-server-url"].string_value();
       
    }
    */
    
    std::unordered_map<std::string, std::shared_ptr<CSFThings2PackRStats> > rstats;

    while (1) {
        //  Wait for start of batch
        zmq::message_t message;
        modelProcessor.recv(&message);

        // TBD: Check if there is any change in the Product Rules.
        if (m_queue) {
            Poco::AutoPtr<Poco::Notification> pNf(m_queue->dequeueNotification());
            while (pNf) {
                CIdkNcapNotification* pWorkNf = dynamic_cast<CIdkNcapNotification*>(pNf.get());
                if (pWorkNf) {
                    // Read Assets, Product Rules, Transducer defs and any other supported
                    // data from the NCAP Controller.
                    // Rebuild the data structures as needed.

                    if ((pWorkNf->data().compare(m_transducer_defs_update_broadcast_message) == 0) ||
                        (pWorkNf->data().compare(m_product_rules_update_broadcast_message) == 0) ||
                        (pWorkNf->data().compare(m_assets_update_broadcast_message) == 0) ||
                        (pWorkNf->data().compare(m_cyber_physical_update_broadcast_message) == 0) ||
                        (pWorkNf->data().compare(m_erp_node_update_broadcast_message) == 0) ||
                        (pWorkNf->data().compare(m_opc_node_update_broadcast_message) == 0)) {

                        std::string* cp = m_ncapControllerClient.getCyberPhysicalConfig();

                        // Build Product Rules, Reload Assets etc.

                        if (G_SFMAIN) // Should never be the case of NULL G_SFMAIN. Who knows!
                        {
                            G_SFMAIN->sfsetCyberPhysicalConfig(*cp);
                            G_SFMAIN->sfProductModelProcessingObjects(products);
                        }

                        delete cp;
                    }
                }
                pNf = m_queue->dequeueNotification();
            }
        }

        // Do some analysis.
        // We have to do a multithread component processing
        // high speed incoming messages.
        std::string modelInputMsg((char*)message.data());
        std::string productsModelProcessingOutput;
        productsModelProcessingOutput.clear();
        
        productsModelProcessingOutput.append("{");  // Top level block begin
        
        // Records aggreated timestamp. // Aggregated Timestamp block begin
        std::stringstream ss;
        // Get the timestamp.
        long long milliseconds_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>
                    (
                      std::chrono::system_clock::now().time_since_epoch()
                    ).count();
        long long nanoseconds_since_epoch = std::chrono::duration_cast<std::chrono::nanoseconds>
                    (
                      std::chrono::system_clock::now().time_since_epoch()
                    ).count();
        ss << "\"aggregated_at\"" << ":" << milliseconds_since_epoch;
        productsModelProcessingOutput.append(ss.str());
        
        productsModelProcessingOutput.append(","); // Aggregated Timestamp block end
        
        // Model-Processing-Output is inserted as array elements. 
        // Model Processing Output Block Begin
        productsModelProcessingOutput.append("\"Model-Processing-Output\": [");
        
        int nProds = products.size();
        for (const auto& myProduct : products) {
            std::string modelOutput;
            myProduct->doProductModelProcessing(modelInputMsg, modelOutput);

            productsModelProcessingOutput.append(modelOutput);

            nProds--;

            if (nProds >= 1) {
                productsModelProcessingOutput.append(",");
            }
        }
        productsModelProcessingOutput.append("]");
        // Model Processing Output Block End
        
        // Other Arrays if generated Begin
        // ...
        // Other Arrays if generated End
        
        productsModelProcessingOutput.append("}"); // Top level block end

        std::string err;
        err.clear();
        json11::Json jIoT = json11::Json::parse(productsModelProcessingOutput, err);
        if (err.empty()) {
          // No Error in parsing the JSON. We can start storing the data in the Timeseries Database.
          // Refer to the Line protocol of InfluxDB and gateway spec in Techpubs of the Portal Project.
          // <measurement>[,<tag-key>=<tag-value>...] <field-key>=<field-value>[,<field2-key>=<field2-value>...] [unix-nano-timestamp]
          
          for (UInt32 i = 0; i < jIoT["Model-Processing-Output"].array_items().size(); i++){
            
            for (UInt32 j = 0; j < jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items().size(); j++){
              
              std::stringstream   lineProtocol;
              std::ostringstream  datasetHashStream;
              
              // Name of the Measurement of Line Protocol
              lineProtocol << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-TEDS"]["type"].string_value();
              lineProtocol << ",";
              
              // Assets. Tags Values for Line Protocol.
              lineProtocol << "teds_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-TEDS"]["TEDSID"].number_value();
              lineProtocol << ",";
              lineProtocol << "teds_uuid=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-TEDS"]["UUID"]["UID"].number_value();
              lineProtocol << ",";
              lineProtocol << "area_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["area_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "control_module_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["control_module_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "equipment_module_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["equipment_module_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "factory_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["factory_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "gateway_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["gateway_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "machine_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["machine_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "shelf_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["shelf_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "site_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["site_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "slot_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["slot_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "work_center_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["work_center_id"].number_value();
              lineProtocol << ",";
              
              // Products
              lineProtocol << "product_id=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Product-Rules-Key"]["product_id"].number_value();
              lineProtocol << ",";
              lineProtocol << "product_name=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Product-Rules-Key"]["product_name"].string_value();
              lineProtocol << ",";
              lineProtocol << "st_instance=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["UUID"]["UID"].number_value();
              
              // Value Delimiter.
              lineProtocol << " ";
              
              
              // ------------------------------------------------------
              // BATCH STATISTICS
              // ------------------------------------------------------
              
              // Object Key = FactoryId.SiteId.AreaID.WorkCenterId.MachineId.EquipmentId.ControlModuleId.ShelfId.SlotId
              // Stats Key = ObjectKey.<Stats_Key>
              // Stats - SampleSize, Min, Max, Mean, Variance, StdDeviation, Skew, Kurtosis, Median
              
              datasetHashStream << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["factory_id"].number_value()
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["site_id"].number_value() 
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["area_id"].number_value()  
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["work_center_id"].number_value() 
                                << "."
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["machine_id"].number_value() 
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["equipment_module_id"].number_value() 
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["control_module_id"].number_value() 
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["shelf_id"].number_value()
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Assets-Key"]["slot_id"].number_value()

                    // Product Segment
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["Meta-Product-Rules-Key"]["product_name"].string_value()

                    // Transducer Segment.
                                << "." 
                                << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["implementation"]["UUID"]["UID"].number_value();;
              
              
              // Check if the dataset is present in the mapper.
              auto thisTransducerStats = rstats.find(datasetHashStream.str());
              if (thisTransducerStats == rstats.end()) {
                  std::shared_ptr<CSFThings2PackRStats> rStatsObj(new CSFThings2PackRStats(),
                                                                  CSFThings2PackRStatsDeleter());
                  rstats.insert({ datasetHashStream.str(), rStatsObj });
                  thisTransducerStats = rstats.find(datasetHashStream.str());
              }
              
              auto statsObj = thisTransducerStats->second;
              
              if (statsObj){
                
                if (statsObj->size() >= VC_SF_MAX_DATASET_SIZE_FOR_RSTATS) {
                  
                  // Field and Values of Line Protocols
                  // Smart Transducer Measurements
                  lineProtocol << "st_response=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["measurement"]["Transducer-Channel-Envelope"]["response"].number_value();
                  lineProtocol << ",";
                  lineProtocol << "st_time_instance=" << static_cast<long>(jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["measurement"]["time_instance"].number_value());
                  lineProtocol << ",";
                  lineProtocol << "st_status=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["measurement"]["status"].number_value();
                                    
                  // SampleSixe, Min, Max, Mean, Variance, StdDeviation, Skew, Kurtosis, Median                  
                  lineProtocol << ",";
                  lineProtocol << "sample_size=" << statsObj->size();
                  
                  lineProtocol << ",";
                  lineProtocol << "min=" << statsObj->min();
                
                  lineProtocol << ",";
                  lineProtocol << "max=" << statsObj->max();
                  
                  lineProtocol << ",";
                  lineProtocol << "mean=" << statsObj->mean();
                  
                  lineProtocol << ",";
                  lineProtocol << "variance=" << statsObj->variance();
                  
                  lineProtocol << ",";
                  lineProtocol << "std_deviation=" << statsObj->sd();
                  
                  lineProtocol << ",";
                  lineProtocol << "skew=" << statsObj->skew();
                  
                  lineProtocol << ",";
                  lineProtocol << "kurtosis=" << statsObj->kurtosis();
                  
                  lineProtocol << ",";
                  lineProtocol << "median=" << statsObj->median();

                  // Publish the System Stats.
                  std::string systemStats;
                  systemStats.clear();
                  
                  json11::Json statsJson = json11::Json::object
                  {
                    { "System-Stats", json11::Json::object {
                        { "transducer-stats", json11::Json::object 
                          {
                            { "sample_size", statsObj->size()},
                            { "sample_duration", statsObj->getStatsDuration()},
                            { "sample_duration_units", "milliseconds" },
                            { "min", statsObj->min() },
                            { "max", statsObj->max() },
                            { "mean", statsObj->mean() },
                            { "variance", statsObj->variance() },
                            { "std_deviation", statsObj->sd() },
                            { "skew", statsObj->skew() },
                            { "kurtosis", statsObj->kurtosis() },
                            { "median", statsObj->median() }
                          }
                        }                    
                      }
                    }
                  };
                  systemStats = statsJson.dump();
                  
                  std::cout << systemStats << std::endl;
                  std::cout << "-----------------------------------------" << std::endl;
                  
                  zmq::message_t sfStatsOutputMessage(systemStats.length() + 1);
                  memset((char*)sfStatsOutputMessage.data(), 0, systemStats.length() + 1);
                  memcpy((char*)sfStatsOutputMessage.data(), systemStats.c_str(), systemStats.length());

                  publisher.send(sfStatsOutputMessage);
                  
                }
                else{
                  // Field and Values of Line Protocols
                  // Smart Transducer Measurements
                  lineProtocol << "st_response=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["measurement"]["Transducer-Channel-Envelope"]["response"].number_value();
                  lineProtocol << ",";
                  lineProtocol << "st_time_instance=" << static_cast<long>(jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["measurement"]["time_instance"].number_value());
                  lineProtocol << ",";
                  lineProtocol << "st_status=" << jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["measurement"]["status"].number_value();                  
                }
              
                // Add method reset stats object if the size of the sample exceeds the limit.
                // So, add it only after checking is the current size of the samples is within the limit or not.
                int transducerResponse = jIoT["Model-Processing-Output"].array_items()[i]["IoT-Transducer-Response"].array_items()[j]["measurement"]["Transducer-Channel-Envelope"]["response"].number_value();
                statsObj->add(transducerResponse);
              }
              
              // Final step to store the counters.
              lineProtocol << " ";
              
              // Timestamp of the record.
              lineProtocol << nanoseconds_since_epoch;
              
              if (!influxDbServerUrl.empty())
              {
                // Post to the Timeseries database.
                CURL *curl;
                CURLcode res;
               
                /* In windows, this will init the winsock stuff */ 
                curl_global_init(CURL_GLOBAL_ALL);
               
                /* get a curl handle */ 
                curl = curl_easy_init();
                if(curl) {
                  
                  curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
                  
                  /* First set the URL that is about to receive our POST. This URL can
                     just as well be a https:// URL if that is what should receive the
                     data. */ 
                  curl_easy_setopt(curl, CURLOPT_URL, influxDbServerUrl.c_str());
                  
                  char lbuff[2048] = {};
                  memcpy(lbuff, lineProtocol.str().c_str(), lineProtocol.str().length());
                  /* Now specify the POST data */ 
                  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, lbuff);
               
                  /* Perform the request, res will get the return code */ 
                  res = curl_easy_perform(curl);
                  /* Check for errors */ 
                  if(res != CURLE_OK) {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n",
                            curl_easy_strerror(res));                        
                  }
               
                  /* always cleanup */ 
                  curl_easy_cleanup(curl);              
                }
                curl_global_cleanup();
              }
            }
          }        
        }

        zmq::message_t sfModelOutputMessage(productsModelProcessingOutput.length() + 1);
        memset((char*)sfModelOutputMessage.data(), 0, productsModelProcessingOutput.length() + 1);
        memcpy((char*)sfModelOutputMessage.data(),
               productsModelProcessingOutput.c_str(),
               productsModelProcessingOutput.length());

        
        // std::cout << "IoT Data Packet : " << productsModelProcessingOutput.length() + 1 << std:: endl  << std::flush;
        // std::cout << "-----------------------------------------" << std::endl;
        // std::cout << productsModelProcessingOutput << std::endl << std::flush;
        
        publisher.send(sfModelOutputMessage);
        
        
        // Let's Publish the data onto WSN (Websocket Service Nodes as well). 
        // Currently, we are handling sf-transducer-insights-protocol here; i.e. raw transducer data
        // is published onto WSN network.
        CVCSfIoTHubEgressWsnReliableRedisQ wsnEq
            (
               G_RELIABLE_REDIS_WSN_Q_FACTORY
               , m_digital_twin_config["wsn"]["remote_wsn_domain"].string_value()
               , m_digital_twin_config["wsn"]["remote_wsn_q_name"].string_value()
            );
  
        wsnEq.push(productsModelProcessingOutput);
        
        
        Poco::Thread::sleep(0);
    }
}
