#include<gtest/gtest.h>
#define private public
#include "ServiceProxyBase.h"
#include "proxy/SmartIosServiceProxyBase.h"
#include "binder/Parcel.h"
namespace goni {
    class Test_SmartIosServiceProxyBase:public testing::Test {
        protected:
            static SmartIosServiceProxyBase *base;
            static void SetUpTestCase() {
                base = new SmartIosServiceProxyBase(new ISmartIosServiceProxyReplier);
            }
            static void TearDownTestCase() {
                if(NULL != base) {
                    delete base;
                    base = NULL;
                }
            }
    };
    SmartIosServiceProxyBase * Test_SmartIosServiceProxyBase::base = NULL;
    TEST_F(Test_SmartIosServiceProxyBase,onConnected) {
        base->onConnected();
    }
    TEST_F(Test_SmartIosServiceProxyBase,smt_launchSource) {
        const uint8_t index =1;
        const SmtIosSource source = SMT_IOS_SOURCE_CARPLAY;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_launchSource(index,source));
        const SmtIosSource source1 = SMT_IOS_SOURCE_WEBLINK;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_launchSource(index,source1));
        const SmtIosSource source2 = SMT_IOS_SOURCE_IPOD;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_launchSource(index,source2));
        const uint8_t index2 =6;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_launchSource(index2,source));
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_launchSource(index2,source1));
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_launchSource(index2,source2));
    }
    TEST_F(Test_SmartIosServiceProxyBase,smt_launchSource_Android) {
        const uint8_t index =1;
        const SmtAndroidSource source = SMT_ANDROID_SOURCE_AAP;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_launchSource_Android(index,source));
        const SmtAndroidSource source2 = SMT_ANDROID_SOURCE_WEBLINK;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_launchSource_Android(index,source2));
    }
    TEST_F(Test_SmartIosServiceProxyBase,smt_setPopStatus) {
        const SmtSetType setType= SMT_IOS_POPUP_SET;
        const uint8_t index =1;
        const SmtPopStatus pop = SMT_POP_INVALID;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_setPopStatus(setType,index,pop));
        const SmtPopStatus pop2 = SMT_AUTOCARPLAY;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_setPopStatus(setType,index,pop2));
        const SmtPopStatusAndroid pop3 = SMT_ANDROID_AUTOWEBLINK;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_setPopStatusAndroid(setType,index,pop3));
    }
    TEST_F(Test_SmartIosServiceProxyBase,smt_getDeviceInfo) {
        const SmtDevReqType reqType = SMT_IOS_DEV_ALL_REQ;
        const uint8_t index = 1;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_getDeviceInfo(reqType,index));
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_getDeviceInfoAndroid(reqType,index));
    }
    TEST_F(Test_SmartIosServiceProxyBase,smt_delSingleDevice) {
        const uint8_t index = 1;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_delSingleDevice(index));
    }
    TEST_F(Test_SmartIosServiceProxyBase,smt_delAllDevices) {
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_delAllDevices());
    }
    TEST_F(Test_SmartIosServiceProxyBase,smt_getDevConnectInfo) {
        uint8_t connState = 1;
        uint8_t index = 1;
        uint8_t popStatus = 1;
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_getDevConnectInfo(connState,index,popStatus));
        EXPECT_EQ(BS_NO_CONNECTION,base->smt_getDevConnectInfoAndroid(connState,index,popStatus));
    }
    TEST_F(Test_SmartIosServiceProxyBase,onAsyncResponse) {
        unsigned int code;
        android::Parcel data;
        code = SmartIosServiceProxyBase::NOTIFY_SMT_DEL_SINGLE_DEVICE_IND;
        EXPECT_EQ(0,base->onAsyncResponse(code,data));
        code = SmartIosServiceProxyBase::NOTIFY_SMT_POP_STATUS_IND;
        EXPECT_EQ(0,base->onAsyncResponse(code,data));
        code = SmartIosServiceProxyBase::NOTIFY_SMT_DEVICE_INFO_IND;
        EXPECT_EQ(0,base->onAsyncResponse(code,data));
        code = SmartIosServiceProxyBase::NOTIFY_SMT_DEL_ALL_DEVICE_IND;
        EXPECT_EQ(0,base->onAsyncResponse(code,data));
        code = SmartIosServiceProxyBase::NOTIFY_SMT_DEV_INFO_CMP_IND;
        EXPECT_EQ(0,base->onAsyncResponse(code,data));
        code = SmartIosServiceProxyBase::NOTIFY_MAX;
        EXPECT_EQ(0,base->onAsyncResponse(code,data));
        code = SmartIosServiceProxyBase::NOTIFY_SMT_POP_STATUS_IND_ANDROID;
        EXPECT_EQ(0,base->onAsyncResponse(code,data));
        code = SmartIosServiceProxyBase::NOTIFY_SMT_DEVICE_INFO_IND_ANDROID;
        EXPECT_EQ(0,base->onAsyncResponse(code,data));
    }
    TEST_F(Test_SmartIosServiceProxyBase,onDisconnected) {
        base->onDisconnected();
    }
}
