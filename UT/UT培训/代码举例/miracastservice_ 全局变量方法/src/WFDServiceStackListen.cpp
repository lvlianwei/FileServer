#ifndef UT_GTEST_FULL_ENG
#include "WFDServiceManager.h"
#include "WFDServiceDefs.h"
#include "WFDServiceServiceDefines.h"
#include "WFDServiceReplier.h"
#include "wfdServiceStub.h"
#include "WFDServiceAVCtr.h"
#else
#include "../test/testWFDServiceManager.h"
#include "../test/testWFDServiceDefs.h"
#include "../test/testWFDServiceServiceDefines.h"
#include "../test/testWFDServiceReplier.h"
#include "../test/testwfdServiceStub.h"
#include "../test/testWFDServiceAVCtr.h"
#include "../test/testWFDDeviceState.h"
#endif
#include "servicebase/SystemLog.h"
#include "WFDServiceStackListen.h"

namespace goni {
DeclearModuleID(DTMODULEID_WFDSERVICE);
#define ISCAPITAL(arg)  (((arg) >= 'a' && (arg) <= 'z') ? ((arg) - 'a') : ((arg) - 'A'))
#define CHAR2HEX(arg)   (((arg) >= '0' && (arg) <= '9') ? ((arg)-'0') : (ISCAPITAL(arg) + 0xa))

WFDStackListener::WFDStackListener(WFDServiceManager* center)          /* __0x008000_DTFUNCID__ */
:mManager(center)
, mNaviState(NAVI_NULL)
, mPlayRetry(MAX_RETRY_TIME)
, mPauseRetry(MAX_RETRY_TIME)
, mIDRRetry(MAX_RETRY_TIME)
{
    MCLOGD("start WFDStackListener\n");
}

WFDStackListener::~WFDStackListener()           /* __0x008001_DTFUNCID__ */
{
    MCLOGD("stop WFDStackListener\n");
    if (m_timer.isActive())
        m_timer.stop();
}



void WFDStackListener::notifyDisplayConnected(int error)          /* __0x008002_DTFUNCID__ */
{
    MCLOGD("notifyDisplayConnected err = %d", error);
    DTLOG_INFO(0x008002, "notifyDisplayConnected err = %d", error);
    android::AutoMutex sync(mSyncObj);
    if (mManager == NULL) {
        DTLOG_PTRASSERT(mManager);
        return;
    }
    WFDServiceStub* stub = mManager->getServiceStub();
    if (stub == NULL) {
		printf("---------------------------------------");
        DTLOG_PTRASSERT(stub);
        return;
    }
    if (error == 0) {
        mManager->onWFDServiceConnected(WFD_SERVICE_CONNECTED);
        int ret = stub->wfdConnectResultInd(WFD_SERVICE_CONNECTED);
        if(BS_NO_ERROR!=ret){
           DTLOG_RET(0x008002, "sendMulticast error1,ret =%d",ret);
        }
    }
    else {
        int ret = stub->wfdConnectResultInd(WFD_SERVICE_UNCONNECTED);
        if(BS_NO_ERROR!=ret){
           DTLOG_RET(0x008002, "sendMulticast error2,ret =%d",ret);
        }
        wfdLocalInfo localInfo;
        mManager->wfdGetLocalInfoData(localInfo);
        if (localInfo.p2pState == P2P_CONNECTED) {
            mManager->wfd_p2pDisconnect();
        }
    }

}

void WFDStackListener::notifyDisplaycCancelConnect(int error)            /* __0x008003_DTFUNCID__ */
{
    MCLOGD("notifyDisplaycCancelConnect\n");
}

void WFDStackListener::notifyDisplayDisconnect(int error)           /* __0x008004_DTFUNCID__ */
{
    MCLOGD("notifyDisplayDisconnect\n");
    DTLOG_INFO(0x008004, "notifyDisplayDisconnect err = %d", error);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        wfdLocalInfo localInfo;
        mManager->wfdGetLocalInfoData(localInfo);
        if (localInfo.p2pState == P2P_CONNECTED) {
            mManager->wfd_p2pDisconnect();
        }
        else {
            //do nothing
       }
    }
}

