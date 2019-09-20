#include "WFDServiceManager.h"
#include "WFDServiceReplier.h"
#include "WFDServiceDefs.h"
#include "servicebase/Message.h"
#include "WFDServiceWifiListen.h"
#include "WFDServiceDTLog.h"
#include "WFDServiceStackListen.h"
#include "WFDLib.h"
#include "wifiProxyBase.h"
#include "WFDServiceAVCtr.h"
#include "wfdServiceStub.h"
#include "WFDServiceSetting.h"
#include "WFDServiceInputListen.h"
#include "BtSub.h"
#include "BtProxyBase.h"
#include "servicebase/SystemLog.h"


namespace goni
{

DeclearModuleID(DTMODULEID_WFDSERVICE);
WFDServiceManager::WFDServiceManager(WFDServiceStub* stub, WFDServiceReplier* replier)   /* __0x004000_DTFUNCID__ */
:mThread(new WFDManagerHandler(this))
, mWifiListener(NULL)
, mWifiProxy(NULL)
, mReplier(replier)
, mStub(stub)
, mState(WFD_POWER_OFF)
, mId(-1)
, listenFlag(false)

{
    MCLOGD("start the WFDServiceManager thread");
    wfdClearLocalInfoData();
    mThread.start();

    //WFDDTLogInst->start();
    DTLOG_INFO(0x004000, "WFDServiceManager::WFDServiceManager");

    mSetting = new WFDSetting(this);
    if (NULL == mSetting) {
        DTLOG_PTRASSERT(mSetting);
        return;
    }

    mStackListener = new WFDStackListener(this);
    if (NULL == mStackListener.get()) {
        DTLOG_PTRASSERT(mStackListener);
        return;
    }
    mWfdLib = new WFDLib(mStackListener.get(), RTP_STREAM_ADDRESS);
    if (NULL == mWfdLib) {
        DTLOG_PTRASSERT(mWfdLib);
        return;
    }
    mPlayer = new WFDServiceAVCtr(this);
    if (NULL == mPlayer.get()) {
        DTLOG_PTRASSERT(mPlayer);
        return;
    }


    mInutListener = new WFDInputListener(this);
    if (NULL == mInutListener.get()) {
        DTLOG_PTRASSERT(mInutListener);
        return;
    }

    mInput = new InputManagerProxyBase(mInutListener.get());
    if (NULL == mInput) {
        DTLOG_PTRASSERT(mInput);
        return;
    }

    mWifiListener = new WFDWifiListener(this);
    if (NULL == mWifiListener.get()) {
        DTLOG_PTRASSERT(mWifiListener);
        return;
    }
    mWifiProxy = new wifiProxyBase(mWifiListener.get());
    if (NULL == mWifiProxy) {
        DTLOG_PTRASSERT(mWifiProxy);
        return;
    }

    mBtProxy = new BtProxyBase(new IBtProxyReplier());
    if (NULL == mBtProxy) {
        DTLOG_PTRASSERT(mBtProxy);
        return;
    }

}

WFDServiceManager::~WFDServiceManager()   /* __0x004001_DTFUNCID__ */
{
    MCLOGD("stop the WFDServiceManager thread");
    DTLOG_INFO(0x004001, "WFDServiceManager::~WFDServiceManager");
    mThread.stop();
    mThread.join();

    if (mWfdLib != NULL) {
        delete mWfdLib;
        mWfdLib = NULL;
    }
    mStackListener = NULL;
    if (mWifiProxy != NULL) {
        delete mWifiProxy;
        mWifiProxy = NULL;
    }
    mWifiListener = NULL;
    if (mInput != NULL) {
        delete mInput;
        mInput = NULL;
    }
    mInutListener = NULL;
    if (mSetting != NULL) {
        delete mSetting;
        mSetting = NULL;
        }

    if (mBtProxy != NULL) {
        delete mBtProxy;
        mBtProxy = NULL;
    }

    mPlayer = NULL;
    //WFDDTLogInst->stop();
    
}

void WFDServiceManager::initialize()   /* __0x004002_DTFUNCID__ */
{
    if (mPlayer != NULL){
        bool ret = mPlayer->onStart();
        if(true != ret){
           DTLOG_INFO(0x004002, "initialize:onStart error");
        }
    }
}

void WFDServiceManager::wfdStateSync(WFDDeviceState_Sp & deviceState)   /* __0x004003_DTFUNCID__ */
{
    MCLOGD("****%s****,mHid = %d,mBt = %d, mState = %d, mSource = %d, mAppState = %d", __func__,mHid,mBt,mState,mSource,mLocalInfoData.appState);
    deviceState->setHid(mHid);
    deviceState->setBt(mBt);
    deviceState->setSvcState(mState);
    deviceState->setSourceState(mSource);
    deviceState->setAppState(mLocalInfoData.appState);
    
}

void WFDServiceManager::SetWfdState(WFDDeviceState_Sp  deviceState)     /* __0x004004_DTFUNCID__ */
{
    MCLOGD("****%s****,mHid = %d,mBt = %d, mState = %d, mSource = %d, mAppState = %d", __func__,mHid,mBt,mState,mSource,mLocalInfoData.appState);
    DTLOG_INFO(0x004004,"****%s****,mHid = %d,mBt = %d, mState = %d, mSource = %d, mAppState = %d", __func__,mHid,mBt,mState,mSource,mLocalInfoData.appState);
    if ((mSource == WFD_SOURCE_CHANGE) &&(deviceState->getSourceState() == WFD_SOURCE_ON) ){
        wfd_play();
    }
    mHid = deviceState->getHid();
    mBt = deviceState->getBt();
    mState = deviceState->getSvcState();
    mSource = deviceState->getSourceState();
    mLocalInfoData.appState = deviceState->getAppState();
    MCLOGD("****%s****,mHid = %d,mBt = %d, mState = %d, mSource = %d, mAppState = %d", __func__,mHid,mBt,mState,mSource,mLocalInfoData.appState);
}

void WFDServiceManager::wfdGetRemoteInfo(WFDRemoteDeviceInfo_Sp& remoteInfo)   /* __0x004005_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    remoteInfo->setSvcState(mState);
    remoteInfo->setAppState(mLocalInfoData.appState);
    remoteInfo->setWidth(mLocalInfoData.width);
    remoteInfo->setHeight(mLocalInfoData.height);
    remoteInfo->setLocked(mLocalInfoData.locked);
    remoteInfo->setMode(mLocalInfoData.screenMode);

}

void WFDServiceManager::wfdSetLocalInfoData(wfdLocalInfo localInfo)   /* __0x004006_DTFUNCID__ */
{
    memcpy(&mLocalInfoData, &localInfo, sizeof(wfdLocalInfo));
}

void WFDServiceManager::wfdGetLocalInfoData(wfdLocalInfo& localInfo)   /* __0x004007_DTFUNCID__ */
{
    memcpy(&localInfo, &mLocalInfoData, sizeof(wfdLocalInfo));
}

void WFDServiceManager::wfdClearLocalInfoData()   /* __0x004008_DTFUNCID__ */
{
    mLocalInfoData.localIp = 0;
    mLocalInfoData.localPort = 0;
    mLocalInfoData.remoteIp = 0;
    mLocalInfoData.remotePort = 0;
    mLocalInfoData.width = 0;
    mLocalInfoData.height = 0;
    mLocalInfoData.locked = false;
    mLocalInfoData.screenMode = Screen_Vertial;
    mLocalInfoData.appMode = MIRROR_INVALID;
    mLocalInfoData.appState = APP_UNAVAILABLE;
    mLocalInfoData.p2pState = P2P_UNCONNECTED;
    mLocalInfoData.appBtMac = 0;
    mLocalInfoData.hdcpSupport = 0;
    mLocalInfoData.naviState = NAVI_VOICE_OFF;
    mLocalInfoData.reP2pMac = 0;
}

void WFDServiceManager::wfdClearStaInfoData()
{
    mLocalInfoData.localStaIp = 0;
    mLocalInfoData.localStaPort = 0;
    mLocalInfoData.remoteStaIp = 0;
    mLocalInfoData.staState = STA_UNCONNECTED;
}


WFDServiceReplier* WFDServiceManager::getServiceReplier()  /* __0x004009_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    return mReplier;
}

SenderId WFDServiceManager::getSenderId()   /* __0x00400A_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    return mId;
}

WFDServiceStub* WFDServiceManager::getServiceStub()   /* __0x00400B_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    return mStub;
}

WFDLib* WFDServiceManager::getWFDLib()   /* __0x00400C_DTFUNCID__ */
{
    return mWfdLib;
}

WFDSetting* WFDServiceManager::getWFDSetting()   /* __0x00400D_DTFUNCID__ */
{
      return mSetting;
}

WFDServiceAVCtr* WFDServiceManager::getMediaPlay()   /* __0x00400E_DTFUNCID__ */
{
    return mPlayer.get();
}

android::status_t WFDServiceManager::wfd_powerOn()   /* __0x00400F_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x00400F, "WFDServiceManager::wfd_powerOn");
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
    if (msg != NULL ) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 50);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x00400F, "wfd_powerOn:postMessage error, ret=%d",ret);
        }
    }

    return 0;
}

android::status_t WFDServiceManager::wfd_powerOff()   /* __0x004010_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x004010, "WFDServiceManager::wfd_powerOff");
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_POWEROFF_CMD);
    if (msg != NULL ) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004010, "wfd_powerOff:postMessage error, ret=%d",ret);
        }
    }

    return 0;
}

android::status_t WFDServiceManager::wfd_sourceChange(SenderId id, const uint8_t& mode)   /* __0x004011_DTFUNCID__ */
{
    MCLOGD("****%s****, mode = %d", __func__, mode);
    DTLOG_INFO(0x004011, "WFDServiceManager::wfd_sourceChange, mode = %d", mode);
    mId = id;
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_SOURCE_CHANGE);
    if (msg != NULL) {
        msg->setMode(mode);
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004011, "wfd_sourceChange:postMessage error, ret=%d",ret);
        }
    }
    return 0; 
}

