/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#ifndef __WFDSERVICE_STUB_BASE_H__
#define __WFDSERVICE_STUB_BASE_H__

#include <string>
#include "StubBase.h"
#include "binder/Parcel.h"
#include "servicebase/ServiceBaseDefines.h"

#include "servicebase/ServiceBaseGlobal.h"

#include "WFDServiceServiceDefines.h"
#include "TouchPoints.h"
#include "WifiAddrST.h"
#include "WFDDeviceInfo.h"
#include "WFDDeviceState.h"
#include "WFDRemoteDeviceInfo.h"
namespace goni {
class ServiceBase;

class WFDServiceStubBase : public StubBase
{
public:
    WFDServiceStubBase(ServiceBase* owner);
    virtual ~WFDServiceStubBase();

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

    enum Multicast_Code
    {
        MULTICAST_WFD_APP_STATUS = SERVICE_FIRST_TRANSACTION,
        MULTICAST_WFD_POWER_STATUS,
        MULTICAST_WFD_INVITATION_IND,
        MULTICAST_WFD_CONNECT_RESULT_IND,
        MULTICAST_WFD_DISCONNECT_IND,
        MULTICAST_WFD_BT_STATUS,
        MULTICAST_WFD_START_LISTEN_IND,
        MULTICAST_WFD_MAC_ADDR,
        MULTICAST_WFD_P2P_VERSION,
        MULTICAST_WFD_GET_GPSTIME_IND,
        MULTICAST_WFD_REMOTE_PIXES_INFO,
        MULTICAST_WFD_REMOTE_SRCEEN_CHANGE,
        MULTICAST_WFD_HIDPOINT,
        MULTICAST_WFD_HARDKEY,
        MULTICAST_WFD_MODE_CHANGE_CFM,
        MULTICAST_WFD_RECEIVER_ID,
        MULTICAST_WFD_APP_DESK_IND,
        MULTICAST_WFD_MODE_CHANGE_REQ,
        MULTICAST_WFD_LINK_QUILTY_IND,

        MULTICAST_MAX
    };

private:
    virtual int onSyncRequest(unsigned int code, const android::Parcel &data, android::Parcel& reply);
    virtual int onAsyncRequest(SenderId &id, unsigned int code, const android::Parcel &data);

protected:
    virtual android::status_t wfdStateSync(WFDDeviceState_Sp& deviceState) = 0;
    virtual android::status_t wfdGetRemoteInfo(WFDRemoteDeviceInfo_Sp& remoteInfo) = 0;
    virtual android::status_t wfdGetLocalDevice(uint16_t& nameLen, uint8_t& name) = 0;
    virtual android::status_t wfd_powerOn(SenderId id) = 0;
    virtual android::status_t wfd_powerOff(SenderId id) = 0;
    virtual android::status_t wfd_sourceChange(SenderId id, const uint8_t& mode) = 0;
    virtual android::status_t wfd_mirrorMode(SenderId id, const MirrorMode& mode) = 0;
    virtual android::status_t wfd_SreenMode(SenderId id, const ScreenMode& mode) = 0;
    virtual android::status_t wfd_getGPSTime(SenderId id) = 0;
    virtual android::status_t wfd_sendHardKey(SenderId id, const HardKey& key) = 0;
    virtual android::status_t wfd_startSearch(SenderId id) = 0;
    virtual android::status_t wfd_stopSearch(SenderId id) = 0;
    virtual android::status_t wfd_acceptInvitation(SenderId id, const bool& accpet) = 0;
    virtual android::status_t wfd_disconnect(SenderId id) = 0;
    virtual android::status_t wfd_enableWfd(SenderId id) = 0;
    virtual android::status_t wfd_disableWfd(SenderId id) = 0;
    virtual android::status_t wfd_play(SenderId id) = 0;
    virtual android::status_t wfd_pause(SenderId id) = 0;
    virtual android::status_t wfd_sendUIBCData(SenderId id, const TouchType& type, const TouchPoints_SpVec& points) = 0;

public:
    virtual android::status_t wfdAppStatus(const uint32_t& err);
    virtual android::status_t wfdPowerStatus(const uint32_t& err);
    virtual android::status_t wfdInvitationInd(const WFDDeviceInfo_Sp& deviceInfo);
    virtual android::status_t wfdConnectResultInd(const uint32_t& err);
    virtual android::status_t wfdDisconnectInd(const uint32_t& err);
    virtual android::status_t wfdBtStatus(const uint32_t& bt, const uint32_t& hid);
    virtual android::status_t wfdStartListenInd(const uint32_t& err);
    virtual android::status_t wfdMacAddr(const uint32_t& len, const uint64_t& mac);
    virtual android::status_t wfdP2pVersion(const uint32_t& len, const android::String8& version);
    virtual android::status_t wfdGetGPSTimeInd(const uint32_t& err, const uint32_t& len, const android::String8& time);
    virtual android::status_t wfdRemotePixesInfo(const wfdSvcState& wfdState, const uint32_t& width, const uint32_t& height);
    virtual android::status_t wfdRemoteSrceenChange(const bool& locked, const ScreenMode& mode);
    virtual android::status_t wfdHIDPoint(const uint32_t& pressed, const uint32_t& width, const uint32_t& height);
    virtual android::status_t wfdHardkey(const HardKey& key);
    virtual android::status_t wfdModeChangeCfm(const uint32_t& mode);
    virtual android::status_t wfdReceiverId(const uint32_t& len, const uint64_t& receiverId);
    virtual android::status_t wfdAppDeskInd(const uint32_t& deskFlag);
    virtual android::status_t wfdModeChangeReq(const uint32_t& appId);
    virtual android::status_t wfdLinkQuiltyInd(const int32_t& sig);
};
}
#endif
/* EOF */