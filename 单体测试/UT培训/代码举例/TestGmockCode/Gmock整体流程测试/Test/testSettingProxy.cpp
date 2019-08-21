#include "testSettingProxy.h"

using namespace Test{
	//实现头文件中的方法
	Singletonwfd::Singletonwfd(){};;//实现私有无参构造函数
	
	Singletonwfd * Singletonwfd::instance=NULL;//定义静态的指针变量为空
	
	Singletonwfd * Singletonwfd::getInstance(){
		if (NULL == instance)
		{
			instance = new Singletonwfd();
		}
		return instance;
	}
	
	void ::Singletonwfd::delInstance()
	{
		if (instance != NULL)
		{
			delete instance;
			instance = NULL;
		}
	}
	
	
	//实现getSettingReadyStatus方法，通过单例方式返回
	bool SettingProxy::getSettingReadyStatus()
	{
		return (Singletonwfd::getInstance())->getSettingReadyStatus();
	}
	
	
}