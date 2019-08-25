/*
 * SmartIosMessage.cpp
 *
 *  Created on: 2017年5月5日
 *      Author: zjh
 */

#include "SmartIosMessage.h"
#include "include/SmartIosServiceDefs.h"
#include "servicebase/SystemLog.h"
namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

SmartIosMessage::SmartIosMessage(SMART_EVENT_ID evt) :mEvtId(evt)    /* __0x404001_DTFUNCID__ */{
    // TODO Auto-generated constructor stub

}
SmartIosMessage::SmartIosMessage(const delAllDeviceReq& req): mEvtId(SMT_DEL_ALL_DEVICE_EVENT)    /* __0x404002_DTFUNCID__ */ {
    memset(&content.delAllReq,0x00,sizeof(content.delAllReq)); 
    content.delAllReq.id = req.id;
}
SmartIosMessage::SmartIosMessage(const delSingleDeviceReq& req): mEvtId(SMT_DEL_SINGLE_DEVICE_EVENT)    /* __0x404003_DTFUNCID__ */ {
    memset(&content.delSinDevReq,0x00,sizeof(content.delSinDevReq));
    content.delSinDevReq.id = req.id;
    content.delSinDevReq.index = req.index;
}
SmartIosMessage::SmartIosMessage(const  LaunchSourceReq& req) : mEvtId(SMT_LAUNCH_SOURCE_EVENT)    /* __0x404004_DTFUNCID__ */ {
    memset(&content.launchReq,0x00,sizeof(content.launchReq));
    content.launchReq.id = req.id;
    content.launchReq.index = req.index;
    content.launchReq.source = req.source;
}
SmartIosMessage::SmartIosMessage(const  LaunchSourceReqAndroid& req) : mEvtId(SMT_LAUNCH_SOURCE_EVENT_ANDROID)    /* __0x404005_DTFUNCID__ */ {
    memset(&content.launchReqAndroid,0x00,sizeof(content.launchReqAndroid));
    content.launchReqAndroid.id = req.id;
    content.launchReqAndroid.index = req.index;
    content.launchReqAndroid.source = req.source;
}

SmartIosMessage::SmartIosMessage(const  SetPopStatusReq& req) : mEvtId(SMT_SET_POP_REQ_EVENT)    /* __0x404006_DTFUNCID__ */ {
    memset(&content.setPopReq,0x00,sizeof(content.setPopReq));
    content.setPopReq.index = req.index;
    content.setPopReq.pop = req.pop;
    content.setPopReq.setType = req.setType;
    content.setPopReq.id = req.id;
}

SmartIosMessage::SmartIosMessage(const  SetPopStatusReqAndroid& req) : mEvtId(SMT_SET_POP_REQ_EVENT_ANDROID)    /* __0x404007_DTFUNCID__ */ {
    memset(&content.setPopReqAndroid,0x00,sizeof(content.setPopReq));
    content.setPopReqAndroid.index = req.index;
    content.setPopReqAndroid.pop = req.pop;
    content.setPopReqAndroid.setType = req.setType;
    content.setPopReqAndroid.id = req.id;
}

SmartIosMessage::SmartIosMessage( const GetDevInfoReq& req) : mEvtId(SMT_GET_DEVINFO_REQ_EVENT)    /* __0x404008_DTFUNCID__ */ {
    memset(&content.getDevReq,0x00,sizeof(content.getDevReq));
    content.getDevReq.index = req.index;
    content.getDevReq.reqType = req.reqType;
    content.getDevReq.id = req.id;
}

SmartIosMessage::SmartIosMessage( const GetDevInfoReqAndroid& req) : mEvtId(SMT_GET_DEVINFO_REQ_EVENT_ANDROID)    /* __0x404009_DTFUNCID__ */ {
    memset(&content.getDevReqAndroid,0x00,sizeof(content.getDevReqAndroid));
    content.getDevReqAndroid.index = req.index;
    content.getDevReqAndroid.reqType = req.reqType;
    content.getDevReqAndroid.id = req.id;
}