android::status_t WFDServiceManager::wfd_mirrorMode(SenderId id, const MirrorMode& mode)   /* __0x004012_DTFUNCID__ */
{
    MCLOGD("****%s****. mode = %d", __func__, mode);
    DTLOG_INFO(0x004012, "WFDServiceManager::wfd_mirrorMode, mode = %d", mode);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_MIRROR_MODE);
    if (msg != NULL) {
        msg->setInt32Parameter(mode);
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        mLocalInfoData.appMode = mode;
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004012, "wfd_mirrorMode postMessage error, ret=%d",ret);
        }
    }
    return 0;
}

android::status_t WFDServiceManager::wfd_SreenMode(SenderId id, const ScreenMode& mode)   /* __0x004013_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x004013, "WFDServiceManager::wfd_SreenMode, mode = %d", mode);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_SCREEN_MODE);
    if (msg != NULL) {
        msg->setInt32Parameter(mode);
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        MCLOGD("****%s****, send to message handler", __func__);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004013, "wfd_mirrorMode postMessage error, ret=%d",ret);
        }
    }
    return 0;
}

void WFDServiceManager::wfd_startListen()   /* __0x004014_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x004014, "WFDServiceManager::wfd_startListen");
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_START_LISTEN);
    if (msg != NULL) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004014, "wfd_mirrorMode postMessage error, ret=%d",ret);
        }
    }
    return;
}

void WFDServiceManager:: wfd_stopListen()   /* __0x004015_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x004015, "WFDServiceManager::wfd_stopListen");
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_STOP_LISTEN);
    if (msg != NULL) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004015, "wfd_mirrorMode postMessage error, ret=%d",ret);
        }
    }
    return;
}


void WFDServiceManager::wfd_addWfdTag()   /* __0x004016_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x004016, "WFDServiceManager::wfd_addWfdTag");
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_ADD_TAG);
    if (msg != NULL) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004016, "wfd_addWfdTag:postMessage error, ret=%d",ret);
        }
    }
    return;
}


android::status_t WFDServiceManager::wfd_startSearch(SenderId id)   /* __0x004034_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    return 0;
}

android::status_t WFDServiceManager::wfd_stopSearch(SenderId id)   /* __0x004017_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    return 0;
}

android::status_t WFDServiceManager::wfd_sendHardKey(SenderId id, const HardKey& key)   /* __0x004018_DTFUNCID__ */
{
    MCLOGD("****%s****key = %d", __func__, key);
    DTLOG_INFO(0x004018, "WFDServiceManager::wfd_sendHardKey, key = %d", key);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_APP_HARDKEY);
    if (msg != NULL) {
        msg->setInt32Parameter(key);
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004018, "wfd_sendHardKey:postMessage error, ret=%d",ret);
        }
    }
    return 0;
}

