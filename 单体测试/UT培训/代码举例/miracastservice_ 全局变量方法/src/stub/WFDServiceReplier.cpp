/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#include "WFDServiceReplier.h"
#include "binder/Parcel.h"
#include "servicebase/ServiceBase.h"
#include "WFDServiceStubBase.h"

namespace goni {

WFDServiceReplier::WFDServiceReplier(ServiceBase* owner)
    :m_owner(owner)
{
}
WFDServiceReplier::~WFDServiceReplier() {}

android::status_t WFDServiceReplier::wfdSearchResultInd(SenderId id, const WFDDeviceInfo_Sp& deviceInfo)
{
    android::Parcel _data;
    deviceInfo->writeToParcel(_data);

    m_owner->sendAsyncResponse(id, WFDServiceStubBase::NOTIFY_WFD_SEARCH_RESULT_IND, _data);
    return 0;
}
android::status_t WFDServiceReplier::wfdSearchFinishedInd(SenderId id, const uint32_t& err)
{
    android::Parcel _data;
    _data.writeInt32(err);

    m_owner->sendAsyncResponse(id, WFDServiceStubBase::NOTIFY_WFD_SEARCH_FINISHED_IND, _data);
    return 0;
}
android::status_t WFDServiceReplier::wfdInvalidAppInd(SenderId id, const uint32_t& err)
{
    android::Parcel _data;
    _data.writeInt32(err);

    m_owner->sendAsyncResponse(id, WFDServiceStubBase::NOTIFY_WFD_INVALID_APP_IND, _data);
    return 0;
}
android::status_t WFDServiceReplier::wfdCurrentAppChangeInd(SenderId id, const uint32_t& err)
{
    android::Parcel _data;
    _data.writeInt32(err);

    m_owner->sendAsyncResponse(id, WFDServiceStubBase::NOTIFY_WFD_CURRENT_APP_CHANGE_IND, _data);
    return 0;
}
android::status_t WFDServiceReplier::wfdNaviVoiceInd(SenderId id, const uint32_t& err)
{
    android::Parcel _data;
    _data.writeInt32(err);

    m_owner->sendAsyncResponse(id, WFDServiceStubBase::NOTIFY_WFD_NAVI_VOICE_IND, _data);
    return 0;
}
android::status_t WFDServiceReplier::wfdSourceChangeCfm(SenderId id, const uint32_t& err, const uint32_t& currentMode)
{
    android::Parcel _data;
    _data.writeInt32(err);
    _data.writeInt32(currentMode);

    m_owner->sendAsyncResponse(id, WFDServiceStubBase::NOTIFY_WFD_SOURCE_CHANGE_CFM, _data);
    return 0;
}
android::status_t WFDServiceReplier::wfdLocalDeviceInd(SenderId id, const uint16_t& nameLen, const std::vector<uint8_t>& name)
{
    android::Parcel _data;
    _data.writeInt32(nameLen);
    _data.writeInt32(name.size());
    _data.write(&name[0], name.size() * sizeof(uint8_t));

    m_owner->sendAsyncResponse(id, WFDServiceStubBase::NOTIFY_WFD_LOCAL_DEVICE_IND, _data);
    return 0;
}
}
/* EOF */