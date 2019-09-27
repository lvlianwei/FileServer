#ifndef WFDSERVICE_MULTILISTEN_H
#define WFDSERVICE_MULTILISTEN_H

#include "wifiSub.h"
#include "BtSub.h"
#include "CarplayServiceSub.h"
#include "CarLifeServiceSub.h"
#include "utils/Mutex.h"

namespace goni{

class WFDServiceStub;
class WFDMultiListener : public IwifiSub, public IBtSub, public media::ICarplayServiceSub, public ICarLifeServiceSub, public android::RefBase
{

public:
    
    WFDMultiListener(WFDServiceStub* stub);
    ~WFDMultiListener();
    //multi message from wifi service
    virtual android::status_t p2pPowerStatusNotify(const WIFI_POWER_STATE_E& powerStatus);
    virtual android::status_t p2pConnectStatusNotify(const WIFI_CONNECT_STATE_E& connStatus);
    virtual android::status_t p2pConnectedInfoNotify(const uint16_t& remotePort, const uint32_t& remoteIP, const uint32_t& localIP);
    virtual android::status_t p2pLinkQuiltyNotify(const int32_t& sigStrength);
    virtual android::status_t p2pListenStatusNotify(const WIFI_LISTEN_STATUS_E& status);
    // add for Miracast R2
#if 0
    virtual android::status_t staConnectStatusNotify(const WIFI_CONNECT_STATE_E& connStatus);
    virtual android::status_t staConnectedInfoNotify(const uint16_t& localPort, const uint32_t& remoteIP, const uint32_t& localIP);
#endif
    //multi message from bt service
    virtual android::status_t genOnConnectionChanged(const uint8_t& index, const uint64_t& addr, const android::String8& name, const BT_FUNCTION_E& function, const uint32_t& result);
    virtual android::status_t genOnDisconnectionChanged(const uint8_t& index, const uint64_t& addr, const android::String8& name, const BT_FUNCTION_E& function, const uint32_t& result);

    //multi message from Carlife service
    virtual android::status_t connectStatusReady();
    virtual android::status_t connectStatusExtract();

    //multi message from CarPlay service
    virtual android::status_t CarplayAuthSuccess();
    virtual android::status_t CarplayExtract();

private:
    WFDServiceStub* mStub;
    mutable android::Mutex mSyncObj;

};

}

#endif
