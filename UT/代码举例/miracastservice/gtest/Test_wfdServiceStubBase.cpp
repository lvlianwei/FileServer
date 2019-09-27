#include"servicebase/ServiceBase.h"
#include<gtest/gtest.h>
#include "proxy/WFDServiceProxyBase.h"
#define private public
#include "stub/WFDServiceStubBase.h"
namespace goni {
    class myBase : public WFDServiceStubBase {
        public:
            myBase():WFDServiceStubBase(new ServiceBase("base")){}
            ~myBase(){}
        protected:
            virtual android::status_t wfdStateSync(WFDDeviceState_Sp& deviceState){return 0;}
            virtual android::status_t wfdGetRemoteInfo(WFDRemoteDeviceInfo_Sp& remoteInfo){return 0;}
            virtual android::status_t wfdGetLocalDevice(uint16_t& nameLen, uint8_t& name){return 0;}
            virtual android::status_t wfd_powerOn(SenderId id){return 0;}
            virtual android::status_t wfd_powerOff(SenderId id){return 0;}
            virtual android::status_t wfd_sourceChange(SenderId id, const uint8_t& mode){return 0;}
            virtual android::status_t wfd_mirrorMode(SenderId id, const MirrorMode& mode){return 0;}
            virtual android::status_t wfd_SreenMode(SenderId id, const ScreenMode& mode){return 0;}
            virtual android::status_t wfd_getGPSTime(SenderId id) {return 0;}
            virtual android::status_t wfd_sendHardKey(SenderId id, const HardKey& key) {return 0;}
            virtual android::status_t wfd_startSearch(SenderId id) {return 0;}
            virtual android::status_t wfd_stopSearch(SenderId id) {return 0;}
            virtual android::status_t wfd_acceptInvitation(SenderId id, const bool& accpet){return 0;}
            virtual android::status_t wfd_disconnect(SenderId id){return 0;}
            virtual android::status_t wfd_enableWfd(SenderId id) {return 0;}
            virtual android::status_t wfd_disableWfd(SenderId id){ return 0;}
            virtual android::status_t wfd_sendUIBCData(SenderId id, const TouchType& type, const TouchPoints_SpVec& points){return 0;}
            virtual android::status_t wfd_play(SenderId id){return 0;}
            virtual android::status_t wfd_pause(SenderId id){return 0;}
    };
    TEST(Test_wfdServiceStubBase,wfdAppStatus) {
        myBase base;
        base.wfdAppStatus(1);
        base.wfdAppStatus(0);
        base.wfdPowerStatus(1);
        base.wfdPowerStatus(0);
        WFDDeviceInfo_Sp info = new WFDDeviceInfo;
        base.wfdInvitationInd(info);
        base.wfdConnectResultInd(1);
        base.wfdConnectResultInd(0);
        base.wfdDisconnectInd(1);
        base.wfdDisconnectInd(0);
        base.wfdBtStatus(0,1);
        base.wfdBtStatus(1,1);
        base.wfdStartListenInd(1);
        base.wfdStartListenInd(0);
        base.wfdMacAddr(0,0);
        base.wfdMacAddr(1,2);
        base.wfdRemotePixesInfo(WFD_POWER_OFF,0,0);
        base.wfdRemotePixesInfo(WFD_POWER_OFF,-1,-100);
        base.wfdRemotePixesInfo(WFD_POWER_OFF,100,100);
        base.wfdRemoteSrceenChange(1,Screen_Horizontal);
        base.wfdRemoteSrceenChange(0,Screen_Horizontal);
        base.wfdHIDPoint(1,-1,-1);
        base.wfdHIDPoint(0,100,100);
        base.wfdHardkey(HOME_DOWN);
        base.wfdHardkey(HOME_DOWN);
        base.wfdModeChangeCfm(0);
        base.wfdModeChangeCfm(1);
        base.wfdReceiverId(0,1);
        base.wfdReceiverId(1,1);
        base.wfdAppDeskInd(1);
        base.wfdAppDeskInd(0);
        base.wfdModeChangeReq(1);
        base.wfdModeChangeReq(0);
        base.wfdLinkQuiltyInd(0);
    }
    TEST(Test_wfdServiceStubBase,onSyncRequest) {
        myBase base;
        unsigned int code;
        android::Parcel data;
        android::Parcel _data;
        code = WFDServiceProxyBase::METHOD_WFD_STATE_SYNC;
        base.onSyncRequest(code,data,_data);
        code = WFDServiceProxyBase::METHOD_WFD_GET_REMOTE_INFO;
        base.onSyncRequest(code,data,_data);
        code = WFDServiceProxyBase::METHOD_WFD_GET_LOCAL_DEVICE;
        base.onSyncRequest(code,data,_data);
    }
    TEST(Test_wfdServiceStubBase,onAsyncRequest) {
        myBase base;
        SenderId id;
        unsigned int code;
        android::Parcel data;
        code = WFDServiceProxyBase::COMMAND_WFD_POWER_ON;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_POWER_OFF;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_SOURCE_CHANGE;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_MIRROR_MODE;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_SREEN_MODE;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_GET_GPSTIME;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_SEND_HARD_KEY;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_START_SEARCH;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_STOP_SEARCH;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_ACCEPT_INVITATION;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_DISCONNECT;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_ENABLE_WFD;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_DISABLE_WFD;
        base.onAsyncRequest(id,code,data);
        code = WFDServiceProxyBase::COMMAND_WFD_SEND_UIBCDATA;
        base.onAsyncRequest(id,code,data);
    }
}
