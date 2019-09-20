#include<gtest/gtest.h>
#include "Test_wfdServiceMgr.h"
#include "WFDServiceWifiListen.h"
#include "wfdServiceStub.h"
#include "WFDServiceManager.h"
#include "WFDServiceReplier.h"
#include "wfdService.h"
#include "Test_wfdService.h"
namespace goni {
    class Test_wfdWifiListen:public testing::Test {
        protected:
            static WFDWifiListener *listen;
            static WFDServiceManager *mgr;
            static WFDServiceReplier *replier;
            static WFDServiceStub *stub;
            static void SetUpTestCase() {
                listen = new WFDWifiListener(Test_wfdService::service->mStub->m_manager);
                listen->onConnected();
            }
            static void TearDownTestCase() {
                if(NULL != listen) {
                    delete listen;
                    listen = NULL;
                }
            }
    };
    WFDWifiListener * Test_wfdWifiListen::listen = NULL;
    TEST_F(Test_wfdWifiListen,p2pInvitationNotify) {
        android::String8 devName("p2p");
        uint64_t macAddr = 1;
        listen->p2pInvitationNotify(devName,macAddr);
    }
    TEST_F(Test_wfdWifiListen,p2pSyncStatusEvt) {
        p2pSyncStatusData_Sp wifidata = new p2pSyncStatusData;
        listen->p2pSyncStatusEvt(wifidata);
    }
}
