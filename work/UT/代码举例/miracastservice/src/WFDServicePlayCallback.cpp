#include "WFDServicePlayCallback.h"
#include "WFDServiceDefs.h"
#include "WFDServiceReplier.h"
#include "WFDServiceManager.h"
#include "WFDServiceAVCtr.h"
#include "servicebase/SystemLog.h"

namespace goni {
DeclearModuleID(DTMODULEID_WFDSERVICE);
WFDServicePlayCallback::WFDServicePlayCallback(WFDServiceManager* manager, WFDServiceAVCtr* player)               /* __0x006000_DTFUNCID__ */
: mManager(manager)
, mPlayer(player)
, retryTimes(PREPARE_RETRY_TIMES)
{
}

WFDServicePlayCallback::~WFDServicePlayCallback()               /* __0x006001_DTFUNCID__ */
{
}

VOID WFDServicePlayCallback::playStatusChanged(const media::NMMP_PlayStatus &status, INT32 mask)            /* __0x006002_DTFUNCID__ */
{
    MCLOGD("*****%s*****",__func__);
    DTLOG_INFO(0x006002, "WFDServicePlayCallback::playStatusChanged");
    if ((mask&NMMP_PLAYSTATUS_MASK_STATE) == NMMP_PLAYSTATUS_MASK_STATE) {
       if ((status.state == media::NMMP_PlaybackState_Error) && (mPlayer != NULL)) {
           DTLOG_INFO(0x006002, "WFDServicePlayCallback::playStatusChanged error");
           int result = mPlayer->stop();
           if ((result >= 1) && (mManager != NULL)){
               WFDDeviceState_Sp deviceState = new WFDDeviceState();
               mManager->wfdStateSync(deviceState);
               deviceState->setSourceState(WFD_SOURCE_OFF);
               mManager->SetWfdState(deviceState);
               mManager->onPlayerErr();
           }
       }
   }

    else if ((mask&NMMP_PLAYSTATUS_MASK_STATE) == NMMP_PLAYSTATUS_MASK_ERRORID) {
       if ((status.state == media::NMMP_ErrorCode_MiracastProtocolSwitchFailed) && (mPlayer != NULL)) {
           // for transport failed
       }
    }

    else if ((mask&NMMP_PLAYSTATUS_MASK_WARNING) == NMMP_PLAYSTATUS_MASK_WARNING) {
       if ((status.state == media::NMMP_WarningCode_MiracastUdpReady) ||(status.state == media::NMMP_WarningCode_MiracastTcpReady)){
           // for transport  success
           MCLOGD("*****%s*****, transport success",__func__);
           if (mManager != NULL &&mPlayer != NULL) {
               int protocl = ((mPlayer->getProtocl())== TRANS_SWITCH_UDP)?TRANS_SWITCH_TCP:TRANS_SWITCH_UDP;
               mPlayer->setProtocl(protocl);
               mManager->onTransSwitchSuccess(protocl);
           }
       }
       else if ((status.state == media::NMMP_WarningCode_MiracastSwitchToUdpFailed) ||(status.state == media::NMMP_WarningCode_MiracastSwitchToTcpFailed)) {
           // for tranport failed
           MCLOGD("*****%s*****, transport failed",__func__);
       }
       else {
           // do nothing
       }
    }
    else {

    }
}

VOID WFDServicePlayCallback::mediaInfoUpdated(const media::NMMP_MediaInfo &info, INT32 mask)            /* __0x006003_DTFUNCID__ */
{
}

VOID WFDServicePlayCallback::onConnected()          /* __0x006004_DTFUNCID__ */
{
    MCLOGD("*****%s*****",__func__);
    DTLOG_INFO(0x006003, "WFDServicePlayCallback::onConnected");
    mPlayer->initialize();
    if (mPlayer != NULL) {
        PLAYERSTATE state = mPlayer->getPlayerState();
        if (state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PREPARE) {
            mPlayer->setUri(0, 0, 0);
        }
        else {
            mPlayer->setPlayerState(PLAYER_STATE_INIT);
        }
    }
}

VOID WFDServicePlayCallback::onDisconnected()           /* __0x006005_DTFUNCID__ */
{
}

VOID WFDServicePlayCallback::onConnectError(INT32 connErrId)           /* __0x006006_DTFUNCID__ */
{
}

VOID WFDServicePlayCallback::ackPrepare(INT32 retCode, INT64 seqId)        /* __0x006007_DTFUNCID__ */
{
    MCLOGD("*****%s*****, retCode = %d",__func__, retCode);
    DTLOG_INFO(0x006007, "WFDServicePlayCallback::ackPrepare, retCode = %d", retCode);
    if (mManager != NULL) {
        if (retCode == media::NMMP_Ret_NoError) {
            retryTimes = PREPARE_RETRY_TIMES;
            mPlayer->play();
        }
        else { //for prepare failed, to retry 3times
            WFDServiceReplier* replier = mManager->getServiceReplier();
            SenderId senderId = mManager->getSenderId();
            if (retryTimes > 0) {
                int err = mPlayer->stop();
                if (err >= 1) {
                    mPlayer->prepare();
                    retryTimes --;
                }
                else{
                  MCLOGD("*****%s*****, stop failed when prepare retry",__func__);
                  retryTimes = PREPARE_RETRY_TIMES;
                  WFDDeviceState_Sp deviceState = new WFDDeviceState();
                  mManager->wfdStateSync(deviceState);
                  deviceState->setSourceState(WFD_SOURCE_OFF);
                  mManager->SetWfdState(deviceState);
                  if (replier != NULL) {
                      int ret = replier->wfdSourceChangeCfm(senderId, WFD_ACTION_NG, WFD_SOURCE_ON);
                      if (BS_NO_ERROR!=ret) {
                          DTLOG_RET(0x006007, "sendAsyncResponse error1, ret=%d",ret);
                      }
                  }
                }

            }
            else {
                retryTimes = PREPARE_RETRY_TIMES;
                WFDDeviceState_Sp deviceState = new WFDDeviceState();
                mManager->wfdStateSync(deviceState);
                deviceState->setSourceState(WFD_SOURCE_OFF);
                mManager->SetWfdState(deviceState);
                if (replier != NULL) {
                    int ret = replier->wfdSourceChangeCfm(senderId, WFD_ACTION_NG, WFD_SOURCE_ON);
                    if (BS_NO_ERROR!=ret) {
                        DTLOG_RET(0x006007, "sendAsyncResponse error2, ret=%d",ret);
                    }
                }
            }
        }
    }
}


VOID WFDServicePlayCallback::ackPlay(INT32 retCode, INT64 seqId)   /* __0x006008_DTFUNCID__ */
{
    MCLOGD("*****%s*****, retCode = %x, seqId = %x",__func__, retCode, seqId);
    DTLOG_INFO(0x006008, "WFDServicePlayCallback::ackPlay, retCode = %d, seqId = %x", retCode, seqId);
    if (mManager != NULL) {
        WFDServiceReplier* replier = mManager->getServiceReplier();
        SenderId senderId = mManager->getSenderId();
        if (retCode == media::NMMP_Ret_NoError) {
            WFDDeviceState_Sp deviceState = new WFDDeviceState();
            mManager->wfdStateSync(deviceState);
            deviceState->setSourceState(WFD_SOURCE_ON);
            mManager->SetWfdState(deviceState);
            PLAYERSTATE state = PLAYER_STATE_PLAYING;
            mPlayer->setPlayerState(state);
            if (replier != NULL) {
                replier->wfdSourceChangeCfm(senderId, WFD_ACTION_OK, WFD_SOURCE_ON);
                wfdLocalInfo localInfo;
                mManager->wfdGetLocalInfoData(localInfo);
                int ret = replier->wfdNaviVoiceInd(senderId, localInfo.naviState);
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x006008, "sendAsyncResponse error1, ret=%d",ret);
                }
            }
        }
        else {
            WFDDeviceState_Sp deviceState = new WFDDeviceState();
            mManager->wfdStateSync(deviceState);
            deviceState->setSourceState(WFD_SOURCE_OFF);
            mManager->SetWfdState(deviceState);
            if (replier != NULL) {
                int ret = replier->wfdSourceChangeCfm(senderId, WFD_ACTION_NG, WFD_SOURCE_ON);
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x006008, "sendAsyncResponse error2, ret=%d",ret);
                }
            }
        }
    }
}



}
