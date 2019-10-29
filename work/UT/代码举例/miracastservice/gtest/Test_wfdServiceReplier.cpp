#include<stdio.h>
#include<gtest/gtest.h>
#include "WFDServiceReplier.h"
#include "servicebase/ServiceBase.h"
#include "Test_wfdService.h"
namespace goni {
    class Test_wfdServiceReplier:public testing::Test {
        protected:
            static WFDServiceReplier *replier;
            static void SetUpTestCase() {
                printf("****************************Test_wfdServiceReplier setup*************************\n");
                replier = new WFDServiceReplier(new ServiceBase("base"));
            }
            static void TearDownTestCase() {
                printf("******************************Test_wfdServiceReplier tearDown************************\n");
                if(NULL != replier) {
                    delete replier;
                    replier = NULL;
                }
                //	Test_wfdService::service->onStop();
                delete Test_wfdService::service;
            }
    };
    WFDServiceReplier * Test_wfdServiceReplier::replier = NULL;
    TEST_F(Test_wfdServiceReplier,wfdSearchResultInd) {
        SenderId id;
        WFDDeviceInfo_Sp info = new WFDDeviceInfo;
        replier->wfdSearchResultInd(id,info);
    }
    TEST_F(Test_wfdServiceReplier,wfdSearchFinishedInd) {
        SenderId id;
        uint32_t err = 1;
        replier->wfdSearchFinishedInd(id,err);
    }
    TEST_F(Test_wfdServiceReplier,wfdInvalidAppInd) {
        SenderId id;
        uint32_t err =1;
        replier->wfdInvalidAppInd(id,err);
    }
    TEST_F(Test_wfdServiceReplier,wfdCurrentAppChangeInd) {
        SenderId id;
        uint32_t err =1;
        replier->wfdCurrentAppChangeInd(id,err);
    }
#if 0
    TEST_F(Test_wfdServiceReplier,wfdGetGPSTimeInd) {
        SenderId id;
        uint32_t err = 1;
        uint32_t len = 10;
        std::vector<uint8_t> time(10);
        replier->wfdGetGPSTimeInd(id,err,len,time);
    }
#endif
    TEST_F(Test_wfdServiceReplier,wfdNaviVoiceInd) {
        SenderId id;
        uint32_t err = 1;
        replier->wfdNaviVoiceInd(id,err);
    }
    TEST_F(Test_wfdServiceReplier,wfdSourceChangeCfm) {
        SenderId id;
        uint32_t err = 1;
        uint32_t curmode = 0;
        replier->wfdSourceChangeCfm(id,err,curmode);
    }
    TEST_F(Test_wfdServiceReplier,wfdLocalDeviceInd) {
        SenderId id;
        uint16_t len = 10;
        std::vector<uint8_t> name(10);
        replier->wfdLocalDeviceInd(id,len,name);
    }
}