void WFDStackListener::notifyPlayResult(int error)        /* __0x008005_DTFUNCID__ */
{
    MCLOGD("notifyPlayResult,error = %d\n",error);
    DTLOG_INFO(0x008005, "notifyPlayResult err = %d", error);
    android::AutoMutex sync(mSyncObj);
    if (mManager == NULL) return;
    WFDDeviceState_Sp deviceState = new WFDDeviceState();
    mManager->wfdStateSync(deviceState);
    wfdSvcState state = deviceState->getSvcState();
    if (state != WFD_CONNECTED) return;

    if (WFD_ERR_OK == error) {
        mPlayRetry = MAX_RETRY_TIME;
        mManager->wfd_sendIDR();
    }
    else {
        if(mPlayRetry > 0) {
            mPlayRetry--;
            mManager->wfd_play();
        }
        else {
            mPlayRetry = MAX_RETRY_TIME;
            MCLOGE("notifyPlayResult failed,error = %d\n",error);
            DTLOG_ERR(0x008005, "notifyPlayResult failed err = %d", error);

        }
    }
}

void WFDStackListener::notifySetUpResult(int error)         /* __0x008006_DTFUNCID__ */
{
    MCLOGD("notifySetUpResult\n");
}

void WFDStackListener::notifyPauseResult(int error)         /* __0x008007_DTFUNCID__ */
{
    MCLOGD("%s,error = %d\n",__func__, error);
    DTLOG_INFO(0x008007, "%s, err = %d", __func__, error);
    android::AutoMutex sync(mSyncObj);
    if (mManager == NULL) return;
    WFDDeviceState_Sp deviceState = new WFDDeviceState();
    mManager->wfdStateSync(deviceState);
    wfdSvcState state = deviceState->getSvcState();
    if (state != WFD_CONNECTED) return;

    if (WFD_ERR_OK == error) {
        mPauseRetry = MAX_RETRY_TIME;
    }
    else {
        if(mPauseRetry > 0) {
            mPauseRetry--;
            mManager->wfd_pause();
        }
        else {
            mPauseRetry = MAX_RETRY_TIME;
            MCLOGE("%s failed,error = %d\n",__func__, error);
            DTLOG_ERR(0x008007, "%s failed err = %d", __func__, error);

        }
    }
}

void WFDStackListener::notifyTearDownResult(int error)           /* __0x008008_DTFUNCID__ */
{
    MCLOGD("notifyTearDownResult\n");
    DTLOG_INFO(0x008008, "notifyTearDownResult err = %d", error);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL && error == WFD_ERR_OK) {

        WFDDeviceState_Sp deviceState = new WFDDeviceState();
        mManager->wfdStateSync(deviceState);
        wfdSvcState state = deviceState->getSvcState();
        if (state != WFD_CONNECTED) return;
        SenderId senderId = mManager->getSenderId();
        mManager->wfd_disconnect(senderId);
    }
}

void WFDStackListener::notifySelectedAudioFormat (unsigned int selectedFormat)            /* __0x008009_DTFUNCID__ */
{
    MCLOGD("notifySelectedAudioFormat\n");
}

void WFDStackListener::notifySelectedVideoSize(unsigned int selectedSize)            /* __0x00800A_DTFUNCID__ */
{
    MCLOGD("notifySelectedVideoSize\n");
}

void WFDStackListener::notifyRtpData(unsigned char* data, unsigned int size, int seq)          /* __0x00800B_DTFUNCID__ */
{
    MCLOGD("notifyRtpData\n");
}

void WFDStackListener::notifyUIBCStreamAddress(unsigned int localIp,unsigned int localUIBCPort)            /* __0x00800C_DTFUNCID__ */
{
    MCLOGD("notifyUIBCStreamAddress\n");
}

void WFDStackListener::notifyRtpStreamAddress(string& uri, unsigned int localRtpPort)            /* __0x00800D_DTFUNCID__ */
{
    MCLOGD("notifyRtpStreamAddress\n");


}

void WFDStackListener::notifyRtpStreamAddress(unsigned int localIp, unsigned int localRtpPort)            /* __0x00800E_DTFUNCID__ */
{
    MCLOGD("notifyRtpStreamAddress port = %d", localRtpPort);
    DTLOG_INFO(0x00800E, "notifyRtpStreamAddress port = %d", localRtpPort);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        wfdLocalInfo localInfo;
        mManager->wfdGetLocalInfoData(localInfo);
        localInfo.localPort = localRtpPort;
        mManager->wfdSetLocalInfoData(localInfo);
    }
}

void WFDStackListener::audioRenderChanged(int error,Role target)            /* __0x00800F_DTFUNCID__ */
{
    MCLOGD("audioRenderChanged\n");
}

