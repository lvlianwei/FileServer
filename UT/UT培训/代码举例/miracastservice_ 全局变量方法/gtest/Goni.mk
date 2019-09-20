LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

    LOCAL_MODULE:= gtstwfd

    LOCAL_MODULE_TAGS := tests

    LOCAL_SRC_FILES :=  \
			Test_wfdService.cpp\
			Test_wfdServiceMgr.cpp\
			Test_wfdServiceStub.cpp\
			Test_wfdServiceAVCtrl.cpp\
			Test_wfdStackListen.cpp\
			Test_wfdInputListen.cpp \
			Test_wfdServiceSetting.cpp \
			Test_wfdWifiListen.cpp\
			Test_wfdMultiListener.cpp \
			Test_wfdServicePlayCB.cpp \
			Test_wfdServiceProxyBase.cpp\
			Test_wfdServiceSub.cpp\
			Test_wfdServiceStubBase.cpp\
			Test_wfdServiceReplier.cpp \
			Test_wfdServiceDTLog.cpp\
			../test/testDefine.cpp\
			../test/testSettingProxy.cpp \
			../test/testWFDServiceManager.cpp \
#			../test/testWFDDeviceState.cpp \

			LOCAL_C_INCLUDES := external/icu4c/common/ \
					    external/googletest/include/ \
					    frameworks/native/include \
					    frameworks/service/miracastservice/src/\
					    frameworks/service/miracastservice/include\
					    platform/base/include\
					    platform/base/servicebase\
					    frameworks/service/miracastservice/common \
					    frameworks/service/miracastservice/src/include \
					    frameworks/service/miracastservice/src/stub \
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
					    platform/media/include \
					    platform/service/settingservice/include \
					    platform/service/inputmanager/include \
					    frameworks/service/carplayservice/include \
					    frameworks/service/carlifeservice/include \
					    platform/base/include/servicebase\
					    system/hallib/interface/include \
					    external/googlemock/include/ \

					    LOCAL_SHARED_LIBRARIES := libgtest libgmock libcutils libwfdTest \
								      libservicebase libbinder libcutils libutils  \
								      libutils liblog libprocess libwfd libthread_wfd \
								      libwifiServiceSub libwifiServiceProxy\
								      libnmmediaplayer libmlooper libInputManagerProxy libsettingproxy \
								      libbtserviceproxy libbtservicesub libcarlifeservicesub libcarplayproxy libnihallib\


								      LOCAL_STATIC_LIBRARIES += libgtest_main libdebugger 
								      LOCAL_CFLAGS += -g -fstack-protector  -fstack-protector-all -w
								      LOCAL_LDFLAGS := -lpthread -lrt -ldl

include $(BUILD_EXECUTABLE)
