#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "func.h"

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
        static void TearDownTestCase()
        {
            if(NULL != func)
            {
                delete func;
                func = NULL;
            }
        }
};

class MockFUNC:public FUNC
{
    public:
        MOCK_METHOD0(get,bool());
        virtual ~MockFUNC(){}
};

FUNC *Test_func::func = NULL;

TEST_F(Test_func,addORmin)
{
    MockFUNC mock;
    EXPECT_CALL(mock,get()).Times(3).WillOnce(Return(false)).WillRepeatedly(Return(true));
    ON_CALL(mock,get()).WillByDefault(Return(false));
    EXPECT_EQ(1,mock.addORmin(4,3));

    ON_CALL(mock,get()).WillByDefault(Return(true));
    EXPECT_EQ(7,mock.addORmin(4,3));

    ON_CALL(mock,get()).WillByDefault(Return(true));
    EXPECT_EQ(5,mock.addORmin(2,3));
}