SmartIosMessage::SmartIosMessage( const DevConStatusInd& ind)  : mEvtId(SMT_DEV_CONSTS_IND_EVENT)    /* __0x40400A_DTFUNCID__ */ {
    memset(&content.conStsInd,0x00,sizeof(content.conStsInd));
    content.conStsInd.index = ind.index;
    content.conStsInd.pop = ind.pop;
    content.conStsInd.state = ind.state;
    content.conStsInd.id = ind.id;
}

SmartIosMessage::SmartIosMessage( const PopStatusInd& ind) : mEvtId(SMT_POPSTATUS_IND_EVENT)    /* __0x40400B_DTFUNCID__ */ {
    memset(&content.popStatusInd,0x00,sizeof(content.popStatusInd));
    content.popStatusInd.index = ind.index;
    content.popStatusInd.pop = ind.pop;
    content.popStatusInd.setType = ind.setType;
    content.popStatusInd.id = ind.id;
}

SmartIosMessage::SmartIosMessage( const DevInfoInd&  ind) : mEvtId(SMT_DEV_INF_IND_EVENT)    /* __0x40400C_DTFUNCID__ */ {
    memset(&content.deviceInfoInd,0x00,sizeof(content.deviceInfoInd));
    content.deviceInfoInd.index =  ind.index;
    content.deviceInfoInd.id =  ind.id;
    content.deviceInfoInd.total = ind.total;
    content.deviceInfoInd.reqType = ind.reqType;
    content.deviceInfoInd.code = ind.code;
    content.deviceInfoInd.nameLen = ind.nameLen;
    memcpy(content.deviceInfoInd.name, ind.name, ind.nameLen);
}
SmartIosMessage::SmartIosMessage(const IapDevInsertInd& iapInsertInd) : mEvtId(SMT_IAP_DEV_INSERT_EVENT)    /* __0x40400D_DTFUNCID__ */
{       
    memset(&content.iapInsertInd,0x00,sizeof(content.iapInsertInd));
    memcpy(content.iapInsertInd.serialNum, iapInsertInd.serialNum, strlen(iapInsertInd.serialNum));
    content.iapInsertInd.isCarplaySupp = iapInsertInd.isCarplaySupp;
    content.iapInsertInd.id = iapInsertInd.id;
}
SmartIosMessage::SmartIosMessage(const IapExactInd& iapExactInd)  : mEvtId(SMT_IAP_DEV_EXACT_EVENT)    /* __0x40400E_DTFUNCID__ */
{
    memset(&content.iapExactInd,0x00,sizeof(content.iapExactInd)); 
    content.iapExactInd.id = iapExactInd.id;
}
SmartIosMessage::SmartIosMessage(const AndroidDevInsertInd& androidInsertInd) : mEvtId(SMT_ANDROID_DEV_INSERT_EVENT)    /* __0x40400F_DTFUNCID__ */
{
    memset(&content.androidInsertInd,0x00,sizeof(content.androidInsertInd));
    memcpy(content.androidInsertInd.serialNum, androidInsertInd.serialNum, strlen(androidInsertInd.serialNum));
    content.androidInsertInd.id = androidInsertInd.id;
}
SmartIosMessage::SmartIosMessage(const AndroidExactInd& androidExactInd)  : mEvtId(SMT_ANDROID_DEV_EXACT_EVENT)    /* __0x404010_DTFUNCID__ */
{
    memset(&content.androidExactInd,0x00,sizeof(content.androidExactInd)); 
    content.androidExactInd.id = androidExactInd.id;
}
SmartIosMessage::SmartIosMessage(const devAutoInfo& info) : mEvtId(SMT_IAP_DEV_AUTO_INFO_EVENT)    /* __0x404011_DTFUNCID__ */{
    memset(&content.devinfo,0x00,sizeof(content.devinfo));
    content.devinfo.id = info.id;
    memcpy(content.devinfo.serinum,info.serinum,SMT_DEV_SERIAL_LEN_MAX);
    memcpy(content.devinfo.devName,info.devName,SMT_DEV_NAME_LEN_MAX);
}
SmartIosMessage::SmartIosMessage(const devAutoInfoAndroid& info) : mEvtId(SMT_IAP_DEV_AUTO_INFO_EVENT_ANDROID)    /* __0x404012_DTFUNCID__ */{
    memset(&content.devinfoAndroid,0x00,sizeof(content.devinfoAndroid));
    content.devinfoAndroid.id = info.id;
    memcpy(content.devinfoAndroid.serinum,info.serinum,SMT_DEV_SERIAL_LEN_MAX);
    memcpy(content.devinfoAndroid.devName,info.devName,SMT_DEV_NAME_LEN_MAX);
}
SmartIosMessage::SmartIosMessage(const IosLaunchResult& result) :mEvtId(SMT_IOS_LAUNCH_RESULT_EVENT)    /* __0x404013_DTFUNCID__ */{
    memset(&content.launchResult, 0x00,sizeof(content.launchResult));
    content.launchResult.launchType = result.launchType;

}
SmartIosMessage::LaunchSourceReq* SmartIosMessage::getLaunchSourceReq()    /* __0x404014_DTFUNCID__ */ {
    return &(content.launchReq);
}
SmartIosMessage::LaunchSourceReqAndroid* SmartIosMessage::getLaunchSourceReqAndroid()    /* __0x404015_DTFUNCID__ */ {
    return &(content.launchReqAndroid);
}
SmartIosMessage::SetPopStatusReq* SmartIosMessage::getSetPopStatusReq()    /* __0x404016_DTFUNCID__ */ {
    return &(content.setPopReq);
}
SmartIosMessage::SetPopStatusReqAndroid* SmartIosMessage::getSetPopStatusReqAndroid()    /* __0x404017_DTFUNCID__ */ {
    return &(content.setPopReqAndroid);
}
SmartIosMessage::GetDevInfoReq* SmartIosMessage::getDevInfoReq()    /* __0x404018_DTFUNCID__ */ {
    return &(content.getDevReq);
}
SmartIosMessage::GetDevInfoReqAndroid* SmartIosMessage::getDevInfoReqAndroid()    /* __0x404019_DTFUNCID__ */ {
    return &(content.getDevReqAndroid);
}
SmartIosMessage::DevConStatusInd* SmartIosMessage::getDevConStatusInd()    /* __0x40401A_DTFUNCID__ */ {
    return &(content.conStsInd);
}
SmartIosMessage::DevInfoInd* SmartIosMessage::getDevInfoInd()    /* __0x40401B_DTFUNCID__ */ {
    return &(content.deviceInfoInd);
}
SmartIosMessage::PopStatusInd* SmartIosMessage::getPopStatusInd()    /* __0x40401C_DTFUNCID__ */ {
    return &(content.popStatusInd);
}
SmartIosMessage::IapDevInsertInd* SmartIosMessage::getIapDevInsertInd()    /* __0x40401D_DTFUNCID__ */{
    return &(content.iapInsertInd);
}
SmartIosMessage::AndroidDevInsertInd* SmartIosMessage::getAndroidDevInsertInd()    /* __0x40401E_DTFUNCID__ */{
    return &(content.androidInsertInd);
}
SmartIosMessage::devAutoInfo* SmartIosMessage::getdevAutoInfo()    /* __0x40401F_DTFUNCID__ */ {
    return &(content.devinfo);
}
SmartIosMessage::devAutoInfoAndroid* SmartIosMessage::getdevAutoInfoAndroid()    /* __0x404020_DTFUNCID__ */ {
    return &(content.devinfoAndroid);
}
SmartIosMessage::delSingleDeviceReq* SmartIosMessage::getDelSinDeviceReq()    /* __0x404021_DTFUNCID__ */ {
    return &(content.delSinDevReq);
}
SmartIosMessage::delAllDeviceReq* SmartIosMessage::getDelAllDeviceReq()    /* __0x404022_DTFUNCID__ */ {
    return &(content.delAllReq);
}
SmartIosMessage::IosLaunchResult* SmartIosMessage::getLaunchResult()    /* __0x404023_DTFUNCID__ */{
    return &(content.launchResult);
}
SmartIosMessage::SMART_EVENT_ID SmartIosMessage::getEvtId()    /* __0x404024_DTFUNCID__ */ {
    return mEvtId;
}
SmartIosMessage::~SmartIosMessage()    /* __0x404025_DTFUNCID__ */ {
    // TODO Auto-generated destructor stub
    mEvtId = SMT_LAUNCH_NULL_EVENT;
}

} /* namespace goni */