android::status_t WFDServiceManager::wfd_acceptInvitation(SenderId id, const bool& accept, uint64_t macAddr)   /* __0x004019_DTFUNCID__ */
{
    MCLOGD("****%s**** accept = %d, macAddr = %llx", __func__, accept, macAddr);
    DTLOG_INFO(0x004019, "WFDServiceManager::wfd_acceptInvitation, accept = %d, macAddr = %llx", accept, macAddr);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_ACCEPT_INVITATION);
    if (msg != NULL) {
        msg->setAccpet(accept);
        msg->setmacAddr(macAddr);
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004019, "wfd_acceptInvitation:postMessage error, ret=%d",ret);
        }
        if (accept == false) {
            m_timer.start(WFD_TIME_30SEC*WFD_SEC2MSEC, true, this, &WFDServiceManager::onOneShotTimer);
            mState = WFD_CONNECTING;
        }
    }
    return 0;
}

android::status_t WFDServiceManager::wfd_disconnect(SenderId id)   /* __0x00401A_DTFUNCID__ */
{
    MCLOGD("****%s****, mP2pConn = %d,mState = %d", __func__, mLocalInfoData.p2pState, mState);
    DTLOG_INFO(0x00401A, "WFDServiceManager::wfd_disconnect, mP2pConn = %d,mState = %d", mLocalInfoData.p2pState, mState);

    if (mLocalInfoData.p2pState == P2P_CONNECTED) {
        android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_WFD_DISCONECT);
        if (msg != NULL) {
            int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
            if(BS_NO_ERROR!=ret){
                DTLOG_RET(0x00401A, "wfd_disconnect:postMessage error, ret=%d",ret);
            }
        }
    }
    else if (mLocalInfoData.p2pState == P2P_CONNECTING) {
        wfd_p2pDisconnect();
    }
    else {
        //do nothing
    }

    return 0;
}

android::status_t WFDServiceManager::wfd_getP2pState()   /* __0x00401B_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_GET_P2P_SATE);
    if (msg != NULL) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
             DTLOG_RET(0x00401B, "wfd_getP2pState:postMessage error, ret=%d",ret);
        }
    }
    return 0;
}

android::status_t WFDServiceManager::wfd_p2pDisconnect()   /* __0x00401C_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    if (mLocalInfoData.p2pState == P2P_CONNECTED ||(mLocalInfoData.p2pState == P2P_CONNECTING)) {
        android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_DISCONNECT);
        if (msg != NULL) {
            int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
            if(BS_NO_ERROR!=ret){
                 DTLOG_RET(0x00401C, "wfd_p2pDisconnect:postMessage error, ret=%d",ret);
            }
        }        
    }
    return 0;
}

android::status_t WFDServiceManager::wfd_getGPSTime(SenderId id)   /* __0x00401D_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x00401D, "WFDServiceManager::wfd_getGPSTime");
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_APP_GPSTIME);
    if (msg != NULL) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x00401D, "wfd_getGPSTime:postMessage error, ret=%d",ret);
        }
    }
    return 0;
}

android::status_t WFDServiceManager::wfd_play()   /* __0x00401E_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_WFD_PLAY);
    if (msg != NULL) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x00401E, "wfd_play:postMessage error, ret=%d",ret);
        }
    }
    return 0;
}

android::status_t WFDServiceManager::wfd_pause()   /* __0x00401F_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_WFD_PAUSE);
    if (msg != NULL) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x00401F, "wfd_pause:postMessage error, ret=%d",ret);
        }
    }
    return 0;
}

android::status_t WFDServiceManager::wfd_sendIDR()   /* __0x004020_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x004020, "WFDServiceManager::wfd_sendIDR");
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_WFD_IDR);
    if (msg != NULL) {
        int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
        if(BS_NO_ERROR!=ret){
            DTLOG_RET(0x004020, "wfd_sendIDR:postMessage error, ret=%d",ret);
        }
    }
    return 0;
}


android::status_t WFDServiceManager::onInvitationInd(android::String8 devName, uint64_t macAddr)   /* __0x004021_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x004021, "WFDServiceManager::onInvitationInd, macAddr = %llx", macAddr);
    if (listenFlag) {
        wfd_acceptInvitation(mId, false, macAddr);
        mLocalInfoData.p2pState = P2P_CONNECTING;
        mLocalInfoData.reP2pMac = macAddr;
#if 0
        android::sp<WFDDeviceInfo> deviceInfo = new WFDDeviceInfo();
        deviceInfo->setAddr(macAddr);
        deviceInfo->setNameLen(devName.length());
        deviceInfo->setDeviceName(devName);

        if (NULL != mStub) {
            mStub->wfdInvitationInd(deviceInfo);

            }
#endif
    }
    else{
        wfd_acceptInvitation(mId, true, macAddr);
    }
    return 0;
}

#if 0
void WFDServiceManager::onPlayerPrepare(std::string uri, uint32_t port)
{
    MCLOGD("****%s****", __func__);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MV_EVT_PLAYER_PREPARE);
    if (msg != NULL) {
        msg->setString(uri);
        mLocalPort = port;
        msg->setLocalPort(mLocalPort);
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
    }
}
#endif

void WFDServiceManager::onWFDServiceConnected(uint32_t result)   /* __0x004022_DTFUNCID__ */
{
    MCLOGD("*****%s*****",__func__);
    if(result == WFD_SERVICE_CONNECTED) {
        mState = WFD_CONNECTED;
        // to get bt state;
        BtDevInfo_Sp device = new BtDevInfo();
        uint32_t connectedFunc = 0;
        if (NULL == mBtProxy) {
            DTLOG_PTRASSERT(mBtProxy);
            return ;
        }
        mBtProxy->getConnectedDevice(device, connectedFunc);        
        MCLOGD("*****%s*****, connectedFunc = %d, btMac = %llx",__func__, connectedFunc, device->getAddr());
        mBtMode = static_cast<uint16_t>(connectedFunc);
        mLocalInfoData.btMac = device->getAddr();
        mBt = static_cast<uint32_t>((mBtMode & 0x07) != 0);
        mHid = static_cast<uint32_t>((mBtMode & 0x04) != 0);
        if (mLocalInfoData.appBtMac != 0 && mLocalInfoData.appBtMac != mLocalInfoData.btMac){
            mHid = 0;
        }
        if (NULL == mStub) {
            DTLOG_PTRASSERT(mStub);
            return ;
        }
        mStub->wfdBtStatus(mBt, mHid);
    }
}

