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
#include <chrono>

#ifdef IDK_PLATFORM_LINUX
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/linux/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/linux/include/json11.hpp"
#include "idk/iHubble/zeromq-4.2.2/linux/include/zmq.hpp"
#include "idk/iHubble/hdf5-1.10.1/linux/include/hdf5.h"
#endif

#ifdef IDK_PLATFORM_ARM_RPI
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Thread.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Runnable.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/ThreadPool.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/Notification.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/NotificationQueue.h"
#include "idk/iHubble/poco-1.8.0.1/raspberry-pi-2/include/Poco/AutoPtr.h"
#include "idk/iHubble/json11/raspberry-pi-2/include/json11.hpp"
#include "idk/iHubble/zeromq-4.2.2/raspberry-pi-2/include/zmq.hpp"
#include "idk/iHubble/hdf5-1.10.1/raspberry-pi-2/include/hdf5.h"
#endif

#ifdef IDK_PLATFORM_ANDROID_21_ARMEABI_V7A // Relative to the Android target IDK
// HDF5 Recorder is not supported in Android Platforms.
#endif

#include "vc_sf_things2pack_recorder.h"

//--------------------------
// HDF5
#define H5FILE_NAME "VC_SF_THINGS2PACK_RECORDER.h5"
#define DATASETNAME "VC_SF_THINGS2PACK_RECORDER"
#define RANK 1
#define LENGTH 1
const hsize_t ndims = 2;
const hsize_t ncols = 1;
//--------------------------

const std::string gstrTranducerResponseVarList = "Timestamp:Response:Capabilities:Status:Alarms";
const std::string gstrTranducerResponseTitle = "TransducerResponseDataset";

SFH5DataSetMapper::SFH5DataSetMapper()
{
    m_offset[0] = 0;
    m_offset[1] = 0;

    m_size[0] = 1;
    m_size[1] = 1;
}
SFH5DataSetMapper::~SFH5DataSetMapper()
{
}

CSFThings2PackRecorder::CSFThings2PackRecorder(const std::string& jstrRecorderConfig,
                                               const std::string& jstrNcapControllerClient)
    : m_ncapControllerClient(jstrNcapControllerClient)
{
    m_jstrRecorderConfig = jstrRecorderConfig;

    std::string jerr;
    jerr.clear();

    json11::Json jrecConf = json11::Json::parse(jstrRecorderConfig, jerr);

    m_ncap_recorder_subscriber_port =
        jrecConf["ncap_model_processor_publisher"]["ncap_model_processor_publisher_port"].number_value();
    m_ncap_recorder_subscriber_address =
        jrecConf["ncap_model_processor_publisher"]["ncap_model_processor_publisher_address"].string_value();
    m_ncap_recorder_subscriber_scheme =
        jrecConf["ncap_model_processor_publisher"]["ncap_model_processor_publisher_scheme"].string_value();

    // Recorder config read from the digital_twin configuration.
    m_hdf5Recorder = 
        jrecConf["digital_twin_config"]["hdf5_historian"].number_value();

}
CSFThings2PackRecorder::~CSFThings2PackRecorder()
{
}

