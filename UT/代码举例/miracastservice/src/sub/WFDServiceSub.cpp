/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#include "sub/WFDServiceSub.h"
#include "servicebase/ServiceBase.h"
namespace goni {

WFDServiceSub::WFDServiceSub(IWFDServiceSub *replier, ServiceBase* owner)
    : SubBase(owner, "WFDService", "multicast")
    , m_replier(replier)
{
}

WFDServiceSub::~WFDServiceSub()
{
}

int WFDServiceSub::onMulticast(unsigned int code, const android::Parcel &data)
{
    switch(code) {
    case MULTICAST_WFD_APP_STATUS:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdAppStatus(err);
        break;
    }
    case MULTICAST_WFD_POWER_STATUS:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdPowerStatus(err);
        break;
    }
    case MULTICAST_WFD_INVITATION_IND:
    {
        WFDDeviceInfo_Sp deviceInfo(new WFDDeviceInfo);
        deviceInfo->readFromParcel(data);
        m_replier->wfdInvitationInd(deviceInfo);
        break;
    }
    case MULTICAST_WFD_CONNECT_RESULT_IND:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdConnectResultInd(err);
        break;
    }
    case MULTICAST_WFD_DISCONNECT_IND:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdDisconnectInd(err);
        break;
    }
    case MULTICAST_WFD_BT_STATUS:
    {
        uint32_t bt = data.readInt32();
        uint32_t hid = data.readInt32();
        m_replier->wfdBtStatus(bt, hid);
        break;
    }
    case MULTICAST_WFD_START_LISTEN_IND:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdStartListenInd(err);
        break;
    }
    case MULTICAST_WFD_MAC_ADDR:
    {
        uint32_t len = data.readInt32();
        uint64_t mac = data.readInt64();
        m_replier->wfdMacAddr(len, mac);
        break;
    }
    case MULTICAST_WFD_P2P_VERSION:
    {
        uint32_t len = data.readInt32();
        android::String8 version = data.readString8();
        m_replier->wfdP2pVersion(len, version);
        break;
    }
    case MULTICAST_WFD_GET_GPSTIME_IND:
    {
        uint32_t err = data.readInt32();
        uint32_t len = data.readInt32();
        android::String8 time = data.readString8();
        m_replier->wfdGetGPSTimeInd(err, len, time);
        break;
    }
    case MULTICAST_WFD_REMOTE_PIXES_INFO:
    {
        wfdSvcState wfdState = static_cast<wfdSvcState>(data.readInt32());
        uint32_t width = data.readInt32();
        uint32_t height = data.readInt32();
        m_replier->wfdRemotePixesInfo(wfdState, width, height);
        break;
    }
    case MULTICAST_WFD_REMOTE_SRCEEN_CHANGE:
    {
        bool locked = data.readInt32();
        ScreenMode mode = static_cast<ScreenMode>(data.readInt32());
        m_replier->wfdRemoteSrceenChange(locked, mode);
        break;
    }
    case MULTICAST_WFD_HIDPOINT:
    {
        uint32_t pressed = data.readInt32();
        uint32_t width = data.readInt32();
        uint32_t height = data.readInt32();
        m_replier->wfdHIDPoint(pressed, width, height);
        break;
    }
    case MULTICAST_WFD_HARDKEY:
    {
        HardKey key = static_cast<HardKey>(data.readInt32());
        m_replier->wfdHardkey(key);
        break;
    }
    case MULTICAST_WFD_MODE_CHANGE_CFM:
    {
        uint32_t mode = data.readInt32();
        m_replier->wfdModeChangeCfm(mode);
        break;
    }
    case MULTICAST_WFD_RECEIVER_ID:
    {
        uint32_t len = data.readInt32();
        uint64_t receiverId = data.readInt64();
        m_replier->wfdReceiverId(len, receiverId);
        break;
    }
    case MULTICAST_WFD_APP_DESK_IND:
    {
        uint32_t deskFlag = data.readInt32();
        m_replier->wfdAppDeskInd(deskFlag);
        break;
    }
    case MULTICAST_WFD_MODE_CHANGE_REQ:
    {
        uint32_t appId = data.readInt32();
        m_replier->wfdModeChangeReq(appId);
        break;
    }
    case MULTICAST_WFD_LINK_QUILTY_IND:
    {
        int32_t sig = data.readInt32();
        m_replier->wfdLinkQuiltyInd(sig);
        break;
    }
    }

    return 0;
}
}
/* EOF */