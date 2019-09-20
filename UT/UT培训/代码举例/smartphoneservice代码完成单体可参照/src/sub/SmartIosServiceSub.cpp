/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#include "sub/SmartIosServiceSub.h"
#include "servicebase/ServiceBase.h"
#include "servicebase/SystemLog.h"
namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

SmartIosServiceSub::SmartIosServiceSub(ISmartIosServiceSub *replier, ServiceBase* owner)    /* __0x301001_DTFUNCID__ */
    : SubBase(owner, "SmartIosService", "multicast")
    , m_replier(replier)
{
}

SmartIosServiceSub::~SmartIosServiceSub()    /* __0x301002_DTFUNCID__ */
{
}

int SmartIosServiceSub::onMulticast(unsigned int code, const android::Parcel &data)    /* __0x301003_DTFUNCID__ */
{
    switch(code) {
    case MULTICAST_SMT_DEV_CONNECT_IND:
    {
        SmtConState_Sp conState(new SmtConState);
        conState->readFromParcel(data);
        m_replier->smtDevConnectInd(conState);
        break;
    }
    case MULTICAST_SMT_DEV_IPA2INSERT_IND:
    {
        uint8_t state = data.readInt32();
        m_replier->smtDevIpa2InsertInd(state);
        break;
    }
    case MULTICAST_SMT_DEV_ANDROIDINSERT_IND:
    {
        SmtConState_Sp conState(new SmtConState);
        conState->readFromParcelAndorid(data);
        m_replier->smtDevAndroidInsertInd(conState);
        break;
    }
    default:
        break;
    }

    return 0;
}
}
/* EOF */