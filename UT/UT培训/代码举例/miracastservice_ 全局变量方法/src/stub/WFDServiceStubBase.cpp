/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#include "WFDServiceStubBase.h"
#include "binder/Parcel.h"
#include "servicebase/ServiceBase.h"

namespace goni {

WFDServiceStubBase::WFDServiceStubBase(ServiceBase* owner)
    : StubBase(owner)
{
    m_owner->createPublisher("multicast");
}

WFDServiceStubBase::~WFDServiceStubBase()
{
    m_owner->destroyPublisher("multicast");
}

int WFDServiceStubBase::onSyncRequest(unsigned int code, const android::Parcel &data, android::Parcel& _data)
{
    switch (code) {
    case METHOD_WFD_STATE_SYNC:
    {
        WFDDeviceState_Sp deviceState(new WFDDeviceState);
        wfdStateSync(deviceState);

        deviceState->writeToParcel(_data);
        break;
    }
    case METHOD_WFD_GET_REMOTE_INFO:
    {
        WFDRemoteDeviceInfo_Sp remoteInfo(new WFDRemoteDeviceInfo);
        wfdGetRemoteInfo(remoteInfo);

        remoteInfo->writeToParcel(_data);
        break;
    }
    case METHOD_WFD_GET_LOCAL_DEVICE:
    {
        uint16_t nameLen;
        uint8_t name;
        wfdGetLocalDevice(nameLen, name);

        _data.writeInt32(nameLen);
        _data.writeInt32(name);
        break;
    }
    }

    return 0;
}
int WFDServiceStubBase::onAsyncRequest(SenderId &id, unsigned int code, const android::Parcel &data)
{
    switch (code) {
    case COMMAND_WFD_POWER_ON:
    {
        wfd_powerOn(id);

        break;
    }
    case COMMAND_WFD_POWER_OFF:
    {
        wfd_powerOff(id);

        break;
    }
    case COMMAND_WFD_SOURCE_CHANGE:
    {
        uint8_t mode = data.readInt32();
        wfd_sourceChange(id, mode);

        break;
    }
    case COMMAND_WFD_MIRROR_MODE:
    {
        MirrorMode mode = static_cast<MirrorMode>(data.readInt32());
        wfd_mirrorMode(id, mode);

        break;
    }
    case COMMAND_WFD_SREEN_MODE:
    {
        ScreenMode mode = static_cast<ScreenMode>(data.readInt32());
        wfd_SreenMode(id, mode);

        break;
    }
    case COMMAND_WFD_GET_GPSTIME:
    {
        wfd_getGPSTime(id);

        break;
    }
    case COMMAND_WFD_SEND_HARD_KEY:
    {
        HardKey key = static_cast<HardKey>(data.readInt32());
        wfd_sendHardKey(id, key);

        break;
    }
    case COMMAND_WFD_START_SEARCH:
    {
        wfd_startSearch(id);

        break;
    }
    case COMMAND_WFD_STOP_SEARCH:
    {
        wfd_stopSearch(id);

        break;
    }
    case COMMAND_WFD_ACCEPT_INVITATION:
    {
        bool accpet = data.readInt32();
        wfd_acceptInvitation(id, accpet);

        break;
    }
    case COMMAND_WFD_DISCONNECT:
    {
        wfd_disconnect(id);

        break;
    }
    case COMMAND_WFD_ENABLE_WFD:
    {
        wfd_enableWfd(id);

        break;
    }
    case COMMAND_WFD_DISABLE_WFD:
    {
        wfd_disableWfd(id);

        break;
    }
    case COMMAND_WFD_PLAY:
    {
        wfd_play(id);

        break;
    }
    case COMMAND_WFD_PAUSE:
    {
        wfd_pause(id);

        break;
    }
    case COMMAND_WFD_SEND_UIBCDATA:
    {
        TouchType type = static_cast<TouchType>(data.readInt32());
        TouchPoints_SpVec points;
        {
            int _len = data.readInt32();
            points.clear();
            for (int i = 0; i < _len; i++) {
                TouchPoints_Sp _tmp(new TouchPoints);
                _tmp->readFromParcel(data);
                points.push_back(_tmp);
            }
        }
        wfd_sendUIBCData(id, type, points);

        break;
    }
    }

    return 0;
}
android::status_t WFDServiceStubBase::wfdAppStatus(const uint32_t& err)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(err);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_APP_STATUS, _data);
}
android::status_t WFDServiceStubBase::wfdPowerStatus(const uint32_t& err)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(err);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_POWER_STATUS, _data);
}
android::status_t WFDServiceStubBase::wfdInvitationInd(const WFDDeviceInfo_Sp& deviceInfo)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    deviceInfo->writeToParcel(_data);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_INVITATION_IND, _data);
}
android::status_t WFDServiceStubBase::wfdConnectResultInd(const uint32_t& err)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(err);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_CONNECT_RESULT_IND, _data);
}
android::status_t WFDServiceStubBase::wfdDisconnectInd(const uint32_t& err)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(err);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_DISCONNECT_IND, _data);
}
android::status_t WFDServiceStubBase::wfdBtStatus(const uint32_t& bt, const uint32_t& hid)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(bt);
    _data.writeInt32(hid);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_BT_STATUS, _data);
}
android::status_t WFDServiceStubBase::wfdStartListenInd(const uint32_t& err)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(err);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_START_LISTEN_IND, _data);
}
android::status_t WFDServiceStubBase::wfdMacAddr(const uint32_t& len, const uint64_t& mac)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(len);
    _data.writeInt64(mac);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_MAC_ADDR, _data);
}
android::status_t WFDServiceStubBase::wfdP2pVersion(const uint32_t& len, const android::String8& version)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(len);
    _data.writeString8(version);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_P2P_VERSION, _data);
}
android::status_t WFDServiceStubBase::wfdGetGPSTimeInd(const uint32_t& err, const uint32_t& len, const android::String8& time)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(err);
    _data.writeInt32(len);
    _data.writeString8(time);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_GET_GPSTIME_IND, _data);
}
android::status_t WFDServiceStubBase::wfdRemotePixesInfo(const wfdSvcState& wfdState, const uint32_t& width, const uint32_t& height)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(static_cast<wfdSvcState>(wfdState));
    _data.writeInt32(width);
    _data.writeInt32(height);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_REMOTE_PIXES_INFO, _data);
}
android::status_t WFDServiceStubBase::wfdRemoteSrceenChange(const bool& locked, const ScreenMode& mode)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(locked);
    _data.writeInt32(static_cast<ScreenMode>(mode));

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_REMOTE_SRCEEN_CHANGE, _data);
}
android::status_t WFDServiceStubBase::wfdHIDPoint(const uint32_t& pressed, const uint32_t& width, const uint32_t& height)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(pressed);
    _data.writeInt32(width);
    _data.writeInt32(height);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_HIDPOINT, _data);
}
android::status_t WFDServiceStubBase::wfdHardkey(const HardKey& key)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(static_cast<HardKey>(key));

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_HARDKEY, _data);
}
android::status_t WFDServiceStubBase::wfdModeChangeCfm(const uint32_t& mode)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(mode);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_MODE_CHANGE_CFM, _data);
}
android::status_t WFDServiceStubBase::wfdReceiverId(const uint32_t& len, const uint64_t& receiverId)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(len);
    _data.writeInt64(receiverId);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_RECEIVER_ID, _data);
}
android::status_t WFDServiceStubBase::wfdAppDeskInd(const uint32_t& deskFlag)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(deskFlag);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_APP_DESK_IND, _data);
}
android::status_t WFDServiceStubBase::wfdModeChangeReq(const uint32_t& appId)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(appId);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_MODE_CHANGE_REQ, _data);
}
android::status_t WFDServiceStubBase::wfdLinkQuiltyInd(const int32_t& sig)
{
    android::Parcel _data;
    _data.writeCString("WFDService");
    _data.writeCString("multicast");
    _data.writeInt32(sig);

    return m_owner->sendMulticast("multicast", MULTICAST_WFD_LINK_QUILTY_IND, _data);
}
}
/* EOF */