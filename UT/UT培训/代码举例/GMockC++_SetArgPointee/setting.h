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
	MOCK_METHOD1(get,void(int*));
	MOCK_METHOD2(get,void(int*,int));
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
    virtual void get(int * p)
    {
	(Singleton::getInstance())->get(p);
    }
    virtual void get(int * values,int num)
    {
	(Singleton::getInstance())->get(values,num);
    }
};



#endif
