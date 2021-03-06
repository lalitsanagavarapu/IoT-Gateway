# -*- CMakeLists.txt generated by CodeLite IDE. Do not edit by hand -*-

cmake_minimum_required(VERSION 2.8.11)

project(iiot-gateway)

# Define some variables
set(PROJECT_PATH "${CMAKE_SOURCE_DIR}/../iiot-gateway")



#{{{{ User Code 1
# Place your code here
#}}}}

include_directories(
    .
    ./idk
    ./include
    ./src/transducer-templates/include
    ./src/transducer-transports/include
    ./things2pack/include
    ./things2pack/liquid-milk/include
    ./things2pack/liquid-oil/include
    ./things2pack/recorder/include
    ./idk/iHubble/poco-1.7.5/linux/include/Poco
    ./idk/iHubble/poco-1.7.5/linux/include
    ./idk/iHubble/zeromq-4.1.5/linux/include
    ./idk/iHubble/libmodbus-3.1.4/linux/include/modbus
    ./idk/iHubble/gsl-2.2/linux/include
    ./idk/iHubble/root-6.06.08/linux/include/root
    ./things2pack/analytics/include
    ./opc/include
    ./opc/packml/include
    ./erp/include
    ./oam/include
    .

)


# Compiler options
add_definitions(-std=c++11)
add_definitions(-g)
add_definitions(-O0)
add_definitions(-Wall)
add_definitions(
    -DIDK_PLATFORM_LINUX
    -DIDK_PLATFORM_FAMILY_THINGS2PACK
)


# Linker options


if(WIN32)
    # Resource options
endif(WIN32)

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L. -L./idk-libs/linux/lib ")

# Define the CXX sources
set ( CXX_SRCS
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_transducer_analog_interface.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_sf_main.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21451_2010_ncap_controller.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_transducer_measurement_interface.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_transducer_service_apis.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_tim_services.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21451_X_2010_ncap_comm_module.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_utils.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_transducer.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_tim_controller.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21451_X_2010_tim_comm_module.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_errors.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/vc_sf_idk_21450_2010_ncap_services.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/src/vc_sf_things2pack_opc_config.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/src/vc_sf_things2pack_assets_config.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/src/vc_sf_things2pack_erp_config.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/src/vc-things2pack-service.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/src/vc_sf_things2pack.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/src/vc_sf_things2pack_product_rules_config.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/src/vc_sf_things2pack_preset_cyber_physical_config.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/src/vc_sf_things2pack_transducer_defs_config.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/idk-json11/json11.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/opc/src/vc_sf_idk_opc_client.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/erp/src/vc_sf_idk_erp_client.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/liquid-oil/src/vc_sf_liquid_oil_rule_engine.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/analytics/src/vc_sf_things2pack_rstats.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/liquid-milk/src/vc_sf_liquid_milk_rule_engine.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/things2pack/recorder/src/vc_sf_things2pack_recorder.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/transducer-transports/src/vc_sf_modbus_tcp_client.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/transducer-templates/src/vc_sf_idk_21450_2010_length_transducer.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/transducer-templates/src/vc_sf_idk_21450_2010_mass_transducer.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/transducer-templates/src/vc_sf_idk_21450_2010_pressure_transducer.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/transducer-templates/src/vc_sf_idk_21450_2010_thickness_transducer.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/src/transducer-templates/src/vc_sf_idk_21450_2010_vision_transducer.cpp
    ${CMAKE_SOURCE_DIR}/../iiot-gateway/opc/packml/src/vc_sf_idk_opc_packml_client.cpp
)

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS
    " -std=c++11 -g -O0 -Wall")

if(WIN32)
    enable_language(RC)
    set(CMAKE_RC_COMPILE_OBJECT
        "<CMAKE_RC_COMPILER> ${RC_OPTIONS} -O coff -i <SOURCE> -o <OBJECT>")
endif(WIN32)



#{{{{ User Code 2
# Place your code here
#}}}}

add_executable(iiot-gateway ${RC_SRCS} ${CXX_SRCS} ${C_SRCS})
target_link_libraries(iiot-gateway ${LINK_OPTIONS})

target_link_libraries(iiot-gateway
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libcurl.a
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libmicrohttpd.a
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/liburiparser.a
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libPocoNet.a
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libPocoFoundation.a
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libzmq.a
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libsodium.a
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libmodbus.a
    pthread
    ssl
    crypto
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libhdf5.a
    dl
    z
    /home/maruthi/4.0-picominer/thing2pack-gw/iiot-gateway/idk-libs/linux/lib/libgsl.a
    cblas
    atlas
    m
)



#{{{{ User Code 3
# Place your code here
#}}}}

