LOCAL_PATH :=$(call my-dir)
include $(CLEAR_VARS)
ifeq ($(TARGET_PRODUCT)_$(TARGET_BUILD_VARIANT), full_eng)
LOCAL_CFLAGS += -DUT_GTEST_FULL_ENG
endif
LOCAL_MODULE        := gtstlaunchios
LOCAL_MODULE_TAGS   := tests

LOCAL_C_INCLUDES := frameworks/native/include \
                    platform/base/include \
                    platform/base/servicebase \
                    external/sqlcipher/ \
                    frameworks/service/smartphoneservice/include \
                    frameworks/service/smartphoneservice/\
                    frameworks/service/smartphoneservice/common \
                    frameworks/service/martphoneservice/src/include \
                    frameworks/service/smartphoneservice/src/stub \
                    frameworks/service/smartphoneservice/src/proxy \
                    frameworks/service/smartphoneservice/src \
                    frameworks/service/smartphoneservice/src/include \
                    frameworks/service/diagservice/include \
                    platform/media/include \
                    platform/service/settingservice/include \
                    platform/service/connectmanager/include \
                    system/hallib/interface/include \
                    external/icu4c/common/ \
                    external/googletest/include/ \
                    platform/base/include/servicebase \
                    external/googlemock/include/ \
                    frameworks/service/smartphoneservice/Test \
                    system/core/include/utils \

LOCAL_SRC_FILES := \
                    Test_smtIosSetting.cpp\
                    Test_smtIosService.cpp\
                    Test_smtIosServiceStub.cpp\
                    Test_smtIosServiceMgr.cpp\
                    Test_smtIosServiceProxyBase.cpp\
                    Test_smtIosConMangerProxy.cpp\

LOCAL_LDLIBS += -lpthread 

LOCAL_SHARED_LIBRARIES := libgtest libgmock libservicebase libbinder libcutils libutils  \
                          libutils liblog libprocess \
                          libnmmputils libmlooper \
                          libsettingproxy \
                          libnihallib \
                          libconnectmanagerproxy\
                          libLaunchIosTest\
                          libsqlcipher\

LOCAL_STATIC_LIBRARIES += libgtest_main libdebugger
LOCAL_CFLAGS += -g -fexceptions -fno-access-control -w
LOCAL_LDFLAGS := -lpthread -lrt -ldl

include $(BUILD_EXECUTABLE)
