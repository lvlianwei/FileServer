/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: aidl/IConnectManager.aidl
 */
#include "testConnectManagerProxyBase.h"
#include "binder/Parcel.h"

namespace goni {
    SingletonSmtIConnectManagerProxy::SingletonSmtIConnectManagerProxy(){
    }


    SingletonSmtIConnectManagerProxy* SingletonSmtIConnectManagerProxy::instance = NULL;
    SingletonSmtIConnectManagerProxy* SingletonSmtIConnectManagerProxy::getInstance(){
        if (NULL == instance)
        {
            instance = new SingletonSmtIConnectManagerProxy();
        }
        return instance;
    }
    void SingletonSmtIConnectManagerProxy::delInstance(){
        if (NULL != instance)
        {
            delete instance;
            instance = NULL;
        }
    }
    ConnectManagerProxyBase::ConnectManagerProxyBase(IConnectManagerProxyReplier* replier, bool autoConnect)
        : ServiceProxyBase("ConnectManager", true, autoConnect)
          , m_replier(replier)
    {
    }
    ConnectManagerProxyBase::~ConnectManagerProxyBase()
    {
    }
    void ConnectManagerProxyBase::onConnected()
    {
        ServiceProxyBase::onConnected();
        m_replier->onConnected();
    }
    void ConnectManagerProxyBase::onDisconnected()
    {
        ServiceProxyBase::onDisconnected();
        m_replier->onDisconnected();
    }

