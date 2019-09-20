#ifndef __WFDSERVICE_STUB_H__
#define __WFDSERVICE_STUB_H__

#include "stub/WFDServiceStubBase.h"

namespace goni {

class wfdService;
class WFDServiceReplier;
class WFDServiceManager;

class WFDServiceStub : public WFDServiceStubBase
{
public:
    WFDServiceStub(wfdService* owner);
    ~WFDServiceStub();

    virtual android::status_t wfdStateSync(WFDDeviceState_Sp & deviceState);
    virtual android::status_t wfdGetRemoteInfo(WFDRemoteDeviceInfo_Sp& remoteInfo);
    virtual android::status_t wfdGetLocalDevice(uint16_t& nameLen, uint8_t& name);
    virtual android::status_t wfd_powerOn(SenderId id);
    virtual android::status_t wfd_powerOff(SenderId id);
    virtual android::status_t wfd_sourceChange(SenderId id, const uint8_t& mode);
    virtual android::status_t wfd_mirrorMode(SenderId id, const MirrorMode& mode);
    virtual android::status_t wfd_SreenMode(SenderId id, const ScreenMode& mode);
    virtual android::status_t wfd_getGPSTime(SenderId id);
    virtual android::status_t wfd_sendHardKey(SenderId id, const HardKey& key);
    virtual android::status_t wfd_startSearch(SenderId id);
    virtual android::status_t wfd_stopSearch(SenderId id);
    virtual android::status_t wfd_acceptInvitation(SenderId id, const bool& accpet);
    virtual android::status_t wfd_disconnect(SenderId id);
    virtual android::status_t wfd_enableWfd(SenderId id);
    virtual android::status_t wfd_disableWfd(SenderId id);
    virtual android::status_t wfd_play(SenderId id);
    virtual android::status_t wfd_pause(SenderId id);
    virtual android::status_t wfd_sendUIBCData(SenderId id, const TouchType& type, const TouchPoints_SpVec & points);

    android::status_t onMultiListen(uint8_t opcode, void* msg);
    void initialize();

private:
    WFDServiceReplier* m_replier;
    SenderId m_iapProxyId;
    WFDServiceManager* m_manager;
    WFDServiceStub(WFDServiceStub&);
    WFDServiceStub& operator=(WFDServiceStub&);
};
}
#endif