void WFDServiceManager::onMsgReceived(uint8_t opcode, void* msg)   /* __0x004023_DTFUNCID__ */
{
    MCLOGD("*****%s*****,opcode = %d", __func__, opcode);
    WFDServiceMsg* recvMsg = reinterpret_cast<WFDServiceMsg*>(msg);
    if (recvMsg == NULL) {
        DTLOG_PTRASSERT(recvMsg);
        return;
    }
    switch(opcode) 
    {
    case MSG_P2P_POWER:
        onP2pPowerStatusNotify(recvMsg);
        break;
    case MSG_P2P_CONNECT:
        onP2pConnectStatusNotify(recvMsg);
        break;
    case MSG_P2P_IP:
        onP2pConnectedInfoNotify(recvMsg);
        break;
    case MSG_P2P_SIG:
        onP2pLinkQuiltyNotify(recvMsg);
        break;
    case MSG_P2P_LISTEN:
        onP2pListenStatusNotify(recvMsg);
        break;
    case MS_BT_CONNECT:
        onBtConnectionChanged(recvMsg);
        break;
    case MS_BT_DISCONNECT:
        onBtDisconnectionChanged(recvMsg);
        break;
    case MS_CARLIFE_CARPLAY_INSERT:
        onCarLifeOrCarPlayInsert();
        break;
    case MS_CARLIFE_CARPLAY_EXTRACT:
        onCarLifeOrCarPlayExtract();
        break;
    case MSG_STA_IP:
        onStaConnectedInfoNotify(recvMsg);
        break;
    default:
        break;
    }
    
    if (msg != NULL) {
        delete reinterpret_cast<WFDServiceMsg*>(msg);
        msg = NULL;
    }
    
}

android::status_t WFDServiceManager::onP2pPowerStatusNotify(WFDServiceMsg* recvMsg)   /* __0x004024_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    if(recvMsg == NULL) return WFD_SERVICE_ERR_FAILED;
    uint32_t powerStatus = recvMsg->getInt32Parameter();
    DTLOG_INFO(0x004024, "WFDServiceManager::onP2pPowerStatusNotify, powerStatus = %d", powerStatus);
    if (powerStatus == WIFI_POWER_STATE_POWER_OFF) {
        if (mState == WFD_CONNECTED){
            wfd_disconnect(mId);
            if (mStub != NULL) {
                int ret = mStub->wfdDisconnectInd(WFD_SERVICE_UNCONNECTED);
                if(BS_NO_ERROR!=ret){
                   DTLOG_RET(0x004024, "onP2pPowerStatusNotify:sendMulticast error1, ret=%d",ret);
                }
            }
        }
        else if (mState == WFD_CONNECTING) {
            if (m_timer.isActive()) m_timer.stop();
            wfd_disconnect(mId);
            if (mStub != NULL) {
                int ret = mStub->wfdConnectResultInd(WFD_SERVICE_UNCONNECTED);
                if(BS_NO_ERROR!=ret){
                   DTLOG_RET(0x004024, "onP2pPowerStatusNotify:sendMulticast error2, ret=%d",ret);
                }
            }
        }
        else {
        }
        mState = WFD_POWER_OFF;
        wfdClearLocalInfoData();
    }
    else if (powerStatus == WIFI_POWER_STATE_POWER_ON) {
        mState = WFD_POWER_ON;
        wfd_addWfdTag();
        wfd_getP2pState();
        if(listenFlag) {
            wfd_startListen();
        }
    }
    else {
    }
    if(mStub != NULL) {
        int ret = mStub->wfdPowerStatus(powerStatus);
        if(BS_NO_ERROR!=ret){
           DTLOG_RET(0x004024, "onP2pPowerStatusNotify:sendMulticast error3, ret=%d",ret);
        }
    }
    return 0;
}

android::status_t WFDServiceManager::onP2pConnectStatusNotify(WFDServiceMsg* recvMsg)   /* __0x004025_DTFUNCID__ */
{
    if(recvMsg == NULL) return WFD_SERVICE_ERR_FAILED;
    uint32_t connectStatus = recvMsg->getInt32Parameter();
    MCLOGD("****%s****,connectStatus = %d, listenFlage = %d, p2pConnect = %d, state = %d", __func__,connectStatus, listenFlag, mLocalInfoData.p2pState, mState);
    DTLOG_INFO(0x004025, "WFDServiceManager::onP2pConnectStatusNotify, connectStatus = %d, listenFlage = %d, p2pConnect = %d, state = %d", connectStatus, listenFlag, mLocalInfoData.p2pState, mState);
    if (connectStatus == WIFI_CONNECT_STATE_DISCONNECTTED && mStub != NULL) {
        if (mLocalInfoData.p2pState == P2P_CONNECTED) {
            // the situation disconnet by remote device
            if (mState == WFD_CONNECTING ) {
                int ret = mStub->wfdConnectResultInd(connectStatus);
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x004025, "onP2pConnectStatusNotify:sendMulticast error1, ret=%d",ret);
                }
            }
            if (mState == WFD_CONNECTED) {
                int ret = mStub->wfdDisconnectInd(connectStatus);
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x004025, "onP2pConnectStatusNotify:sendMulticast error2, ret=%d",ret);
                }
            }
            wfd_disconnect(mId);
        }
        else if (mLocalInfoData.p2pState == P2P_CONNECTING) {
            // connect failed
            m_timer.stop();
            // mStub->wfdConnectResultInd(connectStatus);
        }
        else if (mLocalInfoData.p2pState == P2P_DISCONNECTING ) {
            MCLOGD("****%s****%d", __func__, __LINE__);
            int ret = mStub->wfdDisconnectInd(connectStatus);
            if (BS_NO_ERROR!=ret) {
                DTLOG_RET(0x004025, "onP2pConnectStatusNotify:sendMulticast error3, ret=%d",ret);
            }
        }
        else {
        }
        wfdClearLocalInfoData();
        if(listenFlag) {
            wfd_startListen();
        }
        else {
            wfd_stopListen();
        }
    }
    else if (connectStatus == WIFI_CONNECT_STATE_CONNECTTED) {
        // to add a timer to get the IP
        m_timer.stop();
        m_timer.start(WFD_TIME_60SEC*WFD_SEC2MSEC, true, this, &WFDServiceManager::onOneShotTimer);
        }
    else {
        }
    return 0;
}

