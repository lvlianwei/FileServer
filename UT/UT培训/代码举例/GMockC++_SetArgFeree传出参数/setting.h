#ifndef _SETTING_H
#define _SETTING_H
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

using namespace std;

class Singleton{
public:
	static Singleton* getInstance();
        static void delInstance();
        MOCK_METHOD0(get,bool());
        MOCK_METHOD3(get,bool(string&,int&,char&));
	MOCK_METHOD0(getptr,int*());
private:
	Singleton();
	
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static Singleton* instance;
};


class Setting
{
public:
    virtual ~Setting(){};
public:
    virtual bool get(string& size,int &resize,char &ch)//测试输出参数为string，int，char
    {
	return (Singleton::getInstance())->get(size,resize,ch);
    }
    virtual int * getptr()//测试返回值为int*类型
    {
	return (Singleton::getInstance())->getptr();
    }
};



#endif
