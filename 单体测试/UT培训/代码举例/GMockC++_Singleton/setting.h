#ifndef _SETTING_H
#define _SETTING_H
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Singleton{
public:
	static Singleton* getInstance();
        static void delInstance();
        MOCK_METHOD2(get,bool(int,int&));
	static int m_value;
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
    virtual bool get(int size,int &resize)
    {
	return (Singleton::getInstance())->get(size,resize);
    }
};



#endif
