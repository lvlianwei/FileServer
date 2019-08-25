#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "func.h"
#include "setting.h"
using testing::SetArgReferee;
using testing::AtLeast;
using testing::Return;
using testing::_;
using testing::AnyNumber;
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
TEST_F(Test_func,divide)
{
	EXPECT_CALL(*(Singleton::getInstance()),get(_,_))
                        .WillOnce(DoAll(SetArgReferee<1>(120),Return(true)))
                        .WillOnce(DoAll(SetArgReferee<1>(40),Return(true)))
                        .WillOnce(DoAll(SetArgReferee<1>(777),Return(false)));
	//WillOnce(DoAll(Action1,Action2,Action3......))  DoAll的参数至少是两个,并且有Return()必须放在最后一个
	//SetArgReferee<>() 作用为指定输出参数值，必须满足设定的get(_,_)中需要被修改的参数必须为引用。
	//SetArgReferee<>() 在EXPECT_CALL中不只是期望动作，在这里就已经设定完成,无需再在ON_CALL中设定，下标从0开始
	ON_CALL(*(Singleton::getInstance()),get(_,_)).WillByDefault(Return(true));
    	FUNC func;
	EXPECT_EQ(3,func.divide(9,3));
	
	ON_CALL(*(Singleton::getInstance()),get(_,_)).WillByDefault(Return(true));
	EXPECT_EQ(88,func.divide(9,3));

	ON_CALL(*(Singleton::getInstance()),get(_,_)).WillByDefault(Return(false));	
	EXPECT_EQ(77,func.divide(4,3));
		
	Singleton::delInstance();

}

#if 0
TEST_F(Test_func,addORmin)
{
	EXPECT_CALL(*(Singleton::getInstance()),get()).Times(2).WillOnce(Return(true)).WillOnce(Return(false));
	ON_CALL(*(Singleton::getInstance()),get()).WillByDefault(Return(true));

    	FUNC func;
	EXPECT_EQ(7,func.addORmin(4,3));
	
	ON_CALL(*(Singleton::getInstance()),get()).WillByDefault(Return(false));	
	EXPECT_EQ(1,func.addORmin(4,3));
		
	Singleton::delInstance();

}
#endif
