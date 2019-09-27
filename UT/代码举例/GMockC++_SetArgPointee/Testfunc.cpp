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
using ::testing::SetArrayArgument;
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
	EXPECT_CALL(*(Singleton::getInstance()),get(_))
					.Times(AtLeast(1))
					.WillOnce(SetArgPointee<0>(333));//SetArgPointee改变输出参数为指针类型的输出值
	int value[5]={2,5,13,15,88};
	EXPECT_CALL(*(Singleton::getInstance()),get(_,_))
					.Times(AtLeast(1))
					.WillOnce(SetArrayArgument<0>(value,value+5));//输出参数类型为数组
	FUNC func;
	EXPECT_EQ(0,func.divide(4,3));//实际调用
		
	Singleton::delInstance();

}


