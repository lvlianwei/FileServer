#include "WFDServiceDefs.h"
#include<gtest/gtest.h>
#define private public
#include "Test_wfdServiceMgr.h"
#include "WFDServiceInputListen.h"
#include "wfdServiceStub.h"
#include "WFDServiceManager.h"
#include "WFDServiceReplier.h"
#include "wfdService.h"
#include "Test_wfdService.h"
#include "WFDServiceServiceDefines.h"
#include "string.h"
namespace goni {
    class Test_wfdInputListen:public testing::Test {
        protected:
            static WFDInputListener *listen;
            static WFDServiceManager *mgr;
            static WFDServiceStub *stub;
            static WFDServiceReplier *replier;
            static void SetUpTestCase() {
                listen = new WFDInputListener(Test_wfdService::service->mStub->m_manager);
            }
            static void TearDownTestCase() {
                if(NULL != listen) {
                    delete listen;
                    listen = NULL;
                }
            }
    };
    WFDInputListener * Test_wfdInputListen::listen = NULL;
    TEST_F(Test_wfdInputListen,connect) {
        listen->onConnected();
    }
    TEST_F(Test_wfdInputListen,clearData) {
        listen->clearData();
    }
    TEST_F(Test_wfdInputListen,hardkey) {
        HARD_KEY_VALUE value;
        listen->hardKey(value);
    }
    TEST_F(Test_wfdInputListen,addHidUpKey) {
        listen->addHidUpKey();
    }
#if 1
    TEST_F(Test_wfdInputListen,touchKey) {
        TouchEvent_SpVec events(1);
        events[0] = new TouchEvent;
        WFDDeviceState_Sp device = new WFDDeviceState;
        device->setHid(HID_CONNECTED);
        Test_wfdService::service->mStub->m_manager->SetWfdState(device);
        listen->touchKey(events);
        device->setHid(HID_UNCONNETED);
        Test_wfdService::service->mStub->m_manager->SetWfdState(device);
        listen->touchKey(events);
        TouchEvent_Sp event = new TouchEvent;
        events.push_back(event);
        device->setAppState(APP_AVAILABLE);
        Test_wfdService::service->mStub->m_manager->SetWfdState(device);
        listen->touchKey(events);
        device->setAppState(APP_UNAVAILABLE);
        Test_wfdService::service->mStub->m_manager->SetWfdState(device);
        listen->touchKey(events);
    }
#endif
    TEST_F(Test_wfdInputListen,sendToHID) {
        listen->onHidTimer(NULL);
        TouchEvent_SpVec events(10);
        for(int i = 0; i < 10; i++) {
            events[i] = new TouchEvent;
        }
        TOUCH_STATE state = TOUCH_DOWN;
        events[0]->setState(state);
        listen->sendToHID(events);
        state = TOUCH_UP;
        events[0]->setState(state);
        listen->sendToHID(events);
        state = TOUCH_MOVE;
        events[0]->setState(state);
        listen->sendToHID(events);
    }
    TEST_F(Test_wfdInputListen,sendToApp) {
        TouchEvent_SpVec events(10);
        for(int i = 0; i < 10; i++) {
            events[i] = new TouchEvent;
        }
        TOUCH_STATE state;
        state = TOUCH_UP;
        events[0]->setState(state);
        events[0]->setX(20);
        events[0]->setY(20);
        listen->sendToApp(events);
        events[1]->setState(state);
        events[1]->setX(30);
        events[1]->setY(50);
        listen->sendToApp(events);
        listen->clearData();
        state = TOUCH_DOWN;
        events[0]->setState(state);
        listen->sendToApp(events);
        events[1]->setState(state);
        listen->sendToApp(events);
        listen->clearData();
        state = TOUCH_MOVE;
        events[0]->setState(state);
        listen->sendToApp(events);
        events[1]->setState(state);
        listen->sendToApp(events);
        listen->clearData();
        state = TOUCH_IDLE;
        events[0]->setState(state);
        events[0]->setX(0);
        events[0]->setY(0);
        listen->sendToApp(events);
        events[1]->setX(1);
        events[1]->setY(1);
        events[1]->setState(state);
        listen->sendToApp(events);
        listen->clearData();
    }
    TEST_F(Test_wfdInputListen,sendToWFDStack) {
        multiKey mKey;
        mKey.state = TOUCH_MOVE;
        mKey.dataLen = 4;
        memset(&mKey.data, 0 ,4);
        listen->sendToWFDStack(mKey);
        mKey.state = TOUCH_DOWN;
        listen->sendToWFDStack(mKey);
        mKey.state = TOUCH_UP;
        listen->sendToWFDStack(mKey);
    }
    TEST_F(Test_wfdInputListen,onOneShotTimer) {
        listen->onOneShotTimer(NULL);
    }
    TEST_F(Test_wfdInputListen,onHidTimer) {
        listen->onHidTimer(NULL);
    }
    TEST_F(Test_wfdInputListen,onHidReleaseTimer) {
        listen->onHidReleaseTimer(NULL);
    }
}
