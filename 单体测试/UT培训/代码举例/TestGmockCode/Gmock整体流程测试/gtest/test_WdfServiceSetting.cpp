#include <gmock/gmock.h>

#inlude <gtest/gtest.h>

#include "testSettingProxy.h"

using testing::_;

class Test_wfdServiceSetting:public testing::Test{
	
	protected：
	{
		static goin::WFDSetting *setting;
		static void setUpTestCase(){
			setting =new goin::WFDSetting(new WFDServiceManager);//在WDFSetting的构造方法中，还没有实现WFDSeriviceManager类
			//待定
		}
		
	}
}