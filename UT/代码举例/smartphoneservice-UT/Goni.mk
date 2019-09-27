#####################################wfdServiceStub####################################
LOCAL_PATH :=$(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE        := ioslauncher 
LOCAL_MODULE_TAGS   := user
LOCAL_AIDL_TARGET   := stub

LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
                    external/sqlcipher/ \
                    frameworks/service/smartphoneservice/include \
                    frameworks/service/smartphoneservice/\
                    frameworks/service/smartphoneservice/common \
                    frameworks/service/smartphoneservice/src/include \
                    frameworks/service/smartphoneservice/src/stub \
                    frameworks/service/smartphoneservice/src \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/stub  \
                    platform/media/include \
                    platform/service/connectmanager/include \
                    system/hallib/interface/include \
                    frameworks/service/diagservice/include \



LOCAL_SRC_FILES := \
                    src/main.cpp \
                    src/SmartIosService.cpp \
                    src/SmartIosServiceStub.cpp \
                    src/SmartIosServiceManager.cpp \
                    src/SmartIosSettingProxy.cpp \
                    src/SmartIosMessage.cpp \
                    src/SmartIosConnManagerProxy.cpp \
                    src/stub/SmartIosServiceReplier.cpp \
                    src/stub/SmartIosServiceStubBase.cpp \
                    src/SmartIosDiagServiceSub.cpp\
                    src/DataBase.cpp\

LOCAL_LDLIBS += -lpthread -lrt -ldl 

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils  \
                          libutils liblog libprocess \
                          libnmmputils libmlooper \
                          libnihallib \
                          libconnectmanagerproxy\
                          libsqlcipher\
                          libdiagproxy\

include $(BUILD_EXECUTABLE)
################################SmartIosTool#############################
include $(CLEAR_VARS)

LOCAL_MODULE        := libsmartiostool

LOCAL_MODULE_TAGS   := user
LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
                    external/sqlcipher/ \
                    frameworks/service/smartphoneservice/include \
                    frameworks/service/smartphoneservice/\
                    frameworks/service/smartphoneservice/common \
                    frameworks/service/smartphoneservice/src/include \
                    frameworks/service/smartphoneservice/src/stub \
                    frameworks/service/smartphoneservice/src \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/stub  \
                    platform/media/include \
                    platform/service/connectmanager/include \
                    system/hallib/interface/include \



LOCAL_SRC_FILES := \
                    src/SmartIosTool.cpp\

LOCAL_LDLIBS += -lpthread -lrt -ldl 

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils  \
                          libutils liblog libprocess \
                          libnmmputils libmlooper \
                          libnihallib \
                          libconnectmanagerproxy\
                          libsqlcipher\

include $(BUILD_SHARED_LIBRARY)
########################################tstPrint#################################
include $(CLEAR_VARS)

LOCAL_MODULE        := smtiosTestPrint 

LOCAL_MODULE_TAGS   := eng
LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
                    external/sqlcipher/ \
                    frameworks/service/smartphoneservice/include \
                    frameworks/service/smartphoneservice/\
                    frameworks/service/smartphoneservice/common \
                    frameworks/service/smartphoneservice/src/include \
                    frameworks/service/smartphoneservice/src/stub \
                    frameworks/service/smartphoneservice/src \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/stub  \
                    platform/media/include \
                    platform/service/connectmanager/include \
                    system/hallib/interface/include \



LOCAL_SRC_FILES := \
                    src/tstPrint.cpp\

LOCAL_LDLIBS += -lpthread -lrt -ldl 

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils  \
                          libutils liblog libprocess \
                          libnmmputils libmlooper \
                          libnihallib \
                          libconnectmanagerproxy\
                          libsqlcipher\
                          libsmartiostool\

include $(BUILD_EXECUTABLE)

########################################tstsearchPopDevice#################################
include $(CLEAR_VARS)

LOCAL_MODULE        := smtiosTestSearch
LOCAL_MODULE_TAGS   := eng

LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
                    external/sqlcipher/ \
                    frameworks/service/smartphoneservice/include \
                    frameworks/service/smartphoneservice/\
                    frameworks/service/smartphoneservice/common \
                    frameworks/service/smartphoneservice/src/include \
                    frameworks/service/smartphoneservice/src/stub \
                    frameworks/service/smartphoneservice/src \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/stub  \
                    platform/media/include \
                    platform/service/connectmanager/include \
                    system/hallib/interface/include \



LOCAL_SRC_FILES := \
                    src/tstsearchPopDevice.cpp\

LOCAL_LDLIBS += -lpthread -lrt -ldl 

LOCAL_CFLAGS += -std=gnu++0x

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils  \
                          libutils liblog libprocess \
                          libnmmputils libmlooper \
                          libnihallib \
                          libconnectmanagerproxy\
                          libsqlcipher\
                          libsmartiostool\

include $(BUILD_EXECUTABLE)

##################################libLaunchIosTest.so############################
include $(CLEAR_VARS)

ifeq ($(TARGET_PRODUCT)_$(TARGET_BUILD_VARIANT), full_eng)
LOCAL_CFLAGS += -DUT_GTEST_FULL_ENG
LOCAL_CFLAGS += -fno-access-control
endif

LOCAL_MODULE        := libLaunchIosTest
LOCAL_MODULE_TAGS   := user
LOCAL_AIDL_TARGET   := stub

LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
                    external/sqlcipher/ \
                    frameworks/service/smartphoneservice/include \
                    frameworks/service/smartphoneservice/\
                    frameworks/service/smartphoneservice/common \
                    frameworks/service/smartphoneservice/src/include \
                    frameworks/service/smartphoneservice/src/stub \
                    frameworks/service/smartphoneservice/src/proxy \
                    frameworks/service/smartphoneservice/src \
                    frameworks/service/diagservice/include \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/stub  \
                    platform/media/include \
                    platform/service/settingservice/include \
                    platform/service/connectmanager/include \
                    system/hallib/interface/include \

ifeq ($(TARGET_PRODUCT)_$(TARGET_BUILD_VARIANT), full_eng)
LOCAL_C_INCLUDES += external/googletest/include \
                    external/googlemock/include \
                    $(sort $(call all-subdirs-under,Test)) \
		    		frameworks/service/smartphoneservice/Test
endif

LOCAL_SRC_FILES := \
                    src/SmartIosService.cpp \
                    src/SmartIosServiceStub.cpp \
                    src/SmartIosServiceManager.cpp \
                    src/SmartIosSettingProxy.cpp \
                    src/SmartIosMessage.cpp \
                    src/SmartIosConnManagerProxy.cpp \
                    src/stub/SmartIosServiceReplier.cpp \
                    src/stub/SmartIosServiceStubBase.cpp \
                    src/DataBase.cpp\
                    src/proxy/SmartIosServiceProxyBase.cpp\
                    src/SmartIosDiagServiceSub.cpp\

LOCAL_LDLIBS += -lpthread 

ifeq ($(TARGET_PRODUCT)_$(TARGET_BUILD_VARIANT), full_eng)
LOCAL_SRC_FILES += $(sort $(call all-cpp-files-under,Test))
endif

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils  \
                          libutils liblog libprocess \
                          libnmmputils libmlooper \
                          libsettingproxy \
                          libnihallib \
                          libconnectmanagerproxy\
                          libdiagproxy\
                          libsqlcipher\

ifeq ($(TARGET_PRODUCT)_$(TARGET_BUILD_VARIANT), full_eng)
LOCAL_SHARED_LIBRARIES += libgtest libgmock
else
LOCAL_SHARED_LIBRARIES += libconnectmanagerproxy
endif

include $(BUILD_SHARED_LIBRARY)


##################################libSmartServiceproxy############################
include $(CLEAR_VARS)

LOCAL_MODULE        := libioslauncherproxy
LOCAL_MODULE_TAGS   := user
LOCAL_AIDL_TARGET   := proxy

LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
                    frameworks/service/smartphoneservice/include \
                    frameworks/service/smartphoneservice/src \
                    system/hallib/interface/include \


#LOCAL_SRC_FILES := aidl/IWFDService.aidl
LOCAL_SRC_FILES :=  src/proxy/SmartIosServiceProxyBase.cpp

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils liblog

include $(BUILD_SHARED_LIBRARY)

#################################libsmtIosServicesub#############################
include $(CLEAR_VARS)

LOCAL_MODULE        := libioslaunchersub
LOCAL_MODULE_TAGS   := user 
LOCAL_AIDL_TARGET   := sub

LOCAL_C_INCLUDES := frameworks/native/include \
                    system/core/include \
                    platform/base/include \
                    platform/base/servicebase \
                    system/hallib/interface/include \
                    $(LOCAL_PATH)/include \

#LOCAL_SRC_FILES := aidl/IWFDService.aidl
LOCAL_SRC_FILES := src/sub/SmartIosServiceSub.cpp

LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils liblog

include $(BUILD_SHARED_LIBRARY)


include $(call first-makefiles-under,$(LOCAL_PATH))