    android::status_t ConnectManagerProxyBase::func(const int32_t& a, HFP_DIAL_RESULT& b)
    {
        android::Parcel data, _data;
        _data.writeInt32(a);
        int ret = sendSyncRequest(METHOD_FUNC, _data, &data);
        if (ret == BS_NO_ERROR) {
            b = static_cast<HFP_DIAL_RESULT>(data.readInt32());
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::cmd(const int32_t& a, const int32_t& b)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeInt32(a);
        _data.writeInt32(b);
        return sendAsyncRequest(COMMAND_CMD, _data);
    }
    android::status_t ConnectManagerProxyBase::getIpodInfo(IPOD_DEVICE_TYPE& type, IpodInfo_Sp& info)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_IPOD_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            type = static_cast<IPOD_DEVICE_TYPE>(data.readInt32());
            info->readFromParcel(data);
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getUsbInfo(STORAGE_DEVICE_TYPE& type, StorageInfo_Sp& info)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_USB_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            type = static_cast<STORAGE_DEVICE_TYPE>(data.readInt32());
            info->readFromParcel(data);
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getAoaDevInfo(bool& isInsert)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_AOA_DEV_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            isInsert = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getAoaSndInfo(android::String8& pcm)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_AOA_SND_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            pcm = data.readString8();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::setAppSourceStatus(const bool& isSourceOn)
    {
        android::Parcel data, _data;
        _data.writeInt32(isSourceOn);
        int ret = sendSyncRequest(METHOD_SET_APP_SOURCE_STATUS, _data, &data);
        if (ret == BS_NO_ERROR) {
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::registerProxy(const PROXY_TYPE& type)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeInt32(static_cast<PROXY_TYPE>(type));
        return sendAsyncRequest(COMMAND_REGISTER_PROXY, _data);
    }
    android::status_t ConnectManagerProxyBase::ipodCloseResult(const CON_MGR_RESULT& res)
    {
        android::Parcel data, _data;
        _data.writeInt32(static_cast<CON_MGR_RESULT>(res));
        int ret = sendSyncRequest(METHOD_IPOD_CLOSE_RESULT, _data, &data);
        if (ret == BS_NO_ERROR) {
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::iapAuthResult(const IPOD_DEVICE_TYPE& type, const CON_MGR_RESULT& res)
    {
        android::Parcel data, _data;
        _data.writeInt32(static_cast<IPOD_DEVICE_TYPE>(type));
        _data.writeInt32(static_cast<CON_MGR_RESULT>(res));
        int ret = sendSyncRequest(METHOD_IAP_AUTH_RESULT, _data, &data);
        if (ret == BS_NO_ERROR) {
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::iapSetDevName(const android::String8& devName)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeString8(devName);
        return sendAsyncRequest(COMMAND_IAP_SET_DEV_NAME, _data);
    }
    android::status_t ConnectManagerProxyBase::carplayAuthResult(const CON_MGR_RESULT& res)
    {
        android::Parcel data, _data;
        _data.writeInt32(static_cast<CON_MGR_RESULT>(res));
        int ret = sendSyncRequest(METHOD_CARPLAY_AUTH_RESULT, _data, &data);
        if (ret == BS_NO_ERROR) {
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::carlifeAppLaunch()
    {
        printf("-------桩----------ConnectManagerProxyBase::carlifeAppLaunch---------------\n");;
        android::Parcel _data;
        prepareAsyncData(_data);
        return sendAsyncRequest(COMMAND_CARLIFE_APP_LAUNCH, _data);
    }
    android::status_t ConnectManagerProxyBase::carlifeEapStartConnect()
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        return sendAsyncRequest(COMMAND_CARLIFE_EAP_START_CONNECT, _data);
    }
    android::status_t ConnectManagerProxyBase::carlifeEapAuthResult(const CARLIFE_EAP_AUTH_RESULT& res)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeInt32(static_cast<CARLIFE_EAP_AUTH_RESULT>(res));
        return sendAsyncRequest(COMMAND_CARLIFE_EAP_AUTH_RESULT, _data);
    }
    android::status_t ConnectManagerProxyBase::debug_resetAoa()
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_DEBUG_RESET_AOA, _data, &data);
        if (ret == BS_NO_ERROR) {
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::closeDataConn()
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        return sendAsyncRequest(COMMAND_CLOSE_DATA_CONN, _data);
    }
    android::status_t ConnectManagerProxyBase::resetUsb()
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        return sendAsyncRequest(COMMAND_RESET_USB, _data);
    }
    android::status_t ConnectManagerProxyBase::launchAndroidSource(const ANDROID_SOURCE_TYPE& type)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeInt32(static_cast<ANDROID_SOURCE_TYPE>(type));
        return sendAsyncRequest(COMMAND_LAUNCH_ANDROID_SOURCE, _data);
    }
    android::status_t ConnectManagerProxyBase::getAndroidDevInfo(bool& isConnected, android::String8& serialNum)
    {
        printf("------------------桩--------ConnectManagerProxyBase::getAndroidDevInfo---------\n");
        (SingletonSmtIConnectManagerProxy::getInstance())->getAndroidDevInfo(isConnected,serialNum);
        return 1;
    }
    android::status_t ConnectManagerProxyBase::launchIosSource(const IOS_SOURCE_TYPE& type)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeInt32(static_cast<IOS_SOURCE_TYPE>(type));
        return sendAsyncRequest(COMMAND_LAUNCH_IOS_SOURCE, _data);
    }
    android::status_t ConnectManagerProxyBase::getIosDevConnStatus(bool& isConnected, int32_t& index, IOS_POPUP_STATUS& sts)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_IOS_DEV_CONN_STATUS, _data, &data);
        if (ret == BS_NO_ERROR) {
            isConnected = data.readInt32();
            index = data.readInt32();
            sts = static_cast<IOS_POPUP_STATUS>(data.readInt32());
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getIosDevInfo(bool& isConnected, bool& isCarplaySupp, android::String8& serialNum)
    {
        printf("------------------桩--------ConnectManagerProxyBase::getIosDevInfo---------\n");
        (SingletonSmtIConnectManagerProxy::getInstance())->getIosDevInfo(isConnected,isCarplaySupp,serialNum);
        return 1;
    }
    android::status_t ConnectManagerProxyBase::enableUsbSource(const USB_SOURCE_TYPE& type)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeInt32(static_cast<USB_SOURCE_TYPE>(type));
        return sendAsyncRequest(COMMAND_ENABLE_USB_SOURCE, _data);
    }
    android::status_t ConnectManagerProxyBase::disableUsbSource(const USB_SOURCE_TYPE& type)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeInt32(static_cast<USB_SOURCE_TYPE>(type));
        return sendAsyncRequest(COMMAND_DISABLE_USB_SOURCE, _data);
    }
    android::status_t ConnectManagerProxyBase::getUnsupportType(UNSUPPORT_USB_TYPE& port1Type, UNSUPPORT_USB_TYPE& port2Type)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_UNSUPPORT_TYPE, _data, &data);
        if (ret == BS_NO_ERROR) {
            port1Type = static_cast<UNSUPPORT_USB_TYPE>(data.readInt32());
            port2Type = static_cast<UNSUPPORT_USB_TYPE>(data.readInt32());
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getUsbDevInfo(STORAGE_DEVICE_TYPE& type, StorageInfo_Sp& info, bool& isLastOn)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_USB_DEV_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            type = static_cast<STORAGE_DEVICE_TYPE>(data.readInt32());
            info->readFromParcel(data);
            isLastOn = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getCarlifeDevInfo(CARLIFE_TYPE& type, bool& isInsert, bool& isLastOn)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_CARLIFE_DEV_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            type = static_cast<CARLIFE_TYPE>(data.readInt32());
            isInsert = data.readInt32();
            isLastOn = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getAapDevInfo(bool& isInsert, bool& isLastOn)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_AAP_DEV_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            isInsert = data.readInt32();
            isLastOn = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getIapDevInfo(IpodInfo_Sp& info, bool& isHostMode)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_IAP_DEV_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            info->readFromParcel(data);
            isHostMode = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getIpodDevInfo(IPOD_AUTH_STATE& authState, bool& isLastOn)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_IPOD_DEV_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            authState = static_cast<IPOD_AUTH_STATE>(data.readInt32());
            isLastOn = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getIpodDeviceInfo(IpodInfo_Sp& info, IPOD_AUTH_STATE& authState, bool& isLastOn)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_IPOD_DEVICE_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            info->readFromParcel(data);
            authState = static_cast<IPOD_AUTH_STATE>(data.readInt32());
            isLastOn = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getIpodDevStatus(IpodInfo_Sp& info, IPOD_AUTH_STATE& authState, bool& isLastOn, USB_CHECK_STATUS& usbSts)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_IPOD_DEV_STATUS, _data, &data);
        if (ret == BS_NO_ERROR) {
            info->readFromParcel(data);
            authState = static_cast<IPOD_AUTH_STATE>(data.readInt32());
            isLastOn = data.readInt32();
            usbSts = static_cast<USB_CHECK_STATUS>(data.readInt32());
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getCarplayInfo(IPOD_AUTH_STATE& authState, bool& isLastOn)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_CARPLAY_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            authState = static_cast<IPOD_AUTH_STATE>(data.readInt32());
            isLastOn = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::getCarplayDevInfo(IpodInfo_Sp& info, IPOD_AUTH_STATE& authState, bool& isLastOn)
    {
        android::Parcel data, _data;
        int ret = sendSyncRequest(METHOD_GET_CARPLAY_DEV_INFO, _data, &data);
        if (ret == BS_NO_ERROR) {
            info->readFromParcel(data);
            authState = static_cast<IPOD_AUTH_STATE>(data.readInt32());
            isLastOn = data.readInt32();
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::remountUsbDevice(const int32_t& port)
    {
        android::Parcel data, _data;
        _data.writeInt32(port);
        int ret = sendSyncRequest(METHOD_REMOUNT_USB_DEVICE, _data, &data);
        if (ret == BS_NO_ERROR) {
        }
        return ret;
    }
    android::status_t ConnectManagerProxyBase::androidSetDevName(const android::String8& devName)
    {
        android::Parcel _data;
        prepareAsyncData(_data);
        _data.writeString8(devName);
        return sendAsyncRequest(COMMAND_ANDROID_SET_DEV_NAME, _data);
    }
    int ConnectManagerProxyBase::onAsyncResponse(unsigned int code, const android::Parcel &data)
    {
        switch(code) {
            case NOTIFY_NOTIFY:
                {
                    int32_t a = data.readInt32();
                    int32_t b = data.readInt32();
                    m_replier->notify(a, b);
                    break;
                }
            case NOTIFY_NOTIFY_IPOD_INSERT:
                {
                    IpodInfo_Sp info(new IpodInfo);
                    info->readFromParcel(data);
                    m_replier->notify_ipodInsert(info);
                    break;
                }
            case NOTIFY_NOTIFY_IPOD_EXTRACT:
                {
                    m_replier->notify_ipodExtract();
                    break;
                }
            case NOTIFY_NOTIFY_IPOD_ROLE_SWITCH:
                {
                    USB_ROLE_TYPE type = static_cast<USB_ROLE_TYPE>(data.readInt32());
                    m_replier->notify_ipodRoleSwitch(type);
                    break;
                }
            case NOTIFY_NOTIFY_CARLIFE_INSERT:
                {
                    CARLIFE_TYPE type = static_cast<CARLIFE_TYPE>(data.readInt32());
                    m_replier->notify_carlifeInsert(type);
                    break;
                }
            case NOTIFY_NOTIFY_CARLIFE_AOA_SWITCH:
                {
                    CON_MGR_RESULT res = static_cast<CON_MGR_RESULT>(data.readInt32());
                    m_replier->notify_carlifeAoaSwitch(res);
                    break;
                }
            case NOTIFY_NOTIFY_CARLIFE_EAP_AUTH_RESULT:
                {
                    CON_MGR_RESULT res = static_cast<CON_MGR_RESULT>(data.readInt32());
                    m_replier->notify_carlifeEapAuthResult(res);
                    break;
                }
            case NOTIFY_NOTIFY_CARLIFE_EXTRACT:
                {
                    CARLIFE_TYPE type = static_cast<CARLIFE_TYPE>(data.readInt32());
                    m_replier->notify_carlifeExtract(type);
                    break;
                }
            case NOTIFY_NOTIFY_AAP_AOA_SWITCH:
                {
                    CON_MGR_RESULT res = static_cast<CON_MGR_RESULT>(data.readInt32());
                    m_replier->notify_aapAoaSwitch(res);
                    break;
                }
            case NOTIFY_NOTIFY_AAP_EXTRACT:
                {
                    CARLIFE_TYPE type = static_cast<CARLIFE_TYPE>(data.readInt32());
                    m_replier->notify_aapExtract(type);
                    break;
                }
            case NOTIFY_NOTIFY_EA_SESSION_STATUS_CHANGED:
                {
                    bool isStart = data.readInt32();
                    m_replier->notify_eaSessionStatusChanged(isStart);
                    break;
                }
            case NOTIFY_NOTIFY_USB_MOUNT:
                {
                    StorageInfo_Sp info(new StorageInfo);
                    info->readFromParcel(data);
                    m_replier->notify_usbMount(info);
                    break;
                }
            case NOTIFY_NOTIFY_USB_UNMOUNT:
                {
                    StorageInfo_Sp info(new StorageInfo);
                    info->readFromParcel(data);
                    m_replier->notify_usbUnmount(info);
                    break;
                }
            case NOTIFY_NOTIFY_USB_BAD_REMOVAL:
                {
                    StorageInfo_Sp info(new StorageInfo);
                    info->readFromParcel(data);
                    m_replier->notify_usbBadRemoval(info);
                    break;
                }
            case NOTIFY_NOTIFY_HUB_INSERT:
                {
                    m_replier->notify_hubInsert();
                    break;
                }
            case NOTIFY_NOTIFY_HUB_EXTRACT:
                {
                    m_replier->notify_hubExtract();
                    break;
                }
            case NOTIFY_NOTIFY_OVER_CURRENT:
                {
                    m_replier->notify_overCurrent();
                    break;
                }
            case NOTIFY_NOTIFY_IAP2AUTH_RESULT:
                {
                    CON_MGR_RESULT res = static_cast<CON_MGR_RESULT>(data.readInt32());
                    m_replier->notify_iap2AuthResult(res);
                    break;
                }
            case NOTIFY_NOTIFY_IAP_AUTH_RESULT:
                {
                    IPOD_DEVICE_TYPE type = static_cast<IPOD_DEVICE_TYPE>(data.readInt32());
                    m_replier->notify_iapAuthResult(type);
                    break;
                }
            case NOTIFY_NOTIFY_CARPLAY_AUTH_RESULT:
                {
                    CON_MGR_RESULT res = static_cast<CON_MGR_RESULT>(data.readInt32());
                    m_replier->notify_carplayAuthResult(res);
                    break;
                }
            case NOTIFY_NOTIFY_USB_CHECK_STATUS:
                {
                    USB_CHECK_STATUS sts = static_cast<USB_CHECK_STATUS>(data.readInt32());
                    m_replier->notify_usbCheckStatus(sts);
                    break;
                }
        }
        return 0;
    }
}
/* EOF */
