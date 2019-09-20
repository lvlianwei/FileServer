#include<gtest/gtest.h>
#define private public
#include "Test_wfdServiceMgr.h"
#include "wfdServiceStub.h"
#include "WFDServiceMultiListen.h"
#include "wfdService.h"
#include "Test_wfdService.h"
namespace goni{
    class Test_wfdMultiListen:public testing::Test {
        protected:
            static WFDMultiListener *listen;
            static WFDServiceStub *stub;
            static void SetUpTestCase() {
                //stub = new WFDServiceStub(new wfdService);
                listen = new WFDMultiListener(Test_wfdService::service->mStub);
            }
            static void TearDownTestCase() {
                if(NULL != listen) {
                    delete listen;
                    listen = NULL;
                }
            }
    };
    WFDMultiListener * Test_wfdMultiListen::listen = NULL;
    TEST_F(Test_wfdMultiListen,p2pPowerStatusNotify) {
        WIFI_POWER_STATE_E powerStatus = WIFI_POWER_STATE_POWER_OFF;
        listen->p2pPowerStatusNotify(powerStatus);
    }
    TEST_F(Test_wfdMultiListen,p2pConnectStatusNotify) {
        WIFI_CONNECT_STATE_E connStatus = WIFI_CONNECT_STATE_DISCONNECTTED;
        listen->p2pConnectStatusNotify(connStatus); 
    }
    TEST_F(Test_wfdMultiListen,p2pConnectedInfoNotify) {
        uint16_t remotePort = 80;
        uint32_t remoteIP = 10;
        uint32_t localIP = 11;
        listen->p2pConnectedInfoNotify(remotePort,remoteIP,localIP);
    }
    TEST_F(Test_wfdMultiListen,p2pLinkQuiltyNotify) {
        int32_t sig = 0;
        listen->p2pLinkQuiltyNotify(sig);
    }
    TEST_F(Test_wfdMultiListen,p2pListenStatusNotify) {
        WIFI_LISTEN_STATUS_E status = WIFI_LISTEN_STATUS_START;
        listen->p2pListenStatusNotify(status);
    }
    TEST_F(Test_wfdMultiListen,genOnConnectionChanged) {
        uint8_t index = 0;
        uint64_t addr  =1;
        android::String8 name;
        BT_FUNCTION_E function;
        uint32_t result;
        listen->genOnConnectionChanged(index,addr,name,function,result);
    }
    TEST_F(Test_wfdMultiListen,genOnDisconnectionChanged) {
        uint8_t index = 0;
        uint64_t addr  =1;
        android::String8 name;
        BT_FUNCTION_E function;
        uint32_t result;
        listen->genOnDisconnectionChanged(index,addr,name,function,result);
    }
    TEST_F(Test_wfdMultiListen,connectStatusReady) {
        listen->connectStatusReady();
    }
    TEST_F(Test_wfdMultiListen,connectStatusExtract) {
        listen->connectStatusExtract();
    }
    TEST_F(Test_wfdMultiListen,CarplayAuthSuccess) {
        listen->CarplayAuthSuccess();
    }
    TEST_F(Test_wfdMultiListen,CarplayExtract) {
        listen->CarplayExtract();
    }
}
