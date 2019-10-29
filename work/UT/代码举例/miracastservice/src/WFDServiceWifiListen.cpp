#include "WFDServiceWifiListen.h"
#include "WFDServiceManager.h"
#include "WFDServiceDefs.h"
#include "wfdServiceStub.h"
#include "WFDServiceSetting.h"
namespace goni{


WFDWifiListener::WFDWifiListener(WFDServiceManager* manager)
:wfdManager(manager)
{
}

WFDWifiListener::~WFDWifiListener()
{    
}

void WFDWifiListener::onConnected()
{
     MCLOGD("WFDWifiListener::onConnected");
     if (wfdManager != NULL) {
        WFDSetting* setting = wfdManager->getWFDSetting();
        if (setting != NULL) {
            if (setting->getWFDPower()){
                wfdManager->wfd_powerOn();
            }
            else {
                WFDServiceStub* stub = wfdManager->getServiceStub();
                stub->wfdPowerStatus(WFD_POWER_OFF);

            }
        }
     }

}

void WFDWifiListener::onDisconnected()
{
}


android::status_t WFDWifiListener::p2pInvitationNotify(const android::String8& devName, const uint64_t& macAddr)
{
    MCLOGD("WFDWifiListener::p2pInvitationNotify");
    android::AutoMutex sync(mSyncObj);
    if (NULL != wfdManager) {
        wfdManager->onInvitationInd(devName, macAddr);
    }
    return 0;
}


android::status_t WFDWifiListener::p2pSyncStatusEvt(const p2pSyncStatusData_Sp & wifiData)
{
    MCLOGD("WFDWifiListener::p2pSyncStatusEvt");
    android::AutoMutex sync(mSyncObj);
    if (NULL != wfdManager) {
        WFDServiceStub* stub = wfdManager->getServiceStub();
        if (NULL != stub) {
            const uint32_t macLen = 6;
            const uint64_t mac = wifiData->getMac();
            const android::String8 version = wifiData->getVer();
            const uint32_t verLen = version.length();
            stub->wfdMacAddr(macLen, mac);
            stub->wfdP2pVersion(verLen, version);
        }
    }
    return 0;
}


}
