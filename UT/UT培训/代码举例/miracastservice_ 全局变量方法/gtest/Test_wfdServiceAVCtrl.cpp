#include<gtest/gtest.h>
#include "Test_wfdServiceMgr.h"
#include "WFDServiceAVCtr.h"
#include "wfdServiceStub.h"
#include "WFDServiceManager.h"
#include "WFDServiceReplier.h"
#include "wfdService.h"
#include "TimerManager.h"
#include "Test_wfdService.h"
namespace goni {
    class Test_wfdAVCtrl:public testing::Test {
        protected:
            static WFDServiceAVCtr *ctrl;
            static WFDServiceManager *mgr;
            static WFDServiceStub *stub;
            static WFDServiceReplier *replier;
            static TimerManager * manager;
            static void SetUpTestCase() {
                ctrl = new WFDServiceAVCtr(Test_wfdService::service->mStub->m_manager);
                ctrl->onStart();
                ctrl->initialize();
            }
            static void TearDownTestCase() {
                if(NULL != ctrl) {
                    ctrl->finalize();
                    delete ctrl;
                    ctrl = NULL;
                }
            }
    };
    WFDServiceAVCtr * Test_wfdAVCtrl::ctrl = NULL;
    TEST_F(Test_wfdAVCtrl,setUri) {
        uint32_t Ip = 10;
        uint32_t port = 80;
        uint32_t hdcpFlag = 1;
        ctrl->setUri(Ip,port,hdcpFlag);
    }
    TEST_F(Test_wfdAVCtrl,prepare) {
        ctrl->prepare();
    }
    TEST_F(Test_wfdAVCtrl,play) {
        ctrl->play();
    }
    TEST_F(Test_wfdAVCtrl,pause) {
        ctrl->pause();
    }
    TEST_F(Test_wfdAVCtrl,stop) {
        ctrl->stop();
    }
    TEST_F(Test_wfdAVCtrl,getPlayerState) {
        ctrl->getPlayerState();
    }
    TEST_F(Test_wfdAVCtrl,getAudioLatency) {
        ctrl->getAudioLatency();
    }
    TEST_F(Test_wfdAVCtrl,setPlayerState) {
        PLAYERSTATE state=PLAYER_STATE_INIT;
        ctrl->setPlayerState(state);
        state=PLAYER_STATE_PREPARE;
        ctrl->setPlayerState(state);
        state=PLAYER_STATE_PLAYING;
        ctrl->setPlayerState(state);
        state=PLAYER_STATE_STOP;
        ctrl->setPlayerState(state);
    }
}
