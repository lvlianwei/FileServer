/*
 * SmartIosConManagerProxy.cpp
 *
 *  Created on: 2017年4月13日
 *      Author: zjh
 */

#include "include/SmartIosServiceServiceDefines.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosConnManagerProxy.h"
#include "SmartIosServiceStub.h"
#include "SmartIosServiceManager.h"
#include "servicebase/SystemLog.h"
namespace goni
{
DeclearModuleID(DTMODULEID_SMARTIOS);

SmartIosConMngReply::SmartIosConMngReply(SmartIosServiceManager* serviceManage)    /* __0x402001_DTFUNCID__ */
:serviceManage(serviceManage)
{
    // TODO Auto-generated constructor stub

}

SmartIosConMngReply::~SmartIosConMngReply()    /* __0x402002_DTFUNCID__ */ {
    // TODO Auto-generated destructor stub
}

void SmartIosConMngReply::onConnected()    /* __0x402003_DTFUNCID__ */
{
        DTLOG_INFO(0x402003, "SmartIosConMngReply::onConnected");
        SMTLOGD("SmartIosConMngReply::onConnected");
        android::sp<android::IServiceManager> sm = android::defaultServiceManager();
        bool diedBefore = sm->checkServiceDiedBefore("ConnectManager");//if connect manager died before,do nothing
        if(diedBefore) {
            SMTLOGD("connect manager died before");
            DTLOG_INFO(0x402003, "connect manager died before");
            serviceManage->setLaunchState(LAUNCH_IDLE);
        }
        else {
            SMTLOGD("get dev info from connectMgr");
            android::String8 serinum;
            bool isConn = false;
            bool isCarplaySupp = true;
            serviceManage->getConMngProxy()->getIosDevInfo(isConn,isCarplaySupp,serinum);
            SMTLOGD("isConn %d,isCarplaySupp %d,serinum %s\n",isConn,isCarplaySupp,serinum.string());
            if(isConn) {
                DTLOG_INFO(0x402003, "ios dev connected");
                SMTLOGD("ios dev connected");
                SmartIosServiceManager * smtMgr = SmartIosServiceManager::getInstance();
                SMTLOGD("smtMgr is %p\n",smtMgr);
                smtMgr->onIapDeviceInsert(isCarplaySupp,serinum);
            }
            else {
                SMTLOGD("no ios dev connect");
                //Add for Android device
                android::String8 androidSerinum;
                bool isAndroidConn = false;
                serviceManage->getConMngProxy()->getAndroidDevInfo(isAndroidConn, androidSerinum);
                SMTLOGD("isAndroidConn %d, androidSerinum %s\n",isAndroidConn, androidSerinum.string());
                if (isAndroidConn){
                    DTLOG_INFO(0x402003, "android device connected");
                    SMTLOGD("android device connected");
                    SmartIosServiceManager* smtMgr = SmartIosServiceManager::getInstance();
                    SMTLOGD("smtMgr is %p\n",smtMgr);
                    smtMgr->onAndroidDeviceInsert(androidSerinum);
                }
                else{
                    SMTLOGD("no Android device connect");
                }
            }
        }
}

void SmartIosConMngReply::onDisconnected()    /* __0x402004_DTFUNCID__ */
{
    DTLOG_INFO(0x402003, "SmartIosConMngReply::onConnected");
    SMTLOGD("ConnectManagerDisconnect");
}
SmartIosConManagerProxy::SmartIosConManagerProxy(SmartIosServiceManager* serviceManage)    /* __0x402005_DTFUNCID__ */
    :ConnectManagerProxyBase(new SmartIosConMngReply(serviceManage)){

}
SmartIosConManagerProxy::~SmartIosConManagerProxy()    /* __0x402006_DTFUNCID__ */ {

}
void SmartIosConManagerProxy::launchIosSourceReq(SmtIosSource source )    /* __0x402007_DTFUNCID__ */{
    IOS_SOURCE_TYPE iosSource = IOS_SOURCE_TYPE_UNKNOWN;
    SMTLOGD("launchIosSourceReq req source %d", source);
    switch(source)
    {
        case SMT_IOS_SOURCE_CARPLAY:
            iosSource = IOS_SOURCE_TYPE_CARPLAY;
            break;
        case SMT_IOS_SOURCE_IPOD:
            iosSource = IOS_SOURCE_TYPE_IPOD;
            break;
        case SMT_IOS_SOURCE_WEBLINK:
            iosSource = IOS_SOURCE_TYPE_WEBLINK;
            break;
        default:
            break;
    }
    SMTLOGD("launchIosSourceReq real source %d", iosSource);
    DTLOG_INFO(0x402007, "launchIosSourceReq real source %d", iosSource);
    launchIosSource(iosSource);
}
void SmartIosConManagerProxy::launchAndroidSourceReq(SmtAndroidSource source )    /* __0x402008_DTFUNCID__ */{
    ANDROID_SOURCE_TYPE androidSource = ANDROID_SOURCE_TYPE_UNKNOWN;
    SMTLOGD("launchAndroidSourceReq req source %d", source);
    switch(source)
    {
        case SMT_ANDROID_SOURCE_AAP:
            androidSource = ANDROID_SOURCE_TYPE_AAP;
            break;
        case SMT_ANDROID_SOURCE_WEBLINK:
            androidSource = ANDROID_SOURCE_TYPE_WEBLINK;
            break;
        default:
            break;
    }
    SMTLOGD("launchAndroidSourceReq real source %d", androidSource);
    DTLOG_INFO(0x402008, "launchAndroidSourceReq real source %d", androidSource);
    launchAndroidSource(androidSource);
}
SmartConnectManagerListener::SmartConnectManagerListener(SmartIosServiceStub* stub)    /* __0x402009_DTFUNCID__ */
:mStub(stub)
{
    SMTLOGD("SmartConnectManagerListener");
}
/**
 * @brief notify_iap2Insert ,receive iap2 insert multicast
 *
 * @param serialNum,the device serinum
 *
 * @return 
 */
android::status_t SmartConnectManagerListener::notify_iap2Insert(const bool& isCarplaySupp,const android::String8& serialNum)    /* __0x40200A_DTFUNCID__ */
{
    DTLOG_INFO(0x40200A, "notify_iap2Insert real isCarplaySupp = %d serialNum = %s\n", isCarplaySupp, serialNum.string());
    SMTLOGD("notify_iap2Insert,isCarplaySupp %d",isCarplaySupp);
    if(mStub != NULL)
    {
        /**
            * alone notify iap2 insert ind
            */
        uint8_t state = (uint8_t)SMT_DEV_IPA2_INSERT;
        mStub->smtDevIpa2InsertInd(state);
        mStub->onIap2Insert(isCarplaySupp,serialNum);
    }
    return 0;
}
/**
 * @brief notify_androidInsert ,receive android insert multicast
 *
 * @param serialNum,the device serinum
 *
 * @return 
 */
android::status_t SmartConnectManagerListener::notify_androidInsert(const android::String8& serialNum)    /* __0x40200B_DTFUNCID__ */
{
    DTLOG_INFO(0x40200B, "notify_androidInsert real serialNum = %s\n", serialNum.string());
    if(mStub != NULL)
    {
        mStub->onAndroidInsert(serialNum);
    }
    return 0;
}
/**
 * @brief notify_iap2Extract ,receive iap2 extract multicast
 *
 * @return 
 */
android::status_t SmartConnectManagerListener::notify_iap2Extract()    /* __0x40200C_DTFUNCID__ */
{
    DTLOG_INFO(0x40200C, "notify_iap2Extract");
    SMTLOGD("%s::%s,line %d,notify_iap2Extract",__FILE__,__func__,__LINE__);
    if(mStub != NULL)
    {
            mStub->onIap2Exact();
    }
    return 0;
}
/**
 * @brief notify_androidExtract ,receive android extract multicast
 *
 * @return 
 */
android::status_t SmartConnectManagerListener::notify_androidExtract()    /* __0x40200D_DTFUNCID__ */
{
    DTLOG_INFO(0x40200D, "notify_androidExtract");
    SMTLOGD("%s::%s,line %d,notify_androidExtract",__FILE__,__func__,__LINE__);
    if(mStub != NULL)
    {
        mStub->onAndroidExact();
    }
    return 0;
}
/**
 * @brief notify_iap2AuthInfo ,receive iap2 auth info multicast
 *
 * @param serialNum,device serinum
 * @param devName,really name
 *
 * @return 
 */
android::status_t SmartConnectManagerListener::notify_iap2AuthInfo(const android::String8& serialNum, const android::String8& devName)    /* __0x40200E_DTFUNCID__ */ {
    DTLOG_INFO(0x40200E, "notify_iap2AuthInfo serialNum = %s devName = %s\n", serialNum.string(), devName.string());
    SMTLOGD("%s::%s,line %d,serialnum %s,devname %s\n",__FILE__,__func__,__LINE__,serialNum.string(),devName.string());
    if(mStub != NULL) {
        mStub->onIap2AuthInfo(serialNum,devName);
    }
    return 0;      
}
android::status_t SmartConnectManagerListener::notify_androidAuthInfo(const android::String8& serialNum, const android::String8& devName)    /* __0x40200F_DTFUNCID__ */ {
    SMTLOGD("%s::%s,line %d,serialnum %s,devname %s\n",__FILE__,__func__,__LINE__,serialNum.string(),devName.string());
    if(mStub != NULL) {
        mStub->onAndroidAuthInfo(serialNum,devName);
    }
    return 0;      
}
android::status_t SmartConnectManagerListener::notify_iapAuthResult(const IPOD_DEVICE_TYPE& type, const bool& isLastOn)    /* __0x402010_DTFUNCID__ */ {
    UNUSED(isLastOn);
    SMTLOGD("SmartConnectManagerListener::notify_iapAuthResult,device type is %d",type);
    DTLOG_INFO(0x402010, "notify iap auth result,type is %d", type);
    smtLaunchState state = LAUNCH_IDLE;
    if(mStub != NULL) {
        mStub->notifyLaunchResult(state);
    }
    return 0;
}
}
