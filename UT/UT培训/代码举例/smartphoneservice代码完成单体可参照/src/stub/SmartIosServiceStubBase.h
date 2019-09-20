/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#ifndef __SMART_IOS_SERVICE_STUB_BASE_H__
#define __SMART_IOS_SERVICE_STUB_BASE_H__

#include <string>
#include "StubBase.h"
#include "binder/Parcel.h"
#include "servicebase/ServiceBaseDefines.h"

#include "servicebase/ServiceBaseGlobal.h"

#include "SmartIosServiceServiceDefines.h"
#include "SmtConState.h"
#include "SmtPopState.h"
#include "SmtDeviceInfo.h"
namespace goni {
class ServiceBase;

class SmartIosServiceStubBase : public StubBase
{
public:
    SmartIosServiceStubBase(ServiceBase* owner);
    virtual ~SmartIosServiceStubBase();

    enum Method_Code
    {
        METHOD_SMT_GET_DEV_CONNECT_INFO = SERVICE_FIRST_TRANSACTION,
        METHOD_SMT_GET_DEV_CONNECT_INFO_ANDROID,

        METHOD_MAX
    };

    enum Command_Code
    {
        COMMAND_SMT_LAUNCH_SOURCE = METHOD_MAX,
        COMMAND_SMT_SET_POP_STATUS,
        COMMAND_SMT_SET_POP_STATUS_ANDROID,
        COMMAND_SMT_GET_DEVICE_INFO,
        COMMAND_SMT_GET_DEVICE_INFO_ANDROID,
        COMMAND_SMT_DEL_SINGLE_DEVICE,
        COMMAND_SMT_DEL_ALL_DEVICES,
        COMMAND_SMT_LAUNCH_SOURCE_ANDROID,

        COMMAND_MAX
    };

    enum Notify_Code
    {
        NOTIFY_SMT_POP_STATUS_IND = COMMAND_MAX,
        NOTIFY_SMT_POP_STATUS_IND_ANDROID,
        NOTIFY_SMT_DEVICE_INFO_IND,
        NOTIFY_SMT_DEVICE_INFO_IND_ANDROID,
        NOTIFY_SMT_DEL_SINGLE_DEVICE_IND,
        NOTIFY_SMT_DEL_ALL_DEVICE_IND,
        NOTIFY_SMT_DEV_INFO_CMP_IND,

        NOTIFY_MAX
    };

    enum Multicast_Code
    {
        MULTICAST_SMT_DEV_CONNECT_IND = SERVICE_FIRST_TRANSACTION,
        MULTICAST_SMT_DEV_IPA2INSERT_IND,
        MULTICAST_SMT_DEV_ANDROIDINSERT_IND,

        MULTICAST_MAX
    };

private:
    virtual int onSyncRequest(unsigned int code, const android::Parcel &data, android::Parcel& reply);
    virtual int onAsyncRequest(SenderId &id, unsigned int code, const android::Parcel &data);

protected:
    virtual android::status_t smt_launchSource(SenderId id, const uint8_t& index, const SmtIosSource& source) = 0;
    virtual android::status_t smt_launchSource_Android(SenderId id, const uint8_t& index, const SmtAndroidSource& source) = 0;
    virtual android::status_t smt_setPopStatus(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatus& pop) = 0;
    virtual android::status_t smt_setPopStatusAndroid(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatusAndroid& pop) = 0;
    virtual android::status_t smt_getDeviceInfo(SenderId id, const SmtDevReqType& reqType, const uint8_t& index) = 0;
    virtual android::status_t smt_getDeviceInfoAndroid(SenderId id, const SmtDevReqType& reqType, const uint8_t& index) = 0;
    virtual android::status_t smt_delSingleDevice(SenderId id, const uint8_t& index) = 0;
    virtual android::status_t smt_delAllDevices(SenderId id) = 0;
    virtual android::status_t smt_getDevConnectInfo(uint8_t& connState, uint8_t& index, uint8_t& popStatus) = 0;
    virtual android::status_t smt_getDevConnectInfoAndroid(uint8_t& connState, uint8_t& index, uint8_t& popStatus) = 0;

public:
    virtual android::status_t smtDevConnectInd(const SmtConState_Sp& conState);
    virtual android::status_t smtDevIpa2InsertInd(const uint8_t& state);
    virtual android::status_t smtDevAndroidInsertInd(const SmtConState_Sp& conState);
};
}
#endif
/* EOF */