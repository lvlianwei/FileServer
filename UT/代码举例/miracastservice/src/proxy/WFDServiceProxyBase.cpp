/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#include "proxy/WFDServiceProxyBase.h"
#include "binder/Parcel.h"

namespace goni {

WFDServiceProxyBase::WFDServiceProxyBase(IWFDServiceProxyReplier* replier)
    : ServiceProxyBase("WFDService", true)
    , m_replier(replier)
{
}
WFDServiceProxyBase::WFDServiceProxyBase(IWFDServiceProxyReplier* replier, int testValue)
    : ServiceProxyBase("WFDService", false, false)
    , m_replier(replier)
{
}
WFDServiceProxyBase::~WFDServiceProxyBase()
{
}
void WFDServiceProxyBase::onConnected()
{
    ServiceProxyBase::onConnected();
    m_replier->onConnected();
}
void WFDServiceProxyBase::onDisconnected()
{
    ServiceProxyBase::onDisconnected();
    m_replier->onDisconnected();
}

android::status_t WFDServiceProxyBase::wfdStateSync(WFDDeviceState_Sp& deviceState)
{
    android::Parcel data, _data;
    int ret = sendSyncRequest(METHOD_WFD_STATE_SYNC, _data, &data);
    if (ret == BS_NO_ERROR) {
        deviceState->readFromParcel(data);
    }
    return ret;
}
android::status_t WFDServiceProxyBase::wfdGetRemoteInfo(WFDRemoteDeviceInfo_Sp& remoteInfo)
{
    android::Parcel data, _data;
    int ret = sendSyncRequest(METHOD_WFD_GET_REMOTE_INFO, _data, &data);
    if (ret == BS_NO_ERROR) {
        remoteInfo->readFromParcel(data);
    }
    return ret;
}
android::status_t WFDServiceProxyBase::wfdGetLocalDevice(uint16_t& nameLen, uint8_t& name)
{
    android::Parcel data, _data;
    int ret = sendSyncRequest(METHOD_WFD_GET_LOCAL_DEVICE, _data, &data);
    if (ret == BS_NO_ERROR) {
        nameLen = data.readInt32();
        name = data.readInt32();
    }
    return ret;
}
android::status_t WFDServiceProxyBase::wfd_powerOn()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_POWER_ON, _data);
}
android::status_t WFDServiceProxyBase::wfd_powerOff()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_POWER_OFF, _data);
}
android::status_t WFDServiceProxyBase::wfd_sourceChange(const uint8_t& mode)
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(mode);
    return sendAsyncRequest(COMMAND_WFD_SOURCE_CHANGE, _data);
}
android::status_t WFDServiceProxyBase::wfd_mirrorMode(const MirrorMode& mode)
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(static_cast<MirrorMode>(mode));
    return sendAsyncRequest(COMMAND_WFD_MIRROR_MODE, _data);
}
android::status_t WFDServiceProxyBase::wfd_SreenMode(const ScreenMode& mode)
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(static_cast<ScreenMode>(mode));
    return sendAsyncRequest(COMMAND_WFD_SREEN_MODE, _data);
}
android::status_t WFDServiceProxyBase::wfd_getGPSTime()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_GET_GPSTIME, _data);
}
android::status_t WFDServiceProxyBase::wfd_sendHardKey(const HardKey& key)
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(static_cast<HardKey>(key));
    return sendAsyncRequest(COMMAND_WFD_SEND_HARD_KEY, _data);
}
android::status_t WFDServiceProxyBase::wfd_startSearch()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_START_SEARCH, _data);
}
android::status_t WFDServiceProxyBase::wfd_stopSearch()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_STOP_SEARCH, _data);
}
android::status_t WFDServiceProxyBase::wfd_acceptInvitation(const bool& accpet)
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(accpet);
    return sendAsyncRequest(COMMAND_WFD_ACCEPT_INVITATION, _data);
}
android::status_t WFDServiceProxyBase::wfd_disconnect()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_DISCONNECT, _data);
}
android::status_t WFDServiceProxyBase::wfd_enableWfd()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_ENABLE_WFD, _data);
}
android::status_t WFDServiceProxyBase::wfd_disableWfd()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_DISABLE_WFD, _data);
}
android::status_t WFDServiceProxyBase::wfd_play()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_PLAY, _data);
}
android::status_t WFDServiceProxyBase::wfd_pause()
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_WFD_PAUSE, _data);
}
android::status_t WFDServiceProxyBase::wfd_sendUIBCData(const TouchType& type, const TouchPoints_SpVec& points)
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(static_cast<TouchType>(type));
    {
        _data.writeInt32(points.size());
        TouchPoints_SpVec::const_iterator it = points.begin();
        for (; it != points.end(); it++) {
            (*it)->writeToParcel(_data);
        }
    }
    return sendAsyncRequest(COMMAND_WFD_SEND_UIBCDATA, _data);
}
int WFDServiceProxyBase::onAsyncResponse(unsigned int code, const android::Parcel &data)
{
    switch(code) {
    case NOTIFY_WFD_SEARCH_RESULT_IND:
    {
        WFDDeviceInfo_Sp deviceInfo(new WFDDeviceInfo);
        deviceInfo->readFromParcel(data);
        m_replier->wfdSearchResultInd(deviceInfo);
        break;
    }
    case NOTIFY_WFD_SEARCH_FINISHED_IND:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdSearchFinishedInd(err);
        break;
    }
    case NOTIFY_WFD_INVALID_APP_IND:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdInvalidAppInd(err);
        break;
    }
    case NOTIFY_WFD_CURRENT_APP_CHANGE_IND:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdCurrentAppChangeInd(err);
        break;
    }
    case NOTIFY_WFD_NAVI_VOICE_IND:
    {
        uint32_t err = data.readInt32();
        m_replier->wfdNaviVoiceInd(err);
        break;
    }
    case NOTIFY_WFD_SOURCE_CHANGE_CFM:
    {
        uint32_t err = data.readInt32();
        uint32_t currentMode = data.readInt32();
        m_replier->wfdSourceChangeCfm(err, currentMode);
        break;
    }
    case NOTIFY_WFD_LOCAL_DEVICE_IND:
    {
        uint16_t nameLen = data.readInt32();
        std::vector<uint8_t> name;
        {
            int _len = data.readInt32();
            uint8_t* _tmp_data = (uint8_t*)malloc(_len * sizeof(uint8_t));
            data.read(_tmp_data, _len*sizeof(uint8_t));
            name = std::vector<uint8_t>(_tmp_data, _tmp_data+_len);
            free(_tmp_data);
        }
        m_replier->wfdLocalDeviceInd(nameLen, name);
        break;
    }
    }
    return 0;
}
}
/* EOF */