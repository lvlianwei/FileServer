/*
 * SmartIosServiceStub.cpp
 *
 *  Created on: 2017年5月5日
 *      Author: zjh
 */

#include "SmartIosServiceStub.h"
#include "SmartIosServiceReplier.h"
#include "SmartIosServiceManager.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosService.h"
#include "servicebase/SystemLog.h"

namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

SmartIosServiceStub::SmartIosServiceStub(SmartIosService* owner)    /* __0x407001_DTFUNCID__ */
    :SmartIosServiceStubBase(owner) {
    // TODO Auto-generated constructor stub
    mReplier = new SmartIosServiceReplier(owner);
    if (NULL == mReplier){
        DTLOG_PTRASSERT(mReplier);
    }
    else{
        mManager = new SmartIosServiceManager(this, mReplier);
    }

    SMTLOGD("SmartIosServiceStub SmartIosServiceStub");

}

SmartIosServiceStub::~SmartIosServiceStub()    /* __0x407002_DTFUNCID__ */ {
    // TODO Auto-generated destructor stub
    if (NULL != mManager){
        delete mManager;
        mManager = NULL;
    }
    
    if (NULL != mReplier){
        delete mReplier;
        mReplier = NULL;
    }
}
android::status_t SmartIosServiceStub::smt_launchSource(SenderId id, const uint8_t& index, const SmtIosSource& source)    /* __0x407003_DTFUNCID__ */
{
    return mManager->smt_launchSource(id, index, source);
}
android::status_t SmartIosServiceStub::smt_launchSource_Android(SenderId id, const uint8_t& index, const SmtAndroidSource& source)    /* __0x407004_DTFUNCID__ */
{
    return mManager->smt_launchSource_Android(id, index, source);
}
android::status_t SmartIosServiceStub::smt_setPopStatus(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatus& pop)    /* __0x407005_DTFUNCID__ */
{
    return mManager->smt_setPopStatus(id, setType, index, pop);
}
android::status_t SmartIosServiceStub::smt_setPopStatusAndroid(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatusAndroid& pop)    /* __0x407006_DTFUNCID__ */
{
    return mManager->smt_setPopStatusAndroid(id, setType, index, pop);
}
android::status_t SmartIosServiceStub::smt_getDeviceInfo(SenderId id, const SmtDevReqType& reqType, const uint8_t& index)    /* __0x407007_DTFUNCID__ */
{
    return mManager->smt_getDeviceInfo(id, reqType, index);
}
android::status_t SmartIosServiceStub::smt_getDeviceInfoAndroid(SenderId id, const SmtDevReqType& reqType, const uint8_t& index)    /* __0x407008_DTFUNCID__ */
{
    return mManager->smt_getDeviceInfoAndroid(id, reqType, index);
}
android::status_t SmartIosServiceStub::onMultiListen(uint8_t opcode, void* msg)    /* __0x407009_DTFUNCID__ */
{
    UNUSED(opcode);
    UNUSED(msg);
    return 0;
}
void SmartIosServiceStub::notifyLaunchResult(smtLaunchState state)    /* __0x40700A_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceStub::notifyLaunchResult");
    if(mManager != NULL) {
        mManager->notifyLaunchResult(state);
    }
}
android::status_t SmartIosServiceStub::smt_delSingleDevice(SenderId id, const uint8_t& index)    /* __0x40700B_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceStub::smt_delSingleDevice\n");
    if(mManager != NULL) {
        return mManager->smt_delSingleDevice(id,index);
    }
    return 0;
}
android::status_t SmartIosServiceStub::smt_delAllDevices(SenderId id)    /* __0x40700C_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceStub::smt_delAllDevices");
    if(mManager != NULL) {
        return mManager->smt_delAllDevice(id);
    }
    return 0;
}
android::status_t SmartIosServiceStub::smt_getDevConnectInfo(uint8_t& connState, uint8_t& index, uint8_t& popStatus)    /* __0x40700D_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceStub::smt_getDevConnectInfo");
    if(mManager != NULL) {
      return mManager->getDevConnectInfo(connState,index,popStatus);
    }
    return 0;
}
android::status_t SmartIosServiceStub::smt_getDevConnectInfoAndroid(uint8_t& connState, uint8_t& index, uint8_t& popStatus)    /* __0x40700E_DTFUNCID__ */ {
    SMTLOGD("SmartIosServiceStub::smt_getDevConnectInfoAndroid");
    if(mManager != NULL) {
      return mManager->getDevConnectInfoAndroid(connState,index,popStatus);
    }
    return 0;
}
void SmartIosServiceStub::onIap2Insert(bool isCarplaySupp,const android::String8& serialNumber)    /* __0x40700F_DTFUNCID__ */
{
    if(mManager != NULL)
    {
        mManager->onIapDeviceInsert(isCarplaySupp,serialNumber);
    }
}
void SmartIosServiceStub::onIap2Exact(void)    /* __0x407010_DTFUNCID__ */
{
    if(mManager != NULL)
    {
        mManager->onIapExact();
    }
}
void SmartIosServiceStub::onAndroidInsert(const android::String8& serialNumber)    /* __0x407011_DTFUNCID__ */
{
    if(mManager != NULL)
    {
        mManager->onAndroidDeviceInsert(serialNumber);
    }
}
void SmartIosServiceStub::onAndroidExact(void)    /* __0x407012_DTFUNCID__ */
{
    if(mManager != NULL)
    {
        mManager->onAndroidExact();
    }
}
void SmartIosServiceStub::initialize()    /* __0x407013_DTFUNCID__ */{
    DTLOG_INFO(0x407013, "SmartIosServiceStub::initialize");
    SMTLOGD("SmartIosServiceStub initialize");
    if(mManager != NULL)
    mManager->initialize();
}
void SmartIosServiceStub::deInit()    /* __0x407014_DTFUNCID__ */ {
    DTLOG_INFO(0x407014, "SmartIosServiceStub::deInit");
    SMTLOGD("SmartIosServiceStub deint");
    if(mManager != NULL) {
        mManager->deInit();
    }
}
void SmartIosServiceStub::onIap2AuthInfo(const android::String8& serialNum, const android::String8& devName)    /* __0x407015_DTFUNCID__ */ {
    SMTLOGD("###################%s::%s,line %d",__FILE__,__func__,__LINE__);
    SMTLOGD("serinum %s,devName %s\n",serialNum.string(),devName.string());
    if(mManager != NULL) {
        mManager->onIap2AuthInfo(serialNum,devName); 
    }
}
void SmartIosServiceStub::onAndroidAuthInfo(const android::String8& serialNum, const android::String8& devName)    /* __0x407016_DTFUNCID__ */ {
    SMTLOGD("###################%s::%s,line %d",__FILE__,__func__,__LINE__);
    SMTLOGD("serinum %s,devName %s\n",serialNum.string(),devName.string());
    if(mManager != NULL) {
        mManager->onAndroidAuthInfo(serialNum,devName);
    }
}
} /* namespace goni */
