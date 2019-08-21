/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#include "SmartIosServiceReplier.h"
#include "binder/Parcel.h"
#include "servicebase/ServiceBase.h"
#include "SmartIosServiceStubBase.h"
#include "servicebase/SystemLog.h"

namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

SmartIosServiceReplier::SmartIosServiceReplier(ServiceBase* owner)    /* __0x201001_DTFUNCID__ */
    :m_owner(owner)
{
}
SmartIosServiceReplier::~SmartIosServiceReplier() {}    /* __0x201002_DTFUNCID__ */

android::status_t SmartIosServiceReplier::smtPopStatusInd(SenderId id, const SmtPopState_Sp& pop)    /* __0x201003_DTFUNCID__ */
{
    android::Parcel _data;
    pop->writeToParcel(_data);

    m_owner->sendAsyncResponse(id, SmartIosServiceStubBase::NOTIFY_SMT_POP_STATUS_IND, _data);
    return 0;
}
android::status_t SmartIosServiceReplier::smtPopStatusIndAndroid(SenderId id, const SmtPopState_Sp& pop)    /* __0x201004_DTFUNCID__ */
{
    android::Parcel _data;
    pop->writeToParcelAndorid(_data);

    m_owner->sendAsyncResponse(id, SmartIosServiceStubBase::NOTIFY_SMT_POP_STATUS_IND_ANDROID, _data);
    return 0;
}
android::status_t SmartIosServiceReplier::smtDeviceInfoInd(SenderId id, const SmtDeviceInfo_Sp& dev)    /* __0x201005_DTFUNCID__ */
{
    android::Parcel _data;
    dev->writeToParcel(_data);

    m_owner->sendAsyncResponse(id, SmartIosServiceStubBase::NOTIFY_SMT_DEVICE_INFO_IND, _data);
    return 0;
}
android::status_t SmartIosServiceReplier::smtDeviceInfoIndAndroid(SenderId id, const SmtDeviceInfo_Sp& dev)    /* __0x201006_DTFUNCID__ */
{
    android::Parcel _data;
    dev->writeToParcelAndorid(_data);

    m_owner->sendAsyncResponse(id, SmartIosServiceStubBase::NOTIFY_SMT_DEVICE_INFO_IND_ANDROID, _data);
    return 0;
}
android::status_t SmartIosServiceReplier::smtDelSingleDeviceInd(SenderId id, const uint8_t& index, const uint32_t& err)    /* __0x201007_DTFUNCID__ */
{
    android::Parcel _data;
    _data.writeInt32(index);
    _data.writeInt32(err);

    m_owner->sendAsyncResponse(id, SmartIosServiceStubBase::NOTIFY_SMT_DEL_SINGLE_DEVICE_IND, _data);
    return 0;
}
android::status_t SmartIosServiceReplier::smtDelAllDeviceInd(SenderId id, const uint32_t& err)    /* __0x201008_DTFUNCID__ */
{
    android::Parcel _data;
    _data.writeInt32(err);

    m_owner->sendAsyncResponse(id, SmartIosServiceStubBase::NOTIFY_SMT_DEL_ALL_DEVICE_IND, _data);
    return 0;
}
android::status_t SmartIosServiceReplier::smtDevInfoCmpInd(SenderId id, const uint32_t& err)    /* __0x201009_DTFUNCID__ */
{
    android::Parcel _data;
    _data.writeInt32(err);

    m_owner->sendAsyncResponse(id, SmartIosServiceStubBase::NOTIFY_SMT_DEV_INFO_CMP_IND, _data);
    return 0;
}
}
/* EOF */