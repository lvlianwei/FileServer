/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#ifndef __WFDSERVICE_SUB_H__
#define __WFDSERVICE_SUB_H__

#include <string>
#include "binder/Parcel.h"
#include "SubBase.h"
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

class IWFDServiceSub
{
public:
    virtual ~IWFDServiceSub() {}

    // multicast
    virtual android::status_t wfdAppStatus(const uint32_t& err) { return 0; }
    virtual android::status_t wfdPowerStatus(const uint32_t& err) { return 0; }
    virtual android::status_t wfdInvitationInd(const WFDDeviceInfo_Sp& deviceInfo) { return 0; }
    virtual android::status_t wfdConnectResultInd(const uint32_t& err) { return 0; }
    virtual android::status_t wfdDisconnectInd(const uint32_t& err) { return 0; }
    virtual android::status_t wfdBtStatus(const uint32_t& bt, const uint32_t& hid) { return 0; }
    virtual android::status_t wfdStartListenInd(const uint32_t& err) { return 0; }
    virtual android::status_t wfdMacAddr(const uint32_t& len, const uint64_t& mac) { return 0; }
    virtual android::status_t wfdP2pVersion(const uint32_t& len, const android::String8& version) { return 0; }
    virtual android::status_t wfdGetGPSTimeInd(const uint32_t& err, const uint32_t& len, const android::String8& time) { return 0; }
    // send to Bt	
    virtual android::status_t wfdRemotePixesInfo(const wfdSvcState& wfdState, const uint32_t& width, const uint32_t& height) { return 0; }
    virtual android::status_t wfdRemoteSrceenChange(const bool& locked, const ScreenMode& mode) { return 0; }
    virtual android::status_t wfdHIDPoint(const uint32_t& pressed, const uint32_t& width, const uint32_t& height) { return 0; }
    virtual android::status_t wfdHardkey(const HardKey& key) { return 0; }
    virtual android::status_t wfdModeChangeCfm(const uint32_t& mode) { return 0; }
    virtual android::status_t wfdReceiverId(const uint32_t& len, const uint64_t& receiverId) { return 0; }
    virtual android::status_t wfdAppDeskInd(const uint32_t& deskFlag) { return 0; }
    virtual android::status_t wfdModeChangeReq(const uint32_t& appId) { return 0; }
    virtual android::status_t wfdLinkQuiltyInd(const int32_t& sig) { return 0; }

};

class WFDServiceSub : public SubBase
{
public:
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

public:
    WFDServiceSub(IWFDServiceSub* replier, ServiceBase* owner);
    ~WFDServiceSub();

    virtual int onMulticast(unsigned int code, const android::Parcel &data);

private:
    IWFDServiceSub* m_replier;
    SenderId m_id;

};
}
#endif
/*EOF*/