ENABLE_APP :=0
#####################################wfdServiceStub####################################
LOCAL_PATH :=$(call my-dir)
include $(CLEAR_VARS)
ifeq ($(TARGET_PRODUCT)_$(TARGET_BUILD_VARIANT), full_eng)
LOCAL_CFLAGS += -DUT_GTEST_FULL_ENG                                                                                                                        
endif

LOCAL_MODULE        := wfdService
LOCAL_MODULE_TAGS   := eng
LOCAL_AIDL_TARGET   := stub

LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
		    frameworks/service/miracastservice/include \
		    frameworks/service/miracastservice/common \
		    frameworks/service/miracastservice/src/include \
		    frameworks/service/miracastservice/src/stub \
		    frameworks/service/miracastservice/src \
		    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/stub  \
		    suntec/miracast/wfd/publicinc \
		    suntec/miracast/wfd \
		    suntec/miracast/threadlib/include \
		    frameworks/service/wifiservice/include \
		    frameworks/service/wifiservice/include/sub \
		    frameworks/service/wifiservice/include/proxy \
		    frameworks/service/btservice/include \
		    frameworks/service/btservice/include/sub \
		    frameworks/service/btservice/include/proxy \
		    platform/service/mediaplayerservice/include/ \
    		    platform/service/mediaplayerservice/platform/include \
    		    platform/service/mediaplayerservice/platform/include/mediautils \
    		    platform/service/mediaplayerservice/unifiedplayer/include \
    		    platform/service/audioservice/include \
		    platform/base/indlude \
                    platform/media/include \
		    platform/service/settingservice/include \
		    platform/service/inputmanager/include \
		    frameworks/service/carplayservice/include \
		    frameworks/service/carlifeservice/include \
		    system/hallib/interface/include \
			


LOCAL_SRC_FILES := \
		   src/main.cpp \
                   src/wfdService.cpp \
		   src/wfdServiceStub.cpp \
		   src/WFDServiceManager.cpp \
                   src/WFDServiceStackListen.cpp \
		   src/WFDServiceMultiListen.cpp \
		   src/WFDServiceWifiListen.cpp \
		   src/WFDServicePlayCallback.cpp \
		   src/WFDServiceAVCtr.cpp \
		   src/WFDServiceSetting.cpp \
		   src/WFDServiceInputListen.cpp \
		   src/stub/WFDServiceReplier.cpp \
		   src/stub/WFDServiceStubBase.cpp \
	           src/DiagLog/WFDServiceDTLog.cpp \
# 		   aidl/IWFDService.aidl \ 

LOCAL_LDLIBS += -lpthread 

ifeq ($(ENABLE_APP), 1)
LOCAL_CFLAGS += -DWFD_APP
endif


LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils  \
                          libutils liblog libprocess libwfd libthread_wfd \
			  libwifiServiceSub libwifiServiceProxy\
			  libnmmediaplayer libnmmputils libmlooper \
			  libInputManagerProxy libsettingproxy \
			  libbtserviceproxy libbtservicesub libcarlifeservicesub libcarplayproxy libnihallib \

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_MODULE        := libwfdTest
LOCAL_MODULE_TAGS   := eng

LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
		    frameworks/service/miracastservice/include \
		    frameworks/service/miracastservice/common \
		    frameworks/service/miracastservice/src/include \
		    frameworks/service/miracastservice/src/stub \
		    frameworks/service/miracastservice/src \
		    suntec/miracast/wfd/publicinc \
		    suntec/miracast/wfd \
		    suntec/miracast/threadlib/include \
		    frameworks/service/wifiservice/include \
		    frameworks/service/wifiservice/include/sub \
		    frameworks/service/wifiservice/include/proxy \
		    frameworks/service/btservice/include \
		    frameworks/service/btservice/include/sub \
		    frameworks/service/btservice/include/proxy \
		    platform/service/mediaplayerservice/include/ \
    		    platform/service/mediaplayerservice/platform/include \
    		    platform/service/mediaplayerservice/platform/include/mediautils \
    		    platform/service/mediaplayerservice/unifiedplayer/include \
    		    platform/service/audioservice/include \
		    platform/base/indlude \
                    platform/media/include \
		    platform/service/settingservice/include \
		    platform/service/inputmanager/include \
		    frameworks/service/carplayservice/include \
		    frameworks/service/carlifeservice/include \
		    system/hallib/interface/include \


