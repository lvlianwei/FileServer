#ifndef WFDSERVICE_MANAGER_H
#define WFDSERVICE_MANAGER_H

#include "utils/List.h"
#include "servicebase/MessageHandler.h"
#include "servicebase/LooperThread.h"
#include "WFDServiceServiceDefines.h"
#include "WFDRemoteDeviceInfo.h"
#include "WFDDeviceState.h"
#include "WFDServiceMsg.h"
#include "servicebase/Timer.h"

class WFDLib;
namespace goni
{
class WFDServiceStub;
class Message;
class WFDWifiListener;
class wifiProxyBase;
class WFDMultiListener;
class wifiSub;
class WFDStackListener;
class WFDServiceAVCtr;
class WFDServiceReplier;
class WFDServiceStub;
class WFDSetting;
class WFDInputListener;
class InputManagerProxyBase;
class BtProxyBase;

struct wfdLocalInfo {
    uint32_t localIp;
    uint32_t localPort;
    uint32_t remoteIp;
    uint32_t remotePort;
    uint32_t width;
    uint32_t height;
    bool locked;
    ScreenMode screenMode;
    MirrorMode appMode;
    AppState appState;
    uint32_t p2pState;
    uint64_t appBtMac;
    uint64_t btMac;
    uint32_t hdcpSupport;
    uint32_t naviState;
    uint64_t reP2pMac;
    uint32_t localStaIp;
    uint32_t localStaPort;
    uint32_t remoteStaIp;
    uint32_t staState;
};

class WFDServiceManager
{
public:

    WFDServiceManager(WFDServiceStub* sub, WFDServiceReplier* replier);
    ~WFDServiceManager();
    void run();
    void insertRequest(const android::sp<Message>& msg);
    void extWakeup();

    SenderId getSenderId();
    WFDServiceReplier* getServiceReplier();
    WFDServiceStub* getServiceStub();
    WFDSetting* getWFDSetting();
    WFDLib* getWFDLib();
    WFDServiceAVCtr *getMediaPlay();

    void initialize();
    void wfdStateSync(WFDDeviceState_Sp & deviceState);
    void SetWfdState(WFDDeviceState_Sp  deviceState);
    void wfdGetRemoteInfo(WFDRemoteDeviceInfo_Sp& remoteInfo);

    void wfdSetLocalInfoData(wfdLocalInfo localInfo);
    void wfdGetLocalInfoData(wfdLocalInfo& localInfo);
    void wfdClearLocalInfoData();
    void wfdClearStaInfoData();
    
    android::status_t wfd_powerOn();
    android::status_t wfd_powerOff();
    android::status_t wfd_sourceChange(SenderId id, const uint8_t& mode);
    android::status_t wfd_mirrorMode(SenderId id, const MirrorMode& mode);
    android::status_t wfd_SreenMode(SenderId id, const ScreenMode& mode);
    android::status_t wfd_startSearch(SenderId id);
    android::status_t wfd_stopSearch(SenderId id);
    android::status_t wfd_acceptInvitation(SenderId id, const bool& accept, uint64_t macAddr);
    android::status_t wfd_disconnect(SenderId id);
    android::status_t wfd_getGPSTime(SenderId id);
    android::status_t wfd_sendHardKey(SenderId id, const HardKey& key);
    android::status_t wfd_p2pDisconnect();
    android::status_t wfd_getP2pState();
    android::status_t wfd_play();
    android::status_t wfd_pause();
    android::status_t wfd_sendIDR();

    android::status_t onInvitationInd(android::String8 devName, uint64_t macAddr);

    android::status_t onP2pPowerStatusNotify(WFDServiceMsg* recvMsg);
    android::status_t onP2pConnectStatusNotify(WFDServiceMsg* recvMsg);
    android::status_t onP2pConnectedInfoNotify(WFDServiceMsg* recvMsg);
    android::status_t onP2pLinkQuiltyNotify(WFDServiceMsg* recvMsg);
    android::status_t onP2pListenStatusNotify(WFDServiceMsg* recvMsg);
    android::status_t onBtConnectionChanged(WFDServiceMsg* recvMsg);
    android::status_t onBtDisconnectionChanged(WFDServiceMsg* recvMsg);
    android::status_t onStaConnectedInfoNotify(WFDServiceMsg* recvMsg);
    android::status_t onCarLifeOrCarPlayInsert();
    android::status_t onCarLifeOrCarPlayExtract();
    android::status_t onTransSwitchReq(uint32_t protocl);
    android::status_t onTransSwitchCmp(uint32_t result);
    

    void onMsgReceived(uint8_t opcode, void* msg);
    void wfd_startListen();
    void wfd_stopListen();
    void wfd_addWfdTag();

    void onWFDServiceConnected(uint32_t result);
    void onInputManagerConnected();
    void onOneShotTimer(Timer* timer);
    void onPlayerErr();
    void onTransSwitchSuccess(int protocl);
    

private:
    enum {
        kWhatManager = 1,

    };

    class WFDManagerHandler : public goni::MessageHandler
    {
        public:
            WFDManagerHandler(WFDServiceManager* manager);
            ~WFDManagerHandler();
            virtual void onReceiveMessage(const android::sp<goni::Message> &msg);
            void sendHardKeyToBT(HardKey key);

        private:
            WFDServiceManager* mOwner;
    };
    
    LooperThread mThread;
    android::sp<WFDWifiListener> mWifiListener;
    wifiProxyBase* mWifiProxy;
    android::sp<WFDStackListener> mStackListener;
    WFDLib* mWfdLib;
    android::sp<WFDServiceAVCtr> mPlayer;
    WFDServiceReplier* mReplier;
    WFDServiceStub* mStub;
    WFDSetting* mSetting;
    android::sp<WFDInputListener> mInutListener;
    InputManagerProxyBase* mInput;
    BtProxyBase* mBtProxy;
    goni::EasyTimer<WFDServiceManager> m_timer;
    
    wfdSvcState mState;
    SenderId mId;
    uint32_t mBt;
    uint32_t mHid;
    uint32_t mSource;      // define 0 off 1 on 2 mode is changing
    uint16_t  mBtMode; // 0x01 btphone, 0x02 btAudio, 0x04 btHid, 0x07, bt all
    wfdLocalInfo mLocalInfoData;
    bool listenFlag;
    WFDServiceManager(WFDServiceManager&);
    WFDServiceManager& operator=(WFDServiceManager&);

};



}

#endif//WFDSERVICE_MANAGER_H
