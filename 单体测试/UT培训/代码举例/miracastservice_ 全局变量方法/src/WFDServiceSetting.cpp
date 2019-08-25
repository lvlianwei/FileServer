#include "WFDServiceSetting.h"
#include "WFDServiceDefs.h"
#ifndef UT_GTEST_FULL_ENG
#include "WFDServiceManager.h"
#else
#include "../test/testWFDServiceManager.h"
#endif
#include "servicebase/SystemLog.h"

namespace goni {
DeclearModuleID(DTMODULEID_WFDSERVICE);

#define SETTING_DB_COLUMN_VALUE                     "value"
#define SETTING_WFD_STATUS                  "setting_link_miracast_status"
#define SETTING_SCREEN_HORIZONTAL               "setting_screen_horizontal"
#define SETTING_SYNC_TIME               "setting_auto_time_adjust"
#define SETTING_VAL_ON                              "on"
#define SETTING_VAL_OFF                             "off"


WFDSetting::WFDSetting(WFDServiceManager* manager)   /* __0x007000_DTFUNCID__ */
:mManager(manager)
{
}

bool WFDSetting::getWFDPower()   /* __0x007001_DTFUNCID__ */
{
    SettingProxy proxy;
    std::string key(SETTING_WFD_STATUS);
    std::string value;

    if(proxy.getSettingReadyStatus())
    {
        if(proxy.get(SETTING_DB_COLUMN_VALUE, key, value))
        {
            MCLOGD("%s key=[%s] value=[%s]", __func__, key.c_str(), value.c_str());
            if(value.compare(SETTING_VAL_ON) == 0)
                return true;
            else
                return false;
        }
    }
    DTLOG_INFO(0x007001, "WFDSetting::getWFDPower failed");
    MCLOGD("%s get falied", __func__);
    return false;
}

bool WFDSetting::getHorizontalSetting()   /* __0x007002_DTFUNCID__ */
{
    SettingProxy proxy;
    if(proxy.getSettingReadyStatus())
    {
        std::string key(SETTING_SCREEN_HORIZONTAL);
        std::string value;
        if(proxy.get(SETTING_VAL_ON, key, value))
        {
            MCLOGD("%s key=[%s] value=[%s]", __func__, key.c_str(), value.c_str());
            if(value.compare(SETTING_VAL_ON) == 0)
                return true;
            else
                return false;
        }
    }
    DTLOG_INFO(0x007002, "WFDSetting::getHorizontalSetting failed");
    MCLOGD("%s get falied", __func__);
    return false;
}

bool WFDSetting::getSyncGPSTime()   /* __0x007003_DTFUNCID__ */
{
    return true;
}

void WFDSetting::onNotifyUpdate(const std::string &key, const std::string &value)   /* __0x007004_DTFUNCID__ */
{
    MCLOGD("*****%s**** key = %s, value = %s", __func__, key.c_str(), value.c_str());
    if (key.compare(SETTING_WFD_STATUS) == 0){
        if (value.compare(SETTING_VAL_ON) == 0) {
            mManager->wfd_powerOn();
            }
        else{
            mManager->wfd_powerOff();
            }
        }
     else if(key.compare(SETTING_SCREEN_HORIZONTAL) == 0)
        if (value.compare(SETTING_VAL_ON) == 0) {
            }
        else {
            }
    else if (key.compare(SETTING_SYNC_TIME) == 0) {
        if (value.compare(SETTING_VAL_ON) == 0) {
            }
        else {
            }
        }
    else {
        MCLOGD("*****%s**** not notify to wfd", __func__);
        }
}

}