LOCAL_SRC_FILES := src/wfdService.cpp \
		   src/wfdServiceStub.cpp \
		   src/WFDServiceManager.cpp \
                   src/WFDServiceStackListen.cpp \
		   src/WFDServiceMultiListen.cpp \
		   src/WFDServiceWifiListen.cpp \
		   src/WFDServicePlayCallback.cpp \
		   src/WFDServiceAVCtr.cpp \
		   src/WFDServiceSetting.cpp \
		   src/WFDServiceInputListen.cpp \
		   src/stub/WFDServiceReplier.cpp \
		   src/stub/WFDServiceStubBase.cpp\
                   src/proxy/WFDServiceProxyBase.cpp\
		   src/sub/WFDServiceSub.cpp\
		   src/DiagLog/WFDServiceDTLog.cpp \
# 		   aidl/IWFDService.aidl \ 

LOCAL_LDLIBS += -lpthread 

ifeq ($(ENABLE_APP), 1)
LOCAL_CFLAGS += -DWFD_APP
endif

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils  \
                          libutils liblog libprocess libwfd libthread_wfd \
			  libwifiServiceSub libwifiServiceProxy\
			  libnmmediaplayer libmlooper libInputManagerProxy libsettingproxy \
			  libbtserviceproxy libbtservicesub libcarlifeservicesub libcarplayproxy libnihallib\
	                  libnmmputils\


include $(BUILD_SHARED_LIBRARY)
##################################libwfdServiceproxy############################
include $(CLEAR_VARS)

LOCAL_MODULE        := libwfdServiceproxy
LOCAL_MODULE_TAGS   := optional
LOCAL_AIDL_TARGET   := proxy

LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
                    frameworks/service/miracastservice/include \

#LOCAL_SRC_FILES := aidl/IWFDService.aidl
LOCAL_SRC_FILES :=  src/proxy/WFDServiceProxyBase.cpp

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils liblog 

include $(BUILD_SHARED_LIBRARY)

#################################libwfdServicesub#############################
include $(CLEAR_VARS)

LOCAL_MODULE        := libwfdServicesub
LOCAL_MODULE_TAGS   := optional
LOCAL_AIDL_TARGET   := sub

LOCAL_C_INCLUDES := frameworks/native/include \
                    system/core/include \
                    platform/base/include \
                    platform/base/servicebase \
                    $(LOCAL_PATH)/include \

#LOCAL_SRC_FILES := aidl/IWFDService.aidl
LOCAL_SRC_FILES := src/sub/WFDServiceSub.cpp

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils liblog 

include $(BUILD_SHARED_LIBRARY)


#include $(call first-makefiles-under,$(LOCAL_PATH))

###############################wfdProxyTst############################
include $(CLEAR_VARS)

LOCAL_MODULE        := tstWfdProxy
LOCAL_MODULE_TAGS   := eng

LOCAL_C_INCLUDES := frameworks/native/include \
                    system/core/include \
                    platform/base/include \
                    platform/base/servicebase \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/proxy  \
                    $(LOCAL_PATH)/src/include    \
                    $(LOCAL_PATH)/include/sub \



LOCAL_SRC_FILES := test/tstWFDServiceProxy.cpp \

LOCAL_SHARED_LIBRARIES := libservicebase libprocess libbinder libcutils libutils liblog libwfdServiceproxy libwfdServicesub

include $(BUILD_EXECUTABLE)

###############################wfdSigma############################
include $(CLEAR_VARS)

LOCAL_MODULE        := libSigma
LOCAL_MODULE_TAGS   := eng

LOCAL_C_INCLUDES := frameworks/native/include \
                    system/core/include \
                    platform/base/include \
                    platform/base/servicebase \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/proxy  \
                    $(LOCAL_PATH)/src/include    \
                    $(LOCAL_PATH)/include/sub \



LOCAL_SRC_FILES := test/tstSigma.cpp \

LOCAL_SHARED_LIBRARIES := libservicebase libprocess libbinder libcutils libutils liblog libwfdServiceproxy libwfdServicesub

include $(BUILD_SHARED_LIBRARY)

CURR_PATH := $(LOCAL_PATH)

include $(LOCAL_PATH)/gtest/Goni.mk
