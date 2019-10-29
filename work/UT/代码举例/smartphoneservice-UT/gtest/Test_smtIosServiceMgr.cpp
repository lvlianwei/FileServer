#include<gtest/gtest.h>
#include<gmock/gmock.h>
#define private public
#include "Test_smtIosService.h"
#include "SmartIosServiceManager.h"
#include "SmartIosServiceReplier.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosMessage.h"  
#include "testSmartIosSettingProxy.h"
#include "SmartIosConnManagerProxy.h" 
#include "SmartIosServiceStub.h"
#include "servicebase/Message.h"
#include<stdio.h>
#include<vector>

using testing::_;
using testing::Return;
using testing::AtLeast;
using testing::SetArgPointee;
using testing::DoAll;
using Test::IosDeviceName;
namespace goni {
    class Test_smtIosMgr:public testing::Test {
        public:
            static SmartIosServiceManager::SmartIosManagerHandler * handler;
            static void SetUpTestCase() {
                handler = new SmartIosServiceManager::SmartIosManagerHandler(Test_smtIosService::service->mStub->mManager);
                printf("##################Test smt ios mgr set up###############\n");
            }
            static void TearDownTestCase() {
                printf("#################Test mst ios mgr tear down##############\n");
                delete handler;
            }
    };
    SmartIosServiceManager::SmartIosManagerHandler * Test_smtIosMgr::handler = NULL;
    TEST_F(Test_smtIosMgr,onGetDevInfoReqHandler) {
        SmartIosMessage::GetDevInfoReq devInfoReq;
        memset(&devInfoReq,0,sizeof(devInfoReq));
        devInfoReq.reqType = SMT_IOS_DEV_ALL_REQ;
        SmartIosMessage::GetDevInfoReq* req = NULL;
        req = & devInfoReq;
        SmtDeviceType deviceType = SMT_DEVICE_TYPE_IOS;

        std::vector<IosDeviceName*> mDeviceList;
        IosDeviceName* devnameptr = new IosDeviceName;
        memset(devnameptr,0,sizeof(IosDeviceName));
        memset(devnameptr ->format.deviceName,0,66);
        mDeviceList.push_back(devnameptr);
        std::vector<IosDeviceName*> mDeviceList1;
        IosDeviceName* devnameptr0 = new IosDeviceName;
        memset(devnameptr0,0,sizeof(IosDeviceName));
        mDeviceList1.push_back(devnameptr0);
        IosDeviceName* devnameptr1 = new IosDeviceName;
        memset(devnameptr1,0,sizeof(IosDeviceName));
        mDeviceList1.push_back(devnameptr1);
        IosDeviceName* devnameptr2 = new IosDeviceName;
        memset(devnameptr2,0,sizeof(IosDeviceName));
        mDeviceList1.push_back(devnameptr2);
        IosDeviceName* devnameptr3 = new IosDeviceName;
        memset(devnameptr3,0,sizeof(IosDeviceName));
        mDeviceList1.push_back(devnameptr3);
        IosDeviceName* devnameptr4 = new IosDeviceName;
        memset(devnameptr4,0,sizeof(IosDeviceName));
        mDeviceList1.push_back(devnameptr4);
        IosDeviceName* devnameptr5 = new IosDeviceName;
        memset(devnameptr5,0,sizeof(IosDeviceName));
        mDeviceList1.push_back(devnameptr5);
        std::vector<IosDeviceName*> mDeviceList2;
        IosDeviceName* devnameptr01 = new IosDeviceName;
        memset(devnameptr01,0,sizeof(IosDeviceName));
        mDeviceList2.push_back(devnameptr01);
        std::vector<IosDeviceName*> mDeviceList3;
        IosDeviceName* devnameptr001 = new IosDeviceName;
        memset(devnameptr001,0,sizeof(IosDeviceName));
        memset(devnameptr001 ->format.deviceName,0,100);
        mDeviceList3.push_back(devnameptr001);
        EXPECT_CALL(*(SingletonForSmartIosSettingProxy::getInstance()),getDeviceInfo(_,_,_,_)).Times(AtLeast(4))
            .WillOnce(DoAll(SetArgPointee<2>(mDeviceList),Return(true)))
            .WillOnce(Return(false))
            .WillOnce(DoAll(SetArgPointee<2>(mDeviceList1),Return(true)))
            .WillOnce(DoAll(SetArgPointee<2>(mDeviceList2),Return(true)))
            .WillOnce(DoAll(SetArgPointee<2>(mDeviceList3),Return(true)));
        handler->onGetDevInfoReqHandler(req,deviceType);
        handler->onGetDevInfoReqHandler(req,deviceType);
        devInfoReq.reqType = SMT_IOS_DEV_SINGLE_REQ;
        handler->onGetDevInfoReqHandler(req,deviceType);
        deviceType = SMT_DEVICE_TYPE_ANDROID;
        handler->onGetDevInfoReqHandler(req,deviceType);
        devInfoReq.reqType = SMT_IOS_DEV_ALL_REQ;
        handler->onGetDevInfoReqHandler(req,deviceType);
        SingletonForSmartIosSettingProxy::delInstance();
    }
    TEST_F(Test_smtIosMgr,smt_launchSource) {
        SenderId id = 3;
        uint8_t index = 0; 
        SmtIosSource source = (SmtIosSource)0;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->smt_launchSource(id,index,source));
    }
    TEST_F(Test_smtIosMgr,smt_setPopStatus) {
        SenderId id = 3;
        SmtSetType type = SMT_IOS_POPUP_SET;
        int index = 7;
        SmtPopStatus pop = (SmtPopStatus)0;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->smt_setPopStatus(id,type,index,pop));
        SmtPopStatusAndroid popstatus=(SmtPopStatusAndroid)0;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->smt_setPopStatusAndroid(id,type,index,popstatus));
    }
    TEST_F(Test_smtIosMgr,smt_delSingleDevice) {
        SenderId id = 3;
        int index = 2;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->smt_delSingleDevice(id,index));
    }
    TEST_F(Test_smtIosMgr,smt_delAllDevice) {
        SenderId id = 3;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->smt_delAllDevice(id));
    }
    TEST_F(Test_smtIosMgr,smt_getDeviceInfo) {
        SenderId id = 3;
        SmtDevReqType type = ( SmtDevReqType)0;
        int index = 0;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->smt_getDeviceInfo(id,type,index));
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->smt_getDeviceInfoAndroid(id,type,index));
    }
    TEST_F(Test_smtIosMgr,onIap2AuthInfo) {
        android::String8 serinum("111");
        android::String8 devname("iphone");
        Test_smtIosService::service->mStub->mManager->onIap2AuthInfo(serinum,devname);
        Test_smtIosService::service->mStub->mManager->onAndroidAuthInfo(serinum,devname);
    }
    TEST_F(Test_smtIosMgr,onIapDeviceInsert) {
        android::String8 serinum("111");
        Test_smtIosService::service->mStub->mManager->onIapDeviceInsert(true,serinum);
    }
    TEST_F(Test_smtIosMgr,onIapExact) {
        Test_smtIosService::service->mStub->mManager->onIapExact();
    }
    TEST_F(Test_smtIosMgr,setLaunchState) {
        smtLaunchState state=LAUNCH_IDLE;
        Test_smtIosService::service->mStub->mManager->setLaunchState(state);
    }
    TEST_F(Test_smtIosMgr,onLaunchResultCheckTime) {
        Timer* timer;
        Test_smtIosService::service->mStub->mManager->onLaunchResultCheckTime(timer);
        Test_smtIosService::service->mStub->mManager->mLaunchState = LAUNCHING;
        Test_smtIosService::service->mStub->mManager->onLaunchResultCheckTime(timer);
    }
