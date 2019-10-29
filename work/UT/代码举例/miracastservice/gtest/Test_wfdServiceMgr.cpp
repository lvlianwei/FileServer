#include "Test_wfdServiceMgr.h"
#include "Test_wfdService.h"
namespace goni {
    void * create_serviceMgr(void*msg){
        cout<<"in create thread"<<endl;
        Test_wfdServiceMgr::manager = new TimerManager;
        Test_wfdServiceMgr::stub = new WFDServiceStub(new wfdService);
    }
    pthread_t Test_wfdServiceMgr::pid = 0;
    TimerManager* Test_wfdServiceMgr::manager = NULL;
    WFDServiceManager *Test_wfdServiceMgr::mgr = NULL;
    WFDServiceStub* Test_wfdServiceMgr::stub = NULL;
    WFDServiceReplier * Test_wfdServiceMgr::replier = NULL;
#if 0
    TEST_F(Test_wfdServiceMgr,delayFunc) {
        int count = 0;
        cout << "*****************************delayFunc*******************" << endl;
        while(count < 5) {
            usleep(200000);
            count++;
        }
    }
#endif
    TEST_F(Test_wfdServiceMgr,wfdStateSync) {
        WFDDeviceState_Sp state(new WFDDeviceState);
        state->setHid(1);
        if(Test_wfdService::service->mStub)
        {
            Test_wfdService::service->mStub->m_manager->wfdStateSync(state);
            Test_wfdService::service->mStub->m_manager->SetWfdState(state);
        }
    }
    TEST_F(Test_wfdServiceMgr,wfdGetRemoteInfo) {
        WFDRemoteDeviceInfo_Sp info(new WFDRemoteDeviceInfo);
        if(Test_wfdService::service->mStub) {
            Test_wfdService::service->mStub->m_manager->wfdGetRemoteInfo(info);
        }
    }
    TEST_F(Test_wfdServiceMgr,wfdSetLocalInfoData) {
        wfdLocalInfo info;
        memset(&info,0,sizeof(wfdLocalInfo));
        info.localIp = 10;
        info.localPort = 80;
        if(Test_wfdService::service->mStub) {
            Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        }
    }
    TEST_F(Test_wfdServiceMgr,wfdGetLocalInfoData) {
        wfdLocalInfo info;
        memset(&info,0,sizeof(wfdLocalInfo));
        if(Test_wfdService::service->mStub) {
            Test_wfdService::service->mStub->m_manager->wfdGetLocalInfoData(info);
        }
    }
    TEST_F(Test_wfdServiceMgr,wfdClearLocalInfoData) {
        Test_wfdService::service->mStub->m_manager->wfdClearLocalInfoData();
    }
    TEST_F(Test_wfdServiceMgr,getAll) {
        Test_wfdService::service->mStub->m_manager->getServiceReplier();
        cout << "*********************************getservicereplier***************************" << endl;
        Test_wfdService::service->mStub->m_manager->getSenderId();
        Test_wfdService::service->mStub->m_manager->getServiceStub();
        Test_wfdService::service->mStub->m_manager->getWFDLib();
        Test_wfdService::service->mStub->m_manager->getWFDSetting();
        Test_wfdService::service->mStub->m_manager->getMediaPlay();
    }
    TEST_F(Test_wfdServiceMgr,wfd_powerOn) {
        Test_wfdService::service->mStub->m_manager->wfd_powerOn();
    }
    TEST_F(Test_wfdServiceMgr,wfd_powerOff) {
        Test_wfdService::service->mStub->m_manager->wfd_powerOff();
    }
    TEST_F(Test_wfdServiceMgr,wfd_sourceChange) {
        SenderId id;
        uint8_t mode;
        WFDDeviceState_Sp state(new WFDDeviceState);
        state->setSvcState(WFD_CONNECTED);
        state->setSourceState(WFD_SOURCE_ON);
        Test_wfdService::service->mStub->m_manager->SetWfdState(state);
        Test_wfdService::service->mStub->m_manager->wfd_sourceChange(id,mode);
    }
    TEST_F(Test_wfdServiceMgr,wfd_mirrorMode) {
        SenderId id;
        MirrorMode mode = MIRROR;
        Test_wfdService::service->mStub->m_manager->wfd_mirrorMode(id,mode);
    }
    TEST_F(Test_wfdServiceMgr,wfd_SreenMode) {
        SenderId id;
        ScreenMode mode = Screen_Horizontal;
        Test_wfdService::service->mStub->m_manager->wfd_SreenMode(id,mode);
    }
    TEST_F(Test_wfdServiceMgr,wfd_startListen) {
        Test_wfdService::service->mStub->m_manager->wfd_startListen();
    }
#if 0
    TEST_F(Test_wfdServiceMgr,wfd_stopListen) {
        Test_wfdService::service->mStub->m_manager->wfd_stopListen();
    }
#endif
    TEST_F(Test_wfdServiceMgr,wfd_addWfdTag) {
        Test_wfdService::service->mStub->m_manager->wfd_addWfdTag();
    }
    TEST_F(Test_wfdServiceMgr,wfd_sendHardKey) {
        SenderId id;
        HardKey key =  MENU_DOWN;
        Test_wfdService::service->mStub->m_manager->wfd_sendHardKey(id,key);

    }
    TEST_F(Test_wfdServiceMgr,wfd_acceptInvitation) {
        SenderId id;
        bool accpet = 1;
        uint64_t addr = 0;
        Test_wfdService::service->mStub->m_manager->wfd_acceptInvitation(id,accpet,addr);
        accpet = 0;
        Test_wfdService::service->mStub->m_manager->wfd_acceptInvitation(id,accpet,addr);
    }
    TEST_F(Test_wfdServiceMgr,wfd_disconnect) {
        SenderId id;
        wfdLocalInfo info;
        info.p2pState = P2P_CONNECTED;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        Test_wfdService::service->mStub->m_manager->wfd_disconnect(id);
        info.p2pState = P2P_CONNECTING;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        Test_wfdService::service->mStub->m_manager->wfd_disconnect(id);
    }
    TEST_F(Test_wfdServiceMgr,wfd_getP2pState) {
        Test_wfdService::service->mStub->m_manager->wfd_getP2pState();
    }
    TEST_F(Test_wfdServiceMgr,wfd_p2pDisconnect) {
        wfdLocalInfo info;
        info.p2pState = P2P_CONNECTED;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        Test_wfdService::service->mStub->m_manager->wfd_p2pDisconnect();
    }
#if 0
    TEST_F(Test_wfdServiceMgr,wfd_getGPSTime) {
        SenderId id;
        Test_wfdService::service->mStub->m_manager->wfd_getGPSTime(id);
    }
#endif
    TEST_F(Test_wfdServiceMgr,onInvitationInd) {
        android::String8 devName;
        uint64_t macAddr;
        Test_wfdService::service->mStub->m_manager->onCarLifeOrCarPlayExtract();
        Test_wfdService::service->mStub->m_manager->onInvitationInd(devName,macAddr);
    }
    TEST_F(Test_wfdServiceMgr,onWFDServiceConnected) {
        uint32_t result = 1;
        Test_wfdService::service->mStub->m_manager->onWFDServiceConnected(result);
    }
    TEST_F(Test_wfdServiceMgr,onMsgReceived) {
        uint8_t code;
        WFDServiceMsg *msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,NULL);
        code = MSG_P2P_POWER;
        msg->setInt32Parameter(WIFI_POWER_STATE_POWER_ON);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
#if 0
        msg->setInt32Parameter(WIFI_POWER_STATE_POWER_OFF);
        state->setSvcState(WFD_CONNECTED);
        Test_wfdService::service->mStub->m_manager->SetWfdState(state);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        state->setSvcState(WFD_CONNECTING);
        Test_wfdService::service->mStub->m_manager->SetWfdState(state);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
#endif
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        code = MSG_P2P_CONNECT;
        msg->setInt32Parameter(WIFI_CONNECT_STATE_DISCONNECTTED);
        wfdLocalInfo info;
        info.p2pState = P2P_CONNECTED;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        WFDDeviceState_Sp state (new WFDDeviceState);
        state->setSvcState(WFD_CONNECTING);
        Test_wfdService::service->mStub->m_manager->SetWfdState(state);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
#if 0
        state->setSvcState(WFD_CONNECTED);
        Test_wfdService::service->mStub->m_manager->SetWfdState(state);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        info.p2pState = P2P_CONNECTING;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        info.p2pState = P2P_DISCONNECTING;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        msg->setInt32Parameter(WIFI_CONNECT_STATE_CONNECTTED);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
#endif
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        code = MSG_P2P_IP;
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void*)msg);
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        code = MSG_P2P_SIG;
        state->setSvcState(WFD_CONNECTED);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void*)msg);
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        code = MSG_P2P_LISTEN;
        msg->setInt32Parameter(0);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        msg->setInt32Parameter(1);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        code = MS_BT_CONNECT;
        msg->setInt32Parameter(0);
        msg->setUint16Value(0x01);
        state->setBt(0);
        Test_wfdService::service->mStub->m_manager->SetWfdState(state);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        code = MS_BT_DISCONNECT;
        msg->setInt32Parameter(0);
        msg->setUint16Value(0x01);
        state->setBt(0);
        Test_wfdService::service->mStub->m_manager->SetWfdState(state);
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        code = MS_CARLIFE_CARPLAY_INSERT;
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
        msg = new WFDServiceMsg(MN_EVT_POWERON_CMD);
        code = MS_CARLIFE_CARPLAY_EXTRACT;
        Test_wfdService::service->mStub->m_manager->onMsgReceived(code,(void *)msg);
    }
