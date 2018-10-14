##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=IoT-Hub
ConfigurationName      :=Release
WorkspacePath          :=/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/workspace/picominer
ProjectPath            :=/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Vidcentum R&D Industry 4.0 Apps
Date                   :=13/01/18
CodeLitePath           :=/home/i40apps/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/picominer-gateway
Preprocessors          :=$(PreprocessorSwitch)IDK_PLATFORM_LINUX $(PreprocessorSwitch)IDK_PLATFORM_FAMILY_THINGS2PACK $(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="IoT-Hub.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./idk $(IncludeSwitch)./include $(IncludeSwitch)./include/db/redis $(IncludeSwitch)./include/foundation/qlib $(IncludeSwitch)./src/transducer-templates/include $(IncludeSwitch)./src/transducer-transports/include $(IncludeSwitch)./things2pack/include $(IncludeSwitch)./things2pack/liquid-milk/include $(IncludeSwitch)./things2pack/liquid-oil/include $(IncludeSwitch)./things2pack/recorder/include $(IncludeSwitch)./idk/iHubble/poco-1.8.0.1/linux/include/Poco $(IncludeSwitch)./idk/iHubble/poco-1.8.0.1/linux/include $(IncludeSwitch)./idk/iHubble/zeromq-4.2.2/linux/include $(IncludeSwitch)./idk/iHubble/libmodbus-3.1.4/linux/include/modbus $(IncludeSwitch)./idk/iHubble/gsl-2.4/linux/include $(IncludeSwitch)./idk/iHubble/hiredis-0.13.3/linux/include/hiredis $(IncludeSwitch)./idk/iHubble/hiredis-0.13.3/linux/include/hiredis/adapters $(IncludeSwitch)./things2pack/analytics/include $(IncludeSwitch)./opc/include $(IncludeSwitch)./opc/packml/include $(IncludeSwitch)./erp/include $(IncludeSwitch)./oam/include $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)hiredis $(LibrarySwitch)curl $(LibrarySwitch)cares $(LibrarySwitch)microhttpd $(LibrarySwitch)uriparser $(LibrarySwitch)PocoNet $(LibrarySwitch)PocoFoundation $(LibrarySwitch)zmq $(LibrarySwitch)sodium $(LibrarySwitch)modbus $(LibrarySwitch)pthread $(LibrarySwitch)ssl $(LibrarySwitch)crypto $(LibrarySwitch)hdf5 $(LibrarySwitch)dl $(LibrarySwitch)z $(LibrarySwitch)gsl $(LibrarySwitch)cblas $(LibrarySwitch)atlas $(LibrarySwitch)m 
ArLibs                 :=  "hiredis" "curl" "cares" "microhttpd" "uriparser" "PocoNet" "PocoFoundation" "zmq" "sodium" "modbus" "pthread" "ssl" "crypto" "hdf5" "dl" "z" "gsl" "cblas" "atlas" "m" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)./idk-libs/linux/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -std=c++11 -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_idk-json11_json11.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(ObjectSuffix) $(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(ObjectSuffix) $(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(ObjectSuffix) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_transducer_analog_interface.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_transducer_analog_interface.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_transducer_analog_interface.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_transducer_analog_interface.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_transducer_analog_interface.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_analog_interface.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_transducer_analog_interface.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_sf_main.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_sf_main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_sf_main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_sf_main.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_sf_main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_sf_main.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_sf_main.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(ObjectSuffix): src/vc_sf_idk_21451_2010_ncap_controller.cpp $(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21451_2010_ncap_controller.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(DependSuffix): src/vc_sf_idk_21451_2010_ncap_controller.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(DependSuffix) -MM src/vc_sf_idk_21451_2010_ncap_controller.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(PreprocessSuffix): src/vc_sf_idk_21451_2010_ncap_controller.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21451_2010_ncap_controller.cpp$(PreprocessSuffix) src/vc_sf_idk_21451_2010_ncap_controller.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_transducer_measurement_interface.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_transducer_measurement_interface.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_transducer_measurement_interface.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_transducer_measurement_interface.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_transducer_measurement_interface.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_measurement_interface.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_transducer_measurement_interface.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_transducer_service_apis.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_transducer_service_apis.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_transducer_service_apis.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_transducer_service_apis.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_transducer_service_apis.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_service_apis.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_transducer_service_apis.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_tim_services.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_tim_services.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_tim_services.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_tim_services.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_tim_services.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_services.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_tim_services.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(ObjectSuffix): src/vc_sf_idk_21451_X_2010_ncap_comm_module.cpp $(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21451_X_2010_ncap_comm_module.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(DependSuffix): src/vc_sf_idk_21451_X_2010_ncap_comm_module.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(DependSuffix) -MM src/vc_sf_idk_21451_X_2010_ncap_comm_module.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(PreprocessSuffix): src/vc_sf_idk_21451_X_2010_ncap_comm_module.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_ncap_comm_module.cpp$(PreprocessSuffix) src/vc_sf_idk_21451_X_2010_ncap_comm_module.cpp

$(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(ObjectSuffix): src/vc_sf_idk_utils.cpp $(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_utils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(DependSuffix): src/vc_sf_idk_utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(DependSuffix) -MM src/vc_sf_idk_utils.cpp

$(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(PreprocessSuffix): src/vc_sf_idk_utils.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_utils.cpp$(PreprocessSuffix) src/vc_sf_idk_utils.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_transducer.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_transducer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_transducer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_transducer.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_transducer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_transducer.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_tim_controller.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_tim_controller.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_tim_controller.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_tim_controller.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_tim_controller.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_tim_controller.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_tim_controller.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(ObjectSuffix): src/vc_sf_idk_21451_X_2010_tim_comm_module.cpp $(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21451_X_2010_tim_comm_module.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(DependSuffix): src/vc_sf_idk_21451_X_2010_tim_comm_module.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(DependSuffix) -MM src/vc_sf_idk_21451_X_2010_tim_comm_module.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(PreprocessSuffix): src/vc_sf_idk_21451_X_2010_tim_comm_module.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21451_X_2010_tim_comm_module.cpp$(PreprocessSuffix) src/vc_sf_idk_21451_X_2010_tim_comm_module.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_errors.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_errors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_errors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_errors.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_errors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_errors.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_errors.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(ObjectSuffix): src/vc_sf_idk_21450_2010_ncap_services.cpp $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/vc_sf_idk_21450_2010_ncap_services.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(DependSuffix): src/vc_sf_idk_21450_2010_ncap_services.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(DependSuffix) -MM src/vc_sf_idk_21450_2010_ncap_services.cpp

$(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(PreprocessSuffix): src/vc_sf_idk_21450_2010_ncap_services.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_vc_sf_idk_21450_2010_ncap_services.cpp$(PreprocessSuffix) src/vc_sf_idk_21450_2010_ncap_services.cpp

$(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(ObjectSuffix): things2pack/src/vc-things2pack-service.cpp $(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/src/vc-things2pack-service.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(DependSuffix): things2pack/src/vc-things2pack-service.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(DependSuffix) -MM things2pack/src/vc-things2pack-service.cpp

$(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(PreprocessSuffix): things2pack/src/vc-things2pack-service.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_src_vc-things2pack-service.cpp$(PreprocessSuffix) things2pack/src/vc-things2pack-service.cpp

$(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(ObjectSuffix): things2pack/src/vc_sf_things2pack.cpp $(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/src/vc_sf_things2pack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(DependSuffix): things2pack/src/vc_sf_things2pack.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(DependSuffix) -MM things2pack/src/vc_sf_things2pack.cpp

$(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(PreprocessSuffix): things2pack/src/vc_sf_things2pack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_src_vc_sf_things2pack.cpp$(PreprocessSuffix) things2pack/src/vc_sf_things2pack.cpp

$(IntermediateDirectory)/src_idk-json11_json11.cpp$(ObjectSuffix): src/idk-json11/json11.cpp $(IntermediateDirectory)/src_idk-json11_json11.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/idk-json11/json11.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_idk-json11_json11.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_idk-json11_json11.cpp$(DependSuffix): src/idk-json11/json11.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_idk-json11_json11.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_idk-json11_json11.cpp$(DependSuffix) -MM src/idk-json11/json11.cpp

$(IntermediateDirectory)/src_idk-json11_json11.cpp$(PreprocessSuffix): src/idk-json11/json11.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_idk-json11_json11.cpp$(PreprocessSuffix) src/idk-json11/json11.cpp

$(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(ObjectSuffix): src/utils/vc_sf_utils.cpp $(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/utils/vc_sf_utils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(DependSuffix): src/utils/vc_sf_utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(DependSuffix) -MM src/utils/vc_sf_utils.cpp

$(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(PreprocessSuffix): src/utils/vc_sf_utils.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_utils_vc_sf_utils.cpp$(PreprocessSuffix) src/utils/vc_sf_utils.cpp

$(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(ObjectSuffix): src/utils/vc_sf_time_utils.cpp $(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/utils/vc_sf_time_utils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(DependSuffix): src/utils/vc_sf_time_utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(DependSuffix) -MM src/utils/vc_sf_time_utils.cpp

$(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(PreprocessSuffix): src/utils/vc_sf_time_utils.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_utils_vc_sf_time_utils.cpp$(PreprocessSuffix) src/utils/vc_sf_time_utils.cpp

$(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(ObjectSuffix): src/foundation/qlib/vc_sf_reliable_redis_q.cpp $(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/foundation/qlib/vc_sf_reliable_redis_q.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(DependSuffix): src/foundation/qlib/vc_sf_reliable_redis_q.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(DependSuffix) -MM src/foundation/qlib/vc_sf_reliable_redis_q.cpp

$(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(PreprocessSuffix): src/foundation/qlib/vc_sf_reliable_redis_q.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_foundation_qlib_vc_sf_reliable_redis_q.cpp$(PreprocessSuffix) src/foundation/qlib/vc_sf_reliable_redis_q.cpp

$(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(ObjectSuffix): opc/src/vc_sf_idk_opc_client.cpp $(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/opc/src/vc_sf_idk_opc_client.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(DependSuffix): opc/src/vc_sf_idk_opc_client.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(DependSuffix) -MM opc/src/vc_sf_idk_opc_client.cpp

$(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(PreprocessSuffix): opc/src/vc_sf_idk_opc_client.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opc_src_vc_sf_idk_opc_client.cpp$(PreprocessSuffix) opc/src/vc_sf_idk_opc_client.cpp

$(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(ObjectSuffix): erp/src/vc_sf_idk_erp_client.cpp $(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/erp/src/vc_sf_idk_erp_client.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(DependSuffix): erp/src/vc_sf_idk_erp_client.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(DependSuffix) -MM erp/src/vc_sf_idk_erp_client.cpp

$(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(PreprocessSuffix): erp/src/vc_sf_idk_erp_client.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/erp_src_vc_sf_idk_erp_client.cpp$(PreprocessSuffix) erp/src/vc_sf_idk_erp_client.cpp

$(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(ObjectSuffix): things2pack/liquid-oil/src/vc_sf_liquid_oil_rule_engine.cpp $(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/liquid-oil/src/vc_sf_liquid_oil_rule_engine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(DependSuffix): things2pack/liquid-oil/src/vc_sf_liquid_oil_rule_engine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(DependSuffix) -MM things2pack/liquid-oil/src/vc_sf_liquid_oil_rule_engine.cpp

$(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(PreprocessSuffix): things2pack/liquid-oil/src/vc_sf_liquid_oil_rule_engine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_liquid-oil_src_vc_sf_liquid_oil_rule_engine.cpp$(PreprocessSuffix) things2pack/liquid-oil/src/vc_sf_liquid_oil_rule_engine.cpp

$(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(ObjectSuffix): things2pack/analytics/src/vc_sf_things2pack_rstats.cpp $(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/analytics/src/vc_sf_things2pack_rstats.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(DependSuffix): things2pack/analytics/src/vc_sf_things2pack_rstats.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(DependSuffix) -MM things2pack/analytics/src/vc_sf_things2pack_rstats.cpp

$(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(PreprocessSuffix): things2pack/analytics/src/vc_sf_things2pack_rstats.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_analytics_src_vc_sf_things2pack_rstats.cpp$(PreprocessSuffix) things2pack/analytics/src/vc_sf_things2pack_rstats.cpp

$(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(ObjectSuffix): things2pack/liquid-milk/src/vc_sf_liquid_milk_rule_engine.cpp $(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/liquid-milk/src/vc_sf_liquid_milk_rule_engine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(DependSuffix): things2pack/liquid-milk/src/vc_sf_liquid_milk_rule_engine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(DependSuffix) -MM things2pack/liquid-milk/src/vc_sf_liquid_milk_rule_engine.cpp

$(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(PreprocessSuffix): things2pack/liquid-milk/src/vc_sf_liquid_milk_rule_engine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_liquid-milk_src_vc_sf_liquid_milk_rule_engine.cpp$(PreprocessSuffix) things2pack/liquid-milk/src/vc_sf_liquid_milk_rule_engine.cpp

$(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(ObjectSuffix): things2pack/recorder/src/vc_sf_things2pack_recorder.cpp $(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/recorder/src/vc_sf_things2pack_recorder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(DependSuffix): things2pack/recorder/src/vc_sf_things2pack_recorder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(DependSuffix) -MM things2pack/recorder/src/vc_sf_things2pack_recorder.cpp

$(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(PreprocessSuffix): things2pack/recorder/src/vc_sf_things2pack_recorder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_recorder_src_vc_sf_things2pack_recorder.cpp$(PreprocessSuffix) things2pack/recorder/src/vc_sf_things2pack_recorder.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(ObjectSuffix): things2pack/src/sample-data/vc_sf_things2pack_opc_config.cpp $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/src/sample-data/vc_sf_things2pack_opc_config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(DependSuffix): things2pack/src/sample-data/vc_sf_things2pack_opc_config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(DependSuffix) -MM things2pack/src/sample-data/vc_sf_things2pack_opc_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(PreprocessSuffix): things2pack/src/sample-data/vc_sf_things2pack_opc_config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_opc_config.cpp$(PreprocessSuffix) things2pack/src/sample-data/vc_sf_things2pack_opc_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(ObjectSuffix): things2pack/src/sample-data/vc_sf_things2pack_assets_config.cpp $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/src/sample-data/vc_sf_things2pack_assets_config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(DependSuffix): things2pack/src/sample-data/vc_sf_things2pack_assets_config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(DependSuffix) -MM things2pack/src/sample-data/vc_sf_things2pack_assets_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(PreprocessSuffix): things2pack/src/sample-data/vc_sf_things2pack_assets_config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_assets_config.cpp$(PreprocessSuffix) things2pack/src/sample-data/vc_sf_things2pack_assets_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(ObjectSuffix): things2pack/src/sample-data/vc_sf_things2pack_erp_config.cpp $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/src/sample-data/vc_sf_things2pack_erp_config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(DependSuffix): things2pack/src/sample-data/vc_sf_things2pack_erp_config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(DependSuffix) -MM things2pack/src/sample-data/vc_sf_things2pack_erp_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(PreprocessSuffix): things2pack/src/sample-data/vc_sf_things2pack_erp_config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_erp_config.cpp$(PreprocessSuffix) things2pack/src/sample-data/vc_sf_things2pack_erp_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(ObjectSuffix): things2pack/src/sample-data/vc_sf_things2pack_product_rules_config.cpp $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/src/sample-data/vc_sf_things2pack_product_rules_config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(DependSuffix): things2pack/src/sample-data/vc_sf_things2pack_product_rules_config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(DependSuffix) -MM things2pack/src/sample-data/vc_sf_things2pack_product_rules_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(PreprocessSuffix): things2pack/src/sample-data/vc_sf_things2pack_product_rules_config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_product_rules_config.cpp$(PreprocessSuffix) things2pack/src/sample-data/vc_sf_things2pack_product_rules_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(ObjectSuffix): things2pack/src/sample-data/vc_sf_things2pack_preset_cyber_physical_config.cpp $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/src/sample-data/vc_sf_things2pack_preset_cyber_physical_config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(DependSuffix): things2pack/src/sample-data/vc_sf_things2pack_preset_cyber_physical_config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(DependSuffix) -MM things2pack/src/sample-data/vc_sf_things2pack_preset_cyber_physical_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(PreprocessSuffix): things2pack/src/sample-data/vc_sf_things2pack_preset_cyber_physical_config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_preset_cyber_physical_config.cpp$(PreprocessSuffix) things2pack/src/sample-data/vc_sf_things2pack_preset_cyber_physical_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(ObjectSuffix): things2pack/src/sample-data/vc_sf_things2pack_transducer_defs_config.cpp $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/things2pack/src/sample-data/vc_sf_things2pack_transducer_defs_config.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(DependSuffix): things2pack/src/sample-data/vc_sf_things2pack_transducer_defs_config.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(DependSuffix) -MM things2pack/src/sample-data/vc_sf_things2pack_transducer_defs_config.cpp

$(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(PreprocessSuffix): things2pack/src/sample-data/vc_sf_things2pack_transducer_defs_config.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/things2pack_src_sample-data_vc_sf_things2pack_transducer_defs_config.cpp$(PreprocessSuffix) things2pack/src/sample-data/vc_sf_things2pack_transducer_defs_config.cpp

$(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(ObjectSuffix): src/db/redis/vc_sf_redis_client_factory.cpp $(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/db/redis/vc_sf_redis_client_factory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(DependSuffix): src/db/redis/vc_sf_redis_client_factory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(DependSuffix) -MM src/db/redis/vc_sf_redis_client_factory.cpp

$(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(PreprocessSuffix): src/db/redis/vc_sf_redis_client_factory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_db_redis_vc_sf_redis_client_factory.cpp$(PreprocessSuffix) src/db/redis/vc_sf_redis_client_factory.cpp

$(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(ObjectSuffix): src/transducer-transports/src/vc_sf_modbus_tcp_client.cpp $(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/transducer-transports/src/vc_sf_modbus_tcp_client.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(DependSuffix): src/transducer-transports/src/vc_sf_modbus_tcp_client.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(DependSuffix) -MM src/transducer-transports/src/vc_sf_modbus_tcp_client.cpp

$(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(PreprocessSuffix): src/transducer-transports/src/vc_sf_modbus_tcp_client.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_transducer-transports_src_vc_sf_modbus_tcp_client.cpp$(PreprocessSuffix) src/transducer-transports/src/vc_sf_modbus_tcp_client.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(ObjectSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_length_transducer.cpp $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/transducer-templates/src/vc_sf_idk_21450_2010_length_transducer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(DependSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_length_transducer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(DependSuffix) -MM src/transducer-templates/src/vc_sf_idk_21450_2010_length_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(PreprocessSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_length_transducer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_length_transducer.cpp$(PreprocessSuffix) src/transducer-templates/src/vc_sf_idk_21450_2010_length_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(ObjectSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_mass_transducer.cpp $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/transducer-templates/src/vc_sf_idk_21450_2010_mass_transducer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(DependSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_mass_transducer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(DependSuffix) -MM src/transducer-templates/src/vc_sf_idk_21450_2010_mass_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(PreprocessSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_mass_transducer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_mass_transducer.cpp$(PreprocessSuffix) src/transducer-templates/src/vc_sf_idk_21450_2010_mass_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(ObjectSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_pressure_transducer.cpp $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/transducer-templates/src/vc_sf_idk_21450_2010_pressure_transducer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(DependSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_pressure_transducer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(DependSuffix) -MM src/transducer-templates/src/vc_sf_idk_21450_2010_pressure_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(PreprocessSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_pressure_transducer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_pressure_transducer.cpp$(PreprocessSuffix) src/transducer-templates/src/vc_sf_idk_21450_2010_pressure_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(ObjectSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_thickness_transducer.cpp $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/transducer-templates/src/vc_sf_idk_21450_2010_thickness_transducer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(DependSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_thickness_transducer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(DependSuffix) -MM src/transducer-templates/src/vc_sf_idk_21450_2010_thickness_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(PreprocessSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_thickness_transducer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_thickness_transducer.cpp$(PreprocessSuffix) src/transducer-templates/src/vc_sf_idk_21450_2010_thickness_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(ObjectSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_vision_transducer.cpp $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/transducer-templates/src/vc_sf_idk_21450_2010_vision_transducer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(DependSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_vision_transducer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(DependSuffix) -MM src/transducer-templates/src/vc_sf_idk_21450_2010_vision_transducer.cpp

$(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(PreprocessSuffix): src/transducer-templates/src/vc_sf_idk_21450_2010_vision_transducer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_transducer-templates_src_vc_sf_idk_21450_2010_vision_transducer.cpp$(PreprocessSuffix) src/transducer-templates/src/vc_sf_idk_21450_2010_vision_transducer.cpp

$(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(ObjectSuffix): opc/packml/src/vc_sf_idk_opc_packml_client.cpp $(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/opc/packml/src/vc_sf_idk_opc_packml_client.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(DependSuffix): opc/packml/src/vc_sf_idk_opc_packml_client.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(DependSuffix) -MM opc/packml/src/vc_sf_idk_opc_packml_client.cpp

$(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(PreprocessSuffix): opc/packml/src/vc_sf_idk_opc_packml_client.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/opc_packml_src_vc_sf_idk_opc_packml_client.cpp$(PreprocessSuffix) opc/packml/src/vc_sf_idk_opc_packml_client.cpp

$(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(ObjectSuffix): src/system/global/security/vc_sf_security_errors.cpp $(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/system/global/security/vc_sf_security_errors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(DependSuffix): src/system/global/security/vc_sf_security_errors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(DependSuffix) -MM src/system/global/security/vc_sf_security_errors.cpp

$(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(PreprocessSuffix): src/system/global/security/vc_sf_security_errors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_system_global_security_vc_sf_security_errors.cpp$(PreprocessSuffix) src/system/global/security/vc_sf_security_errors.cpp

$(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(ObjectSuffix): src/system/global/wsn/vc_sf_es_errors.cpp $(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/i40apps/Industry-4.0/Picominer-2.0/Picominer-EGW/iot-hub/IoT-Hub/src/system/global/wsn/vc_sf_es_errors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(DependSuffix): src/system/global/wsn/vc_sf_es_errors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(DependSuffix) -MM src/system/global/wsn/vc_sf_es_errors.cpp

$(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(PreprocessSuffix): src/system/global/wsn/vc_sf_es_errors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_system_global_wsn_vc_sf_es_errors.cpp$(PreprocessSuffix) src/system/global/wsn/vc_sf_es_errors.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


