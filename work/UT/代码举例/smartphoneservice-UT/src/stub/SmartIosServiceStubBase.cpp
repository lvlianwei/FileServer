/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#include "SmartIosServiceStubBase.h"
#include "binder/Parcel.h"
#include "servicebase/ServiceBase.h"
#include "servicebase/SystemLog.h"

namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

SmartIosServiceStubBase::SmartIosServiceStubBase(ServiceBase* owner)    /* __0x202001_DTFUNCID__ */
    : StubBase(owner)
{
    m_owner->createPublisher("multicast");
}

SmartIosServiceStubBase::~SmartIosServiceStubBase()    /* __0x202002_DTFUNCID__ */
{
    m_owner->destroyPublisher("multicast");
}

int SmartIosServiceStubBase::onSyncRequest(unsigned int code, const android::Parcel &data, android::Parcel& _data)    /* __0x202003_DTFUNCID__ */
{
    UNUSED(data);
    switch (code) {
        case METHOD_SMT_GET_DEV_CONNECT_INFO:
        {
            uint8_t connState;
            uint8_t index;
            uint8_t popStatus;
            smt_getDevConnectInfo(connState, index, popStatus);

            _data.writeInt32(connState);
            _data.writeInt32(index);
            _data.writeInt32(popStatus);
            break;
        }
        case METHOD_SMT_GET_DEV_CONNECT_INFO_ANDROID:
        {
            uint8_t connState;
            uint8_t index;
            uint8_t popStatus;
            smt_getDevConnectInfoAndroid(connState, index, popStatus);

            _data.writeInt32(connState);
            _data.writeInt32(index);
            _data.writeInt32(popStatus);
            break;
        }
        default:
            break;
    }

    return 0;
}
int SmartIosServiceStubBase::onAsyncRequest(SenderId &id, unsigned int code, const android::Parcel &data)    /* __0x202004_DTFUNCID__ */
{
    switch (code) {
        case COMMAND_SMT_LAUNCH_SOURCE:
        {
            uint8_t index = data.readInt32();
            SmtIosSource source = static_cast<SmtIosSource>(data.readInt32());
            smt_launchSource(id, index, source);

            break;
        }
        case COMMAND_SMT_LAUNCH_SOURCE_ANDROID:
        {
            uint8_t index = data.readInt32();
            SmtAndroidSource source = static_cast<SmtAndroidSource>(data.readInt32());
            smt_launchSource_Android(id, index, source);

            break;
        }
        case COMMAND_SMT_SET_POP_STATUS:
        {
            SmtSetType setType = static_cast<SmtSetType>(data.readInt32());
            uint8_t index = data.readInt32();
            SmtPopStatus pop = static_cast<SmtPopStatus>(data.readInt32());
            smt_setPopStatus(id, setType, index, pop);

            break;
        }
        case COMMAND_SMT_SET_POP_STATUS_ANDROID:
        {
            SmtSetType setType = static_cast<SmtSetType>(data.readInt32());
            uint8_t index = data.readInt32();
            SmtPopStatusAndroid pop = static_cast<SmtPopStatusAndroid>(data.readInt32());
            smt_setPopStatusAndroid(id, setType, index, pop);

            break;
        }
        case COMMAND_SMT_GET_DEVICE_INFO:
        {
            SmtDevReqType reqType = static_cast<SmtDevReqType>(data.readInt32());
            uint8_t index = data.readInt32();
            smt_getDeviceInfo(id, reqType, index);

            break;
        }
        case COMMAND_SMT_GET_DEVICE_INFO_ANDROID:
        {
            SmtDevReqType reqType = static_cast<SmtDevReqType>(data.readInt32());
            uint8_t index = data.readInt32();
            smt_getDeviceInfoAndroid(id, reqType, index);

            break;
        }
        case COMMAND_SMT_DEL_SINGLE_DEVICE:
        {
            uint8_t index = data.readInt32();
            smt_delSingleDevice(id, index);

            break;
        }
        case COMMAND_SMT_DEL_ALL_DEVICES:
        {
            smt_delAllDevices(id);

            break;
        }
        default:
            break;
    }

    return 0;
}
android::status_t SmartIosServiceStubBase::smtDevConnectInd(const SmtConState_Sp& conState)    /* __0x202005_DTFUNCID__ */
{
    android::Parcel _data;
    _data.writeCString("SmartIosService");
    _data.writeCString("multicast");
    conState->writeToParcel(_data);

    return m_owner->sendMulticast("multicast", MULTICAST_SMT_DEV_CONNECT_IND, _data);
}
android::status_t SmartIosServiceStubBase::smtDevIpa2InsertInd(const uint8_t& state)    /* __0x202006_DTFUNCID__ */
{
    android::Parcel _data;
    _data.writeCString("SmartIosService");
    _data.writeCString("multicast");
    _data.writeInt32(state);

    return m_owner->sendMulticast("multicast", MULTICAST_SMT_DEV_IPA2INSERT_IND, _data);
}

android::status_t SmartIosServiceStubBase::smtDevAndroidInsertInd(const SmtConState_Sp& conState)    /* __0x202007_DTFUNCID__ */
{
    android::Parcel _data;
    _data.writeCString("SmartIosService");
    _data.writeCString("multicast");
    conState->writeToParcelAndorid(_data);

    return m_owner->sendMulticast("multicast", MULTICAST_SMT_DEV_ANDROIDINSERT_IND, _data);
}
}
/* EOF */