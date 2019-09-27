/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#ifndef __SMART_IOS_SERVICE_SUB_H__
#define __SMART_IOS_SERVICE_SUB_H__

#include <string>
#include "binder/Parcel.h"
#include "SubBase.h"
#include "servicebase/ServiceBaseDefines.h"
#include "servicebase/ServiceBaseGlobal.h"
#include "SmartIosServiceServiceDefines.h"
#include "SmtConState.h"
#include "SmtPopState.h"
#include "SmtDeviceInfo.h"
namespace goni {
class ServiceBase;

class ISmartIosServiceSub
{
public:
    virtual ~ISmartIosServiceSub() {}

    // multicast
    //multicast smtDevConppStatus(uint err);
    virtual android::status_t smtDevConnectInd(const SmtConState_Sp& conState) {
        UNUSED(conState);
        return 0;
    }
    virtual android::status_t smtDevIpa2InsertInd(const uint8_t& state) {
        UNUSED(state);
        return 0;
    }
    virtual android::status_t smtDevAndroidInsertInd(const SmtConState_Sp& conState) {
        UNUSED(conState);
        return 0;
    }

};

class SmartIosServiceSub : public SubBase
{
public:
    enum Multicast_Code
    {
        MULTICAST_SMT_DEV_CONNECT_IND = SERVICE_FIRST_TRANSACTION,
        MULTICAST_SMT_DEV_IPA2INSERT_IND,
        MULTICAST_SMT_DEV_ANDROIDINSERT_IND,

        MULTICAST_MAX
    };

public:
    SmartIosServiceSub(ISmartIosServiceSub* replier, ServiceBase* owner);
    ~SmartIosServiceSub();

    virtual int onMulticast(unsigned int code, const android::Parcel &data);

private:
    ISmartIosServiceSub* m_replier;
    SenderId m_id;

};
}
#endif
/*EOF*/