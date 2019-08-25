/*
 * SmartIosMessage.h
 *
 *  Created on: 2017年5月5日
 *      Author: zjh
 */

#ifndef  __SMARTPHONESERVICE_SRC_SMARTIOSMESSAGE_H_
#define __SMARTPHONESERVICE_SRC_SMARTIOSMESSAGE_H_

#include "servicebase/Message.h"
#include "servicebase/ServiceBaseDefines.h"
#include "SmartIosServiceServiceDefines.h"
#include "include/SmartIosTypeDefines.h"
namespace goni {

#define SMT_DEV_NAME_LEN_MAX 64
#define SMT_DEV_SERIAL_LEN_MAX 43



class SmartIosMessage :public Message {

public:
    typedef enum {
            SMT_LAUNCH_NULL_EVENT,
            SMT_LAUNCH_SOURCE_EVENT,
            SMT_LAUNCH_SOURCE_EVENT_ANDROID,
            SMT_SET_POP_REQ_EVENT,
            SMT_SET_POP_REQ_EVENT_ANDROID,
            SMT_GET_DEVINFO_REQ_EVENT,
            SMT_GET_DEVINFO_REQ_EVENT_ANDROID,
            SMT_DEL_SINGLE_DEVICE_EVENT,
            SMT_DEL_ALL_DEVICE_EVENT,
            SMT_DEV_CONSTS_IND_EVENT,
            SMT_POPSTATUS_IND_EVENT,
            SMT_DEV_INF_IND_EVENT,
            SMT_IAP_DEV_INSERT_EVENT,
            SMT_IAP_DEV_EXACT_EVENT,
            SMT_ANDROID_DEV_INSERT_EVENT,
            SMT_ANDROID_DEV_EXACT_EVENT,
            SMT_IAP_DEV_AUTO_INFO_EVENT,
            SMT_IAP_DEV_AUTO_INFO_EVENT_ANDROID,
            SMT_IOS_LAUNCH_RESULT_EVENT
    }SMART_EVENT_ID;
    typedef struct {
        SenderId id;
        char serinum[SMT_DEV_SERIAL_LEN_MAX];
        char devName[SMT_DEV_NAME_LEN_MAX + 1];
    }devAutoInfo;
    typedef struct {
        SenderId id;
        char serinum[SMT_DEV_SERIAL_LEN_MAX];
        char devName[SMT_DEV_NAME_LEN_MAX + 1];
    }devAutoInfoAndroid;
    typedef struct {
        SenderId id;
        uint8_t index;
    }delSingleDeviceReq;
    typedef struct {
        SenderId id;
    }delAllDeviceReq;
    typedef struct {
            SenderId id;
            int32_t index;
            SmtIosSource source;
    }LaunchSourceReq;
    typedef struct {
            SenderId id;
            int32_t index;
            SmtAndroidSource source;
    }LaunchSourceReqAndroid;

    typedef struct {
            SenderId id;
            SmtSetType setType;
            int32_t  index;
            SmtPopStatus pop;
    }SetPopStatusReq;
    typedef struct {
            SenderId id;
            SmtSetType setType;
            int32_t  index;
            SmtPopStatusAndroid pop;
    }SetPopStatusReqAndroid;

    typedef struct {
            SenderId id;
            SmtDevReqType reqType;
            int32_t index;
    }GetDevInfoReq;
    
    typedef struct {
            SenderId id;
            SmtDevReqType reqType;
            int32_t index;
    }GetDevInfoReqAndroid;

    typedef struct {
            SenderId id;
            SmtConnectState state;
            int32_t index;
            SmtPopStatus  pop;
    }DevConStatusInd;

    typedef struct {
            SenderId id;
            SmtSetType setType;
            int32_t  index;
            SmtPopStatus pop;
    }PopStatusInd;

    typedef struct {
            SenderId id;
            SmtDevReqType reqType;
            int32_t total;
            int32_t index;
            int32_t code;
            int32_t nameLen;
            uint8_t name[SMT_DEV_NAME_LEN_MAX];
    }DevInfoInd;