void WFDStackListener::notifyUIBCResult(bool result, unsigned int width, unsigned int height)   /* __0x008010_DTFUNCID__ */
{
    MCLOGD("notifyUIBCResult width = %d, height = %d", width, height);
    DTLOG_INFO(0x008010, "notifyUIBCResult width = %d, height = %d", width, height);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        wfdLocalInfo localInfo;
        mManager->wfdGetLocalInfoData(localInfo);
        localInfo.height = height;
        localInfo.width = width;
        mManager->wfdSetLocalInfoData(localInfo);
        WFDServiceStub* stub = mManager->getServiceStub();
        if (stub != NULL) {
#ifdef WFD_APP

            WFDDeviceState_Sp deviceState = new WFDDeviceState();
            mManager->wfdStateSync(deviceState);
            wfdSvcState state = deviceState->getSvcState();
            int ret = stub->wfdRemotePixesInfo(state, width, height);
            if(BS_NO_ERROR!=ret){
                DTLOG_RET(0x008010, "sendMulticast error1,ret =%d",ret);
            }

#else
            WFDServiceStub* stub = mManager->getServiceStub();
            WFDDeviceState_Sp deviceState = new WFDDeviceState();
            mManager->wfdStateSync(deviceState);
            deviceState->setAppState(static_cast<AppState>(result));
            mManager->SetWfdState(deviceState);
            int ret = stub->wfdAppStatus(static_cast<uint32_t>(result));
            if(BS_NO_ERROR!=ret){
                DTLOG_RET(0x008010, "sendMulticast error2,ret =%d",ret);
            }

#endif
        }
    }
}

void WFDStackListener::notifyScreenInfo(unsigned char locked, unsigned char cross)   /* __0x008011_DTFUNCID__ */
{
    MCLOGD("notifyScreenInfo locked = %d, cross = %d", locked, cross);
    DTLOG_INFO(0x008011, "notifyScreenInfo locked = %d, cross = %d", locked, cross);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        WFDServiceStub* stub = mManager->getServiceStub();
        if (stub != NULL) {
            ScreenMode mode;
            if (cross == 0) {
                mode = Screen_Horizontal;
                }
            else {
                mode = Screen_Vertial;
            }
            wfdLocalInfo localInfo;
            mManager->wfdGetLocalInfoData(localInfo);
            localInfo.locked = locked;
            localInfo.screenMode = mode;
            mManager->wfdSetLocalInfoData(localInfo);
            int ret = stub->wfdRemoteSrceenChange(locked, mode);
            if(BS_NO_ERROR!=ret){
                DTLOG_RET(0x008011, "sendMulticast error,ret =%d",ret);
            }
        }
    }
}

void WFDStackListener::notifyAppAvailableInd(uint error)   /* __0x008012_DTFUNCID__ */
{
    MCLOGD("WFDStackListener::notifyAppAvailableInd, errpr = %d", error);
    DTLOG_INFO(0x008012, "WFDStackListener::notifyAppAvailableInd, errpr = %d", error);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        WFDServiceStub* stub = mManager->getServiceStub();
        WFDDeviceState_Sp deviceState = new WFDDeviceState();
        mManager->wfdStateSync(deviceState);
        deviceState->setAppState(static_cast<AppState>(error));
        mManager->SetWfdState(deviceState);
        if (stub != NULL) {
            int ret = stub->wfdAppStatus(error);
            if(BS_NO_ERROR!=ret){
                DTLOG_RET(0x008012, "sendMulticast error,ret =%d",ret);
            }
        }
        
    }
}