#if 0
    TEST_F(Test_wfdServiceMgr,onInputManagerConnected) {
        Test_wfdService::service->mStub->m_manager->onInputManagerConnected();
    }
#endif
    TEST_F(Test_wfdServiceMgr,onOneShotTimer) {
        Test_wfdService::service->mStub->m_manager->onOneShotTimer(NULL);
    }
    TEST_F(Test_wfdServiceMgr,wfdMgrHandler) {
        WFDServiceManager::WFDManagerHandler handler(Test_wfdService::service->mStub->m_manager);
        android::sp<Message> Msg = new WFDServiceMsg(MN_EVT_POWERON_CMD) ;
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_SOURCE_CHANGE);
        ((WFDServiceMsg*)Msg.get())->setMode(WFD_SOURCE_OFF);
        WFDDeviceState_Sp deviceState = new WFDDeviceState;
        deviceState->setSourceState(WFD_SOURCE_ON);
        Test_wfdService::service->mStub->m_manager->SetWfdState(deviceState);
        handler.onReceiveMessage(Msg);
        ((WFDServiceMsg*)Msg.get())->setMode(WFD_SOURCE_ON);
        deviceState->setSourceState(WFD_SOURCE_OFF);
        deviceState->setSvcState(WFD_CONNECTED);
        Test_wfdService::service->mStub->m_manager->SetWfdState(deviceState);
        handler.onReceiveMessage(Msg);
        ((WFDServiceMsg*)Msg.get())->setMode(WFD_SOURCE_ON);
        deviceState->setSourceState(WFD_SOURCE_ON);
        Test_wfdService::service->mStub->m_manager->SetWfdState(deviceState);
        handler.onReceiveMessage(Msg);
        ((WFDServiceMsg*)Msg.get())->setMode(WFD_SOURCE_OFF);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_MIRROR_MODE);
        ((WFDServiceMsg*)Msg.get())->setInt32Parameter(MIRROR);
        handler.onReceiveMessage(Msg);
        ((WFDServiceMsg*)Msg.get())->setInt32Parameter(APP);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_SCREEN_MODE);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_START_LISTEN);
        deviceState->setSvcState(WFD_POWER_OFF);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_STOP_LISTEN);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_ADD_TAG);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_START_SEARCH);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_ACCEPT_INVITATION);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_DISCONNECT);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_GET_P2P_SATE);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_WFD_START);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_WFD_DISCONECT);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_APP_HARDKEY);
        wfdLocalInfo info;
        info.appMode = APP;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        ((WFDServiceMsg*)Msg.get())->setInt32Parameter(PRE_TRACK_DOWN);
        handler.onReceiveMessage(Msg);
        ((WFDServiceMsg*)Msg.get())->setInt32Parameter(BACK_DOWN);
        handler.onReceiveMessage(Msg);
        ((WFDServiceMsg*)Msg.get())->setInt32Parameter(HOME_DOWN);
        handler.onReceiveMessage(Msg);
        info.appMode = MIRROR;
        Test_wfdService::service->mStub->m_manager->wfdSetLocalInfoData(info);
        ((WFDServiceMsg*)Msg.get())->setInt32Parameter(PRE_TRACK_DOWN);
        handler.onReceiveMessage(Msg);
        ((WFDServiceMsg*)Msg.get())->setInt32Parameter(BACK_DOWN);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_WFD_PLAY);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_WFD_PAUSE);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_POWEROFF_CMD);
        deviceState->setSvcState(WFD_POWER_OFF);
        handler.onReceiveMessage(Msg);
        deviceState->setSvcState(WFD_CONNECTED);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_WFD_IDR);
        handler.onReceiveMessage(Msg);
        Msg = new WFDServiceMsg(MN_EVT_APP_GPSTIME);
        handler.onReceiveMessage(Msg);
    }
    TEST_F(Test_wfdServiceMgr,wfd_startSearch) {
        Test_wfdService::service->mStub->m_manager->wfd_startSearch(0);
        Test_wfdService::service->mStub->m_manager->wfd_stopSearch(1);
    }
    TEST_F(Test_wfdServiceMgr,onPlayerErr) {
        Test_wfdService::service->mStub->m_manager->onPlayerErr();
    }
    TEST_F(Test_wfdServiceMgr,wfd_play) {
        Test_wfdService::service->mStub->m_manager->wfd_play();
    }
    TEST_F(Test_wfdServiceMgr,wfd_pause) {
        Test_wfdService::service->mStub->m_manager->wfd_pause();
    }
    TEST_F(Test_wfdServiceMgr,onCarLifeOrCarPlayInsert) {
        Test_wfdService::service->mStub->m_manager->onCarLifeOrCarPlayInsert();
    }
    TEST_F(Test_wfdServiceMgr,onCarLifeOrCarPlayExtract) {
        Test_wfdService::service->mStub->m_manager->onCarLifeOrCarPlayExtract();
    }
    TEST_F(Test_wfdServiceMgr,onInputManagerConnected) {
        Test_wfdService::service->mStub->m_manager->onInputManagerConnected();
    }
}

