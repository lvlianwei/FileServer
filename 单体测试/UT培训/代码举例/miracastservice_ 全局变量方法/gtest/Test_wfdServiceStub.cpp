#include<stdio.h>
#include<gtest/gtest.h>
#define private public
#include "Test_wfdService.h"
#include "wfdServiceStub.h"
namespace goni {
    class Test_wfdServiceStub:public testing::Test {
        protected:
            static void SetUpTestCase() {
                printf("***********************Test_wfdServiceStub setup**********************\n");
            }
            static void TearDownTestCase() {
                printf("**************************Test_wfdServiceStub teardown***************************\n");
            }
    };
    TEST_F(Test_wfdServiceStub,wfdStateSync) {
        WFDDeviceState_Sp state = new WFDDeviceState;
        Test_wfdService::service->mStub->wfdStateSync(state);
    }
    TEST_F(Test_wfdServiceStub,wfdGetRemoteInfo) {
        WFDRemoteDeviceInfo_Sp info = new WFDRemoteDeviceInfo;
        Test_wfdService::service->mStub->wfdGetRemoteInfo(info);
    }
    TEST_F(Test_wfdServiceStub,wfdGetLocalDevice) {
        uint16_t namelen;
        uint8_t name;
        Test_wfdService::service->mStub->wfdGetLocalDevice(namelen,name);
    }
    TEST_F(Test_wfdServiceStub,wfd_powerOn) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_powerOn(id);
    }
    TEST_F(Test_wfdServiceStub,wfd_powerOff) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_powerOff(id);
        Test_wfdService::service->mStub->wfd_stopSearch(id);
    }
    TEST_F(Test_wfdServiceStub,wfd_sourceChange) {
        SenderId id;
        uint8_t mode;
        Test_wfdService::service->mStub->wfd_sourceChange(id,mode);
    }
    TEST_F(Test_wfdServiceStub,wfd_mirrorMode) {
        SenderId id;
        MirrorMode mode;
        Test_wfdService::service->mStub->wfd_mirrorMode(id,mode);
    }
    TEST_F(Test_wfdServiceStub,wfd_SreenMode) {
        SenderId id;
        ScreenMode mode;
        Test_wfdService::service->mStub->wfd_SreenMode(id,mode);
    }
    TEST_F(Test_wfdServiceStub,wfd_getGPSTime) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_getGPSTime(id);
    }
#if 1
    TEST_F(Test_wfdServiceStub,wfd_sendHardKey) {
        SenderId id;
        HardKey key;
        Test_wfdService::service->mStub->wfd_sendHardKey(id,key);
    }
#endif
    TEST_F(Test_wfdServiceStub,wfd_startSearch) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_startSearch(id);
    }
    TEST_F(Test_wfdServiceStub,wfd_acceptInvitation) {
        SenderId id;
        bool accept  = 1;
        Test_wfdService::service->mStub->wfd_acceptInvitation(id,accept);
    }
    TEST_F(Test_wfdServiceStub,wfd_disconnect) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_disconnect(id);
    }
    TEST_F(Test_wfdServiceStub,wfd_sendUIBCData) {
        SenderId id;
        TouchType type;
        TouchPoints_SpVec points(10);
        for(int i = 0; i < 10; i ++) {
            points[i] = new TouchPoints;
        }
        Test_wfdService::service->mStub->wfd_sendUIBCData(id,type,points);
    }
    TEST_F(Test_wfdServiceStub,onMultiListen) {
        uint8_t opcode;
        void *msg = NULL;
        Test_wfdService::service->mStub->onMultiListen(opcode,msg);
    }
    TEST_F(Test_wfdServiceStub,initialize) {
        Test_wfdService::service->mStub->initialize();
    }
    TEST_F(Test_wfdServiceStub,wfd_enableWfd) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_enableWfd(id);
    }
    TEST_F(Test_wfdServiceStub,wfd_disableWfd) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_disableWfd(id);
    }
    TEST_F(Test_wfdServiceStub,wfd_play) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_play(id);
    }
    TEST_F(Test_wfdServiceStub,wfd_pause) {
        SenderId id;
        Test_wfdService::service->mStub->wfd_pause(id);
    }
}