void WFDStackListener::notifyNaviVoiceInd(uint error)   /* __0x008013_DTFUNCID__ */
{
    MCLOGD("WFDStackListener::notifyNaviVoiceInd, error = %d", error);
    DTLOG_INFO(0x008013, "notifyNaviVoiceInd, error = %d", error);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        if (!(error == NAVI_BEGIN || error == NAVI_END)) return;
        MCLOGD("WFDStackListener::notifyNaviVoiceInd, mNaviState =  %x, state = %d, line = %d", mNaviState, error, __LINE__);

        if (error == NAVI_BEGIN) {
            if (mNaviState == NAVI_NULL || mNaviState == NAVI_END) {
                onSendNaviState(NAVI_BEGIN);
            }
            else if (mNaviState == NAVI_ENDING) {
                if (m_timer.isActive())
                    m_timer.stop();
                mNaviState = NAVI_BEGIN;
                MCLOGD("WFDStackListener::notifyNaviVoiceInd, mNaviState =  %x, line = %d", mNaviState, __LINE__);
                DTLOG_INFO(0x008013, "WFDStackListener::notifyNaviVoiceInd, mNaviState =  %x, line = %d", mNaviState, __LINE__);

            }
            else {
                // naviState == NAVI_BEGIN
                MCLOGD("WFDStackListener::notifyNaviVoiceInd, in the state do nothing");
                DTLOG_INFO(0x008013, "WFDStackListener::notifyNaviVoiceInd, in the state do nothing");
            }
        }
        else {
            if (mNaviState == NAVI_BEGIN) {
                WFDServiceAVCtr* mediaPlayer = mManager->getMediaPlay();
                if (mediaPlayer != NULL) {
                    int32_t latency = mediaPlayer->getAudioLatency();
                    MCLOGD("WFDStackListener::notifyNaviVoiceInd, latency = %d\n", latency);
                    DTLOG_INFO(0x008013, "WFDStackListener::notifyNaviVoiceInd, latency = %d", latency);
                    if (latency > 0) {
                        if (m_timer.isActive())
                            m_timer.stop();
                        mNaviState = NAVI_ENDING;
                        m_timer.start(latency, true, this, &WFDStackListener::onNaviVoiceLatency);
                    }
                    else{
                        onSendNaviState(NAVI_END);
                    }
                }
            }

            else {
                MCLOGD("WFDStackListener::notifyNaviVoiceInd, in the state do nothing");
                DTLOG_INFO(0x008013, "WFDStackListener::notifyNaviVoiceInd, in the state do nothing");
                // mNaviState == NAVI_ENDING || mNaviState == NAVI_END || mNaviState == NAVI_NULL
            }

        }

    }
}


void WFDStackListener::notifyGPSTimeInd(uint error, uint len, unsigned char* time)   /* __0x008014_DTFUNCID__ */
{
    MCLOGD("WFDStackListener::notifyGPSTimeInd, error = %d, len = %d\n", error, len);
    DTLOG_INFO(0x008014, "notifyGPSTimeInd, error = %d, len = %d", error, len);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        WFDServiceStub* stub = mManager->getServiceStub();
        if (stub != NULL) {
             android::String8 timeDatata;
            if (len > 0) {
                timeDatata  = android::String8(reinterpret_cast<const char*>(time));
            }
            else {
                timeDatata = android::String8("");
            }
            int ret = stub->wfdGetGPSTimeInd(error, len, static_cast<const android::String8>(timeDatata));
            if(BS_NO_ERROR!=ret){
               DTLOG_RET(0x008014, "sendMulticast error,ret =%d",ret);
            }
        }
    }
}

void WFDStackListener::notifyCurrentAppChange(uint appId)   /* __0x008015_DTFUNCID__ */
{
    MCLOGD("WFDStackListener::notifyCurrentAppChange, appId = %d\n", appId);
    DTLOG_INFO(0x008015, "notifyCurrentAppChange, appId = %d", appId);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        WFDServiceStub* stub = mManager->getServiceStub();
        if (stub != NULL)
        {
            if (appId == 0){
                stub->wfdAppDeskInd(APP_ON_DESK);
            }
            else {
                stub->wfdAppDeskInd(APP_NO_DESK);
            }
            wfdLocalInfo localInfo;
            mManager->wfdGetLocalInfoData(localInfo);
            if (localInfo.appMode == MIRROR && appId == 0) {

                    stub->wfdModeChangeReq(APP_ON_DESK);
            }
            WFDServiceReplier* replier = mManager->getServiceReplier();
            SenderId senderId = mManager->getSenderId();
            if (replier != NULL) {
                int ret = replier->wfdCurrentAppChangeInd(senderId, appId);
                if(BS_NO_ERROR!=ret){
                   DTLOG_RET(0x008015, "sendAsyncResponse error,ret =%d",ret);
                }
            }

        }
    }

}

