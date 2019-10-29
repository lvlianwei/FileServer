enum SMT_SVC_ERROR_CODE
{
    SMT_SVC_SUCCESS,
    SMT_SVC_FAILED,
    SMT_SVC_INVALID_PARAM,
    SMT_SVC_ILLAGE_STATUS,
    SMT_SVC_OPERATION_ERROR,
    SMT_SVC_TIMEOUT_ERROR
};
enum SmtConnectState
{
    SMT_DISCONNECT,
    SMT_CONNECTED
};
enum SMT_DEV_IAP2_INSERT_STATE {
    SMT_DEV_IAP2_EXTRACT,
    SMT_DEV_IPA2_INSERT
};
enum SMT_DEV_ANDROID_INSERT_STATE {
    SMT_DEV_ANDROID_EXTRACT
    SMT_DEV_ANDROID_INSERT,
};
enum SmtPopStatus
{
    SMT_POP_INVALID,
    SMT_AUTOCARPLAY,
    SMT_AUTOWEBLINK
};

enum SmtPopStatusAndroid 
{
    SMT_ANDROID_POP_INVALID,
    SMT_ANDROID_AUTOAAP,
    SMT_ANDROID_AUTOWEBLINK
};

enum SmtSetType
{
    SMT_IOS_POPUP_SET,
    SMT_IOS_MANU_SET
};

enum SmtDevReqType
{
    SMT_IOS_DEV_ALL_REQ,
    SMT_IOS_DEV_SINGLE_REQ
};

enum SmtIosSource
{
    SMT_IOS_SOURCE_CARPLAY,
    SMT_IOS_SOURCE_WEBLINK,
    SMT_IOS_SOURCE_IPOD
};

enum SmtAndroidSource
{
    SMT_ANDROID_SOURCE_AAP,
    SMT_ANDROID_SOURCE_WEBLINK
};

parcelable SmtConState
{
    SmtConnectState cState;
    uint index;
    SmtPopStatus pop;
    bool isCarplaySupp;
};

parcelable SmtPopState
{
    SmtSetType setType;
    uint index;
    SmtPopStatus pop;
};

parcelable SmtDeviceInfo
{
    SmtDevReqType reqType;
    uint total;
    uint index;
    uint code;
    SmtPopStatus  pop; 
    uint nameLen;
    string* name;
};

interface ISmartIosService
{

    //void smtStateSync(out WFDDeviceState deviceState) ;
    //void smtGetRemoteInfo(out WFDRemoteDeviceInfo remoteInfo);
    //void smtGetLocalDevice(out uint16 nameLen, out uint8* name);

//General
    in smt_launchSource(uint8 index, SmtIosSource source);
    in smt_launchSource_Android(uint8 index, SmtAndroidSource source);
    in smt_setPopStatus(SmtSetType setType, uint8 index, SmtPopStatus pop);
    in smt_getDeviceInfo(SmtDevReqType reqType, uint8 index) ;
    in smt_delSingleDevice(uint8 index);
    in smt_delAllDevices();
    void smt_getDevConnectInfo(out uint8 connState,out uint8 index,out uint8 popStatus);

// reply

    out smtPopStatusInd(SmtPopState pop);

    out smtDeviceInfoInd(SmtDeviceInfo dev);
    out smtDelSingleDeviceInd(uint8 index,uint err);
    out smtDelAllDeviceInd(uint err);

    out smtDevInfoCmpInd(uint err);

// multicast

    //multicast smtDevConppStatus(uint err);
    multicast smtDevConnectInd(SmtConState conState);
    multicast smtDevIpa2InsertInd(uint8 state);
    multicast smtDevAndroidInsertInd(uint8 state);

}

