/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#ifndef GONI_SMART_IOS_SERVICE_PROXY_BASE_H
#define GONI_SMART_IOS_SERVICE_PROXY_BASE_H

#include "servicebase/ServiceProxyBase.h"
#include "servicebase/ServiceBaseDefines.h"

#include "servicebase/ServiceBaseGlobal.h"
#include "SmartIosServiceServiceDefines.h"
#include "SmtConState.h"
#include "SmtPopState.h"
#include "SmtDeviceInfo.h"
namespace goni {

class ISmartIosServiceProxyReplier
{
public:
    virtual ~ISmartIosServiceProxyReplier() {}

    virtual void onConnected() {}

    virtual void onDisconnected() {}

    // reply
    virtual android::status_t smtPopStatusInd(const SmtPopState_Sp& pop) { 
        UNUSED(pop);
        return 0;
    }
    virtual android::status_t smtPopStatusIndAndroid(const SmtPopState_Sp& pop) { 
        UNUSED(pop);
        return 0;
    }
    virtual android::status_t smtDeviceInfoInd(const SmtDeviceInfo_Sp& dev) {
        UNUSED(dev);
        return 0;
    }
    virtual android::status_t smtDeviceInfoIndAndroid(const SmtDeviceInfo_Sp& dev) {
        UNUSED(dev);
        return 0;
    }
    virtual android::status_t smtDelSingleDeviceInd(const uint8_t& index, const uint32_t& err) {
        UNUSED(index);
        UNUSED(err);
        return 0;
    }
    virtual android::status_t smtDelAllDeviceInd(const uint32_t& err) {
        UNUSED(err);
        return 0;
    }
    virtual android::status_t smtDevInfoCmpInd(const uint32_t& err) {
        UNUSED(err);
        return 0;
    }
};

class SmartIosServiceProxyBase : public ServiceProxyBase
{
public:
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

public:
    SmartIosServiceProxyBase(ISmartIosServiceProxyReplier* replier);
    ~SmartIosServiceProxyBase();

    virtual void onConnected();
    virtual void onDisconnected();

    //void smtStateSync(out WFDDeviceState deviceState) ;
    //void smtGetRemoteInfo(out WFDRemoteDeviceInfo remoteInfo);
    //void smtGetLocalDevice(out uint16 nameLen, out uint8* name);
    //General
    android::status_t smt_launchSource(const uint8_t& index, const SmtIosSource& source);
    android::status_t smt_launchSource_Android(const uint8_t& index, const SmtAndroidSource& source);
    android::status_t smt_setPopStatus(const SmtSetType& setType, const uint8_t& index, const SmtPopStatus& pop);
    android::status_t smt_setPopStatusAndroid(const SmtSetType& setType, const uint8_t& index, const SmtPopStatusAndroid& pop);
    android::status_t smt_getDeviceInfo(const SmtDevReqType& reqType, const uint8_t& index);
    android::status_t smt_getDeviceInfoAndroid(const SmtDevReqType& reqType, const uint8_t& index);
    android::status_t smt_delSingleDevice(const uint8_t& index);
    android::status_t smt_delAllDevices();
    android::status_t smt_getDevConnectInfo(uint8_t& connState, uint8_t& index, uint8_t& popStatus);
    android::status_t smt_getDevConnectInfoAndroid(uint8_t& connState, uint8_t& index, uint8_t& popStatus);
private:
    virtual int onAsyncResponse(unsigned int code, const android::Parcel &reply);

private:
    ISmartIosServiceProxyReplier* m_replier;
};
}
#endif
/* EOF */