void WFDStackListener::notifyInvalidAppInd(uint state)   /* __0x008016_DTFUNCID__ */
{
    MCLOGD("WFDStackListener::notifyInvalidAppInd, state = %d", state);
    DTLOG_INFO(0x008016, "nnotifyInvalidAppInd, state = %d", state);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        WFDServiceReplier* replier = mManager->getServiceReplier();
        SenderId senderId = mManager->getSenderId();
        if (replier != NULL) {
            int ret = replier->wfdInvalidAppInd(senderId, state);
            if(BS_NO_ERROR!=ret){
               DTLOG_RET(0x008016, "sendAsyncResponse error,ret =%d",ret);
            }
        }
    }
}

void WFDStackListener::notifyModeChangeSuccess(unsigned char mode)   /* __0x008017_DTFUNCID__ */
{
    MCLOGD("WFDStackListener::notifyModeCangeSuccess, mode = %d", mode);
    DTLOG_INFO(0x008017, "notifyModeCangeSuccess, mode = %d", mode);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        WFDServiceStub* stub = mManager->getServiceStub();
        if (stub != NULL) {
            int ret = stub->wfdModeChangeCfm(static_cast<uint32_t>(mode));
            if(BS_NO_ERROR!=ret){
               DTLOG_RET(0x008017, "sendMulticast error,ret =%d",ret);
            }
        }
    }
}

void WFDStackListener::notifyRemoteBtMac(char macLen, char* macAddr)   /* __0x008018_DTFUNCID__ */
{
    MCLOGD("WFDStackListener::notifyRemoteBtMac, macLen = %d, macAddr = %s", macLen, macAddr);
    DTLOG_INFO(0x008018, "notifyRemoteBtMac, macLen = %d, macAddr = %s", macLen, macAddr);
    android::AutoMutex sync(mSyncObj);
    if (macLen == 17){
        uint64_t mac = char2U64(macAddr);
        wfdLocalInfo localInfo;
        mManager->wfdGetLocalInfoData(localInfo);
        localInfo.appBtMac = mac;
        mManager->wfdSetLocalInfoData(localInfo);
        MCLOGD("WFDStackListener::notifyRemoteBtMac,bt mac = %llx, app bt mac = %llx",localInfo.btMac, localInfo.appBtMac);
        if ((localInfo.btMac != 0) && (mac == localInfo.btMac)) {
            MCLOGD("WFDStackListener::notifyRemoteBtMac, bt and App connect the Same phone");
            DTLOG_INFO(0x008018, "bt and App connect the Same phone");
        }
        else if (localInfo.btMac == 0) {
            MCLOGD("WFDStackListener::notifyRemoteBtMac, bt did not connect, do nothing");
            DTLOG_INFO(0x008018, "bt did not connect, do nothing");
        }
        else {
            MCLOGD("WFDStackListener::notifyRemoteBtMac, bt and App connect the different phone");
            DTLOG_ERR(0x008018, "notifyRemoteBtMac, bt and App connect the different phone");
            WFDDeviceState_Sp deviceState = new WFDDeviceState();
            mManager->wfdStateSync(deviceState);
            uint32_t hid = deviceState->getHid();
            if (hid == 1) {
                hid = 0;
                deviceState->setHid(hid);
                mManager->SetWfdState(deviceState);
                WFDServiceStub* stub = mManager->getServiceStub();
                int ret = stub->wfdBtStatus(deviceState->getBt(), hid);
                if(BS_NO_ERROR!=ret){
                   DTLOG_RET(0x008018, "sendMulticast error,ret =%d",ret);
                }
            }
        }

    }
    else{
        MCLOGD("WFDStackListener::notifyRemoteBtMac, uncorrect macAddr");
        DTLOG_INFO(0x008018, "WFDStackListener::notifyRemoteBtMac,uncorrect macAddr");
    }

}

void WFDStackListener::notifyPeerDeviceHdcp(int error)   /* __0x008019_DTFUNCID__ */
{
    android::AutoMutex sync(mSyncObj);
    MCLOGD("notifyPeerDeviceHdcp, hdcpSupport=%d", error);
    DTLOG_INFO(0x008019, "notifyPeerDeviceHdcp, hdcpSupport=%d", error);
    if (mManager == NULL) return;
    wfdLocalInfo localInfo;
    mManager->wfdGetLocalInfoData(localInfo);
    localInfo.hdcpSupport = error;
    mManager->wfdSetLocalInfoData(localInfo);

}

