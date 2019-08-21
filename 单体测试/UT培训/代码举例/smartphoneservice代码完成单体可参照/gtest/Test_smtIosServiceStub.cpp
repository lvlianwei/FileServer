#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "testSmartIosSettingProxy.h"
#include<stdio.h>
#define private public
#include "Test_smtIosService.h"
using testing::_;
using testing::Return;
using testing::AtLeast;
using testing::AnyNumber;
namespace goni {
    class Test_smtIosServiceStub:public testing::Test {
        public:
            static void SetUpTestCase() {
				EXPECT_CALL(*(SingletonForSmartIosSettingProxy::getInstance()),getDeviceInfo(_,_,_,_)).Times(AnyNumber()).WillOnce(Return(true));
				EXPECT_CALL(*(SingletonForSmartIosSettingProxy::getInstance()),iapDeviceInsert(_,_,_)).Times(AnyNumber()).WillRepeatedly(Return(1));
                printf("######################Test smt ios service stub set up############\n");
            }
            static void TearDownTestCase() {
            	SingletonForSmartIosSettingProxy::delInstance();
                printf("######################Test smt ios service stub tear down############\n");
            }
    };
    TEST_F(Test_smtIosServiceStub,smt_launchSource) {
        SenderId id = 3;
        int index = 0;
        SmtIosSource source = (SmtIosSource)0;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_launchSource(id,index,source));
    }
    TEST_F(Test_smtIosServiceStub,smt_setPopStatus) {
        SenderId id = 3;
        SmtSetType reqType =  SMT_IOS_POPUP_SET;
        int index = 6;
        SmtPopStatus pop = SMT_AUTOCARPLAY;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_setPopStatus(id,reqType,index,pop));
    }
    TEST_F(Test_smtIosServiceStub,smt_getDeviceInfo) {
        SenderId id = 3;
        SmtDevReqType type = SMT_IOS_DEV_ALL_REQ;
        int index = 0;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_getDeviceInfo(id,type,index));
    }
    TEST_F(Test_smtIosServiceStub,smt_delSingleDevice) {
        SenderId id = 3;
        int index = 1;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_delSingleDevice(id,index));
    }
    TEST_F(Test_smtIosServiceStub,smt_delAllDevices) {
        SenderId id = 3;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_delAllDevices(id));
    }
    TEST_F(Test_smtIosServiceStub,onIap2Insert) {
        android::String8 serinum("12345");
        Test_smtIosService::service->mStub->onIap2Insert(true,serinum);
    }
    TEST_F(Test_smtIosServiceStub,onIap2Exact) {
        Test_smtIosService::service->mStub->onIap2Exact();
    }
    TEST_F(Test_smtIosServiceStub,onIap2AuthInfo) {
        android::String8 serinum("12354");
        android::String8 devname("iphone");
        Test_smtIosService::service->mStub->onIap2AuthInfo(serinum,devname);
    }
    TEST_F(Test_smtIosServiceStub,smt_launchSource_Android) {
        SenderId id = 3;
        const uint8_t index=10;
        const SmtAndroidSource source = SMT_ANDROID_SOURCE_AAP;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_launchSource_Android(id,index,source));
    }
    TEST_F(Test_smtIosServiceStub,notifyLaunchResult) {
        smtLaunchState state=LAUNCH_IDLE;
        Test_smtIosService::service->mStub->notifyLaunchResult(state);
    }
    TEST_F(Test_smtIosServiceStub,smt_getDevConnectInfo) {
        uint8_t connState=0;
        uint8_t index=1;
        uint8_t popStatus=1;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_getDevConnectInfo(connState,index,popStatus));
    }
    TEST_F(Test_smtIosServiceStub,onAndroidInsert) {
        const android::String8 serinum("12354");
        Test_smtIosService::service->mStub->onAndroidInsert(serinum);
    }
    TEST_F(Test_smtIosServiceStub,onAndroidExact) {
        Test_smtIosService::service->mStub->onAndroidExact();
    }
    TEST_F(Test_smtIosServiceStub,deInit) {
        Test_smtIosService::service->mStub->deInit();
    }
    TEST_F(Test_smtIosServiceStub,smtDevConnectInd) {
        const SmtConState_Sp conState(new SmtConState);
        EXPECT_NE(BS_NO_CONNECTION,Test_smtIosService::service->mStub->smtDevConnectInd(conState));
    }
    TEST_F(Test_smtIosServiceStub,smtDevIpa2InsertInd) {
        const uint8_t state = 1;
        EXPECT_NE(BS_NO_CONNECTION,Test_smtIosService::service->mStub->smtDevIpa2InsertInd(state));
    }
    TEST_F(Test_smtIosServiceStub,smtDevAndroidInsertInd) {
        const SmtConState_Sp state(new SmtConState);
        EXPECT_NE(BS_NO_CONNECTION,Test_smtIosService::service->mStub->smtDevAndroidInsertInd(state));
    }
#if 0
    TEST_F(Test_smtIosServiceStub,onSyncRequest) {
        android::Parcel data;
        android::Parcel _data;
        android::String8 str;
        unsigned int code = SmartIosServiceStubBase::METHOD_SMT_GET_DEV_CONNECT_INFO;
        data.writeString8(str);
        _data.writeString8(str);
        Test_smtIosService::service->mStub->onSyncRequest(code, data, _data);
        code = SmartIosServiceStubBase::METHOD_SMT_GET_DEV_CONNECT_INFO_ANDROID;
        Test_smtIosService::service->mStub->onSyncRequest(code, data, _data);
    }
    TEST_F(Test_smtIosServiceStub,onAsyncRequest) {
        goni::SenderId id = 1;
        android::Parcel _data;
        unsigned int code = SmartIosServiceStubBase::COMMAND_SMT_LAUNCH_SOURCE;
        _data.setDataPosition(0);
        _data.writeInt32(3);
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
        code =SmartIosServiceStubBase::COMMAND_SMT_SET_POP_STATUS;
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
        code =SmartIosServiceStubBase::COMMAND_SMT_GET_DEVICE_INFO;
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
        code =SmartIosServiceStubBase::COMMAND_SMT_DEL_SINGLE_DEVICE;
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
        code =SmartIosServiceStubBase::COMMAND_SMT_DEL_ALL_DEVICES;
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
        code =SmartIosServiceStubBase::COMMAND_SMT_LAUNCH_SOURCE_ANDROID;
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
        code =SmartIosServiceStubBase::COMMAND_MAX;
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
        code =SmartIosServiceStubBase::COMMAND_SMT_SET_POP_STATUS_ANDROID;
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
        code =SmartIosServiceStubBase::COMMAND_SMT_GET_DEVICE_INFO_ANDROID;
        Test_smtIosService::service->mStub->onAsyncRequest(id, code, _data);
    }
#endif
    TEST_F(Test_smtIosServiceStub,smt_setPopStatusAndroid) {
        SenderId id = 3;
        SmtSetType type = SMT_IOS_POPUP_SET;
        int index = 7;
        SmtPopStatusAndroid pop = (SmtPopStatusAndroid)0;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_setPopStatusAndroid(id,type,index,pop));
        SmtDevReqType reqtype = SMT_IOS_DEV_ALL_REQ;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_getDeviceInfoAndroid(id,reqtype,index));
        uint8_t connState=0;
        uint8_t index1=1;
        uint8_t popStatus=1;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->smt_getDevConnectInfoAndroid(connState,index1,popStatus));
        android::String8 serinum("12354");
        android::String8 devname("iphone");
        Test_smtIosService::service->mStub->onAndroidAuthInfo(serinum,devname);
    }
}
