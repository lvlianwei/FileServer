#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "func.h"
#include "setting.h"

using testing::AtLeast;
using testing::Return;
using testing::_;

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

class MockFUNC:public Setting
{
    public:
	MOCK_METHOD0(get,bool());
        virtual ~MockFUNC(){}
};

FUNC *Test_func::func = NULL;

TEST_F(Test_func,addORmin)
{
    
    EXPECT_EQ(8888,func->addORmin(NULL));//传入参数为NULL
    MockFUNC* mock= new MockFUNC;//定义一个*mock对象
    mock->m_state = 22;
    EXPECT_CALL(*mock,get());//Times默认为1,WillOnce无特殊需求可以省略
    ON_CALL(*mock,get()).WillByDefault(Return(true));//设定get()返回值为true
    EXPECT_EQ(7777,func->addORmin(mock));//自定义的mock对象作为参数传入被测函数
    testing::Mock::AllowLeak(mock);//delete mock object
}


