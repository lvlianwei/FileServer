#ifndef _SETTING_H
#define_SETTING_H
#include<gmock/gmock.h>
#include<gtest/gtest.h>
#include <string>
namespace Test{
class Singletonwfd{
	
	public:
		//定义两个静态方法,用来获取和删除该单例
		static Singletonwfd* getInstance();
		static void delInstance();
		MOCK_METHOD0(getSettingReadyStatus,bool);
	
	
	//单例模式，私有的构造方法
	private:
		Singletonwfd();//无参构造
		Singletonwfd(const Singletonwfd& single)=delete;//拷贝构造
		Singletonwfd oprator=(const singletonwfd)=delete;//=号赋值构造
		static Singletonwfd * instance;
	
};


	
class SettingProxy{
public:		
	virtual ~SettingProxy(){};
		
public:
	virtual bool getSettingReadyStatus();
};
using namespace Test;
}