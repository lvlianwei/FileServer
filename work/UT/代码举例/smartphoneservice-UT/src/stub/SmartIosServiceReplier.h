/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#ifndef __SMART_IOS_SERVICE_REPLIER_H__
#define __SMART_IOS_SERVICE_REPLIER_H__

#include "StubBase.h"
#include "servicebase/ServiceBaseGlobal.h"
#include "SmartIosServiceServiceDefines.h"
#include "SmtConState.h"
#include "SmtPopState.h"
#include "SmtDeviceInfo.h"
namespace goni {

class ServiceBase;

class SmartIosServiceReplier
{
public:
    SmartIosServiceReplier(ServiceBase* owner);
    virtual ~SmartIosServiceReplier();

    // reply
    virtual android::status_t smtPopStatusInd(SenderId id, const SmtPopState_Sp& pop);
    virtual android::status_t smtPopStatusIndAndroid(SenderId id, const SmtPopState_Sp& pop);
    virtual android::status_t smtDeviceInfoInd(SenderId id, const SmtDeviceInfo_Sp& dev);
    virtual android::status_t smtDeviceInfoIndAndroid(SenderId id, const SmtDeviceInfo_Sp& dev);
    virtual android::status_t smtDelSingleDeviceInd(SenderId id, const uint8_t& index, const uint32_t& err);
    virtual android::status_t smtDelAllDeviceInd(SenderId id, const uint32_t& err);
    virtual android::status_t smtDevInfoCmpInd(SenderId id, const uint32_t& err);

private:
    ServiceBase* m_owner;
};
}
#endif
/* EOF */