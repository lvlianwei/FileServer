#include<gtest/gtest.h>
#include "Test_wfdServiceMgr.h"
#include "WFDServiceDefs.h"
#include "WFDServiceServiceDefines.h"
#include "WFDServiceStackListen.h"
#include "wfdServiceStub.h"
#include "WFDServiceManager.h"
#include "WFDServiceReplier.h"
#include "wfdService.h"
#include "Test_wfdService.h"
#include "../test/testDefine.h"
namespace goni {
    class Test_wfdServiceStackListen:public testing::Test {
        protected:
            static WFDStackListener *listen;
            static WFDServiceManager *mgr;
            static WFDServiceStub *stub;
            static WFDServiceReplier *replier;
            static void SetUpTestCase() {
                listen = new WFDStackListener(Test_wfdService::service->mStub->m_manager);
            }
            static void TearDownTestCase() {
                if(NULL != listen) {
                    delete listen;
                    listen = NULL;
                }
            }
    };
    WFDStackListener * Test_wfdServiceStackListen::listen = NULL;
    TEST_F(Test_wfdServiceStackListen,notifyDisplayConnected) {
		UTretvalue = 1;
        listen->notifyDisplayConnected(1);
        listen->notifyDisplayConnected(0);
		UTretvalue = 0;
        listen->notifyDisplayConnected(1);
        listen->notifyDisplayConnected(0);
    }
    TEST_F(Test_wfdServiceStackListen,notifyDisplaycCancelConnect) {
        listen->notifyDisplaycCancelConnect(1);
    }
    TEST_F(Test_wfdServiceStackListen,notifySetUpResult) {
        listen->notifySetUpResult(1);
    }
    TEST_F(Test_wfdServiceStackListen,notifyTearDownResult) {
        listen->notifyTearDownResult(0);
    }
    TEST_F(Test_wfdServiceStackListen,notifySelectedAudioFormat) {
        listen->notifySelectedAudioFormat(1);
    }
    TEST_F(Test_wfdServiceStackListen,notifySelectVideoSize) {
        listen->notifySelectedVideoSize(1);
    }
    TEST_F(Test_wfdServiceStackListen,notifyRtpData) {
        listen->notifyRtpData(NULL,0,0);
    }
    TEST_F(Test_wfdServiceStackListen,notifyUIBCStreamAddress) {
        listen->notifyUIBCStreamAddress(0,0);
        string uri;
        listen->notifyRtpStreamAddress(uri,80);
    }
    TEST_F(Test_wfdServiceStackListen,notifyDisplayDisconnect) {
        listen->notifyDisplayDisconnect(1);
    }
    TEST_F(Test_wfdServiceStackListen,notifyPlayResult) {
    	UTcompvalue = 1;
        listen->notifyPlayResult(0);
		UTcompvalue = 0;
        listen->notifyPlayResult(1);
		UTcompvalue = 0;
        listen->notifyPlayResult(0);
		UTcompvalue = 1;
        listen->notifyPlayResult(1);
    }
    TEST_F(Test_wfdServiceStackListen,notifyPauseResult) {
        listen->notifyPauseResult(0);
        listen->notifyPauseResult(1);
    }
    TEST_F(Test_wfdServiceStackListen,notifyRtpStreamAddress) {
        unsigned int localIp = 10;
        unsigned int localRtpPort = 80;
        listen->notifyRtpStreamAddress(localIp,localRtpPort);
    }
    TEST_F(Test_wfdServiceStackListen,notifyUIBCResult) {
        bool result  = 1;
        unsigned int width = 0;
        unsigned int height = 1;
        listen->notifyUIBCResult(result,width,height);
    }
    TEST_F(Test_wfdServiceStackListen,notifyScreenInfo) {
        unsigned char locked = 0;
        unsigned char cross = 1;
        listen->notifyScreenInfo(locked,cross);
        cross = 0;
        listen->notifyScreenInfo(locked,cross);
    }
    TEST_F(Test_wfdServiceStackListen,notifyAppAvailableInd) {
        listen->notifyAppAvailableInd(0);
    }
    TEST_F(Test_wfdServiceStackListen,notifyNaviVoiceInd) {
        listen->notifyNaviVoiceInd(NAVI_BEGIN);
        listen->notifyNaviVoiceInd(NAVI_END);
        listen->notifyNaviVoiceInd(MAX_RETRY_TIME);
    }
    TEST_F(Test_wfdServiceStackListen,notifyGPSTimeInd) {
        uint error;
        uint len = 20;
        unsigned char* time = (unsigned char *)malloc(20);
        memset(time,0,20);
        listen->notifyGPSTimeInd(error,len,time);
        free(time);
        time = NULL;
        len = 0;
        listen->notifyGPSTimeInd(error,len,time);
    }
    TEST_F(Test_wfdServiceStackListen,notifyCurrentAppChange) {
        wfdLocalInfo info;
        memset(&info,0,sizeof(info));
        info.appMode = APP;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        listen->notifyCurrentAppChange(0);
        listen->notifyCurrentAppChange(1);
        info.appMode = MIRROR;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        listen->notifyCurrentAppChange(0);
        info.appMode = MIRROR_INVALID;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        listen->notifyCurrentAppChange(0);
    }
    TEST_F(Test_wfdServiceStackListen,notifyInvalidAppInd) {
        listen->notifyInvalidAppInd(1);
    }
    TEST_F(Test_wfdServiceStackListen,notifyModeCangeSuccess) {
        listen->notifyModeChangeSuccess(0);
        listen->notifyModeChangeSuccess(1);
    }
    TEST_F(Test_wfdServiceStackListen,audioRenderChanged) {
        listen->audioRenderChanged(0,(Role)0);
        listen->audioRenderChanged(1,(Role)1);
    }
    TEST_F(Test_wfdServiceStackListen,notifyReceiverId) {
        unsigned long long revId = 1;
        listen->notifyReceiverId(revId);
    }
    TEST_F(Test_wfdServiceStackListen,notifyPeerDeviceHdcp) {
        int error = WFD_ERR_OK;
        listen->notifyPeerDeviceHdcp(error);
    }
    TEST_F(Test_wfdServiceStackListen,notifyRemoteBtMac) {
        char macLen = 17;
        char * macAddr = new char(macLen);
        listen->notifyRemoteBtMac(macLen,macAddr);
        wfdLocalInfo info;
        info.btMac = 1;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        listen->notifyRemoteBtMac(macLen,macAddr);
    }
    TEST_F(Test_wfdServiceStackListen,onSendNaviState) {
        int naviState;
        listen->onSendNaviState(naviState);
    }
    TEST_F(Test_wfdServiceStackListen,notifySendIDRResult) {
        int error = WFD_ERR_OK;
        listen->notifySendIDRResult(error);
    }
}