#if 1
    TEST_F(Test_smtIosMgr,onReceiveMessage) {
        EXPECT_CALL(*(SingletonForSmartIosSettingProxy::getInstance()),getDeviceInfo(_,_,_,_)).Times(AtLeast(1)).WillRepeatedly(Return(true));
        EXPECT_CALL(*(SingletonForSmartIosSettingProxy::getInstance()),iapDeviceInsert(_,_,_)).Times(AtLeast(1)).WillRepeatedly(Return(1));
        SmartIosMessage::LaunchSourceReq launchReq;
        memset(&launchReq,0,sizeof(launchReq));
        android::sp<SmartIosMessage> msg = new SmartIosMessage(launchReq);
        printf("handler %p\n",handler);
        handler->onReceiveMessage((Message*)msg.get());


        SmartIosMessage::SetPopStatusReq popReq;
        memset(&popReq,0,sizeof(popReq));
        msg = new SmartIosMessage(popReq);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::delSingleDeviceReq delReq;
        memset(&delReq,0,sizeof(delReq));
        msg = new SmartIosMessage(delReq);
        handler->onReceiveMessage((Message*)msg.get());
        SmartIosMessage::delAllDeviceReq req;
        memset(&req,0,sizeof(&req));
        msg = new SmartIosMessage(req);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::IapDevInsertInd insertDev;
        memset(&insertDev,0,sizeof(insertDev));
        memcpy(insertDev.serialNum,"111",40);
        msg = new SmartIosMessage(insertDev);
        handler->onReceiveMessage((Message*)msg.get());
        memcpy(insertDev.serialNum,"222",40);
        msg = new SmartIosMessage(insertDev);
        handler->onReceiveMessage((Message*)msg.get());
        memcpy(insertDev.serialNum,"333",40);
        msg = new SmartIosMessage(insertDev);
        handler->onReceiveMessage((Message*)msg.get());

        memset(&popReq,0,sizeof(popReq));
        msg = new SmartIosMessage(popReq);
        popReq.index = 1;
        popReq.setType = SMT_IOS_POPUP_SET;
        popReq.pop = SMT_AUTOWEBLINK;
        handler->onReceiveMessage((Message*)msg.get());
        popReq.index = 2;
        popReq.setType = SMT_IOS_POPUP_SET;
        popReq.pop = SMT_AUTOWEBLINK;
        msg = new SmartIosMessage(popReq);
        handler->onReceiveMessage((Message*)msg.get());
        popReq.index = 3;
        popReq.setType = SMT_IOS_POPUP_SET;
        popReq.pop = SMT_AUTOWEBLINK;
        msg = new SmartIosMessage(popReq);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::GetDevInfoReq devInfoReq;
        memset(&devInfoReq,0,sizeof(devInfoReq));
        devInfoReq.reqType = SMT_IOS_DEV_ALL_REQ;
        msg = new SmartIosMessage(devInfoReq);
        handler->onReceiveMessage((Message*)msg.get());


        SmartIosMessage::devAutoInfo devinfo;
        memset(&devinfo,0,sizeof(devinfo));
        msg = new SmartIosMessage(devinfo);
        handler->onReceiveMessage((Message*)msg.get());
        SmartIosMessage::IapExactInd exactDev;
        memset(&exactDev,0,sizeof(exactDev));
        msg = new SmartIosMessage(exactDev);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::LaunchSourceReq sourceReq;
        memset(&sourceReq,0,sizeof(sourceReq));
        msg = new SmartIosMessage(sourceReq);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::LaunchSourceReqAndroid sourceReqAndroid;
        memset(&sourceReqAndroid,0,sizeof(sourceReqAndroid));
        msg = new SmartIosMessage(sourceReqAndroid);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::DevConStatusInd DevstatusInd;
        memset(&DevstatusInd,0,sizeof(&DevstatusInd));
        msg = new SmartIosMessage(DevstatusInd);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::PopStatusInd popStatusInd ;
        memset(&popStatusInd,0,sizeof(popStatusInd));
        msg = new SmartIosMessage(popStatusInd);
        handler->onReceiveMessage((Message*)msg.get());
#if 0
        SmartIosMessage::DevInfoInd DevInfoInd ;
        memset(&DevInfoInd,0,sizeof(&DevInfoInd));
        msg = new SmartIosMessage(DevInfoInd);
        handler->onReceiveMessage((Message*)msg.get());
#endif
        SmartIosMessage::AndroidDevInsertInd DevInsertInd ;
        memset(&DevInsertInd,0,sizeof(&DevInsertInd));
        msg = new SmartIosMessage(DevInsertInd);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::IosLaunchResult IosResult ;
        memset(&IosResult,0,sizeof(&IosResult));
        msg = new SmartIosMessage(IosResult);
        handler->onReceiveMessage((Message*)msg.get());

        SmartIosMessage::AndroidExactInd EcactInd;
        memset(&EcactInd,0,sizeof(&EcactInd));
        msg = new SmartIosMessage(EcactInd);
        handler->onReceiveMessage((Message*)msg.get());
        SingletonForSmartIosSettingProxy::delInstance();
		SingletonForSmartIosSettingProxy::delInstance();
    }
    TEST_F(Test_smtIosMgr,getInstance) {
        Test_smtIosService::service->mStub->mManager->getInstance();
    }
    TEST_F(Test_smtIosMgr,deInit) {
        Test_smtIosService::service->mStub->mManager->deInit();
    }
    TEST_F(Test_smtIosMgr,notifyLaunchResult) {
        smtLaunchState state = LAUNCH_IDLE;
        Test_smtIosService::service->mStub->mManager->notifyLaunchResult(state);
        state = LAUNCHING;
        Test_smtIosService::service->mStub->mManager->notifyLaunchResult(state);
    }
    TEST_F(Test_smtIosMgr,smt_launchSource_Android) {
        SenderId id = 3;
        uint8_t index = 0; 
        SmtAndroidSource source = (SmtAndroidSource)0;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->smt_launchSource_Android(id,index,source));
    }
    TEST_F(Test_smtIosMgr,getDevConnectInfo) {
        uint8_t connState = 1;
        uint8_t index = 2;
        uint8_t popStatus = 1;
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->getDevConnectInfo(connState,index,popStatus));
        EXPECT_EQ(0,Test_smtIosService::service->mStub->mManager->getDevConnectInfoAndroid(connState,index,popStatus));
    }
    TEST_F(Test_smtIosMgr,onAndroidDeviceInsert) {
        android::String8 serinum("111");
        Test_smtIosService::service->mStub->mManager->onAndroidDeviceInsert(serinum);
        serinum = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
        Test_smtIosService::service->mStub->mManager->onAndroidDeviceInsert(serinum);
    }
    TEST_F(Test_smtIosMgr,onAndroidExact) {
        Test_smtIosService::service->mStub->mManager->onAndroidExact();
    }
    TEST_F(Test_smtIosMgr,onMsgReceived) {
        uint8_t opcode = 1;
        void* msg = NULL;
        Test_smtIosService::service->mStub->mManager->onMsgReceived(opcode,msg);
    }

#endif
}
