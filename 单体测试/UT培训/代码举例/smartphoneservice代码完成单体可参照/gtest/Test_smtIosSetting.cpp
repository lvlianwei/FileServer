#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "SmartIosSettingProxy.h"
#include"testsqlite3.h"

using namespace std;
using testing::_;
using testing::Return;
using testing::AtLeast;
using ::testing::SetArgPointee;
using ::testing::SetArgReferee;
using ::testing::AnyNumber;
namespace goni { 
    class Test_smtIosSettingProxy:public testing::Test {
        public:
            static SmartIosSettingProxy * settingProxy;
            static void SetUpTestCase() {
                settingProxy = new SmartIosSettingProxy;
                printf("##################Test smt SettingProxy set up###############\n");
            }
            static void TearDownTestCase() {
                printf("#################Test mst SettingProxy tear down##############\n");
                delete settingProxy;
                settingProxy = NULL;
            }
    };
    SmartIosSettingProxy * Test_smtIosSettingProxy::settingProxy = NULL;
    class MOCKSETTING:public SmartIosSettingProxy{
        public:
            MOCK_METHOD1(dbOperateRetJudgement,enum SMT_SQL_RET (int));
            virtual ~MOCKSETTING(){}
    };
    class MOCKSETPOPSTATUS:public SmartIosSettingProxy{
        public:
            MOCK_METHOD1(dbOperateRetJudgement,enum SMT_SQL_RET (int));
            MOCK_METHOD2(deleteNoPopDevice,bool(uint8_t  , SmtDeviceType  ));
            MOCK_METHOD1(getPopDeviceMaxPriority,int (SmtDeviceType ));
            MOCK_METHOD4(insertPopDevice ,bool(IosDeviceName* devname, SmtPopStatus setting, int maxPriority, SmtDeviceType deviceType));
            MOCK_METHOD4(insertPopDeviceNoName,bool(IosDeviceName* devname, SmtPopStatus setting, int maxPriority, SmtDeviceType deviceType));
            virtual ~MOCKSETPOPSTATUS(){}
    }; 
	class MOCKIAPDEVICEINSERT:public SmartIosSettingProxy{
        public:
            MOCK_METHOD1(dbOperateRetJudgement,enum SMT_SQL_RET (int));
			MOCK_METHOD0(ForGetLocalValue,int ());
            virtual ~MOCKIAPDEVICEINSERT(){}
    };
	extern bool VALUE;
    TEST_F(Test_smtIosSettingProxy,deInit) {
        settingProxy->deInit();
    }
    TEST_F(Test_smtIosSettingProxy,initSqlite3DB) {
        MOCKSETTING mock;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        mock.ForSetLocalValue(0);
        mock.initSqlite3DB();
        mock.ForSetLocalValue(1);
        mock.initSqlite3DB();
        mock.ForSetLocalValue(6);
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.ForSetLocalValue(0);
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.ForSetLocalValue(1);
        mock.initSqlite3DB();
        mock.ForSetLocalValue(0);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        mock.ForSetLocalValue(6);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)). WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)) 
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)) 
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
        mock.ForSetLocalValue(0);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.initSqlite3DB();
    }
    TEST_F(Test_smtIosSettingProxy,updatePopStatusDevicesPriority) {

        MOCKSETTING mock;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        int priority =1;
        mock.updatePopStatusDevicesPriority(priority);
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.updatePopStatusDevicesPriority(priority);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.updatePopStatusDevicesPriority(priority);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_FAIL));
        mock.updatePopStatusDevicesPriority(priority);
    }
    TEST_F(Test_smtIosSettingProxy,updateNoPopStatusDevicesPriority) {

        MOCKSETTING mock;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));

        SmtDeviceType type = SMT_DEVICE_TYPE_ANDROID;
        int priority =1;
        sqlite3 * mdb1;
        mock.mdb = mdb1;
        mock.updateNoPopStatusDevicesPriority(priority,type);
        type = SMT_DEVICE_TYPE_IOS;
        mock.updateNoPopStatusDevicesPriority(priority,type);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.updateNoPopStatusDevicesPriority(priority,type);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.updateNoPopStatusDevicesPriority(priority,type);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_FAIL));
        mock.updateNoPopStatusDevicesPriority(priority,type);
    }

    TEST_F(Test_smtIosSettingProxy,insertPopDevice) {
        MOCKSETTING mock;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        uint8_t index =1;
        IosDeviceName devname;
        SmtPopStatus setting = SMT_AUTOCARPLAY;
        int maxPriority =1;
        SmtDeviceType deviceType =SMT_DEVICE_TYPE_ANDROID;
        mock.insertPopDevice(&devname, setting, maxPriority, deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        EXPECT_TRUE(mock.insertPopDevice(&devname, setting, maxPriority, deviceType));
        deviceType =SMT_DEVICE_TYPE_IOS;
        EXPECT_TRUE(mock.insertPopDevice(&devname, setting, maxPriority, deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.insertPopDevice(&devname, setting, maxPriority, deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.insertPopDevice(&devname, setting, maxPriority, deviceType));
    }
    TEST_F(Test_smtIosSettingProxy,insertPopDeviceNoName) {
        MOCKSETTING mock;
        IosDeviceName devname;
        SmtPopStatus setting = SMT_AUTOCARPLAY;
        int maxPriority =1;
        SmtDeviceType deviceType =SMT_DEVICE_TYPE_ANDROID;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.insertPopDeviceNoName(&devname, setting, maxPriority, deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        EXPECT_TRUE(mock.insertPopDeviceNoName(&devname, setting, maxPriority, deviceType));
        deviceType =SMT_DEVICE_TYPE_IOS;
        EXPECT_TRUE(mock.insertPopDeviceNoName(&devname, setting, maxPriority, deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.insertPopDeviceNoName(&devname, setting, maxPriority, deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.insertPopDeviceNoName(&devname, setting, maxPriority, deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.insertPopDeviceNoName(&devname, setting, maxPriority, deviceType));
    }
    TEST_F(Test_smtIosSettingProxy,setPopStatusReq) {
        MOCKSETPOPSTATUS mock;
        SmtSetType setType = SMT_IOS_POPUP_SET;
        uint8_t index = 0;
        SmtPopStatus setting = SMT_AUTOCARPLAY;
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
        char * sql2 = NULL;
        char * errMsg = NULL; 
        index = 6;
        setType = SMT_IOS_MANU_SET;
		IosDeviceName devname;
		devname.format.nameIsValid = NAME_IS_INVALID;
		IosDeviceName devname1;
		devname1.format.nameIsValid = NAME_IS_VALID;
		EXPECT_CALL(mock,insertPopDeviceNoName (_,_,_,_)).Times(AtLeast(1)).WillRepeatedly(Return(false));
		EXPECT_CALL(*(SingletonForSqlite3::getInstance()),sqlite3_get_table(_,_,_,_,_,_)).Times(AtLeast(1)).WillRepeatedly(Return(1));
		//EXPECT_CALL(*(SingletonForSqlite3::getInstance()),sqlite3_exec(_,_,_,_,_)).Times(AtLeast(1)).WillRepeatedly(SetArgReferee<3>(devname1));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType)); 
		deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
		EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType));
        deviceType = SMT_DEVICE_TYPE_IOS;
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_FAIL)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType));
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType));

        setType = SMT_IOS_POPUP_SET;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        mock.ForSetLocalValue(0);
        EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType)); 
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType)); 
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        EXPECT_CALL(mock,deleteNoPopDevice(_,_)).WillOnce(Return(false));
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        mock.ForSetLocalValue(1);
		EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType));
		EXPECT_CALL(mock,deleteNoPopDevice(_,_)).Times(AtLeast(1)).WillRepeatedly(Return(true));
        EXPECT_CALL(mock,getPopDeviceMaxPriority(_)).Times(AtLeast(1)).WillRepeatedly(Return(1));
        EXPECT_CALL(mock,insertPopDevice (_,_,_,_)).Times(AtLeast(1)).WillRepeatedly(Return(false));
		EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType));  
		VALUE = 1;
		EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType));  
		EXPECT_CALL(mock,getPopDeviceMaxPriority(_)).Times(AtLeast(1)).WillRepeatedly(Return(6));
		EXPECT_EQ(5,mock.setPopStatusReq(setType,index,setting,deviceType));

        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(6,mock.setPopStatusReq(setType,index,setting,deviceType));
        index = 1;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(1,mock.setPopStatusReq(setType,index,setting,deviceType)); 
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(1,mock.setPopStatusReq(setType,index,setting,deviceType));
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(1,mock.setPopStatusReq(setType,index,setting,deviceType));
		VALUE = 0;
		deviceType = SMT_DEVICE_TYPE_IOS;
		EXPECT_CALL(mock,insertPopDevice (_,_,_,_)).Times(AnyNumber()).WillRepeatedly(Return(true));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		EXPECT_EQ(1,mock.setPopStatusReq(setType,index,setting,deviceType));
		index = 1;
		EXPECT_EQ(1,mock.setPopStatusReq(setType,index,setting,deviceType));
		setType = SMT_IOS_MANU_SET;
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(1).WillOnce(Return(SMT_SQL_RET_FAIL));
		EXPECT_EQ(1,mock.setPopStatusReq(setType,index,setting,deviceType));
		SingletonForSqlite3::delInstance();
    }

    TEST_F(Test_smtIosSettingProxy,setDeviceName) {
        MOCKIAPDEVICEINSERT mock;
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
		mock.ForSetLocalValue(0);
		EXPECT_CALL(mock,ForGetLocalValue()).Times(AtLeast(1)).WillRepeatedly(Return(0));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		mock.setDeviceName("12342","iphone8",deviceType);
        mock.initSqlite3DB();
        mock.setDeviceName("12342","iphone8",deviceType);
		EXPECT_CALL(mock,ForGetLocalValue()).Times(AtLeast(1)).WillRepeatedly(Return(0));
		mock.ForSetLocalValue(1);
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        mock.setDeviceName("12345","Android",deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.setDeviceName("12342","iphone8",deviceType);
        deviceType = SMT_DEVICE_TYPE_IOS;
        mock.setDeviceName("12345","Android",deviceType);
        char a[]="";
        mock.setDeviceName("12345",a,deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.setDeviceName("12345","Android",deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.setDeviceName("12345","Android",deviceType);
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.setDeviceName("12345","",deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.setDeviceName("12345","Android",deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.setDeviceName("12345","Android",deviceType);
		EXPECT_CALL(mock,ForGetLocalValue()).Times(AtLeast(1)).WillRepeatedly(Return(1));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.setDeviceName("12345","Android",deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.setDeviceName("12345","Android",deviceType);  
		deviceType = SMT_DEVICE_TYPE_ANDROID;
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
			.WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
		mock.setDeviceName("12345","Android",deviceType);
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		mock.setDeviceName("12345","Android",deviceType);
    }
    TEST_F(Test_smtIosSettingProxy,iapDeviceInsert) {
        MOCKIAPDEVICEINSERT mock;
        uint8_t selectStatus = 0;
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
		EXPECT_CALL(*(SingletonForSqlite3::getInstance()),sqlite3_get_table(_,_,_,_,_,_)).Times(AtLeast(1)).WillRepeatedly(Return(1));
		EXPECT_CALL(mock,ForGetLocalValue()).Times(AtLeast(1)).WillRepeatedly(Return(0));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        char a[]="";
		mock.ForSetLocalValue(0);
        EXPECT_EQ(0,mock.iapDeviceInsert(a,&selectStatus,deviceType));
        EXPECT_EQ(0,mock.iapDeviceInsert("2325",&selectStatus,deviceType));
        mock.initSqlite3DB();
        EXPECT_EQ(6,mock.iapDeviceInsert("2325",&selectStatus,deviceType));
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_EQ(6,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(0,mock.iapDeviceInsert("2325",&selectStatus,deviceType));
        mock.initSqlite3DB();
        EXPECT_EQ(0,mock.iapDeviceInsert("2325",&selectStatus,deviceType));
        deviceType = SMT_DEVICE_TYPE_IOS;
        EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)) .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType)); 
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        mock.ForSetLocalValue(1);
        EXPECT_EQ(6,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        mock.ForSetLocalValue(SMT_IOS_NOPOP_DEVICE_MAX);
        EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.ForSetLocalValue(6);
        EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.ForSetLocalValue(6);
		deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
		EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS))
            .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
		EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
		EXPECT_CALL(mock,ForGetLocalValue()).Times(AtLeast(1)).WillOnce(Return(0)).WillRepeatedly(Return(1));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		EXPECT_EQ(5,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)) .WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		EXPECT_CALL(mock,ForGetLocalValue()).Times(1).WillOnce(Return(1));
		EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
		EXPECT_CALL(mock,ForGetLocalValue()).Times(AtLeast(1)).WillRepeatedly(Return(0));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
		EXPECT_EQ(0,mock.iapDeviceInsert("1325",&selectStatus,deviceType));
    } 
    TEST_F(Test_smtIosSettingProxy,getDeviceInfo) {
        MOCKSETTING mock;
		char* aa = "safjoi1qjekl21132";
		char* bb = "1";
		char* column_value[COLUMN_NUM] = {aa,bb,bb,aa,bb,bb};
		char** pp = column_value;
        SmtDevReqType reqType =SMT_IOS_DEV_ALL_REQ;
        uint8_t index =1;
        std::vector<IosDeviceName*>  mDevList;
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
        reqType =SMT_IOS_DEV_ALL_REQ;
		EXPECT_CALL(*(SingletonForSqlite3::getInstance()),sqlite3_get_table(_,_,_,_,_,_)).Times(AtLeast(1)).WillRepeatedly(Return(1));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        EXPECT_FALSE(mock.getDeviceInfo(reqType,index,&mDevList,deviceType));
		EXPECT_CALL(*(SingletonForSqlite3::getInstance()),sqlite3_get_table(_,_,_,_,_,_)).Times(AtLeast(1))
					.WillRepeatedly(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)));
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_TRUE(mock.getDeviceInfo(reqType,index,&mDevList,deviceType));
		reqType = SMT_IOS_DEV_SINGLE_REQ;
		EXPECT_TRUE(mock.getDeviceInfo(reqType,index,&mDevList,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.getDeviceInfo(reqType,index,&mDevList,deviceType));
		SingletonForSqlite3::delInstance();
    }
    TEST_F(Test_smtIosSettingProxy,getSerialNumIndex) {
        std::string serialNum = "24235";
        EXPECT_EQ(0,settingProxy->getSerialNumIndex(serialNum));
    }
    TEST_F(Test_smtIosSettingProxy,isPopStatusValidLow) {
        uint8_t pop = 1;
        EXPECT_FALSE(settingProxy->isPopStatusValidLow(pop));
    }
    TEST_F(Test_smtIosSettingProxy,isPopDeviceBySerinum) {
        const char * serinum = "57689";
        MOCKSETTING mock;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        mock.ForSetLocalValue(0);
        EXPECT_FALSE(mock.isPopDeviceBySerinum(serinum));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        mock.ForSetLocalValue(1);
        EXPECT_TRUE(mock.isPopDeviceBySerinum(serinum));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.isPopDeviceBySerinum(serinum));
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        mock.ForSetLocalValue(0);
		EXPECT_FALSE(mock.isPopDeviceBySerinum(serinum));
    }
    TEST_F(Test_smtIosSettingProxy,replaceNoPopDevice) {
    	char* aa = "safjoi1qjekl21132";
		char* bb = "1";
		char* cc = "2";
		char* column_value[COLUMN_NUM] = {aa,bb,bb,aa,bb,bb};
		char* column_value1[COLUMN_NUM] = {aa,cc,bb,aa,bb,bb};
		char** pp = column_value;
		char** pp1 = column_value1;
        MOCKSETTING mock;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		EXPECT_CALL(*(SingletonForSqlite3::getInstance()),sqlite3_get_table(_,_,_,_,_,_)).Times(AtLeast(1))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp1),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp1),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp1),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp1),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)));
        uint8_t index = 1;
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
        mock.replaceNoPopDevice("12342",1,"iphone8",1,2,index,deviceType);
        index = 10;
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
		deviceType = SMT_DEVICE_TYPE_IOS;
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
		deviceType = SMT_DEVICE_TYPE_IOS;
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replaceNoPopDevice("12342",1,"iphone8",0,1,index,deviceType);
		SingletonForSqlite3::delInstance();
    }
    TEST_F(Test_smtIosSettingProxy,replacePopDevice) {
        MOCKSETTING mock;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		char* aa = "safjoi1qjekl21132";
		char* bb = "1";
		char* cc = "2";
		char* column_value[COLUMN_NUM] = {aa,bb,bb,aa,bb,bb};
		char* column_value1[COLUMN_NUM] = {aa,cc,bb,aa,bb,bb};
		char** pp = column_value;
		char** pp1 = column_value1;
		EXPECT_CALL(*(SingletonForSqlite3::getInstance()),sqlite3_get_table(_,_,_,_,_,_)).Times(AtLeast(1))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp1),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp1),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp1),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp1),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)))
					.WillOnce(DoAll(SetArgPointee<2>(pp),SetArgPointee<3>(1),SetArgPointee<4>(0),Return(1)));
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
        mock.replacePopDevice("12342",1,"iphone8",1,2,deviceType);
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
		deviceType = SMT_DEVICE_TYPE_IOS;
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
		deviceType = SMT_DEVICE_TYPE_IOS;
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.replacePopDevice("12342",1,"iphone8",0,1,deviceType);
		
		SingletonForSqlite3::delInstance();
    }
    TEST_F(Test_smtIosSettingProxy,getNoPopStatusDeviceMaxPriority) {
        MOCKSETTING mock;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
        EXPECT_EQ(0,mock.getNoPopStatusDeviceMaxPriority(deviceType));
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_EQ(0,mock.getNoPopStatusDeviceMaxPriority(deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(0,mock.getNoPopStatusDeviceMaxPriority(deviceType));
    }
    TEST_F(Test_smtIosSettingProxy,getPopDeviceMaxPriority) {
        MOCKSETTING mock;
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        EXPECT_EQ(0,mock.getPopDeviceMaxPriority(deviceType));
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_EQ(0,mock.getPopDeviceMaxPriority(deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_EQ(0,mock.getPopDeviceMaxPriority(deviceType));
    }
    TEST_F(Test_smtIosSettingProxy,deleteNoPopDevice) {
        MOCKSETTING mock;
        uint8_t index = 6;
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        EXPECT_TRUE(mock.deleteNoPopDevice(index,deviceType));
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        EXPECT_TRUE(mock.deleteNoPopDevice(index,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.deleteNoPopDevice(index,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.deleteNoPopDevice(index,deviceType));
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        EXPECT_FALSE(mock.deleteNoPopDevice(index,deviceType));
    }
    TEST_F(Test_smtIosSettingProxy,resetSqliteDB) {
        settingProxy->resetSqliteDB();
    }
    TEST_F(Test_smtIosSettingProxy,resetSettingDB) {
        settingProxy->resetSettingDB();
    }
    TEST_F(Test_smtIosSettingProxy,clearNoCompleteData) {
        settingProxy->clearNoCompleteData();
    }
    TEST_F(Test_smtIosSettingProxy,getInstance) {
        settingProxy->getInstance();
    }
    TEST_F(Test_smtIosSettingProxy,dbOperateResultCountClear) {
        settingProxy->dbOperateResultCountClear();
    }

    TEST_F(Test_smtIosSettingProxy,dbOperateRetJudgement) {
        int ret;
        ret = SQLITE_OK;
        EXPECT_EQ(SMT_SQL_RET_SUCCESS,settingProxy->dbOperateRetJudgement(ret));
        ret = SQLITE_INTERNAL;
        EXPECT_EQ(SMT_SQL_RET_NEED_DELETE_DB,settingProxy->dbOperateRetJudgement(ret));
        ret = SQLITE_IOERR;
        EXPECT_EQ(SMT_SQL_RET_NEED_RESET_DB,settingProxy->dbOperateRetJudgement(ret));
        ret = SQLITE_ABORT;
        EXPECT_EQ(SMT_SQL_RET_FAIL,settingProxy->dbOperateRetJudgement(ret));
    }
    TEST_F(Test_smtIosSettingProxy,deleteTableFromDB) {
        MOCKSETTING mock;
        SMT_DB_TABLE_TYPE tableType;
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        mock.initSqlite3DB();
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_FAIL));
        mock.deleteTableFromDB(tableType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
        tableType = SMT_DB_TABLE_TYPE_POP_IOS;
        mock.deleteTableFromDB(tableType);
        tableType = SMT_DB_TABLE_TYPE_NO_POP_IOS;
        mock.deleteTableFromDB(tableType);
        tableType = SMT_DB_TABLE_TYPE_POP_ANDROID;
        mock.deleteTableFromDB(tableType);
        tableType = SMT_DB_TABLE_TYPE_NO_POP_ANDROID;
        mock.deleteTableFromDB(tableType);
        tableType = SMT_DB_TABLE_TYPE_VERSION;
        mock.deleteTableFromDB(tableType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_FAIL));
        mock.deleteTableFromDB(tableType);
        EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_SUCCESS)).WillOnce(Return(SMT_SQL_RET_FAIL));
        mock.deleteTableFromDB(tableType);
    }
    TEST_F(Test_smtIosSettingProxy,delAllDevice) {
        settingProxy->delAllDevice();
        settingProxy->delSingleDevice(1);
    }
    TEST_F(Test_smtIosSettingProxy,ForLocalFunc) {
        settingProxy->ForLocalFunc(); 
		settingProxy->ForGetLocalValue();
    } 
    TEST_F(Test_smtIosSettingProxy,isPopStatusValidHigh) {
        settingProxy->isPopStatusValidHigh(3);
    }
	TEST_F(Test_smtIosSettingProxy,closeDB) {
		MOCKSETTING mock;
		EXPECT_CALL(mock,dbOperateRetJudgement(_)).Times(AtLeast(1)).WillRepeatedly(Return(SMT_SQL_RET_SUCCESS));
		mock.initSqlite3DB();
        mock.closeDB();
    }

}

