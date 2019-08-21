/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#ifndef __WFDSERVICE_REPLIER_H__
#define __WFDSERVICE_REPLIER_H__

#include "StubBase.h"
#include "servicebase/ServiceBaseGlobal.h"
#include "WFDServiceServiceDefines.h"
#include "TouchPoints.h"
#include "WifiAddrST.h"
#include "WFDDeviceInfo.h"
#include "WFDDeviceState.h"
#include "WFDRemoteDeviceInfo.h"
namespace goni {

class ServiceBase;

class WFDServiceReplier
{
public:
    WFDServiceReplier(ServiceBase* owner);
    virtual ~WFDServiceReplier();

    // reply	
    virtual android::status_t wfdSearchResultInd(SenderId id, const WFDDeviceInfo_Sp& deviceInfo);
    virtual android::status_t wfdSearchFinishedInd(SenderId id, const uint32_t& err);
    virtual android::status_t wfdInvalidAppInd(SenderId id, const uint32_t& err);
    virtual android::status_t wfdCurrentAppChangeInd(SenderId id, const uint32_t& err);
    virtual android::status_t wfdNaviVoiceInd(SenderId id, const uint32_t& err);
    virtual android::status_t wfdSourceChangeCfm(SenderId id, const uint32_t& err, const uint32_t& currentMode);
    virtual android::status_t wfdLocalDeviceInd(SenderId id, const uint16_t& nameLen, const std::vector<uint8_t>& name);

private:
    ServiceBase* m_owner;
};
}
#endif
/* EOF */