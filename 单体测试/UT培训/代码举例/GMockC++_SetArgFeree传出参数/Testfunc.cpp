#include "gtest/gtest.h"
#include <iostream>
#include "gmock/gmock.h"
#include "func.h"
#include "setting.h"
using namespace std;

using ::testing::SetArgReferee;
using testing::AtLeast;
using testing::Return;
using testing::_;
using ::testing::DoAll;
using ::testing::SetArgPointee;

class Test_func:public testing::Test
{
    protected:
        static FUNC *func;
        static void SetUpTestCase()
        {
            func = new FUNC;
        }
        static void TeatDownTestCase()
        {
            if(NULL != func)
            {
                delete func;
                func = NULL;
            }
        }
};


FUNC *Test_func::func = NULL;
TEST_F(Test_func,addORmin)
{
	int ptr=3;int* p=&ptr;
	EXPECT_CALL(*(Singleton::getInstance()),get(_,_,_))
                        .Times(3)
                        .WillOnce(DoAll(SetArgReferee<0>("aa"),SetArgReferee<1>(120),SetArgReferee<2>('w'),Return(true)))
                        .WillOnce(DoAll(SetArgReferee<0>("bb"),SetArgReferee<1>(20),Return(true)))
                        .WillOnce(DoAll(SetArgReferee<0>("cc"),SetArgReferee<1>(400),Return(false)));
	//get接口的参数是引用才能使用SetArgReferee对输出参数string,char,value进行自定义赋值
	//Return()必须放在DoAll()的最后一个参数,并且DoAll()至少有两个参数
	EXPECT_CALL(*(Singleton::getInstance()),getptr()).Times(3);//期待getptr()被调用三次 不写Times默认为期待调用一次 WillOnce不写也OK 
	ON_CALL(*(Singleton::getInstance()),getptr()).WillByDefault(testing::ReturnNull());//设定getptr()返回空指针
	ON_CALL(*(Singleton::getInstance()),get(_,_,_)).WillByDefault(Return(true));//设定get(string&,int&,char&)返回值为true
    	FUNC func;
	EXPECT_EQ(3,func.divide(9,3));//实际调用
	ON_CALL(*(Singleton::getInstance()),getptr()).WillByDefault(testing::Return(p));//设定getptr()返回值为指针类型
	ON_CALL(*(Singleton::getInstance()),get(_,_,_)).WillByDefault(Return(true));//设定get(string&,int&,char&)返回值为true
	EXPECT_EQ(88,func.divide(9,3));//实际调用
	ON_CALL(*(Singleton::getInstance()),getptr()).WillByDefault(testing::ReturnNull());//设定getptr()返回空指针
	ON_CALL(*(Singleton::getInstance()),get(_,_,_)).WillByDefault(Return(false));//设定返回值为false
	EXPECT_EQ(77,func.divide(4,3));//实际调用
		
	Singleton::delInstance();

}
/*

EXPECT_CALL(*(Singleton::getInstance()),get(_,_,_))
                        .Times(3)
                        .WillOnce(DoAll(SetArgReferee<0>("aa"),SetArgReferee<1>(120),SetArgReferee<2>('w'),Return(true)))
                        .WillOnce(DoAll(SetArgReferee<0>("bb"),SetArgReferee<1>(20),Return(true)))
                        .WillOnce(DoAll(SetArgReferee<0>("cc"),SetArgReferee<1>(400),Return(false)));
ON_CALL和EXPECT_CALL配对使用，不然会报警告。但WillOnce等可以省略
testing::ReturnNull()
*/

