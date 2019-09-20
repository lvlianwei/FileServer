/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#include "proxy/SmartIosServiceProxyBase.h"
#include "binder/Parcel.h"
#include "servicebase/SystemLog.h"

namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

SmartIosServiceProxyBase::SmartIosServiceProxyBase(ISmartIosServiceProxyReplier* replier)    /* __0x101001_DTFUNCID__ */
    : ServiceProxyBase("SmartIosService", true)
    , m_replier(replier)
{
}
SmartIosServiceProxyBase::~SmartIosServiceProxyBase()    /* __0x101002_DTFUNCID__ */
{
}
void SmartIosServiceProxyBase::onConnected()    /* __0x101003_DTFUNCID__ */
{
    DTLOG_INFO(0x101003, "SmartIosServiceProxyBase::onConnected");
    ServiceProxyBase::onConnected();
    m_replier->onConnected();
}
void SmartIosServiceProxyBase::onDisconnected()    /* __0x101004_DTFUNCID__ */
{
    DTLOG_INFO(0x101004, "SmartIosServiceProxyBase::onDisconnected");
    ServiceProxyBase::onDisconnected();
    m_replier->onDisconnected();
}

android::status_t SmartIosServiceProxyBase::smt_launchSource(const uint8_t& index, const SmtIosSource& source)    /* __0x101005_DTFUNCID__ */
{
    DTLOG_INFO(0x101005, "smt_launchSource index = %d source = %d", index, source);
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(index);
    _data.writeInt32(static_cast<SmtIosSource>(source));
    return sendAsyncRequest(COMMAND_SMT_LAUNCH_SOURCE, _data);
}
android::status_t SmartIosServiceProxyBase::smt_launchSource_Android(const uint8_t& index, const SmtAndroidSource& source)    /* __0x101006_DTFUNCID__ */
{
    DTLOG_INFO(0x101006, "smt_launchSource_Android index = %d source = %d", index, source);
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(index);
    _data.writeInt32(static_cast<SmtIosSource>(source));
    return sendAsyncRequest(COMMAND_SMT_LAUNCH_SOURCE_ANDROID, _data);
}
android::status_t SmartIosServiceProxyBase::smt_setPopStatus(const SmtSetType& setType, const uint8_t& index, const SmtPopStatus& pop)    /* __0x101007_DTFUNCID__ */
{
    DTLOG_INFO(0x101007, "smt_setPopStatus setType = %d index = %d pop = %d", setType, index, pop);
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(static_cast<SmtSetType>(setType));
    _data.writeInt32(index);
    _data.writeInt32(static_cast<SmtPopStatus>(pop));
    return sendAsyncRequest(COMMAND_SMT_SET_POP_STATUS, _data);
}
android::status_t SmartIosServiceProxyBase::smt_setPopStatusAndroid(const SmtSetType& setType, const uint8_t& index, const SmtPopStatusAndroid& pop)    /* __0x101008_DTFUNCID__ */
{
    DTLOG_INFO(0x101008, "smt_setPopStatusAndroid setType = %d index = %d pop = %d", setType, index, pop);
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(static_cast<SmtSetType>(setType));
    _data.writeInt32(index);
    _data.writeInt32(static_cast<SmtPopStatusAndroid>(pop));
    return sendAsyncRequest(COMMAND_SMT_SET_POP_STATUS_ANDROID, _data);
}
android::status_t SmartIosServiceProxyBase::smt_getDeviceInfo(const SmtDevReqType& reqType, const uint8_t& index)    /* __0x101009_DTFUNCID__ */
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(static_cast<SmtDevReqType>(reqType));
    _data.writeInt32(index);
    return sendAsyncRequest(COMMAND_SMT_GET_DEVICE_INFO, _data);
}
android::status_t SmartIosServiceProxyBase::smt_getDeviceInfoAndroid(const SmtDevReqType& reqType, const uint8_t& index)    /* __0x10100A_DTFUNCID__ */
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(static_cast<SmtDevReqType>(reqType));
    _data.writeInt32(index);
    return sendAsyncRequest(COMMAND_SMT_GET_DEVICE_INFO_ANDROID, _data);
}
android::status_t SmartIosServiceProxyBase::smt_delSingleDevice(const uint8_t& index)    /* __0x10100B_DTFUNCID__ */
{
    android::Parcel _data;
    prepareAsyncData(_data);
    _data.writeInt32(index);
    return sendAsyncRequest(COMMAND_SMT_DEL_SINGLE_DEVICE, _data);
}
android::status_t SmartIosServiceProxyBase::smt_delAllDevices()    /* __0x10100C_DTFUNCID__ */
{
    android::Parcel _data;
    prepareAsyncData(_data);
    return sendAsyncRequest(COMMAND_SMT_DEL_ALL_DEVICES, _data);
}
android::status_t SmartIosServiceProxyBase::smt_getDevConnectInfo(uint8_t& connState, uint8_t& index, uint8_t& popStatus)    /* __0x10100D_DTFUNCID__ */
{
    android::Parcel data, _data;
    int ret = sendSyncRequest(METHOD_SMT_GET_DEV_CONNECT_INFO, _data, &data);
    if (ret == BS_NO_ERROR) {
        connState = data.readInt32();
        index = data.readInt32();
        popStatus = data.readInt32();
        DTLOG_INFO(0x10100D, "smt_getDevConnectInfo connState = %d index = %d popStatus = %d", connState, index, popStatus);
    }
    return ret;
}
android::status_t SmartIosServiceProxyBase::smt_getDevConnectInfoAndroid(uint8_t& connState, uint8_t& index, uint8_t& popStatus)    /* __0x10100E_DTFUNCID__ */
{
    android::Parcel data, _data;
    int ret = sendSyncRequest(METHOD_SMT_GET_DEV_CONNECT_INFO_ANDROID, _data, &data);
    if (ret == BS_NO_ERROR) {
        connState = data.readInt32();
        index = data.readInt32();
        popStatus = data.readInt32();
        DTLOG_INFO(0x10100E, "smt_getDevConnectInfoAndroid connState = %d index = %d popStatus = %d", connState, index, popStatus);
    }
    return ret;
}
int SmartIosServiceProxyBase::onAsyncResponse(unsigned int code, const android::Parcel &data)    /* __0x10100F_DTFUNCID__ */
{
    switch(code) {
        case NOTIFY_SMT_POP_STATUS_IND:
        {
            SmtPopState_Sp pop(new SmtPopState);
            pop->readFromParcel(data);
            m_replier->smtPopStatusInd(pop);
            break;
        }
        case NOTIFY_SMT_POP_STATUS_IND_ANDROID:
        {
            SmtPopState_Sp pop(new SmtPopState);
            pop->readFromParcelAndorid(data);
            m_replier->smtPopStatusIndAndroid(pop);
            break;
        }
        case NOTIFY_SMT_DEVICE_INFO_IND:
        {
            SmtDeviceInfo_Sp dev(new SmtDeviceInfo);
            dev->readFromParcel(data);
            m_replier->smtDeviceInfoInd(dev);
            break;
        }
        case NOTIFY_SMT_DEVICE_INFO_IND_ANDROID:
        {
            SmtDeviceInfo_Sp dev(new SmtDeviceInfo);
            dev->readFromParcelAndorid(data);
            m_replier->smtDeviceInfoIndAndroid(dev);
            break;
        }
        case NOTIFY_SMT_DEL_SINGLE_DEVICE_IND:
        {
            uint8_t index = data.readInt32();
            uint32_t err = data.readInt32();
            m_replier->smtDelSingleDeviceInd(index, err);
            break;
        }
        case NOTIFY_SMT_DEL_ALL_DEVICE_IND:
        {
            uint32_t err = data.readInt32();
            m_replier->smtDelAllDeviceInd(err);
            break;
        }
        case NOTIFY_SMT_DEV_INFO_CMP_IND:
        {
            uint32_t err = data.readInt32();
            m_replier->smtDevInfoCmpInd(err);
            break;
        }
        default:
            break;
    }
    return 0;
}
}
/* EOF */