int CSFThings2PackRecorder::sfRecorderMain()
{
    //  Prepare context and socket
    zmq::context_t context(1);
    zmq::socket_t dataCollector(context, ZMQ_SUB);

    std::string dcSubMQ;
    dcSubMQ.clear();
    dcSubMQ.append(m_ncap_recorder_subscriber_scheme);
    dcSubMQ.append("://");
    dcSubMQ.append(m_ncap_recorder_subscriber_address);
    dcSubMQ.append(":");

    // Just a local block ... some memory may be saved.
    {
        char buff2[33] = {};
        snprintf(buff2, sizeof(buff2), "%d", m_ncap_recorder_subscriber_port);
        dcSubMQ.append(buff2);
    }

    dataCollector.connect(dcSubMQ.c_str());
    dataCollector.setsockopt(ZMQ_SUBSCRIBE, L"", 0);

    if (m_hdf5Recorder)
    {
      // Open HDF5 File to store transducer responses
      hid_t hfile;

      // HDF5 dataset mapper
      // Basically, a dataset is created for each transducer under a specific group.
      // The dataset is extended for each response received.
      // So, we need to remember the last write of the response to point to next write
      // as well. Also, we need to keep some housekeeping information about the dataset.
      m_hDSMapper.erase(m_hDSMapper.begin(), m_hDSMapper.end());

      while (1) {
          // Print Timestamp for each loop:
          long long datacollection_start = std::chrono::duration_cast<std::chrono::milliseconds>(
              std::chrono::system_clock::now().time_since_epoch()).count();

          /*
           * Create the HDF5 file.
           */
          hfile = H5Fcreate(H5FILE_NAME, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

          // Every File must have Assets, Products, and Transducer Libraries.
          // TBD. Each SF Library is a JSON String of length 4K.
          // This must be revisited and make the SFLibrary datasets to dynamic
          // data structure.

          bool bDoesHFileHaveSFLibraries = false;

          int maxEventCounter = 0;

          while (maxEventCounter < VC_SF_MAX_DATASET_SIZE_FOR_RECORDER) {
              maxEventCounter++;
              zmq::message_t ncapEvent;

              //  Wait for next request from client
              dataCollector.recv(&ncapEvent);
              std::string rcvdEvent((char*)ncapEvent.data());

              /* 
              // Print Timestamp for each loop:
              long long milliseconds_since_epoch_start = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch()).count();
              */
              
              if (!bDoesHFileHaveSFLibraries) {
                  hid_t hdataset, hspace, hgrp;
                  herr_t hstatus;
                  hsize_t hdims[] = { 1 };

                  SFLibraryDataSet sfld;
                  hid_t sfld_id, assets_t, products_t, transducers_t, preset_t; /* File datatype identifier */

                  std::string* pAssetsLib = m_ncapControllerClient.getAssetsLibrary();
                  strncpy(sfld.assets, pAssetsLib->c_str(), sizeof(sfld.assets));
                  delete pAssetsLib;

                  std::string* pProductsLib = m_ncapControllerClient.getProductLibrary();
                  strncpy(sfld.products, pProductsLib->c_str(), sizeof(sfld.products));
                  delete pProductsLib;

                  std::string* pTransducersLib = m_ncapControllerClient.getTransducerLibrary();
                  strncpy(sfld.transducers, pTransducersLib->c_str(), sizeof(sfld.transducers));
                  delete pTransducersLib;

                  std::string* pPresetLib = m_ncapControllerClient.getPresetLibrary();
                  strncpy(sfld.preset, pPresetLib->c_str(), sizeof(sfld.preset));
                  delete pPresetLib;

                  /*
                   * Create the memory data type.
                   */

                  assets_t = H5Tcopy(H5T_C_S1);
                  hstatus = H5Tset_size(assets_t, sizeof(sfld.assets));

                  products_t = H5Tcopy(H5T_C_S1);
                  hstatus = H5Tset_size(products_t, sizeof(sfld.products));

                  transducers_t = H5Tcopy(H5T_C_S1);
                  hstatus = H5Tset_size(transducers_t, sizeof(sfld.transducers));

                  preset_t = H5Tcopy(H5T_C_S1);
                  hstatus = H5Tset_size(preset_t, sizeof(sfld.preset));

                  sfld_id = H5Tcreate(H5T_COMPOUND, sizeof(SFLibraryDataSet));

                  H5Tinsert(sfld_id, "assets", HOFFSET(SFLibraryDataSet, assets), assets_t);

                  H5Tinsert(sfld_id, "products", HOFFSET(SFLibraryDataSet, products), products_t);

                  H5Tinsert(sfld_id, "transducers", HOFFSET(SFLibraryDataSet, transducers), transducers_t);

                  H5Tinsert(sfld_id, "preset", HOFFSET(SFLibraryDataSet, preset), preset_t);

                  // Now we have all necessary information to create a dataset.

                  // Check if Group exists

                  hgrp = H5Gopen2(hfile, "/SFLibrary", H5P_DEFAULT);
                  if (hgrp < 0) {
                      hgrp = H5Gcreate2(hfile, "/SFLibrary", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
                  }

                  /*
                   * Create the data space.
                   */
                  hspace = H5Screate_simple(RANK, hdims, NULL);

                  /*
                   * Create the dataset.
                   */
                  hdataset =
                      H5Dcreate2(hfile, "/SFLibrary/Dataset", sfld_id, hspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

                  /*
                   * Wtite data to the dataset;
                   */
                  hstatus = H5Dwrite(hdataset, sfld_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, &sfld);

                  /*
                   * Release resources
                   */
                  H5Tclose(assets_t);
                  H5Tclose(products_t);
                  H5Tclose(transducers_t);
                  H5Tclose(preset_t);

                  H5Tclose(sfld_id);
                  H5Sclose(hspace);
                  H5Dclose(hdataset);
                  H5Gclose(hgrp);

                  H5Fflush(hfile, H5F_SCOPE_GLOBAL);

                  bDoesHFileHaveSFLibraries = true;
              }

              // Create/Verify HDF5 groups for a given response.
              std::string err;
              std::string transducerType;
              std::string productName;

              int factoryId;
              int siteId;
              int areaId;
              int workCenterId;
              int machineId;
              int equipmentModuleId;
              int controlModuleId;
              int shelfId;
              int slotId;

              int transducerUid;
              int capabilities;
              int trStatus;
              int trAlarms;

              double timeInstance = 0;
              int transducerResponse = 0;

              json11::Json sfModelProcessingOutput;
              json11::Json sfMsgRootArray;

              err.clear();
              sfModelProcessingOutput = json11::Json::parse(rcvdEvent, err);
              if (!err.empty()) {
                  // TBD Log
                  // There is some error in the response packet.
                  // Dump the response packet into error dataset.
              }

              for (unsigned int i = 0; i < sfModelProcessingOutput["Model-Processing-Output"].array_items().size(); i++) {
                  sfMsgRootArray = sfModelProcessingOutput["Model-Processing-Output"][i]["IoT-Transducer-Response"];

                  // Iterate the jsonArray and print the info of JSONObjects
                  for (unsigned int j = 0; j < sfMsgRootArray.array_items().size(); j++) {
                      json11::Json jTransducerObj = sfMsgRootArray.array_items()[j];

                      transducerType = jTransducerObj["implementation"]["Meta-TEDS"]["type"].string_value();

                      // TBD This is a temp. fix.
                      // Pick up supported transducers from a global object.
                      std::vector<std::string> transducers = { "thickness", "length", "mass", "vision", "pressure" };

                      for (unsigned int k = 0; k < transducers.size(); k++) {
                          if (transducerType.compare(transducers[k]) == 0) {

                              hid_t hdataset, hspace, hgrp, hfilespace;
                              herr_t hstatus;
                              hsize_t hdims[ndims] = { 1, ncols }; /* Dataspace dimensions while creation */
                              hsize_t hmaxdims[ndims] = { H5S_UNLIMITED, H5S_UNLIMITED };
                              hsize_t hsize[2];
                              hsize_t hoffset[2];

                              // Assets Segment in the Group Path
                              factoryId =
                                  jTransducerObj["implementation"]["Meta-Assets-Key"]["factory_id"].number_value();
                              siteId = jTransducerObj["implementation"]["Meta-Assets-Key"]["site_id"].number_value();
                              areaId = jTransducerObj["implementation"]["Meta-Assets-Key"]["area_id"].number_value();
                              workCenterId =
                                  jTransducerObj["implementation"]["Meta-Assets-Key"]["work_center_id"].number_value();
                              machineId =
                                  jTransducerObj["implementation"]["Meta-Assets-Key"]["machine_id"].number_value();
                              equipmentModuleId =
                                  jTransducerObj["implementation"]["Meta-Assets-Key"]["equipment_module_id"]
                                      .number_value();
                              controlModuleId =
                                  jTransducerObj["implementation"]["Meta-Assets-Key"]["control_module_id"].number_value();
                              shelfId = jTransducerObj["implementation"]["Meta-Assets-Key"]["shelf_id"].number_value();
                              slotId = jTransducerObj["implementation"]["Meta-Assets-Key"]["slot_id"].number_value();

                              // Product Segment in the Group Path
                              productName = jTransducerObj["implementation"]["Meta-Product-Rules-Key"]["product_name"]
                                                .string_value();

                              transducerUid = jTransducerObj["implementation"]["UUID"]["UID"].number_value();

                              std::ostringstream groupPathStream;

                              /*
                              // Asset Segment
                              groupPathStream << "/factory_id."               << factoryId
                                              << "#site_id."                  << siteId
                                              << "#area_id."                  << areaId
                                              << "#work_center_id."           << workCenterId
                                              << "#machine_id."               << machineId
                                              << "#equipment_module_id."      << equipmentModuleId
                                              << "#control_module_id."        << controlModuleId
                                              << "#shelf_id."                 << shelfId
                                              << "#slot_id."                  << slotId

                                              // Product Segment
                                              << "#product_name."     << productName

                                              // Transducer Segment.
                                              << "#transducer_id."    << transducerUid;
                               */

                              // Asset Segment
                              groupPathStream << factoryId << "." << siteId << "." << areaId << "." << workCenterId << "."
                                              << machineId << "." << equipmentModuleId << "." << controlModuleId << "."
                                              << shelfId << "." << slotId

                                  // Product Segment
                                              << "." << productName

                                  // Transducer Segment.
                                              << "." << transducerUid;

                              std::string groupPath = groupPathStream.str();

                              std::ostringstream datasetHashStream;

                              // Asset Segment
                              datasetHashStream << factoryId << "." << siteId << "." << areaId << "." << workCenterId
                                                << "." << machineId << "." << equipmentModuleId << "." << controlModuleId
                                                << "." << shelfId << "." << slotId

                                  // Product Segment
                                                << "." << productName

                                  // Transducer Segment.
                                                << "." << transducerUid;

                              // Check if the dataset is present in the mapper.
                              auto myDsMapper = m_hDSMapper.find(datasetHashStream.str());
                              if (myDsMapper == m_hDSMapper.end()) {
                                  std::shared_ptr<SFH5DataSetMapper> dsMapper(new SFH5DataSetMapper(),
                                                                              SFH5DataSetMapperDeleter());
                                  m_hDSMapper.insert({ datasetHashStream.str(), dsMapper });
                                  myDsMapper = m_hDSMapper.find(datasetHashStream.str());
                              }
                              auto mapper = myDsMapper->second;

                              timeInstance = jTransducerObj["measurement"]["time_instance"].number_value();

                              transducerResponse =
                                  jTransducerObj["measurement"]["Transducer-Channel-Envelope"]["response"].number_value();
                              trStatus =
                                  jTransducerObj["measurement"]["Transducer-Channel-Envelope"]["status"].number_value();
                              // TBD
                              // Alarm management will be introduced soon.
                              trAlarms = 0;

                              capabilities = jTransducerObj["implementation"]["capabilities"].number_value();

                              // Now we have all necessary information to create a dataset.
                              // Check if Group exists

                              hgrp = H5Gopen2(hfile, groupPath.c_str(), H5P_DEFAULT);
                              if (hgrp < 0) {
                                  hgrp = H5Gcreate2(hfile, groupPath.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

                                  // Create a 2D dataspace
                                  // The size of the first dimension is unlimited (initially 0)
                                  // The size of the second dimension is fixed
                                  hspace = H5Screate_simple(ndims, hdims, hmaxdims);

                                  // Create a dataset creation property list
                                  // The layout of the dataset have to be chunked when using unlimited dimensions
                                  hid_t plist = H5Pcreate(H5P_DATASET_CREATE);
                                  H5Pset_layout(plist, H5D_CHUNKED);

                                  // The choice of the chunk size affects performances
                                  hsize_t chunk_dims[ndims] = { 10, ncols };
                                  H5Pset_chunk(plist, ndims, chunk_dims);

                                  /*
                                   * Create the dataset.
                                   */

                                  TransducerResponseDataSet trd;
                                  hid_t trd_id; /* File datatype identifier */

                                  trd.timestamp = timeInstance;
                                  trd.response = transducerResponse;
                                  trd.alarms = maxEventCounter; // trAlarms;
                                  trd.status = trStatus;
                                  trd.capabilities = capabilities;

                                  /*
                                   * Create the memory data type.
                                   */
                                  trd_id = H5Tcreate(H5T_COMPOUND, sizeof(TransducerResponseDataSet));
                                  H5Tinsert(trd_id,
                                            "Timestamp",
                                            HOFFSET(TransducerResponseDataSet, timestamp),
                                            H5T_NATIVE_DOUBLE);

                                  H5Tinsert(
                                      trd_id, "Response", HOFFSET(TransducerResponseDataSet, response), H5T_NATIVE_INT);

                                  H5Tinsert(trd_id,
                                            "Capabilities",
                                            HOFFSET(TransducerResponseDataSet, capabilities),
                                            H5T_NATIVE_INT);

                                  H5Tinsert(trd_id, "Status", HOFFSET(TransducerResponseDataSet, status), H5T_NATIVE_INT);

                                  H5Tinsert(trd_id, "Alarms", HOFFSET(TransducerResponseDataSet, alarms), H5T_NATIVE_INT);

                                  // Time Instance (Timestamp) is the name of the dataset.
                                  // So, append Timestamp to groupPathStream

                                  // groupPathStream << "/" << timeInstance;
                                  groupPathStream << "/TransducerResponseDataset";

                                  hdataset = H5Dcreate2(hfile,
                                                        groupPathStream.str().c_str(),
                                                        trd_id,
                                                        hspace,
                                                        H5P_DEFAULT,
                                                        plist,
                                                        H5P_DEFAULT);

                                  /*
                                   * Extend the dataset. This call assures that dataset is at least 1x1.
                                   */
                                  hsize[0] = mapper->m_size[0];
                                  hsize[1] = mapper->m_size[1];
                                  hstatus = H5Dset_extent(hdataset, hsize);

                                  /*
                                   * Select a hyperslab.
                                   */
                                  hfilespace = H5Dget_space(hdataset);
                                  hoffset[0] = mapper->m_offset[0];
                                  hoffset[1] = mapper->m_offset[1];

                                  hsize_t dims1[2] = { 1, 1 };

                                  hstatus = H5Sselect_hyperslab(hfilespace, H5S_SELECT_SET, hoffset, NULL, dims1, NULL);

                                  /*
                                   * Wtite data to the dataset;
                                   */
                                  hstatus = H5Dwrite(hdataset, trd_id, hspace, hfilespace, H5P_DEFAULT, &trd);

                                  // Close resources
                                  H5Pclose(plist);
                                  H5Tclose(trd_id);
                                  H5Sclose(hspace);
                                  H5Sclose(hfilespace);
                                  H5Dclose(hdataset);
                                  H5Gclose(hgrp);

                                  
                              } else {

                                  TransducerResponseDataSet trd;
                                  hid_t trd_id; /* File datatype identifier */

                                  trd.timestamp = timeInstance;
                                  trd.response = transducerResponse;
                                  trd.alarms = maxEventCounter; // trAlarms;
                                  trd.status = trStatus;
                                  trd.capabilities = capabilities;

                                  /*
                                   * Create the memory data type.
                                   */
                                  trd_id = H5Tcreate(H5T_COMPOUND, sizeof(TransducerResponseDataSet));
                                  H5Tinsert(trd_id,
                                            "Timestamp",
                                            HOFFSET(TransducerResponseDataSet, timestamp),
                                            H5T_NATIVE_DOUBLE);

                                  H5Tinsert(
                                      trd_id, "Response", HOFFSET(TransducerResponseDataSet, response), H5T_NATIVE_INT);

                                  H5Tinsert(trd_id,
                                            "Capabilities",
                                            HOFFSET(TransducerResponseDataSet, capabilities),
                                            H5T_NATIVE_INT);

                                  H5Tinsert(trd_id, "Status", HOFFSET(TransducerResponseDataSet, status), H5T_NATIVE_INT);

                                  H5Tinsert(trd_id, "Alarms", HOFFSET(TransducerResponseDataSet, alarms), H5T_NATIVE_INT);

                                  hspace = H5Screate_simple(ndims, hdims, NULL);

                                  groupPathStream << "/TransducerResponseDataset";

                                  hdataset = H5Dopen2(hfile, groupPathStream.str().c_str(), H5P_DEFAULT);

                                  /*
                                   * Extend the dataset. This call assures that dataset is at least 1x1.
                                   */
                                  hsize[0] = mapper->m_size[0]++;
                                  hsize[1] = mapper->m_size[1];
                                  hstatus = H5Dset_extent(hdataset, hsize);

                                  /*
                                   * Select a hyperslab.
                                   */
                                  hfilespace = H5Dget_space(hdataset);

                                  hoffset[0] = mapper->m_offset[0]++;
                                  hoffset[1] = mapper->m_offset[1];

                                  hsize_t dims1[2] = { 1, 1 };

                                  hstatus = H5Sselect_hyperslab(hfilespace, H5S_SELECT_SET, hoffset, NULL, dims1, NULL);

                                  /*
                                   * Wtite data to the dataset;
                                   */
                                  hstatus = H5Dwrite(hdataset, trd_id, hspace, hfilespace, H5P_DEFAULT, &trd);

                                  // Close resources
                                  H5Tclose(trd_id);
                                  H5Sclose(hspace);
                                  H5Sclose(hfilespace);
                                  H5Dclose(hdataset);
                                  H5Gclose(hgrp);

                              }

                          }
                          // We have opened the group.
                          else {
                              // NOP
                          }
                      }
                  }
              }
              H5Fflush(hfile, H5F_SCOPE_GLOBAL);

              /* Uncomment if you want to debug on how much time it is taking to record events */
              /*
              long long milliseconds_since_epoch_end = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::system_clock::now().time_since_epoch()).count();

              
              std::cout << "Delta run time end (ms) -> "
                        << (milliseconds_since_epoch_end - milliseconds_since_epoch_start) << " " << maxEventCounter
                        << std::endl;
              */
              // Poco::Thread::sleep(0);
          }

          std::cout << "I AM DONE!!! "
                    << "\n" << maxEventCounter * 4 << "RECORDS WERE CREATED" << std::endl;
          H5Fclose(hfile);

          // Print Timestamp for each loop:
          long long datacollection_end = std::chrono::duration_cast<std::chrono::milliseconds>(
              std::chrono::system_clock::now().time_since_epoch()).count();

          std::cout << "TOTAL TIME TO RUN THE TEST: \n"
                    << "START \n" << datacollection_start << "END \n" << datacollection_end << "DURATION (sec) \n"
                    << (datacollection_end - datacollection_start) / 1000 << std::endl;

          return VC_SF_ERROR_NO_ERROR;
      }
      return VC_SF_ERROR_NO_ERROR;
    
    }
    return VC_SF_ERROR_NO_ERROR;
}

void CSFThings2PackRecorder::run()
{
    sfRecorderMain();

    return;
}