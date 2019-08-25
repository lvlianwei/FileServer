#ifndef WFDSERVICE_WIFILISTEN_H
#define WFDSERVICE_WIFILISTEN_H

#include "wifiProxyBase.h"
#include "utils/Mutex.h"

namespace goni{

class WFDServiceManager;
class WFDWifiListener : public IwifiProxyReplier , public android::RefBase
{
public:

WFDWifiListener(WFDServiceManager* manager);
~WFDWifiListener();
    virtual void onConnected();

    virtual void onDisconnected();

    virtual android::status_t p2pInvitationNotify(const android::String8& devName, const uint64_t& macAddr);
    virtual android::status_t p2pSyncStatusEvt(const p2pSyncStatusData_Sp & wifiData);

private:
    WFDServiceManager* wfdManager;
    mutable android::Mutex mSyncObj;
    WFDWifiListener(WFDWifiListener&);
    WFDWifiListener& operator=(WFDWifiListener&);
};



}

#endif
