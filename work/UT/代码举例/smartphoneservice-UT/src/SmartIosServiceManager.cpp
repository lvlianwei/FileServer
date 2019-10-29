
#include "SmartIosServiceManager.h"
#include "SmartIosServiceReplier.h"
#include "SmartIosMessage.h"
#ifdef UT_GTEST_FULL_ENG
#include "testSmartIosSettingProxy.h"
#else
#include "SmartIosSettingProxy.h"
#endif
#include "SmartIosConnManagerProxy.h"
#include "SmartIosServiceStub.h"
#include "servicebase/Message.h"
#include "servicebase/SystemLog.h"
namespace goni
{
DeclearModuleID(DTMODULEID_SMARTIOS);

SmartIosServiceManager * SmartIosServiceManager::manager = NULL;
#define USE_SQLITE3 "use_sqlite3"
SmartIosServiceManager::SmartIosServiceManager(SmartIosServiceStub* stub, SmartIosServiceReplier* replier)    /* __0x406001_DTFUNCID__ */
:mThread(new SmartIosManagerHandler(this))
, mReplier(replier)
, mStub(stub)
,mConProxy(NULL)
,mLaunchState(LAUNCH_IDLE)
{
    SMTLOGD("start the SmartIosServiceManager thread");
    SMTLOGD("this is %p",this);
    manager = this;
    mConnState = 0;
    mIndex = 0;
    mPopStatus = 0;
    mThread.start(false, 0, THREAD_PRIORITY_DISPLAY, 0);
}

SmartIosServiceManager::~SmartIosServiceManager()    /* __0x406002_DTFUNCID__ */
{
    SMTLOGD("stop the SmartIosServiceManager thread");
    mThread.stop();
    mThread.join();
}
SmartIosServiceManager* SmartIosServiceManager::getInstance()    /* __0x406003_DTFUNCID__ */ {
     return manager;
}
void SmartIosServiceManager::deInit()    /* __0x406004_DTFUNCID__ */ {
    DTLOG_INFO(0x406004, "SmartIosServiceManager::deInit");
    SMTLOGD("SmartIosServiceManager::deInit");
    SmartIosSettingProxy::getInstance()->deInit(); 
}
void SmartIosServiceManager::initialize()    /* __0x406005_DTFUNCID__ */
{
    DTLOG_INFO(0x406005, "SmartIosServiceManager::initialize");
    SMTLOGD("SmartIosServiceManager::initialize");
    mConProxy = new SmartIosConManagerProxy(this);
#ifndef USE_SQLITE3
    SmartIosSettingProxy::getInstance()->clearNoCompleteData();
#else
#endif
    //SmartIosSettingProxy::getInstance()->resetDB();
}

SmartIosServiceReplier* SmartIosServiceManager::getServiceReplier()    /* __0x406006_DTFUNCID__ */
{
    SMTLOGD("****%s****", __func__);
    return mReplier;
}

SmartIosServiceStub* SmartIosServiceManager::getServiceStub()    /* __0x406007_DTFUNCID__ */
{
    SMTLOGD("****%s****", __func__);
    return mStub;
}
void SmartIosServiceManager::onLaunchResultCheckTime(Timer* timer)    /* __0x406008_DTFUNCID__ */ {
    UNUSED(timer);
    SMTLOGD("/***********SmartIosServiceManager::onLaunchResultCheckTime***************/");
    if(mLaunchState != LAUNCH_IDLE) {
        mLaunchState = LAUNCH_IDLE;
    }
}
SmartIosConManagerProxy* SmartIosServiceManager::getConMngProxy()    /* __0x406009_DTFUNCID__ */
{
    return mConProxy;
}
void SmartIosServiceManager::notifyLaunchResult(smtLaunchState state)    /* __0x40600A_DTFUNCID__ */ {
    SmartIosMessage::IosLaunchResult result;
    result.launchType = state;
    android::sp<SmartIosMessage> msg = new SmartIosMessage(result);
    if(msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
}
android::status_t SmartIosServiceManager::smt_launchSource(SenderId id, const uint8_t& index, const SmtIosSource& source)    /* __0x40600B_DTFUNCID__ */
{
    SmartIosMessage::LaunchSourceReq launchReq;
    launchReq.id = id;
    launchReq.index = index;
    launchReq.source = source;
    android::sp<SmartIosMessage>msg = new SmartIosMessage(launchReq);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
    return 0;
}
android::status_t SmartIosServiceManager::smt_launchSource_Android(SenderId id, const uint8_t& index, const SmtAndroidSource& source)    /* __0x40600C_DTFUNCID__ */
{
    SmartIosMessage::LaunchSourceReqAndroid launchReq;
    launchReq.id = id;
    launchReq.index = index;
    launchReq.source = source;
    android::sp<SmartIosMessage>msg = new SmartIosMessage(launchReq);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
    return 0;
}
android::status_t SmartIosServiceManager:: smt_setPopStatus(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatus& pop)    /* __0x40600D_DTFUNCID__ */
{
    SmartIosMessage::SetPopStatusReq popReq;
    popReq.id = id;
    popReq.index = index;
    popReq.setType = setType;

    popReq.pop = pop;
    android::sp<SmartIosMessage>msg = new SmartIosMessage(popReq);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
    return 0;
}
android::status_t SmartIosServiceManager::smt_setPopStatusAndroid(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatusAndroid& pop)    /* __0x40600E_DTFUNCID__ */
{
    SmartIosMessage::SetPopStatusReqAndroid popReq;
    popReq.id = id;
    popReq.index = index;
    popReq.setType = setType;

    popReq.pop = pop;
    android::sp<SmartIosMessage>msg = new SmartIosMessage(popReq);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
    return 0;
}
/**
 * @brief getDevConnectInfo ,IF for funcmng,to get dev connect state 
 *
 * @param connState,connect or disconnect
 * @param index,device priority
 * @param popStatus device pop value
 *
 * @return 
 */
android::status_t SmartIosServiceManager::getDevConnectInfo(uint8_t& connState,uint8_t& index,uint8_t& popStatus)    /* __0x40600F_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceManager::getDevConnectInfo");
    connState = mConnState;
    index = mIndex;
    popStatus = mPopStatus;
    return 0;
}
android::status_t SmartIosServiceManager::getDevConnectInfoAndroid(uint8_t& connState,uint8_t& index,uint8_t& popStatus)    /* __0x406010_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceManager::getDevConnectInfo");
    connState = mConnStateAndroid;
    index = mIndexAndroid;
    popStatus = mPopStatusAndroid;
    return 0;
}
android::status_t SmartIosServiceManager::smt_delSingleDevice(SenderId id,const uint8_t& index)    /* __0x406011_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceManager::smt_delSingleDevice");
    SmartIosMessage::delSingleDeviceReq delReq;
    delReq.id = id;
    delReq.index = index;
    android::sp<SmartIosMessage> msg = new SmartIosMessage(delReq);
    if(msg != NULL) {
           mThread.postMessage(reinterpret_cast<Message*>(msg.get()),0);
    }
    return 0;       
}
android::status_t SmartIosServiceManager::smt_delAllDevice(SenderId id)    /* __0x406012_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceManager::smt_delAllDevice");
    SmartIosMessage::delAllDeviceReq req;
    req.id = id;
    android::sp<SmartIosMessage> msg = new SmartIosMessage(req);
    if(msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()),0);
    }
    return 0;       
}
android::status_t SmartIosServiceManager::smt_getDeviceInfo(SenderId id, const SmtDevReqType& reqType, const uint8_t& index)    /* __0x406013_DTFUNCID__ */
{
    SmartIosMessage::GetDevInfoReq devInfoReq;
    devInfoReq.id = id;
    devInfoReq.index = index;
    devInfoReq.reqType = reqType;

    android::sp<SmartIosMessage>msg = new SmartIosMessage(devInfoReq);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
    return 0;
}
android::status_t SmartIosServiceManager::smt_getDeviceInfoAndroid(SenderId id, const SmtDevReqType& reqType, const uint8_t& index)    /* __0x406014_DTFUNCID__ */
{
    SmartIosMessage::GetDevInfoReqAndroid devInfoReq;
    devInfoReq.id = id;
    devInfoReq.index = index;
    devInfoReq.reqType = reqType;

    android::sp<SmartIosMessage>msg = new SmartIosMessage(devInfoReq);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
    return 0;
}
void SmartIosServiceManager::onIap2AuthInfo(const android::String8& serialNum, const android::String8& devName)    /* __0x406015_DTFUNCID__ */ {
    SmartIosMessage::devAutoInfo devinfo;
    memset(&devinfo,0x00,sizeof(devinfo));
    memcpy(devinfo.serinum, serialNum.string(), SMT_DEV_SERIAL_LEN_MAX);
    memcpy(devinfo.devName, devName.string(), SMT_DEV_NAME_LEN_MAX);
    

    devinfo.devName[SMT_DEV_NAME_LEN_MAX] = '\0';
    SMTLOGD("line %d,serinum %s,devName %s\n",__LINE__,serialNum.string(),devName.string());
    android::sp<SmartIosMessage> msg = new SmartIosMessage(devinfo);
    if(msg != NULL) {
         mThread.postMessage(reinterpret_cast<Message*>(msg.get()),0);
    }
}
void SmartIosServiceManager::onAndroidAuthInfo(const android::String8& serialNum, const android::String8& devName)    /* __0x406016_DTFUNCID__ */ {
    SmartIosMessage::devAutoInfoAndroid devinfo;
    memset(&devinfo,0x00,sizeof(devinfo));
    memcpy(devinfo.serinum, serialNum.string(), SMT_DEV_SERIAL_LEN_MAX);
    memcpy(devinfo.devName, devName.string(), SMT_DEV_NAME_LEN_MAX);
    

    devinfo.devName[SMT_DEV_NAME_LEN_MAX] = '\0';
    SMTLOGD("line %d,serinum %s,devName %s\n",__LINE__,serialNum.string(),devName.string());
    android::sp<SmartIosMessage> msg = new SmartIosMessage(devinfo);
    if(msg != NULL) {
         mThread.postMessage(reinterpret_cast<Message*>(msg.get()),0);
    }
}
void SmartIosServiceManager::onIapDeviceInsert(bool isCarplaySupp,android::String8 serialNumber)    /* __0x406017_DTFUNCID__ */
{
    SmartIosMessage::IapDevInsertInd insertDev;
    memset(&insertDev, 0x00, sizeof(insertDev));

    memcpy(insertDev.serialNum, serialNumber.string(), SMT_DEV_SERIAL_LEN_MAX);

    
    insertDev.isCarplaySupp = isCarplaySupp;
    SMTLOGD("onIapDeviceInsert serialNumber %s", insertDev.serialNum);
    SMTLOGD("onIapDeviceInsert isCarplaySupp %d",isCarplaySupp);

    android::sp<SmartIosMessage>msg = new SmartIosMessage(insertDev);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
}
void SmartIosServiceManager::onIapExact()    /* __0x406018_DTFUNCID__ */
{
    SmartIosMessage::IapExactInd exactDev;
    android::sp<SmartIosMessage>msg = new SmartIosMessage(exactDev);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
}
void SmartIosServiceManager::onAndroidDeviceInsert(android::String8 serialNumber)    /* __0x406019_DTFUNCID__ */
{
    SmartIosMessage::AndroidDevInsertInd insertDev;
    memset(&insertDev, 0x00, sizeof(insertDev));
    
    if (SMT_DEV_SERIAL_LEN_MAX < serialNumber.length()){
        memcpy(insertDev.serialNum, serialNumber.string(), SMT_DEV_SERIAL_LEN_MAX);
    }
    else {
        memcpy(insertDev.serialNum, serialNumber.string(), serialNumber.length());
    }

    SMTLOGD("onAndroidDeviceInsert serialNumber %s", insertDev.serialNum);

    android::sp<SmartIosMessage>msg = new SmartIosMessage(insertDev);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
}
void SmartIosServiceManager::onAndroidExact()    /* __0x40601A_DTFUNCID__ */
{
    SmartIosMessage::AndroidExactInd exactDev;
    android::sp<SmartIosMessage>msg = new SmartIosMessage(exactDev);
    if (msg != NULL) {
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 0);
    }
}
#if 0
void SmartIosServiceManager::onSmartIosServiceConnected(uint32_t result)
{
	SMTLOGD("*****%s*****",__func__);
    if(result == SmartIos_SERVICE_CONNECTED) {
        mState = SmartIos_CONNECTED;
        // to get bt state;
        BtDevInfo_Sp device = new BtDevInfo();
        uint32_t connectedFunc = 0;
        mBtProxy->getConnectedDevice(device, connectedFunc);        
        SMTLOGD("*****%s*****, connectedFunc = %d, btMac = %llx",__func__, connectedFunc, device->getAddr());
        mBtMode = static_cast<uint16_t>(connectedFunc);
        mLocalInfoData.btMac = device->getAddr();
        mBt = static_cast<uint32_t>((mBtMode & 0x07) != 0);
        mHid = static_cast<uint32_t>((mBtMode & 0x04) != 0);
        if (mLocalInfoData.appBtMac != 0 && mLocalInfoData.appBtMac != mLocalInfoData.btMac){
            mHid = 0;
        }
        mStub->wfdBtStatus(mBt, mHid);
    }
}

#endif

void SmartIosServiceManager::onMsgReceived(uint8_t opcode, void* msg)    /* __0x40601B_DTFUNCID__ */
{
    SMTLOGD("*****%s*****,opcode = %d", __func__, opcode);
    UNUSED(msg);
}

SmartIosServiceManager::SmartIosManagerHandler::SmartIosManagerHandler(SmartIosServiceManager* manager)    /* __0x40601C_DTFUNCID__ */
:mOwner(manager)
{
   mid = -1;
   SMTLOGD("mid = -1");
}

SmartIosServiceManager::SmartIosManagerHandler::~SmartIosManagerHandler()    /* __0x40601D_DTFUNCID__ */
{
}

void SmartIosServiceManager::SmartIosManagerHandler::onReceiveMessage(const android::sp<Message> &msg)    /* __0x40601E_DTFUNCID__ */
{
    SMTASSERT(msg.get() != NULL);
    SmartIosMessage* message = static_cast<SmartIosMessage*>(msg.get());
    if (mOwner == NULL || message == NULL) return;
    switch(message->getEvtId())
    {
        case SmartIosMessage:: SMT_LAUNCH_SOURCE_EVENT:
        {
            SmartIosMessage::LaunchSourceReq* req = message->getLaunchSourceReq();
            onLaunchSourceReqHandler(req);
        }
            break;
            case SmartIosMessage:: SMT_LAUNCH_SOURCE_EVENT_ANDROID:
        {
            SmartIosMessage::LaunchSourceReqAndroid* req = message->getLaunchSourceReqAndroid();
            onLaunchSourceReqHandlerAndroid(req);
        }
            break;
        case SmartIosMessage::SMT_SET_POP_REQ_EVENT:
        {
            SmartIosMessage::SetPopStatusReq* req = message->getSetPopStatusReq();
            onSetPopStatusReqHandler(req);
        }
            break;
        case SmartIosMessage::SMT_SET_POP_REQ_EVENT_ANDROID:
        {
            SmartIosMessage::SetPopStatusReqAndroid* req = message->getSetPopStatusReqAndroid();
            onSetPopStatusReqHandlerAndroid(req);
        }
            break;
        case SmartIosMessage::SMT_GET_DEVINFO_REQ_EVENT:
        {
            SmartIosMessage::GetDevInfoReq* req = message->getDevInfoReq();
            onGetDevInfoReqHandler(req, SMT_DEVICE_TYPE_IOS);
            break;
        }
        case SmartIosMessage::SMT_GET_DEVINFO_REQ_EVENT_ANDROID:
        {
            SmartIosMessage::GetDevInfoReqAndroid* req = message->getDevInfoReqAndroid();
            onGetDevInfoReqHandler((SmartIosMessage::GetDevInfoReq*)req, SMT_DEVICE_TYPE_ANDROID);
            break;
        }
        case SmartIosMessage::SMT_IAP_DEV_INSERT_EVENT:
        {
            SmartIosMessage::IapDevInsertInd* insertDev = message->getIapDevInsertInd();
            onIapDeviceInsertHandler(insertDev);

            break;
        }
        case SmartIosMessage::SMT_IAP_DEV_EXACT_EVENT:
        {
            onIapExactHandler();
            break;
        }
        case SmartIosMessage::SMT_ANDROID_DEV_INSERT_EVENT:
        {
            SmartIosMessage::AndroidDevInsertInd* insertDev = message->getAndroidDevInsertInd();
            onAndroidDeviceInsertHandler(insertDev);

            break;
        }
        case SmartIosMessage::SMT_ANDROID_DEV_EXACT_EVENT:
        {
            onAndroidExactHandler();
            break;
        }
        case SmartIosMessage::SMT_IAP_DEV_AUTO_INFO_EVENT:
        {
            SmartIosMessage::devAutoInfo* devinfo = message->getdevAutoInfo();
            onDevAutoInfoHandler(devinfo, SMT_DEVICE_TYPE_IOS);
            break;
        }
        case SmartIosMessage::SMT_IAP_DEV_AUTO_INFO_EVENT_ANDROID:
        {
            SmartIosMessage::devAutoInfoAndroid* devinfo = message->getdevAutoInfoAndroid();
            onDevAutoInfoHandler((SmartIosMessage::devAutoInfo*)devinfo, SMT_DEVICE_TYPE_ANDROID);
            break;
        }
        case SmartIosMessage::SMT_DEL_SINGLE_DEVICE_EVENT:
        {
            SmartIosMessage::delSingleDeviceReq* delReq = message->getDelSinDeviceReq();
            onDelSingleDeviceHandler(delReq);
            break;
        }
        case SmartIosMessage::SMT_DEL_ALL_DEVICE_EVENT:
        {
            SmartIosMessage::delAllDeviceReq * req = message->getDelAllDeviceReq();
            onDelAllDeviceHandler(req);
            break;
        }
        case SmartIosMessage::SMT_IOS_LAUNCH_RESULT_EVENT:
        {
            SmartIosMessage::IosLaunchResult* launchResult = message->getLaunchResult();
            onLaunchResultNotify(launchResult);
            break;
        }
        default:
            break;
    }

}
void SmartIosServiceManager::SmartIosManagerHandler::onLaunchResultNotify(const SmartIosMessage::IosLaunchResult* result)    /* __0x40601F_DTFUNCID__ */ {
    SMTLOGD("SmartIosManagerHandler::onLaunchResultNotify");
    SMTLOGD("mLaunchState %d,notify launchType %d",mOwner->mLaunchState,result->launchType);
    mOwner->mLaunchState = result->launchType;
    if(mOwner->mTimer.isActive()) {
        SMTLOGD("-----------------------stop timer");
        mOwner->mTimer.stop();
    }
}
void SmartIosServiceManager::SmartIosManagerHandler::onDevAutoInfoHandler(const SmartIosMessage::devAutoInfo* devinfo, SmtDeviceType deviceType)    /* __0x406020_DTFUNCID__ */ {
     SMTLOGD("SmartIosManagerHandler::onDevAutoInfoHandler");
     SMTLOGD("onDevAutoInfoHandler,devinfo.serinum %s,devinfo.devname %s\n",devinfo->serinum,devinfo->devName);
     SmartIosSettingProxy::getInstance()->setDeviceName(devinfo->serinum, devinfo->devName, deviceType);
     SMTLOGD("mid %d",mid);
     SmartIosMessage::GetDevInfoReq devInfoReq;
     devInfoReq.id = mid;
     devInfoReq.index = 0;
     devInfoReq.reqType = SMT_IOS_DEV_ALL_REQ;
     SMTLOGD("after get devname,need get dev info,nofity UI");
     onGetDevInfoReqHandler(&devInfoReq, deviceType);    
}
void SmartIosServiceManager::SmartIosManagerHandler::onLaunchSourceReqHandler(const SmartIosMessage::LaunchSourceReq* req)    /* __0x406021_DTFUNCID__ */ {
    SMTLOGD("SmartIosManagerHandler::onLaunchSourceReqHandler");
    SMTLOGD("onLaunchSourceReqHandler index %d source %d", req->index, req->source);
    DTLOG_INFO(0x406021, "smartios on launch source,source is %d", req->source);
    SMTLOGD("current launch state is %d",mOwner->mLaunchState);	
    DTLOG_INFO(0x406021, "current launch state is %d", mOwner->mLaunchState);
    if(mOwner != NULL)
    {
        mOwner->getConMngProxy()->launchIosSourceReq(req->source);
#if 0
        if(mOwner->mLaunchState == LAUNCH_IDLE) {
            mOwner->mLaunchState = LAUNCHING;
            mOwner->getConMngProxy()->launchIosSourceReq(req->source);
            mOwner->mTimer.start(LAUNCH_RESULT_CHECK_TIME,true,mOwner,&SmartIosServiceManager::onLaunchResultCheckTime);            			
        }
        else {
            SMTLOGD("launch state is not idle");
        }
#endif
    }
}
void SmartIosServiceManager::SmartIosManagerHandler::onLaunchSourceReqHandlerAndroid(const SmartIosMessage::LaunchSourceReqAndroid* req)    /* __0x406022_DTFUNCID__ */ {
    SMTLOGD("SmartIosManagerHandler::onLaunchSourceReqHandlerAndroid");
    SMTLOGD("onLaunchSourceReqHandlerAndroid index %d source %d", req->index, req->source);
    if(mOwner != NULL)
    {
        mOwner->getConMngProxy()->launchAndroidSourceReq(req->source);
    }
}
void SmartIosServiceManager::SmartIosManagerHandler::onSetPopStatusReqHandler(const SmartIosMessage::SetPopStatusReq* req)    /* __0x406023_DTFUNCID__ */{
    SMTLOGD("SmartIosManagerHandler::onSetPopStatusReqHandler");
    SMTLOGD("onSetPopStatusReqHandler setType %d index %d pop %d", req->setType, req->index, req->pop);
    DTLOG_INFO(0x406023, "set pop status req, setType %d, index %d, pop %d",req->setType, req->index, req->pop);
    int index = SmartIosSettingProxy::getInstance()->setPopStatusReq(req->setType,req->index, req->pop, SMT_DEVICE_TYPE_IOS);
    SMTLOGD("after set pop status,return index is %d",index);
    DTLOG_INFO(0x406023, "after set pop status,return index %d", index);
    android::sp<SmtPopState> state  = new  SmtPopState();
    state->setIndex(index);
    state->setPop(req->pop);
    state->setSetType( req->setType);
    mOwner->getServiceReplier()->smtPopStatusInd(req->id, state);
}
void SmartIosServiceManager::SmartIosManagerHandler::onSetPopStatusReqHandlerAndroid(const SmartIosMessage::SetPopStatusReqAndroid* req)    /* __0x406024_DTFUNCID__ */{
    SMTLOGD("SmartIosManagerHandler::onSetPopStatusReqHandler::onSetPopStatusReqHandlerAndroid");
    SMTLOGD("onSetPopStatusReqHandlerAndroid setType %d index %d pop %d", req->setType, req->index, req->pop);
    DTLOG_INFO(0x406024, "set pop status req,setType %d, index %d, pop %d",req->setType, req->index, req->pop);
    int index = SmartIosSettingProxy::getInstance()->setPopStatusReq(req->setType,req->index, (SmtPopStatus)req->pop, SMT_DEVICE_TYPE_ANDROID);
    SMTLOGD("after set pop status,return index is %d",index);
    DTLOG_INFO(0x406024, "after set pop status,return index %d", index);
    android::sp<SmtPopState> state = new SmtPopState();
    state->setIndex(index);
    state->setPopAndroid(req->pop);
    state->setSetType(req->setType);
    mOwner->getServiceReplier()->smtPopStatusIndAndroid(req->id, state);
}
void SmartIosServiceManager::SmartIosManagerHandler::onGetDevInfoReqHandler(const SmartIosMessage::GetDevInfoReq* req, SmtDeviceType deviceType)    /* __0x406025_DTFUNCID__ */ {
    std::vector<IosDeviceName*> mDeviceList;
    SMTLOGD("get dev info,req->id %d",req->id);
    mid = req->id;
    SMTLOGD("SmartIosServiceManager::onGetDevInfoReqHandler index %d reqType %d", req->index, req->reqType);
    if(SmartIosSettingProxy::getInstance()->getDeviceInfo(req->reqType, (uint8_t)req->index, &mDeviceList, deviceType))
    {
        SMTLOGD("onGetDevInfoReqHandler success");
        if(mDeviceList.size() == 0)
        {
            SMTLOGD("onGetDevInfoReqHandler no pop device");
        }
        else
        {
            uint8_t count = mDeviceList.size();
#if 1
            SMTLOGD("onGetDevInfoReqHandler success count %d", count);
            if(count > SMT_IOS_POP_DEVICE_MAX) {
                SMTLOGD("count is error");
                count = SMT_IOS_POP_DEVICE_MAX;
            }
#endif
            if(req->reqType == SMT_IOS_DEV_SINGLE_REQ)
            {
                android::sp<SmtDeviceInfo> devInfo = new SmtDeviceInfo();
                devInfo->setIndex(mDeviceList[0]->format.priority);
                devInfo->setReqType(SMT_IOS_DEV_SINGLE_REQ);
                devInfo->setTotal( 0XFF);
                devInfo->setCode( 0x00);
                devInfo->setNameLen(0);
                SMTLOGD("onGetDevInfoReqHandler index %d reqType %d total %d namelen %d", devInfo->getIndex(), devInfo->getReqType(), devInfo->getTotal(), devInfo->getNameLen());
                if (SMT_DEVICE_TYPE_IOS == deviceType){
                    mOwner->getServiceReplier()->smtDeviceInfoInd(req->id, devInfo);
                }
                else{
                    mOwner->getServiceReplier()->smtDeviceInfoIndAndroid(req->id, devInfo);
                }
            }
            else
            {

                uint8_t  i = 0;
                for(i = 0; i < count; i ++)
                {
                    android::sp<SmtDeviceInfo> devInfo = new SmtDeviceInfo();
                    //devInfo->setIndex( mDeviceList[i]->format.priority);
                    //devInfo->setIndex(mDeviceList[i]->format.priority);
                    devInfo->setIndex(mDeviceList[i]->format.priority);
                    //devInfo->setPop((SmtPopStatus)mDeviceList[i]->format.popStatus);
                    devInfo->setReqType(SMT_IOS_DEV_ALL_REQ);
                    devInfo->setTotal( count);
                    devInfo->setCode( 0x00);
                    char devName[SMT_IOS_DEVICE_NAME_MAX_LEN + 1];
                    int len = strlen((char*)mDeviceList[i]->format.deviceName);
                    if(len > SMT_IOS_DEVICE_NAME_MAX_LEN) {
                        len = SMT_IOS_DEVICE_NAME_MAX_LEN;
                    }
                    memcpy(devName,mDeviceList[i]->format.deviceName,len);
                    devName[len] = '\0';
                    devInfo->setNameLen(strlen(devName));
                    android::String8 name(devName);
                    devInfo->setName(name);
                    SMTLOGD("onGetDevInfoReqHandler index %d,pop %d, reqType %d total %d namelen %d,name %s",devInfo->getIndex(),devInfo->getPop(), devInfo->getReqType(), devInfo->getTotal(), devInfo->getNameLen(),devInfo->getName().string());
                    if (SMT_DEVICE_TYPE_IOS == deviceType){
                        devInfo->setPop((SmtPopStatus)mDeviceList[i]->format.popStatus);
                        mOwner->getServiceReplier()->smtDeviceInfoInd(req->id, devInfo);
                    }
                    else{
                        devInfo->setPopAndroid((SmtPopStatusAndroid)mDeviceList[i]->format.popStatus);
                        mOwner->getServiceReplier()->smtDeviceInfoIndAndroid(req->id, devInfo);
                    }
                }
            }
            uint8_t  i = 0;
            for(i = 0; i < count; i ++)
            {
                IosDeviceName* dev =mDeviceList[i];
                if(dev != NULL)
                    delete dev;
            }
        }
    }
    //no pop device
    else {
        SMTLOGD("line %d,no pop devices",__LINE__);
        android::sp<SmtDeviceInfo> devinfo = new SmtDeviceInfo();
        devinfo->setTotal(0);
        devinfo->setReqType(SMT_IOS_DEV_ALL_REQ);
        if (SMT_DEVICE_TYPE_IOS == deviceType){
            mOwner->getServiceReplier()->smtDeviceInfoInd(req->id, devinfo);
        }
        else{
            mOwner->getServiceReplier()->smtDeviceInfoIndAndroid(req->id, devinfo);
        }
    }

}

void SmartIosServiceManager::SmartIosManagerHandler::onIapDeviceInsertHandler(const SmartIosMessage::IapDevInsertInd* ind)    /* __0x406026_DTFUNCID__ */{
    //TODO NULL
    uint8_t popStatus;
    //android::String8 serial(ind->serialNum);
    SMTLOGD("SmartIosManagerHandler::onIapDeviceInsertHandler");
    SMTLOGD("serial number is %s   length is %d", ind->serialNum, strlen(ind->serialNum));
    SMTLOGD("isCarplaySupp %d",ind->isCarplaySupp);
    DTLOG_INFO(0x406026, "on iap2 insert,isCarplaySupp %d", ind->isCarplaySupp);
    uint8_t index = SmartIosSettingProxy::getInstance()->iapDeviceInsert(ind->serialNum, &popStatus, SMT_DEVICE_TYPE_IOS);
    SMTLOGD("line %d,index %d,popStatus %d",__LINE__,index,popStatus);
    android::sp<SmtConState> con  = new SmtConState;
    DTLOG_INFO(0x406026, "after insert index = %d", index);
    if(index != SMT_IOS_DEVICE_INDEX_INVALID)
    {
        con->setIndex(index);
        mOwner->mIndex = index;
        con->setPop(static_cast<SmtPopStatus>(popStatus));
        mOwner->mPopStatus = popStatus;
        uint8_t cState = SMT_CONNECTED;
        if(!(ind->isCarplaySupp)) {
            cState |= (1 << 7);
        }
        mOwner->mConnState = cState;
        con->setCState(SMT_CONNECTED);
        con->setIsCarplaySupp(ind->isCarplaySupp);
        mOwner->getServiceStub()->smtDevConnectInd(con);
    }
}
void SmartIosServiceManager::SmartIosManagerHandler::onAndroidDeviceInsertHandler(const SmartIosMessage::AndroidDevInsertInd* ind)    /* __0x406027_DTFUNCID__ */{
    uint8_t popStatus;
    //android::String8 serial(ind->serialNum);
    SMTLOGD("SmartIosManagerHandler::onAndroidDeviceInsertHandler");
    SMTLOGD("serial number is %s   length is %d", ind->serialNum, strlen(ind->serialNum));
    SMTLOGD("isAAPSupp %d",ind->isAAPSupp);
    DTLOG_INFO(0x406027, "on android insert,isAAPSupp %d", ind->isAAPSupp);
    uint8_t index = SmartIosSettingProxy::getInstance()->iapDeviceInsert(ind->serialNum, &popStatus, SMT_DEVICE_TYPE_ANDROID);
    SMTLOGD("line %d,index %d,popStatus %d",__LINE__,index,popStatus);
    DTLOG_INFO(0x406027, "after insert index = %d", index);
    if(index != SMT_IOS_DEVICE_INDEX_INVALID)
    {
        android::sp<SmtConState> con  = new SmtConState ;
        con->setIndexAndroid(index);
        mOwner->mIndexAndroid = index;
        con->setPopAndroid(static_cast<SmtPopStatusAndroid>(popStatus));
        mOwner->mPopStatusAndroid = popStatus;
        uint8_t cState = SMT_CONNECTED;
        if(!(ind->isAAPSupp)) {
            cState |= (1 << 7);
        }
        mOwner->mConnStateAndroid = cState;
        con->setCStateAndroid(SMT_CONNECTED);
        con->setIsAAPSupp(ind->isAAPSupp);
        mOwner->getServiceStub()->smtDevAndroidInsertInd(con);
    }
}

void SmartIosServiceManager::SmartIosManagerHandler::onAndroidExactHandler(void)    /* __0x406028_DTFUNCID__ */ {
    SMTLOGD("SmartIosManagerHandler::onAndroidExactHandler");
    android::sp<SmtConState> con  = new SmtConState;
    con->setIndexAndroid(0xFF);
    con->setPopAndroid(SMT_ANDROID_POP_INVALID);
    con->setCStateAndroid(SMT_DISCONNECT);
    mOwner->getServiceStub()->smtDevAndroidInsertInd(con);
}
void SmartIosServiceManager::SmartIosManagerHandler::onDelSingleDeviceHandler(const SmartIosMessage::delSingleDeviceReq * req)    /* __0x406029_DTFUNCID__ */ {
    SMTLOGD("SmartIosManagerHandler::onDelSingleDeviceHandler,index = %d",req->index);
    SmartIosSettingProxy::getInstance()->delSingleDevice(req->index);
    uint32_t err = 0;
    mOwner->getServiceReplier()->smtDelSingleDeviceInd(req->id,req->index,err);
}
void SmartIosServiceManager::SmartIosManagerHandler::onDelAllDeviceHandler(const SmartIosMessage::delAllDeviceReq* req)    /* __0x40602A_DTFUNCID__ */ {
    SMTLOGD("SmartIosManagerHandler::onDelAllDeviceHandler");
    SmartIosSettingProxy::getInstance()->delAllDevice();
    uint32_t err = 0;
    mOwner->getServiceReplier()->smtDelAllDeviceInd(req->id,err);
}
/**
 * @brief onIapExactHandler ,notify funcmng device disconnect,funcmng notify UI
 */
void SmartIosServiceManager::SmartIosManagerHandler::onIapExactHandler(void)    /* __0x40602B_DTFUNCID__ */ {
    SMTLOGD("SmartIosManagerHandler::onIapExactHandler");
    DTLOG_INFO(0x40602B, "on iap2 exact");
    android::sp<SmtConState> con  = new SmtConState ;
    con->setIndex (0xFF);
    con->setPop(SMT_POP_INVALID);
    con->setCState(SMT_DISCONNECT);
    mOwner->getServiceStub()->smtDevConnectInd(con);
    mOwner->mLaunchState = LAUNCH_IDLE;
    if(mOwner->mTimer.isActive()) {
        SMTLOGD("---------------------------------stop timer");
        mOwner->mTimer.stop();
    }
}
}