android::status_t WFDServiceManager::onP2pConnectedInfoNotify(WFDServiceMsg* recvMsg)   /* __0x004026_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x004026, "WFDServiceManager::onP2pConnectedInfoNotify");
    if (recvMsg != NULL) {
        mLocalInfoData.remotePort =static_cast<uint32_t>(recvMsg->getRemotePort());
        mLocalInfoData.localIp= recvMsg->getLocalIP();
        mLocalInfoData.remoteIp= recvMsg->getRemoteIp();
        mLocalInfoData.p2pState = P2P_CONNECTED;
        m_timer.stop();
        android::sp<WFDDeviceInfo> deviceInfo = new WFDDeviceInfo();
        deviceInfo->setAddr(mLocalInfoData.reP2pMac);
        if(NULL != mStub) {
            int ret = mStub->wfdInvitationInd(deviceInfo);
            if(BS_NO_ERROR!=ret){
                 DTLOG_RET(0x004026, "onP2pConnectedInfoNotify:sendMulticast error, ret=%d",ret);
            }
        }
        android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_WFD_START);
        if (msg != NULL) {
            int ret = mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
            if(BS_NO_ERROR!=ret){
                 DTLOG_RET(0x004026, "onP2pConnectedInfoNotify:postMessage error, ret=%d",ret);
            }
        }
    }
    return 0;
}

android::status_t WFDServiceManager::onStaConnectedInfoNotify(WFDServiceMsg* recvMsg)
{
    MCLOGD("****%s****", __func__);
    if (recvMsg != NULL) {
        mLocalInfoData.localStaPort =static_cast<uint32_t>(recvMsg->getRemotePort());
        mLocalInfoData.localStaIp= recvMsg->getLocalIP();
        mLocalInfoData.remoteStaIp= recvMsg->getRemoteIp();
        mLocalInfoData.staState = STA_CONNECTED;

        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_WFD_START_MDNS);
        if (msg != NULL) {
            mThread.postMessage(reinterpret_cast<Message*>(msg), 1);
        }
    }
    return 0;

}

android::status_t WFDServiceManager::onP2pLinkQuiltyNotify(WFDServiceMsg* recvMsg)   /* __0x004027_DTFUNCID__ */
{   
    if (recvMsg == NULL) return WFD_SERVICE_ERR_FAILED;
    int32_t sig = recvMsg->getInt32Parameter();
    MCLOGD("****%s****%d*****%d", __func__, __LINE__, sig);
    if(mState == WFD_CONNECTED) {
        if (mStub != NULL) {
            int ret = mStub->wfdLinkQuiltyInd(sig);
            if(BS_NO_ERROR!=ret){
                 DTLOG_RET(0x004027, "onP2pLinkQuiltyNotify:sendMulticast error, ret=%d",ret);
            }
        }
    }
    return 0;
}

android::status_t WFDServiceManager::onP2pListenStatusNotify(WFDServiceMsg* recvMsg)   /* __0x004028_DTFUNCID__ */
{
    if (recvMsg == NULL) return WFD_SERVICE_ERR_FAILED;
    uint32_t listenState = recvMsg->getInt32Parameter();
    MCLOGD("****%s**** listenState = %d", __func__, listenState);
    DTLOG_INFO(0x004028, "WFDServiceManager::onP2pListenStatusNotify,listenState = %d", listenState);
    if (listenState == 0) {
        mState = WFD_LISTENING;
        if (mStub != NULL) {
            int ret = mStub->wfdStartListenInd(listenState);
            if(BS_NO_ERROR!=ret){
                 DTLOG_RET(0x004028, "onP2pListenStatusNotify:sendMulticast error1, ret=%d",ret);
            }
        }
    }
    else {
        mState = WFD_POWER_ON;
        if (mStub != NULL) {
            int ret = mStub->wfdStartListenInd(listenState);
            if(BS_NO_ERROR!=ret){
                 DTLOG_RET(0x004028, "onP2pListenStatusNotify:sendMulticast error2, ret=%d",ret);
            }
        }
    }
    return 0;
}

android::status_t WFDServiceManager::onBtConnectionChanged(WFDServiceMsg* recvMsg)   /* __0x004029_DTFUNCID__ */
{
    if (recvMsg == NULL) return WFD_SERVICE_ERR_FAILED;
    uint16_t btMode = recvMsg->getUint16Value();
    uint32_t result = recvMsg->getInt32Parameter();
    uint64_t btMac = recvMsg->getU64Parameter();
    MCLOGD("****%s****, btMode = %d, result = %d, btMac = %llx", __func__, btMode, result, btMac);
    if (result == 0 && mStub != NULL) {
        wfdLocalInfo localInfo;
        wfdGetLocalInfoData(localInfo);
        localInfo.btMac = btMac;
        wfdSetLocalInfoData(localInfo);
        mBtMode = mBtMode | btMode;
        uint32_t bt = static_cast<uint32_t>((mBtMode & 0x07) != 0);
        uint32_t hid = static_cast<uint32_t>((mBtMode & 0x04) != 0);
        MCLOGD("****%s****, btMac = %llx, appBtMac = %llx", __func__, btMac, mLocalInfoData.appBtMac);
        if ((bt != mBt) ||  (hid != mHid)){
            mBt = bt;
            mHid = hid;
            if (mLocalInfoData.appBtMac != 0 && mLocalInfoData.appBtMac != btMac){
                mHid = 0;
            }
            mStub->wfdBtStatus(mBt, mHid);
        }
    }
    else {
        
    }
    return 0;
}

