#include<gtest/gtest.h>
#define private public
#include "proxy/WFDServiceProxyBase.h"
namespace goni {
    class Test_wfdServiceProxyBase:public testing::Test {
        protected:
            static WFDServiceProxyBase *base;
            static void SetUpTestCase() {
                base = new WFDServiceProxyBase(new IWFDServiceProxyReplier);
            }
            static void TearDownTestCase() {
                if(NULL != base) {
                    delete base;
                    base = NULL;
                }
            }
    };
    WFDServiceProxyBase * Test_wfdServiceProxyBase::base = NULL;
    TEST_F(Test_wfdServiceProxyBase,onConnected) {
        base->onConnected();
    }
    TEST_F(Test_wfdServiceProxyBase,onDisconnected) {
        base->onDisconnected();
    }
    TEST_F(Test_wfdServiceProxyBase,wfdStateSync) {
        WFDDeviceState_Sp state = new WFDDeviceState;
        base->wfdStateSync(state);
    }
    TEST_F(Test_wfdServiceProxyBase,wfdGetRemoteInfo) {
        WFDRemoteDeviceInfo_Sp info = new WFDRemoteDeviceInfo;
        base->wfdGetRemoteInfo(info);
    }
    TEST_F(Test_wfdServiceProxyBase,wfdGetLocalDevice) {
        uint16_t nameLen;
        uint8_t name;
        base->wfdGetLocalDevice(nameLen,name);
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_powerOn) {
        base->wfd_powerOn();
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_powerOff) {
        base->wfd_powerOff();
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_sourceChange) {
        uint8_t mode = 0;
        base->wfd_sourceChange(mode);
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_mirrorMode) {
        MirrorMode mode;
        base->wfd_mirrorMode(mode);
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_SreenMode) {
        ScreenMode mode;
        base->wfd_SreenMode(mode);
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_getGPSTime) {
        base->wfd_getGPSTime();
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_sendHardKey) {
        HardKey key = HOME_DOWN;
        base->wfd_sendHardKey(key);
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_startSearch) {
        base->wfd_startSearch();
        base->wfd_stopSearch();
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_acceptInvitation) {
        base->wfd_acceptInvitation(1);
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_sendUIBCData) {
        TouchType type = TouchType_Press;
        TouchPoints_SpVec points(10);
        for(int i = 0; i < 10; i++) {
            points[i] = new TouchPoints;
            points[i]->setPointerId(i);
            points[i]->setX(i);
            points[i]->setY(i);
        }
        base->wfd_sendUIBCData(type,points);
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_disconnect) {
        base->wfd_disconnect();
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_enableWfd) {
        base->wfd_enableWfd();
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_disableWfd) {
        base->wfd_disableWfd();
    }
    TEST_F(Test_wfdServiceProxyBase,onAsyncResponse) {
        unsigned int code;
        android::Parcel data;
        code = WFDServiceProxyBase::NOTIFY_WFD_SEARCH_RESULT_IND;
        base->onAsyncResponse(code,data);
        code = WFDServiceProxyBase::NOTIFY_WFD_SEARCH_FINISHED_IND;
        base->onAsyncResponse(code,data);
        code = WFDServiceProxyBase::NOTIFY_WFD_INVALID_APP_IND;
        base->onAsyncResponse(code,data);
        code = WFDServiceProxyBase::NOTIFY_WFD_CURRENT_APP_CHANGE_IND;
        base->onAsyncResponse(code,data);
        code = WFDServiceProxyBase::NOTIFY_WFD_NAVI_VOICE_IND;
        base->onAsyncResponse(code,data);
        code = WFDServiceProxyBase::NOTIFY_WFD_SOURCE_CHANGE_CFM;
        base->onAsyncResponse(code,data);
        code = WFDServiceProxyBase::NOTIFY_WFD_LOCAL_DEVICE_IND;
        base->onAsyncResponse(code,data);
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_play) {
        base->wfd_play();
    }
    TEST_F(Test_wfdServiceProxyBase,wfd_pause) {
        base->wfd_pause();
    }
}
