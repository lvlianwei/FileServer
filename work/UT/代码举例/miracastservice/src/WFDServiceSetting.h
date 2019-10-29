#ifndef WFDSERVICE_SERSETTING_H
#define WFDSERVICE_SERSETTING_H
#ifndef UT_GTEST_FULL_ENG
#include "proxy/SettingProxy.h"
#else
#include "../test/testSettingProxy.h"
#endif

namespace goni {

class WFDServiceManager;

class WFDSetting:public SettingProxy
{
public:
    WFDSetting(WFDServiceManager* manager);
    ~WFDSetting() {}

    bool getWFDPower();
    bool getHorizontalSetting();
    bool getSyncGPSTime();

    virtual void onNotifyUpdate(const std::string &key, const std::string &value);

 private:
    WFDServiceManager* mManager;
    WFDSetting(WFDSetting&);
    WFDSetting& operator=(WFDSetting&);
};



}


#endif // WFDSERVICE_SERSETTING_H

