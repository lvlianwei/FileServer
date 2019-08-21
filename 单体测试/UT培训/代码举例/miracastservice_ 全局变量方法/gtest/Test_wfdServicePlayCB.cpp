#include <gtest/gtest.h>
#include "Test_wfdServiceMgr.h"
#include "WFDServicePlayCallback.h"
#include "wfdServiceStub.h"
#include "WFDServiceManager.h"
#include "WFDServiceReplier.h"
#include "wfdService.h"
#include "WFDServiceAVCtr.h"
#include "Test_wfdService.h"
namespace goni {
    class Test_wfdServicePlayCB :public testing::Test {
        protected:
            static WFDServicePlayCallback * cb;
            static WFDServiceManager *mgr;
            static WFDServiceStub *stub;
            static WFDServiceReplier *replier;
            static WFDServiceAVCtr *ctr;
            static void SetUpTestCase() {
                ctr = new WFDServiceAVCtr(Test_wfdService::service->mStub->m_manager);
                ctr->onStart();
                ctr->initialize();
                ctr->setPlayerState(PLAYER_STATE_PLAYING);
                cb = new WFDServicePlayCallback(Test_wfdService::service->mStub->m_manager,ctr);
                cb->onConnected();
            }
            static void TearDownTestCase() {
                if(NULL != cb) {
                    delete cb;
                    cb = NULL;
                }
                if(ctr) {
                    delete ctr;
                    ctr = NULL;
                }
                if(stub) {
                    delete stub;
                    stub = NULL;
                }
            }
    };
    WFDServicePlayCallback *Test_wfdServicePlayCB::cb = NULL;
    WFDServiceAVCtr *Test_wfdServicePlayCB::ctr = NULL;
    WFDServiceStub *Test_wfdServicePlayCB::stub = NULL;
    TEST_F(Test_wfdServicePlayCB,playStatusChanged) {
        media::NMMP_PlayStatus status;
        INT32 mask = NMMP_PLAYSTATUS_MASK_STATE;
        status.state = media::NMMP_PlaybackState_Error;
        cb->playStatusChanged(status,mask);
    }
    TEST_F(Test_wfdServicePlayCB,ackPrepare) {
        INT32 retCode = media::NMMP_Ret_NoError;
        INT64 seqId;
        cb->ackPrepare(retCode,seqId);
        retCode = 10;
        cb->ackPrepare(retCode,seqId);
    }
    TEST_F(Test_wfdServicePlayCB,ackPlay) {
        INT32 retCode = media::NMMP_Ret_NoError;
        INT64 seqId;
        cb->ackPlay(retCode,seqId);
        retCode = 10;
        cb->ackPlay(retCode,seqId);
    }
    TEST_F(Test_wfdServicePlayCB,onDisconnected) {
        media::NMMP_MediaInfo status;
        INT32 mask = NMMP_PLAYSTATUS_MASK_STATE;
        cb->onDisconnected();
        cb->onConnectError(mask);
        cb->mediaInfoUpdated(status,mask);
    }
}
