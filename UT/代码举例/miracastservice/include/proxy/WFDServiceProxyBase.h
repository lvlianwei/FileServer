/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#ifndef GONI_WFDSERVICE_PROXY_BASE_H
#define GONI_WFDSERVICE_PROXY_BASE_H

#include "servicebase/ServiceProxyBase.h"
#include "servicebase/ServiceBaseDefines.h"

#include "servicebase/ServiceBaseGlobal.h"
#include "WFDServiceServiceDefines.h"
#include "TouchPoints.h"
#include "WifiAddrST.h"
#include "WFDDeviceInfo.h"
#include "WFDDeviceState.h"
#include "WFDRemoteDeviceInfo.h"
namespace goni {

class IWFDServiceProxyReplier
{
public:
    virtual ~IWFDServiceProxyReplier() {}

    virtual void onConnected() {}

    virtual void onDisconnected() {}

    // reply	
    virtual android::status_t wfdSearchResultInd(const WFDDeviceInfo_Sp& deviceInfo) { return 0; }
    virtual android::status_t wfdSearchFinishedInd(const uint32_t& err) { return 0; }
    virtual android::status_t wfdInvalidAppInd(const uint32_t& err) { return 0; }
    virtual android::status_t wfdCurrentAppChangeInd(const uint32_t& err) { return 0; }
    virtual android::status_t wfdNaviVoiceInd(const uint32_t& err) { return 0; }
    virtual android::status_t wfdSourceChangeCfm(const uint32_t& err, const uint32_t& currentMode) { return 0; }
    virtual android::status_t wfdLocalDeviceInd(const uint16_t& nameLen, const std::vector<uint8_t>& name) { return 0; }
};

class WFDServiceProxyBase : public ServiceProxyBase
{
public:
    enum Method_Code
    {
        METHOD_WFD_STATE_SYNC = SERVICE_FIRST_TRANSACTION,
        METHOD_WFD_GET_REMOTE_INFO,
        METHOD_WFD_GET_LOCAL_DEVICE,

        METHOD_MAX
    };

    enum Command_Code
    {
        COMMAND_WFD_POWER_ON = METHOD_MAX,
        COMMAND_WFD_POWER_OFF,
        COMMAND_WFD_SOURCE_CHANGE,
        COMMAND_WFD_MIRROR_MODE,
        COMMAND_WFD_SREEN_MODE,
        COMMAND_WFD_GET_GPSTIME,
        COMMAND_WFD_SEND_HARD_KEY,
        COMMAND_WFD_START_SEARCH,
        COMMAND_WFD_STOP_SEARCH,
        COMMAND_WFD_ACCEPT_INVITATION,
        COMMAND_WFD_DISCONNECT,
        COMMAND_WFD_ENABLE_WFD,
        COMMAND_WFD_DISABLE_WFD,
        COMMAND_WFD_PLAY,
        COMMAND_WFD_PAUSE,
        COMMAND_WFD_SEND_UIBCDATA,

        COMMAND_MAX
    };

    enum Notify_Code
    {
        NOTIFY_WFD_SEARCH_RESULT_IND = COMMAND_MAX,
        NOTIFY_WFD_SEARCH_FINISHED_IND,
        NOTIFY_WFD_INVALID_APP_IND,
        NOTIFY_WFD_CURRENT_APP_CHANGE_IND,
        NOTIFY_WFD_NAVI_VOICE_IND,
        NOTIFY_WFD_SOURCE_CHANGE_CFM,
        NOTIFY_WFD_LOCAL_DEVICE_IND,

        NOTIFY_MAX
    };

public:
    WFDServiceProxyBase(IWFDServiceProxyReplier* replier);
    WFDServiceProxyBase(IWFDServiceProxyReplier* replier, int testValue);
    ~WFDServiceProxyBase();

    virtual void onConnected();
    virtual void onDisconnected();

    android::status_t wfdStateSync(WFDDeviceState_Sp& deviceState);
    android::status_t wfdGetRemoteInfo(WFDRemoteDeviceInfo_Sp& remoteInfo);
    android::status_t wfdGetLocalDevice(uint16_t& nameLen, uint8_t& name);
    //General
    android::status_t wfd_powerOn();
    android::status_t wfd_powerOff();
    android::status_t wfd_sourceChange(const uint8_t& mode);
    android::status_t wfd_mirrorMode(const MirrorMode& mode);
    android::status_t wfd_SreenMode(const ScreenMode& mode);
    android::status_t wfd_getGPSTime();
    android::status_t wfd_sendHardKey(const HardKey& key);
    // p2p
    android::status_t wfd_startSearch();
    android::status_t wfd_stopSearch();
    android::status_t wfd_acceptInvitation(const bool& accpet);
    // 
    android::status_t wfd_disconnect();
    android::status_t wfd_enableWfd();
    android::status_t wfd_disableWfd();
    android::status_t wfd_play();
    android::status_t wfd_pause();
    // wfd stack
    android::status_t wfd_sendUIBCData(const TouchType& type, const TouchPoints_SpVec& points);
private:
    virtual int onAsyncResponse(unsigned int code, const android::Parcel &reply);

private:
    IWFDServiceProxyReplier* m_replier;
};
}
#endif
/* EOF */