void WFDStackListener::notifySendIDRResult(int error)   /* __0x00801A_DTFUNCID__ */
{
    MCLOGD("%s,error = %d",__func__, error);
    DTLOG_INFO(0x00801A, "%s, err = %d", __func__, error);
    android::AutoMutex sync(mSyncObj);
    if (mManager == NULL) return;
    WFDDeviceState_Sp deviceState = new WFDDeviceState();
    mManager->wfdStateSync(deviceState);
    wfdSvcState state = deviceState->getSvcState();
    if (state != WFD_CONNECTED) return;

    if (WFD_ERR_OK == error) {
        mIDRRetry = MAX_RETRY_TIME;
    }
    else {
        if(mIDRRetry > 0) {
            mIDRRetry--;
            mManager->wfd_sendIDR();
        }
        else {
            mIDRRetry = MAX_RETRY_TIME;
            MCLOGE("%s failed,error = %d",__func__, error);
            DTLOG_ERR(0x00801A, "%s failed err = %d", __func__, error);

        }
    }
}

void WFDStackListener::notifyReceiverId(unsigned long long revId)   /* __0x00801B_DTFUNCID__ */
{
    MCLOGD("notifyReceiverId::revID = %llx", revId);
    DTLOG_INFO(0x00801B, "notifyReceiverId ::revID = %llx", revId);
    android::AutoMutex sync(mSyncObj);
    if (mManager != NULL) {
        WFDServiceStub* stub = mManager->getServiceStub();
        if (stub != NULL) {
            int ret = stub->wfdReceiverId(5, revId);
            if(BS_NO_ERROR!=ret){
               DTLOG_RET(0x00801B, "sendMulticast error,ret =%d",ret);
            }
        }
    }
}

uint64_t WFDStackListener::char2U64(const char* ptr)   /* __0x00801C_DTFUNCID__ */
{
   MCLOGD("WFDStackListener::char2U64");
   uint64_t result = 0;
   for(int i = 0; i < 17; i++) {       
       if ((i%3) == 2) continue;
       if (i != 0) {
           result = result<<4;
       }
       char tmp = CHAR2HEX(ptr[i]);
       result = (result | tmp);       
   }
   return result;
}

void WFDStackListener::onNaviVoiceLatency(Timer *timer)   /* __0x00801D_DTFUNCID__ */
{
    android::AutoMutex sync(mSyncObj);
    onSendNaviState(NAVI_END);

}

void WFDStackListener::onSendNaviState(int naviState)   /* __0x00801E_DTFUNCID__ */
{
    MCLOGD("WFDStackListener::onSendNaviState, naviState = %d", naviState);
    DTLOG_INFO(0x00801E, "onSendNaviState, naviState = %d", naviState);
    mNaviState = naviState;
    if (mManager != NULL) {
        WFDServiceReplier* replier = mManager->getServiceReplier();

        wfdLocalInfo localInfo;
        mManager->wfdGetLocalInfoData(localInfo);
        localInfo.naviState = mNaviState;
        mManager->wfdSetLocalInfoData(localInfo);

        WFDDeviceState_Sp deviceState = new WFDDeviceState();
        mManager->wfdStateSync(deviceState);
        uint16_t soureState = deviceState->getSourceState();

        if (replier != NULL && (soureState == WFD_SOURCE_ON)) {
            SenderId senderId = mManager->getSenderId();
            replier->wfdNaviVoiceInd(senderId, mNaviState);
        }
    }
}

void WFDStackListener::notifyTranportSwitch(TransProtocl method)
{
    MCLOGD("WFDStackListener::notifyTranportSwitch, method = %d\n", method);
    if (mManager != NULL) {
        mManager->onTransSwitchReq(static_cast<int>(method));
    }

}

void WFDStackListener::notifySwitchCompleted(uint result)
{
    MCLOGD("WFDStackListener::notifySwitchCompleted, result = %d\n", result);
    if (mManager != NULL) {
        mManager->onTransSwitchCmp(result);
    }
}

void WFDStackListener::notifyRemoteStaConnected(uint result)
{
    MCLOGD("WFDStackListener::%s, result = %d\n", __func__, result);
    if (mManager != NULL) {
        android::sp<WFDDeviceInfo> deviceInfo = new WFDDeviceInfo();
        wfdLocalInfo localInfo;
        mManager->wfdGetLocalInfoData(localInfo);
        deviceInfo->setAddr(localInfo.reP2pMac);

        WFDServiceStub* stub = mManager->getServiceStub();
        if (stub != NULL) {
            stub->wfdInvitationInd(deviceInfo);
        }
    }
}

}
