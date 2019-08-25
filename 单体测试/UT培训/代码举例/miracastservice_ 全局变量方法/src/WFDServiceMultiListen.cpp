#include "WFDServiceMsg.h"
#include "WFDServiceMultiListen.h"
#include "WFDServiceDefs.h"
#include "wfdServiceStub.h"
#include "servicebase/SystemLog.h"

namespace goni{
DeclearModuleID(DTMODULEID_WFDSERVICE);
WFDMultiListener::WFDMultiListener(WFDServiceStub* stub)         /* __0x005000_DTFUNCID__ */
:mStub(stub)
{
}

WFDMultiListener::~WFDMultiListener()         /* __0x005001_DTFUNCID__ */
{
}

android::status_t WFDMultiListener::p2pPowerStatusNotify(const WIFI_POWER_STATE_E& powerStatus)          /* __0x005002_DTFUNCID__ */
{
    MCLOGD("WFDMultiListener::p2pPowerStatusNotify");
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        msg->setInt32Parameter(powerStatus);
        mStub->onMultiListen(MSG_P2P_POWER, reinterpret_cast<void*>(msg));
        }
    return 0;
}

android::status_t WFDMultiListener::p2pConnectStatusNotify(const WIFI_CONNECT_STATE_E& connStatus)            /* __0x005003_DTFUNCID__ */
{
    MCLOGD("WFDMultiListener::p2pConnectStatusNotify");
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        msg->setInt32Parameter(connStatus);
        mStub->onMultiListen(MSG_P2P_CONNECT, reinterpret_cast<void*>(msg));
    }
    return 0;
}

android::status_t WFDMultiListener::p2pConnectedInfoNotify(const uint16_t& remotePort, const uint32_t& remoteIP, const uint32_t& localIP)         /* __0x005004_DTFUNCID__ */
{
    MCLOGD("WFDMultiListener::p2pConnectedInfoNotify, remotePort = %d, remoteIp = %x", remotePort, remoteIP);
    DTLOG_INFO(0x005004, "p2pConnectedInfoNotify remotePort = %d remoteIp = %x", remotePort, remoteIP);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        msg->setLocalIP(localIP);
        msg->setRemoteIP(remoteIP);
        msg->setRemotePort(remotePort);
        mStub->onMultiListen(MSG_P2P_IP, reinterpret_cast<void*>(msg));
    }
    return 0;
}

android::status_t WFDMultiListener::p2pLinkQuiltyNotify(const int32_t& sigStrength)         /* __0x005005_DTFUNCID__ */
{
    MCLOGD("WFDMultiListener::p2pLinkQuiltyNotify");
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        msg->setInt32Parameter(sigStrength);
        mStub->onMultiListen(MSG_P2P_SIG, reinterpret_cast<void*>(msg));
    }
    return 0;
}

android::status_t WFDMultiListener::p2pListenStatusNotify(const WIFI_LISTEN_STATUS_E& status)         /* __0x005006_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        msg->setInt32Parameter(status);
        mStub->onMultiListen(MSG_P2P_LISTEN, reinterpret_cast<void*>(msg));
    }
    return 0;
}

#if 0
android::status_t WFDMultiListener::staConnectStatusNotify(const WIFI_CONNECT_STATE_E& connStatus)
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    return 0;
}

android::status_t WFDMultiListener::staConnectedInfoNotify(const uint16_t& localPort, const uint32_t& remoteIP, const uint32_t& localIP)
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        msg->setLocalIP(localIP);
        msg->setRemoteIP(remoteIP);
        msg->setRemotePort(localPort);
        mStub->onMultiListen(MSG_STA_IP, reinterpret_cast<void*>(msg));
    }
    return 0;
}
#endif

android::status_t WFDMultiListener::genOnConnectionChanged(const uint8_t& index, const uint64_t& addr, const android::String8& name, const BT_FUNCTION_E& function, const uint32_t& result)   /* __0x005007_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        msg->setUint16Value((uint16_t)function);
        msg->setInt32Parameter(result);
        msg->setU64Parameter(addr);
        mStub->onMultiListen(MS_BT_CONNECT, reinterpret_cast<void*>(msg));
        }
    return 0;
}

android::status_t WFDMultiListener::genOnDisconnectionChanged(const uint8_t& index, const uint64_t& addr, const android::String8& name, const BT_FUNCTION_E& function, const uint32_t& result)   /* __0x005008_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        msg->setUint16Value((uint16_t)function);
        msg->setInt32Parameter(result);
        msg->setU64Parameter(addr);
        mStub->onMultiListen(MS_BT_DISCONNECT, reinterpret_cast<void*>(msg));
        }
    return 0;
}

android::status_t WFDMultiListener::connectStatusReady()          /* __0x005009_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        // WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        // mStub->onMultiListen(MS_CARLIFE_CARPLAY_INSERT, reinterpret_cast<void*>(msg));
        }
    return 0;

}

android::status_t WFDMultiListener::connectStatusExtract()         /* __0x00500A_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        // WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        // mStub->onMultiListen(MS_CARLIFE_CARPLAY_EXTRACT, reinterpret_cast<void*>(msg));
        }
    return 0;
}


android::status_t WFDMultiListener::CarplayAuthSuccess()           /* __0x00500B_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        // WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        // mStub->onMultiListen(MS_CARLIFE_CARPLAY_INSERT, reinterpret_cast<void*>(msg));
        }
    return 0;
}

android::status_t WFDMultiListener::CarplayExtract()         /* __0x00500C_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    if (mStub != NULL) {
        // WFDServiceMsg* msg = new WFDServiceMsg(MN_EVT_MULTI_MSG);
        // mStub->onMultiListen(MS_CARLIFE_CARPLAY_EXTRACT, reinterpret_cast<void*>(msg));
        }
    return 0;
}


}
