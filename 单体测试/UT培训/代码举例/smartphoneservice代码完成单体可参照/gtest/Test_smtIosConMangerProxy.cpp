#include "testConnectManagerSub.h"
#include "testIServiceManager.h"
#include "testConnectManagerProxyBase.h"
#include "testSmartIosSettingProxy.h"
#include "include/SmartIosServiceServiceDefines.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosConnManagerProxy.h"
#include "SmartIosServiceManager.h"
#include "include/SmartIosServiceDTLog.h"
#include "SmartIosServiceReplier.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Test_smtIosService.h"

using testing::_;
using testing::Return;
using testing::SetArgReferee;
using testing::AtLeast;
using testing::AnyNumber;
namespace goni {
    class SmartIosServiceStub;
    class SmartIosSettingProxy;
    class SmartIosConManagerProxy;
    class SmartIosMessage;
    class SmartIosServiceManager;
    class ServiceBase;
    class Test_SmartIosConMngReply:public testing::Test {
        public:
            static SmartIosConMngReply* mngReply;
            static void SetUpTestCase() {
                EXPECT_CALL(*(SingletonSmtIConnectManagerProxy::getInstance()),getIosDevInfo(_,_,_)).Times(AnyNumber()).WillOnce(Return(1));
				EXPECT_CALL(*(SingletonForSmartIosSettingProxy::getInstance()),iapDeviceInsert(_,_,_)).Times(AnyNumber()).WillRepeatedly(Return(1));
				EXPECT_CALL(*(SingletonForSmartIosSettingProxy::getInstance()),getDeviceInfo(_,_,_,_)).Times(AnyNumber()).WillRepeatedly(Return(true));
                ServiceBase *smartIosService = new SmartIosService;
                SmartIosServiceStub* stub = new SmartIosServiceStub((SmartIosService*)smartIosService);
                SmartIosServiceReplier *replier = new SmartIosServiceReplier(smartIosService);
                SmartIosServiceManager *smartIosServiceManager = new SmartIosServiceManager(stub, replier);
                mngReply = new SmartIosConMngReply(smartIosServiceManager);
                printf("##################Test smt SmartIosConMngReply set up###############\n");
                smartIosServiceManager ->initialize();

            }
            static void TearDownTestCase() {
                SingletonForSmartIosSettingProxy::delInstance();
                printf("#################Test mst SmartIosConMngReply tear down##############\n");
                delete mngReply;
            }
    };
    SmartIosConMngReply *Test_SmartIosConMngReply::mngReply = NULL;
    TEST_F(Test_SmartIosConMngReply,onDisconnected) {
        mngReply->onDisconnected();
    }
    TEST_F(Test_SmartIosConMngReply,onConnected) {
        EXPECT_CALL(*(SingletonSmtIService::getInstance()),checkServiceDiedBefore(_)).WillOnce(Return(true));
        mngReply->onConnected();
        EXPECT_CALL(*(SingletonSmtIService::getInstance()),checkServiceDiedBefore(_)).WillOnce(Return(false));
        mngReply->onConnected();
        EXPECT_CALL(*(SingletonSmtIService::getInstance()),checkServiceDiedBefore(_)).WillOnce(Return(false));
        mngReply->onConnected();
        EXPECT_CALL(*(SingletonSmtIService::getInstance()),checkServiceDiedBefore(_)).WillOnce(Return(false));
        mngReply->onConnected();
        SingletonSmtIService::delInstance();
        SingletonSmtIConnectManagerProxy::delInstance();
    }
    TEST_F(Test_SmartIosConMngReply,notify) {
        const int32_t a=1;
        const int32_t b=1;
        EXPECT_EQ(0,mngReply->notify(a,b));
    }
    TEST_F(Test_SmartIosConMngReply,notify_ipodInsert) {
        const IpodInfo_Sp sp = new IpodInfo;
        EXPECT_EQ(0,mngReply->notify_ipodInsert(sp));
        const android::String8 serialNum("smartiop");
        EXPECT_EQ(0,mngReply->notify_androidInsert(serialNum));
    }
    TEST_F(Test_SmartIosConMngReply,notify_ipodRoleSwitch) {
        const USB_ROLE_TYPE type = USB_ROLE_TYPE_HOST;
        EXPECT_EQ(0,mngReply->notify_ipodRoleSwitch(type));
    }
    TEST_F(Test_SmartIosConMngReply,notify_carlifeInsert) {
        EXPECT_EQ(0,mngReply->notify_carlifeInsert());
    }
    TEST_F(Test_SmartIosConMngReply,notify_carlifeAoaSwitch) {
        const CON_MGR_RESULT res = CON_MGR_RESULT_SUCCESS;
        EXPECT_EQ(0,mngReply->notify_carlifeAoaSwitch(res));
    }
    TEST_F(Test_SmartIosConMngReply,notify_carlifeEapAuthResult) {
        const CON_MGR_RESULT res = CON_MGR_RESULT_SUCCESS;
        EXPECT_EQ(0,mngReply->notify_carlifeEapAuthResult(res));
    }
    TEST_F(Test_SmartIosConMngReply,notify_carlifeExtract) {
        EXPECT_EQ(0,mngReply->notify_carlifeExtract());
        EXPECT_EQ(0,mngReply->notify_hubInsert());
        EXPECT_EQ(0,mngReply->notify_hubExtract());
    }
    TEST_F(Test_SmartIosConMngReply,notify_usbMount) {
        const StorageInfo_Sp sp = new StorageInfo;
        EXPECT_EQ(0,mngReply->notify_usbMount(sp));
    }
    TEST_F(Test_SmartIosConMngReply,notify_usbUnmount) {
        const StorageInfo_Sp sp = new StorageInfo;
        EXPECT_EQ(0,mngReply->notify_usbUnmount(sp));
    }
    TEST_F(Test_SmartIosConMngReply,notify_usbBadRemoval) {
        const StorageInfo_Sp sp = new StorageInfo;
        EXPECT_EQ(0,mngReply->notify_usbBadRemoval(sp));
    }
    TEST_F(Test_SmartIosConMngReply,notify_iap2AuthResult) {
        const CON_MGR_RESULT type = CON_MGR_RESULT_SUCCESS;
        EXPECT_EQ(0,mngReply->notify_iap2AuthResult(type));
    }
    TEST_F(Test_SmartIosConMngReply,notify_iapAuthResult) {
        const IPOD_DEVICE_TYPE type = IPOD_DEVICE_TYPE_IAP2;
        EXPECT_EQ(0,mngReply->notify_iapAuthResult(type));
    }
    TEST_F(Test_SmartIosConMngReply,notify_carplayAuthResult) {
        const CON_MGR_RESULT res = CON_MGR_RESULT_SUCCESS;
        EXPECT_EQ(0,mngReply->notify_carplayAuthResult(res));
    }
    TEST_F(Test_SmartIosConMngReply,notify_usbCheckStatus) {
        const USB_CHECK_STATUS sts = USB_CHECK_STATUS_INSERT;
        EXPECT_EQ(0,mngReply->notify_usbCheckStatus(sts));
    }
    class Test_SmartIosConManagerProxy:public testing::Test{
        public:
            static SmartIosConManagerProxy* mgrProxy;
            static void SetUpTestCase() {
                ServiceBase *smartIosService = new SmartIosService;
                SmartIosServiceStub* stub = new SmartIosServiceStub((SmartIosService*)smartIosService);
                SmartIosServiceReplier *replier = new SmartIosServiceReplier(smartIosService);
                SmartIosServiceManager *smartIosServiceManager = new SmartIosServiceManager(stub, replier);
                mgrProxy = new SmartIosConManagerProxy(smartIosServiceManager);
                printf("##################Test smt SmartIosConManagerProxy set up###############\n");
            }
            static void TearDownTestCase() {
                printf("#################Test mst SmartIosConManagerProxy tear down##############\n");
                delete mgrProxy;
            }
    };
    SmartIosConManagerProxy* Test_SmartIosConManagerProxy::mgrProxy = NULL;
    TEST_F(Test_SmartIosConManagerProxy,launchIosSourceReq) {
        mgrProxy->launchIosSourceReq(SMT_IOS_SOURCE_CARPLAY);
        mgrProxy->launchIosSourceReq(SMT_IOS_SOURCE_IPOD);
        mgrProxy->launchIosSourceReq(SMT_IOS_SOURCE_WEBLINK);
    }
    TEST_F(Test_SmartIosConManagerProxy,launchAndroidSourceReq) {
        mgrProxy->launchAndroidSourceReq(SMT_ANDROID_SOURCE_AAP);
        mgrProxy->launchAndroidSourceReq(SMT_ANDROID_SOURCE_WEBLINK);
    }
    class Test_SmartConnectManagerListener:public testing::Test {
        public:
            static SmartConnectManagerListener* listener;
            static void SetUpTestCase() {
                ServiceBase *smartIosService = new SmartIosService;
                SmartIosServiceStub* stub = new SmartIosServiceStub((SmartIosService*)smartIosService);
                listener = new SmartConnectManagerListener(stub);
                printf("##################Test smt SmartConnectManagerListener set up###############\n");
            }
            static void TearDownTestCase() {
                printf("#################Test mst SmartConnectManagerListener tear down##############\n");
                delete listener;
            }
    };
    SmartConnectManagerListener *Test_SmartConnectManagerListener::listener = NULL;
    TEST_F(Test_SmartConnectManagerListener,notify_iap2Insert) {
        const bool isCarplaySupp = 1;
        const android::String8 serialNum;
        EXPECT_EQ(0,listener->notify_iap2Insert(isCarplaySupp,serialNum));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_androidInsert) {
        const android::String8 serialNum;
        EXPECT_EQ(0,listener->notify_androidInsert(serialNum));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_iap2Extract) {
        EXPECT_EQ(0,listener->notify_iap2Extract());	
    }
    TEST_F(Test_SmartConnectManagerListener,notify_androidExtract) {
        EXPECT_EQ(0,listener->notify_androidExtract());
    }
    TEST_F(Test_SmartConnectManagerListener,notify_iap2AuthInfo) {
        const android::String8 serialNum;
        const android::String8 devName;
        EXPECT_EQ(0,listener->notify_iap2AuthInfo(serialNum,devName));
        EXPECT_EQ(0,listener->notify_androidAuthInfo(serialNum,devName));
        EXPECT_EQ(0,listener->notify_androidInsert(serialNum));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_iapAuthResult) {
        const IPOD_DEVICE_TYPE type=IPOD_DEVICE_TYPE_IAP1_IPOD;
        const bool isLastOn= 1;
        EXPECT_EQ(0,listener->notify_iapAuthResult(type,isLastOn));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_unsupportUsbExtract) {
        EXPECT_EQ(0,listener->notify_unsupportUsbExtract());
        EXPECT_EQ(0,listener->notify_overCurrent());
        EXPECT_EQ(0,listener->notify_ipodExtract());
        EXPECT_EQ(0,listener->notify_carlifeExtract());
        EXPECT_EQ(0,listener->notify_hubExtract());
        EXPECT_EQ(0,listener->notify_iap2Extract());
        EXPECT_EQ(0,listener->notify_androidExtract());
    }
    TEST_F(Test_SmartConnectManagerListener,notify_unsupportUsbInsert) {
        const UNSUPPORT_USB_TYPE type = UNSUPPORT_USB_TYPE_NORESPONSE;
        EXPECT_EQ(0,listener->notify_unsupportUsbInsert(type));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_ipodInsert) {
        const IpodInfo_Sp info = new IpodInfo;
        EXPECT_EQ(0,listener->notify_ipodInsert(info));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_ipodRoleSwitch) {
        const IpodInfo_Sp info = new IpodInfo;
        const USB_ROLE_TYPE type = USB_ROLE_TYPE_DEVICE;
        EXPECT_EQ(0,listener->notify_ipodRoleSwitch(info,type));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_iap2AuthResult) {
        const CON_MGR_RESULT res = CON_MGR_RESULT_SUCCESS;
        const bool isLastOn = 1;
        EXPECT_EQ(0,listener->notify_iap2AuthResult(res,isLastOn));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_carplayAuthResult) {
        const CON_MGR_RESULT res=CON_MGR_RESULT_SUCCESS;
        EXPECT_EQ(0,listener->notify_carplayAuthResult(res));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_carlifeInsert) {
        const bool isLastOn = 1;
        EXPECT_EQ(0,listener->notify_carlifeInsert(isLastOn));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_carlifeAoaSwitch) {
        const CON_MGR_RESULT res=CON_MGR_RESULT_SUCCESS;
        EXPECT_EQ(0,listener->notify_carlifeAoaSwitch(res));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_usbMount) {
        const StorageInfo_Sp info = new StorageInfo;
        EXPECT_EQ(0,listener->notify_usbMount(info));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_usbUnmount) {
        const StorageInfo_Sp info = new StorageInfo;
        EXPECT_EQ(0,listener->notify_usbUnmount(info));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_usbBadRemoval) {
        const StorageInfo_Sp info = new StorageInfo;
        EXPECT_EQ(0,listener->notify_usbBadRemoval(info));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_hubInsert) {
        const bool isLastOn=1;
        EXPECT_EQ(0,listener->notify_hubInsert(isLastOn));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_iosDevConnected) {
        const int32_t index =6;
        const IOS_POPUP_STATUS sts =IOS_POPUP_STATUS_NOCARLIFE_MANUCARPLAY;
        EXPECT_EQ(0,listener->notify_iosDevConnected(index,sts));
    }
    TEST_F(Test_SmartConnectManagerListener,notify_iosDevDisconnected) {
        const int32_t index =6;
        EXPECT_EQ(0,listener->notify_iosDevDisconnected(index));
    }
}