android::status_t WFDServiceManager::onBtDisconnectionChanged(WFDServiceMsg* recvMsg)   /* __0x00402A_DTFUNCID__ */
{
    if (recvMsg == NULL) return WFD_SERVICE_ERR_FAILED;
    uint16_t btMode = recvMsg->getUint16Value();
    uint32_t result = recvMsg->getInt32Parameter();
    uint64_t btMac = recvMsg->getU64Parameter();
    MCLOGD("****%s****, btMode = %d, result = %d, mBtMode = %d,", __func__, btMode, result, mBtMode);
    DTLOG_INFO(0x00402A, "WFDServiceManager::onBtDisconnectionChanged,btMode = %d, result = %d, mBtMode = %d,",btMode, result, mBtMode);
    if (mStub != NULL) {
        mBtMode = mBtMode &(~btMode);        
        uint32_t bt = static_cast<uint32_t>((mBtMode & 0x05) != 0);
        uint32_t hid = static_cast<uint32_t>((mBtMode & 0x04) != 0);
        if ((bt != mBt) ||  (hid != mHid)){
            mBt = bt;
            mHid = hid;
            if (mLocalInfoData.appBtMac != 0 && mLocalInfoData.appBtMac != btMac){
                mHid = HID_UNCONNETED;
            }
            mStub->wfdBtStatus(mBt, mHid);
        }
        if (mBt == 0) {
            wfdLocalInfo localInfo;
            wfdGetLocalInfoData(localInfo);
            localInfo.btMac = 0;
            wfdSetLocalInfoData(localInfo);
        }
    }
    else {
    }
    return 0;
}

android::status_t WFDServiceManager::onCarLifeOrCarPlayInsert()   /* __0x00402B_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x00402B, "WFDServiceManager::onCarLifeOrCarPlayInsert");
    listenFlag = false;
    if (mState == WFD_CONNECTING || mState == WFD_CONNECTED ){
        wfd_sourceChange(mId, WFD_SOURCE_OFF);
        MCLOGD("****%s****%d", __func__, __LINE__);
        wfd_disconnect(mId);
    }
    wfd_stopListen();
    return 0;

}

android::status_t WFDServiceManager::onCarLifeOrCarPlayExtract()   /* __0x00402C_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    DTLOG_INFO(0x00402C, "WFDServiceManager::onCarLifeOrCarPlayExtract");
    listenFlag = true;
    wfd_startListen();
    return 0;

}

android::status_t WFDServiceManager::onTransSwitchReq(uint32_t protocl)
{
    MCLOGD("****%s****", __func__);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_WFD_SWITCH_REQ);
    if (msg != NULL) {
        msg->setTransProtocl(protocl);
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
    }
    return 0;
}

android::status_t WFDServiceManager::onTransSwitchCmp(uint32_t result)
{
    MCLOGD("****%s****", __func__);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_WFD_SWITCH_CMP);
    if (msg != NULL) {
        msg->setInt32Parameter(result);
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
    }
    return 0;
}

void WFDServiceManager::onInputManagerConnected()   /* __0x00402D_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    if(mInput != NULL) {
        mInput->registerClient(INPUT_MIRACAST);
    }
}

void WFDServiceManager::onOneShotTimer(Timer* timer)   /* __0x00402E_DTFUNCID__ */
{
    MCLOGD("****%s****", __func__);
    wfd_disconnect(mId);
    wfdClearLocalInfoData();
    // mStub->wfdConnectResultInd(WIFI_STATE_DISCONNECTTED);

}

void WFDServiceManager::onPlayerErr()    /* __0x00402F_DTFUNCID__ */
{
    DTLOG_INFO(0x00402F, "WFDServiceManager::onPlayerErr");
    MCLOGD("****%s****", __func__);
    wfd_disconnect(mId);
    //wfdClearLocalInfoData();
}

void WFDServiceManager::onTransSwitchSuccess(int protocl)
{
    MCLOGD("****%s****", __func__);
    android::sp<WFDServiceMsg> msg = new WFDServiceMsg(MN_EVT_WFD_SWITCH_SUCCESS);
    if (msg != NULL) {
        msg->setTransProtocl(protocl);
        mThread.postMessage(reinterpret_cast<Message*>(msg.get()), 1);
    }
}


WFDServiceManager::WFDManagerHandler::WFDManagerHandler(WFDServiceManager* manager)   /* __0x004030_DTFUNCID__ */
:mOwner(manager)
{
}

WFDServiceManager::WFDManagerHandler::~WFDManagerHandler()    /* __0x004031_DTFUNCID__ */
{
}

