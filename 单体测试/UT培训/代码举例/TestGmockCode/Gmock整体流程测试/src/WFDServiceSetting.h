#ifndef WFDSERVICE_SERSETTING_H
#define WFDSERVICE_SERSETTING_H

#include "proxy/SettingProxy.h"

/*
	待测文件的头文件--原文件，未修改
*/

namespace goni {

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

