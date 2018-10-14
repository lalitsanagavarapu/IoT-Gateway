LOCAL_PATH := $(call my-dir)

########################################
# idk -> is soft link to appropriate version of the IDK build folder.
########################################


# json11 C++ JSON Library
include $(CLEAR_VARS)
LOCAL_MODULE := json11
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include \
                           $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)

# Sodium Library
include $(CLEAR_VARS)
LOCAL_MODULE := libsodium-1.0.11
LOCAL_SRC_FILES := idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/lib/libsodium.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include \
                           $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include/sodium
include $(PREBUILT_STATIC_LIBRARY)

# ZeroMQ Library
include $(CLEAR_VARS)
LOCAL_MODULE := zeromq-4.1.5
LOCAL_SRC_FILES := idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/lib/libzmq.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)


# Crypto Library
include $(CLEAR_VARS)
LOCAL_MODULE := crypto-1.0.2j
LOCAL_SRC_FILES := idk/iHubble/openssl-1.0.2j/$(APP_PLATFORM)/$(APP_ABI)/lib/libcrypto.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/openssl-1.0.2g/$(APP_PLATFORM)/$(APP_ABI)/include/openssl \
                           $(LOCAL_PATH)/idk/iHubble/openssl-1.0.2g/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# SSL Library
include $(CLEAR_VARS)
LOCAL_MODULE := ssl-1.0.2j
LOCAL_SRC_FILES := idk/iHubble/openssl-1.0.2j/$(APP_PLATFORM)/$(APP_ABI)/lib/libssl.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/openssl-1.0.2j/$(APP_PLATFORM)/$(APP_ABI)/include/openssl \
                           $(LOCAL_PATH)/idk/iHubble/openssl-1.0.2j/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# CURL Library
include $(CLEAR_VARS)
LOCAL_MODULE := curl-7.50.3
LOCAL_SRC_FILES := idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/lib/libcurl.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include/curl \
                           $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# HTTPD Library
include $(CLEAR_VARS)
LOCAL_MODULE := libmicrohttpd-0.9.51
LOCAL_SRC_FILES := idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/lib/libmicrohttpd.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)


# URI Parser Library
include $(CLEAR_VARS)
LOCAL_MODULE := uriparser-0.8.4
LOCAL_SRC_FILES := idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/lib/liburiparser.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include/uriparser \
                           $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# MODBUS Library
include $(CLEAR_VARS)
LOCAL_MODULE := libmodbus-3.1.4
LOCAL_SRC_FILES := idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/lib/libmodbus.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include/modbus \
                           $(LOCAL_PATH)/idk/iHubble/$(LOCAL_MODULE)/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# POCO Foundation Library
include $(CLEAR_VARS)
LOCAL_MODULE := pocofoundation-1.7.5
LOCAL_SRC_FILES := idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/lib/libPocoFoundation.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include/Poco \
                           $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# POCO Utils Library
include $(CLEAR_VARS)
LOCAL_MODULE := pocoutils-1.7.5
LOCAL_SRC_FILES := idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/lib/libPocoUtil.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include/Poco \
                           $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# POCO Network Library
include $(CLEAR_VARS)
LOCAL_MODULE := poconet-1.7.5
LOCAL_SRC_FILES := idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/lib/libPocoNet.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include/Poco \
                           $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# POCO JSON Library
include $(CLEAR_VARS)
LOCAL_MODULE := pocojson-1.7.5
LOCAL_SRC_FILES := idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/lib/libPocoJSON.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include/Poco \
                           $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# POCO XML Library
include $(CLEAR_VARS)
LOCAL_MODULE := pocoxml-1.7.5
LOCAL_SRC_FILES := idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/lib/libPocoXML.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include/Poco \
                           $(LOCAL_PATH)/idk/iHubble/poco-1.7.5/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# GSL Library
include $(CLEAR_VARS)
LOCAL_MODULE := gsl-2.2
LOCAL_SRC_FILES := idk/iHubble/gsl-2.2/$(APP_PLATFORM)/$(APP_ABI)/lib/libgsl.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/gsl-2.2/$(APP_PLATFORM)/$(APP_ABI)/include/gsl \
                           $(LOCAL_PATH)/idk/iHubble/gsl-2.2/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# GSL Library CBLAS
