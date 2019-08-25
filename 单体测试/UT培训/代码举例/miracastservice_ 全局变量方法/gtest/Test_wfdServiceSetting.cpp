#include<gtest/gtest.h>
#include "Test_wfdServiceMgr.h"
#include "WFDServiceSetting.h"
#include "wfdServiceStub.h"
#include "WFDServiceManager.h"
#include "WFDServiceReplier.h"
#include "wfdService.h"
#include "Test_wfdService.h"
#include "../test/testDefine.h"
//#include "../test/testSettingProxy.h"

namespace goni {

	extern bool UTretvalue ;
    extern bool UTcompvalue ;
    class Test_wfdServiceSetting:public testing::Test{
        protected:
            static WFDSetting *setting;
            static WFDServiceManager* mgr;
            static WFDServiceStub * stub;
            static WFDServiceReplier * replier;
            static void SetUpTestCase() {
                // stub = new WFDServiceStub(new wfdService);
                // replier = new WFDServiceReplier(new ServiceBase("base"));
                // mgr = new WFDServiceManager(stub,replier);
                setting = new WFDSetting(Test_wfdService::service->mStub->m_manager);
            }
            static void TearDownTestCase() {
                if(NULL != setting) {
                    delete setting;
                    setting = NULL;
                }
            }
    };
    WFDSetting * Test_wfdServiceSetting::setting = NULL;
    TEST_F(Test_wfdServiceSetting,getWFDPower) {
		UTretvalue = 1;
		UTcompvalue = 1;
		EXPECT_TRUE(setting->getWFDPower());
		UTcompvalue = 0;
		EXPECT_TRUE(setting->getWFDPower());
		UTretvalue = 0;
		UTcompvalue = 1;
		EXPECT_FALSE(setting->getWFDPower());
		UTretvalue = 0;
		UTcompvalue = 0;
		EXPECT_FALSE(setting->getWFDPower());
    }
    TEST_F(Test_wfdServiceSetting,getHorizontalSetting) {
		UTretvalue = 1;
		UTcompvalue = 1;
		EXPECT_TRUE(setting->getHorizontalSetting());
		UTcompvalue = 0;
		EXPECT_FALSE(setting->getHorizontalSetting());
		UTretvalue = 0;
		UTcompvalue = 1;
		EXPECT_FALSE(setting->getHorizontalSetting());
		UTretvalue = 0;
		UTcompvalue = 0;
		EXPECT_FALSE(setting->getHorizontalSetting());
    }
    TEST_F(Test_wfdServiceSetting,getSyncGPSTime) {
        setting->getSyncGPSTime();
    }
    TEST_F(Test_wfdServiceSetting,onNotifyUpdate) {
        std::string key;
        std::string value;
        key = "setting_screen_horizontal";
        value = "on";
        setting->onNotifyUpdate(key,value);
        key = "setting_auto_time_adjust";
        value = "on";
        setting->onNotifyUpdate(key,value);
        key = "setting_link_miracast_status";
        value = "on";
        setting->onNotifyUpdate(key,value);
        value = "off";
        setting->onNotifyUpdate(key,value);
        key = "no notify";
        setting->onNotifyUpdate(key,value);
    }
}