void WFDServiceManager::WFDManagerHandler::onReceiveMessage(const android::sp<Message> &msg)    /* __0x004032_DTFUNCID__ */
{
    MCASSERT(msg.get() != NULL);
    WFDServiceMsg* req = static_cast<WFDServiceMsg*>(msg.get());
    if (mOwner == NULL || req == NULL) return;
    MCLOGD("*****%s*****, funcId=%d, mState = %d", __func__, req->funcId(),mOwner->mState );
    DTLOG_INFO(0x004032, "WFDServiceManager::onReceiveMessage,funcId=%d, mState = %d", req->funcId(),mOwner->mState);
    switch (req->funcId())
    {
    case MN_EVT_POWERON_CMD:
    {
        if (mOwner->mWifiProxy != NULL) {
            if (mOwner->mState == WFD_POWER_OFF) {
                MCLOGD("*****%s*****, to power on mState = %d", __func__,mOwner->mState );
                int ret = mOwner->mWifiProxy->p2pPowerOn();
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x004032, "sendAsyncRequest error1, ret=%d",ret);
                }
            }
            else {
                if (mOwner->mStub != NULL) {
                    int ret = mOwner->mStub->wfdPowerStatus(WFD_POWER_ON);
                    if (BS_NO_ERROR!=ret) {
                        DTLOG_RET(0x004032, "sendMulticast error1, ret=%d",ret);
                    }
                }
            }
        }
        break;
    }
    case MN_EVT_POWEROFF_CMD:
    {
        if (mOwner->mWifiProxy != NULL) {
            if (mOwner->mState == WFD_POWER_OFF) {
                int ret = mOwner->mStub->wfdPowerStatus(WFD_POWER_OFF);
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x004032, "sendMulticast error2, ret=%d",ret);
                }
            }
            else {
                int ret = mOwner->mWifiProxy->p2pPowerOff();
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x004032, "sendAsyncRequest error2, ret=%d",ret);
                }
            }
        }
        break;
    }
    case MN_EVT_SOURCE_CHANGE:
    {
        if (mOwner->mPlayer != NULL) {
            uint8_t mode = req->getMode();
            if ((mode == WFD_SOURCE_OFF) && (mOwner->mSource != WFD_SOURCE_OFF)){
                int err = mOwner->mPlayer->stop();
                if (err >= 1) {
                    mOwner->mSource = WFD_SOURCE_OFF;
                    int ret = mOwner->mReplier->wfdSourceChangeCfm(mOwner->mId, WFD_ACTION_OK, mode);
                    if (BS_NO_ERROR!=ret) {
                        DTLOG_RET(0x004032, "sendAsyncResponse error1, ret=%d",ret);
                    }
                    int rett = mOwner->mReplier->wfdNaviVoiceInd(mOwner->mId, NAVI_VOICE_OFF);
                    if (BS_NO_ERROR!=rett) {
                        DTLOG_RET(0x004032, "sendAsyncResponse error2, ret=%d",ret);
                    }
                }
                else {
                    int ret = mOwner->mReplier->wfdSourceChangeCfm(mOwner->mId, WFD_ACTION_NG, mode);
                    if (BS_NO_ERROR!=ret) {
                        DTLOG_RET(0x004032, "sendAsyncResponse error3, ret=%d",ret);
                    }
                    MCLOGE("*****%s*****,source off failed", __func__);
                    DTLOG_ERR(0x004032, "WFDServiceManager::source off failed");
                }

            }
            else if ((mode == WFD_SOURCE_ON) && (mOwner->mSource == WFD_SOURCE_OFF) && (mOwner->mState == WFD_CONNECTED)) {
                MCLOGD("****%s****%d", __func__, __LINE__);
                mOwner->mSource = WFD_SOURCE_CHANGE;
                mOwner->mPlayer->setUri(mOwner->mLocalInfoData.localIp, mOwner->mLocalInfoData.localPort, mOwner->mLocalInfoData.hdcpSupport);

            }
            else if (mode == mOwner->mSource) {
                int ret = mOwner->mReplier->wfdSourceChangeCfm(mOwner->mId, WFD_ACTION_OK, mode);
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x004032, "sendAsyncResponse error4, ret=%d",ret);
                }
            }
            else {
                MCLOGE("*****%s*****,In the state = %d, could not source change", __func__, mOwner->mSource);
                DTLOG_ERR(0x004032, "WFDServiceManager::MN_EVT_SOURCE_CHANGE,In the state = %d, could not source change", mOwner->mSource);
                int ret = mOwner->mReplier->wfdSourceChangeCfm(mOwner->mId, WFD_ACTION_NG, mode);
                if (BS_NO_ERROR!=ret) {
                    DTLOG_RET(0x004032, "sendAsyncResponse error5, ret=%d",ret);
                }
            }
        }
        break;
    }
    case MN_EVT_MIRROR_MODE:
    {
        if(mOwner->mWfdLib != NULL && mOwner->mState == WFD_CONNECTED) {
            uint32_t mode = req->getInt32Parameter();
            APP_MODE appMode = APP_NOWORK;
            if (mode == MIRROR) {
                appMode = APP_MIRROR;
            }
            if (mode == APP) {
                appMode = APP_SMARTPHONE;
            }
            mOwner->mWfdLib->sendWorkModeChange(appMode);
            }
        break;
    }
    case MN_EVT_SCREEN_MODE:
    {
        if((mOwner->mWfdLib != NULL) && (mOwner->mState == WFD_CONNECTED)) {
            uint32_t mode = req->getInt32Parameter();
            mOwner->mWfdLib->sendForceSwitchScreen();
       }
        break;
    }
    case MN_EVT_START_LISTEN:
    {
        if ((mOwner->mWifiProxy != NULL) && (mOwner->mState > WFD_POWER_OFF)) {
            int ret = mOwner->mWifiProxy->p2pStartListen();
            if (BS_NO_ERROR!=ret) {
                DTLOG_RET(0x004032, "sendAsyncRequest error3, ret=%d",ret);
            }
        }
        break;
    }
    case MN_EVT_STOP_LISTEN:
    {
        if ((mOwner->mWifiProxy != NULL) && (mOwner->mState > WFD_POWER_OFF)) {
            int ret = mOwner->mWifiProxy->p2pStopListen();
            if (BS_NO_ERROR!=ret) {
                DTLOG_RET(0x004032, "sendAsyncRequest error4, ret=%d",ret);
            }
        }
        break;
    }
    case MN_EVT_ADD_TAG:
    {
        if (mOwner->mWifiProxy != NULL) {
            int ret = mOwner->mWifiProxy->p2pAddServiceTag(WIFI_SERVICE_TAG_MIRACAST);
            if (BS_NO_ERROR!=ret) {
                DTLOG_RET(0x004032, "sendAsyncRequest error5, ret=%d",ret);
            }
        }
        break;
    }
    case MN_EVT_START_SEARCH:
        break;
    case MN_EVT_ACCEPT_INVITATION:
    {
        if (mOwner->mWifiProxy != NULL) {
            bool accept = req->getAccept();
            uint64_t mac = req->getmacAddr();
            int ret = mOwner->mWifiProxy->p2pInvitation((P2P_INVITATION_ACCEPT_E)accept, mac);
            if (BS_NO_ERROR!=ret) {
                DTLOG_RET(0x004032, "sendAsyncRequest error6, ret=%d",ret);
            }
        }
        break;
    }
    case MN_EVT_DISCONNECT:
    {
        if (mOwner->mWifiProxy != NULL) {
            mOwner->mLocalInfoData.p2pState = P2P_DISCONNECTING;
            int ret = mOwner->mWifiProxy->p2pDisconnect(); 
            if (BS_NO_ERROR!=ret) {
                DTLOG_RET(0x004032, "sendAsyncRequest error7, ret=%d",ret);
            }
        }
        break;
    }
    case MN_EVT_GET_P2P_SATE:
        if (mOwner->mWifiProxy != NULL) {
            int ret = mOwner->mWifiProxy->p2pSyncStatus();
            if (BS_NO_ERROR!=ret) {
                DTLOG_RET(0x004032, "sendAsyncRequest error8, ret=%d",ret);
            }
        }
        break;
		
    case MN_EVT_WFD_START:
    {
        if (mOwner->mWfdLib != NULL) {
            int ret = mOwner->mWfdLib->startRTSPConnect(static_cast<unsigned int>(mOwner->mLocalInfoData.remoteIp), static_cast<unsigned int>(mOwner->mLocalInfoData.remotePort));
            if (-1 == ret) {
                DTLOG_INFO(0x004032, "startRTSPConnect failed");
            }
        }
        break;
    }
	case MN_EVT_WFD_START_MDNS:
    {
        if (mOwner->mWfdLib != NULL) {
#if 0
            // add for 6.7.2 test, need to modify after test
            unsigned int port = mOwner->mLocalInfoData.localStaPort;
            if (port == 7236) {
                mOwner->mWfdLib->startRTSPConnect(0xC0A56452, 7236);
            }
            else {
                mOwner->mWfdLib->startmDNS(static_cast<unsigned int>(mOwner->mLocalInfoData.localStaIp), static_cast<unsigned int>(mOwner->mLocalInfoData.localStaPort), static_cast<unsigned int>(mOwner->mLocalInfoData.remoteStaIp));

            }
#endif
            mOwner->mWfdLib->startmDNS(static_cast<unsigned int>(mOwner->mLocalInfoData.localStaIp), static_cast<unsigned int>(mOwner->mLocalInfoData.localStaPort), static_cast<unsigned int>(mOwner->mLocalInfoData.remoteStaIp));
        }
        break;
    }
    case MN_EVT_WFD_DISCONECT:
    {
        if (mOwner->mWfdLib != NULL) {
            mOwner->mWfdLib->disconnect();
            }
        break;
    }
    case MN_EVT_WFD_PLAY:
        if (mOwner->mWfdLib != NULL) {
            mOwner->mWfdLib->play();
            }
        break;
    case MN_EVT_WFD_PAUSE:
        if (mOwner->mWfdLib != NULL) {
            mOwner->mWfdLib->pause();
            }
        break;
    case MN_EVT_WFD_IDR:
        if (mOwner->mWfdLib != NULL) {
            mOwner->mWfdLib->sendIDR();
        }
        break;
    case MN_EVT_APP_GPSTIME:
    {
        if((mOwner->mWfdLib != NULL) && (mOwner->mState == WFD_CONNECTED)) {
            mOwner->mWfdLib->sendGetGPSRq();
        }
        break;
    }
    case MN_EVT_WFD_SWITCH_REQ:
    {
        if (mOwner->mPlayer != NULL) {
            int32_t mode = req->getProtocl();
            mOwner->mPlayer->tranSwitchReq(mode);
        }
        break;
    }
    case MN_EVT_WFD_SWITCH_CMP:
    {
        if (mOwner->mPlayer != NULL) {
            uint32_t result = req->getInt32Parameter();
            mOwner->mPlayer->tranSwitchCmp(result);
        }
        break;
    }
    case MN_EVT_WFD_SWITCH_SUCCESS:
    {
        if (mOwner->mWfdLib != NULL) {
            int protocl = req->getProtocl();
            mOwner->mWfdLib->tranSwitchSuccess(protocl);
        }
        break;
     }
    case MN_EVT_APP_HARDKEY:
    {
        const HardKey key = static_cast<HardKey>(req->getInt32Parameter());
        wfdLocalInfo localInfo;
        mOwner->wfdGetLocalInfoData(localInfo);
        MCLOGD("******func = %s*****,line = %d, hardkey=%d, appmode = %d", __func__, __LINE__, key, localInfo.appMode);
        DTLOG_INFO(0x004032, "WFDServiceManager::MN_EVT_APP_HARDKEY, hardkey=%d, appmode = %d", key, localInfo.appMode);
        if (key ==  PRE_TRACK_DOWN || key == NEXT_TRACK_DOWN || key == PRE_TRACK_UP || key == NEXT_TRACK_UP)
        {
            mOwner->mWfdLib->sendHardKey(static_cast<HARD_KEY>(key));
        }
        else {

            if (localInfo.appMode == APP) {
                if (key == HOME_DOWN || key == HOME_UP || key == MENU_DOWN || key == MENU_UP) {
                    mOwner->mWfdLib->sendHardKey(static_cast<HARD_KEY>(key));
                }
                else {
                    sendHardKeyToBT(key);
                }
            }
             else if (localInfo.appMode == MIRROR) {
                sendHardKeyToBT(key);
            }
            else {
                MCLOGD("*****%s*****,In the modeState = %d, could not control back", __func__, localInfo.appMode);
                DTLOG_INFO(0x004032, "*****%s*****,In the modeState = %d, could not control back", __func__, localInfo.appMode);
            }
        }

        break;
    }
    default:
        break;
    }
}

void WFDServiceManager::WFDManagerHandler::sendHardKeyToBT(HardKey key)   /* __0x004033_DTFUNCID__ */
{
    WFDDeviceState_Sp deviceState = new WFDDeviceState();
    mOwner->wfdStateSync(deviceState);
    if (deviceState->getHid() == HID_CONNECTED) {
        mOwner->mStub->wfdHardkey(key);
    }
    else {
        MCLOGE("******func = %s*****,line = %d, hardkey=%d,  HID not connectded", __func__, __LINE__, key);
        DTLOG_INFO(0x004033, "WFDManagerHandler::sendHardKeyToBT, hardkey=%d, HID not connectded", key);

    }
}

}