include $(CLEAR_VARS)
LOCAL_MODULE := gsl-2.2-cblas
LOCAL_SRC_FILES := idk/iHubble/gsl-2.2/$(APP_PLATFORM)/$(APP_ABI)/lib/libgslcblas.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/idk/iHubble/gsl-2.2/$(APP_PLATFORM)/$(APP_ABI)/include/gsl \
                           $(LOCAL_PATH)/idk/iHubble/gsl-2.2/$(APP_PLATFORM)/$(APP_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

# Application 
include $(CLEAR_VARS)
TARGET_ARCH  := armeabi-v7a
TARGET_ABI   := android-21-armeabi-v7a
LOCAL_ARM_MODE := arm
LOCAL_MODULE := vc_iot_platform_0.4.0
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include  \
                           $(LOCAL_PATH)/things2pack/include  \
                           $(LOCAL_PATH)/idk \
                           $(LOCAL_PATH)/idk/iHubble 
LOCAL_CFLAGS += -DIDK_PLATFORM_ANDROID_21_ARMEABI_V7A \
                -DIDK_PLATFORM_FAMILY_THINGS2PACK \
                -I$(LOCAL_PATH)/include \
                -I$(LOCAL_PATH)/things2pack/include \
                -I$(LOCAL_PATH)/things2pack/liquid-milk/include \
                -I$(LOCAL_PATH)/things2pack/liquid-oil/include \
                -I$(LOCAL_PATH)/src/transducer-templates/include \
                -I$(LOCAL_PATH)/src/transducer-transports/include \
                -I$(LOCAL_PATH)/things2pack/recorder/include \
                -I$(LOCAL_PATH)/things2pack/analytics/include \
                -I$(LOCAL_PATH)/opc/include  \
                -I$(LOCAL_PATH)/erp/include  \
                -I$(LOCAL_PATH)/opc/packml/include

LOCAL_CFLAGS += -g -Wall -fPIC -Os \
                -W -Wno-unused-parameter -Wuninitialized \
                -std=c++11

# TARGET_CFLAGS  =  -mthumb -march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16 -marm -Os
# TARGET_LDFLAGS =  -Wl,--fix-cortex-a8 

LOCAL_SRC_FILES := src/vc_sf_idk_21450_2010_transducer_analog_interface.cpp \
                   src/vc_sf_idk_21450_2010_transducer.cpp \
                   src/vc_sf_idk_21450_2010_transducer_measurement_interface.cpp \
                   src/vc_sf_idk_21450_2010_errors.cpp \
                   src/vc_sf_idk_21450_2010_transducer_service_apis.cpp \
                   src/vc_sf_idk_21450_2010_sf_main.cpp  \
                   src/vc_sf_idk_21450_2010_transducer_signal_conditioner.cpp \
                   src/vc_sf_idk_21450_2010_ncap_services.cpp \
                   src/vc_sf_idk_21451_2010_ncap_controller.cpp \
                   src/vc_sf_idk_21450_2010_tim_controller.cpp \
                   src/vc_sf_idk_21451_X_2010_ncap_comm_module.cpp \
                   src/vc_sf_idk_21450_2010_tim_services.cpp \
                   src/vc_sf_idk_21451_X_2010_tim_comm_module.cpp \
                   src/vc_sf_idk_21450_2010_transducer_a2d_d2a.cpp \
                   src/vc_sf_idk_utils.cpp \
                   erp/src/vc_sf_idk_erp_client.cpp \
                   opc/src/vc_sf_idk_opc_client.cpp \
                   opc/packml/src/vc_sf_idk_opc_packml_client.cpp \
                   src/transducer-templates/src/vc_sf_idk_21450_2010_pressure_transducer.cpp \
                   src/transducer-templates/src/vc_sf_idk_21450_2010_length_transducer.cpp \
                   src/transducer-templates/src/vc_sf_idk_21450_2010_mass_transducer.cpp \
                   src/transducer-templates/src/vc_sf_idk_21450_2010_thickness_transducer.cpp \
                   src/transducer-templates/src/vc_sf_idk_21450_2010_vision_transducer.cpp \
                   src/transducer-transports/src/vc_sf_modbus_tcp_client.cpp \
                   src/idk-json11/json11.cpp \
                   things2pack/liquid-milk/src/vc_sf_liquid_milk_rule_engine.cpp \
                   things2pack/liquid-oil/src/vc_sf_liquid_oil_rule_engine.cpp \
                   things2pack/src/vc-things2pack-service.cpp \
                   things2pack/src/vc_sf_things2pack.cpp \
                   things2pack/src/vc_sf_things2pack_assets_config.cpp \
                   things2pack/src/vc_sf_things2pack_product_rules_config.cpp \
                   things2pack/src/vc_sf_things2pack_transducer_defs_config.cpp \
                   things2pack/src/vc_sf_things2pack_preset_cyber_physical_config.cpp \
                   things2pack/src/vc_sf_things2pack_erp_config.cpp \
                   things2pack/src/vc_sf_things2pack_opc_config.cpp \
                   things2pack/analytics/src/vc_sf_things2pack_rstats.cpp
                   
# things2pack/recorder/src/vc_sf_things2pack_recorder.cpp is not for Android as it involves HDF5.
# Use sqlite recorder for Android build.
                   
LOCAL_LDFLAGS   += -L$(call host-path,$(LOCAL_PATH)/lib)
LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog -ldl -lz -lm


LOCAL_SHARED_LIBRARIES := 
LOCAL_STATIC_LIBRARIES := curl-7.50.3 \
			  ssl-1.0.2j crypto-1.0.2j \
			  libmicrohttpd-0.9.51 \
                          pocofoundation-1.7.5 pocoutils-1.7.5 pocojson-1.7.5 pocoxml-1.7.5 poconet-1.7.5 \
                          gsl-2.2 gsl-2.2-cblas \
                          zeromq-4.1.5 libsodium-1.0.11 \
                          uriparser-0.8.4 \
                          libmodbus-3.1.4

include $(BUILD_SHARED_LIBRARY)