    typedef struct {
        SenderId id;
        bool isCarplaySupp;
        char serialNum[SMT_DEV_SERIAL_LEN_MAX];
    }IapDevInsertInd;
    
    typedef struct {
        SenderId id;
        bool isAAPSupp;
        char serialNum[SMT_DEV_SERIAL_LEN_MAX];
    }AndroidDevInsertInd;

    typedef struct{
            SenderId id;
            uint32_t dummy;
    }IapExactInd;
    typedef struct{
        smtLaunchState launchType;
    }IosLaunchResult;
        
    typedef struct{
            SenderId id;
            uint32_t dummy;
    }AndroidExactInd;

    typedef union
    {
            LaunchSourceReq launchReq;
            LaunchSourceReqAndroid launchReqAndroid;
            SetPopStatusReq setPopReq;
            SetPopStatusReqAndroid setPopReqAndroid;
            GetDevInfoReq getDevReq;
            GetDevInfoReqAndroid getDevReqAndroid;
            DevConStatusInd conStsInd;
            PopStatusInd popStatusInd;
            DevInfoInd  deviceInfoInd;
            IapDevInsertInd iapInsertInd;
            AndroidDevInsertInd androidInsertInd;
            IapExactInd iapExactInd;
            AndroidExactInd androidExactInd;
            devAutoInfo devinfo;
            devAutoInfoAndroid devinfoAndroid;
            delSingleDeviceReq delSinDevReq;
            delAllDeviceReq delAllReq;
    IosLaunchResult launchResult;
    }uMsgContent;

public:
    SmartIosMessage(SMART_EVENT_ID evt);
    SmartIosMessage(const LaunchSourceReq& req);
    SmartIosMessage(const LaunchSourceReqAndroid& req);
    SmartIosMessage(const SetPopStatusReq& req);
    SmartIosMessage(const SetPopStatusReqAndroid& req);
    SmartIosMessage(const GetDevInfoReq& req);
    SmartIosMessage(const GetDevInfoReqAndroid& req);
    SmartIosMessage(const DevConStatusInd& ind);
    SmartIosMessage(const PopStatusInd& ind);
    SmartIosMessage(const DevInfoInd& ind);
    SmartIosMessage(const IapDevInsertInd& iapInsertInd);
    SmartIosMessage(const IapExactInd& iapExactInd);
    SmartIosMessage(const AndroidDevInsertInd& androidInsertInd);
    SmartIosMessage(const AndroidExactInd& androidExactInd);
    SmartIosMessage(const devAutoInfo& info);
    SmartIosMessage(const devAutoInfoAndroid& info);
    SmartIosMessage(const delSingleDeviceReq& req);
    SmartIosMessage(const delAllDeviceReq& req);
    SmartIosMessage(const IosLaunchResult& result);
    virtual ~SmartIosMessage();

public:
    LaunchSourceReq* getLaunchSourceReq();
    LaunchSourceReqAndroid* getLaunchSourceReqAndroid();
    SetPopStatusReq* getSetPopStatusReq();
    SetPopStatusReqAndroid* getSetPopStatusReqAndroid();
    GetDevInfoReq* getDevInfoReq();
    GetDevInfoReqAndroid* getDevInfoReqAndroid();
    DevConStatusInd* getDevConStatusInd();
    DevInfoInd* getDevInfoInd();
    PopStatusInd* getPopStatusInd();
    IapDevInsertInd* getIapDevInsertInd();
    AndroidDevInsertInd* getAndroidDevInsertInd();
    devAutoInfo* getdevAutoInfo();
    devAutoInfoAndroid* getdevAutoInfoAndroid();
    delSingleDeviceReq * getDelSinDeviceReq();
    delAllDeviceReq* getDelAllDeviceReq();
    IosLaunchResult* getLaunchResult();
    SMART_EVENT_ID getEvtId();

public:
    //SmartIosMessage(const SmartIosMessage&);
    //SmartIosMessage& operator=(const SmartIosMessage&);
private:
    SMART_EVENT_ID mEvtId;
    uMsgContent content;
};

} /* namespace goni */

#endif /* FRAMEWORKS_SERVICE_SMARTPHONESERVICE_SRC_SMARTIOSMESSAGE_H_ */
