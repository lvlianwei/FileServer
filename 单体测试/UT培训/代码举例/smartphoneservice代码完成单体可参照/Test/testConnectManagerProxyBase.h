/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: aidl/IConnectManager.aidl
 */
#ifndef TEST_GONI_CONNECT_MANAGER_PROXY_BASE_H
#define TEST_GONI_CONNECT_MANAGER_PROXY_BASE_H

#include "servicebase/ServiceProxyBase.h"
#include "servicebase/ServiceBaseDefines.h"

#include "servicebase/ServiceBaseGlobal.h"
#include "ConnectManagerServiceDefines.h"
#include "UsbInfo.h"
#include "IpodInfo.h"
#include "StorageInfo.h"
#include "AndroidInfo.h"
#include<gtest/gtest.h>
#include<gmock/gmock.h>
namespace goni {

    class IConnectManagerProxyReplier
    {
        public:
            virtual ~IConnectManagerProxyReplier() {}

            virtual void onConnected() {}

            virtual void onDisconnected() {}

            virtual android::status_t notify(const int32_t& a, const int32_t& b) { return 0; }
            virtual android::status_t notify_ipodInsert(const IpodInfo_Sp& info) { return 0; }
            virtual android::status_t notify_ipodExtract() { return 0; }
            virtual android::status_t notify_ipodRoleSwitch(const USB_ROLE_TYPE& type) { return 0; }
            virtual android::status_t notify_carlifeInsert(const CARLIFE_TYPE& type) { return 0; }
            virtual android::status_t notify_carlifeAoaSwitch(const CON_MGR_RESULT& res) { return 0; }
            virtual android::status_t notify_carlifeEapAuthResult(const CON_MGR_RESULT& res) { return 0; }
            virtual android::status_t notify_carlifeExtract(const CARLIFE_TYPE& type) { return 0; }
            virtual android::status_t notify_aapAoaSwitch(const CON_MGR_RESULT& res) { return 0; }
            virtual android::status_t notify_aapExtract(const CARLIFE_TYPE& type) { return 0; }
            virtual android::status_t notify_eaSessionStatusChanged(const bool& isStart) { return 0; }
            virtual android::status_t notify_usbMount(const StorageInfo_Sp& info) { return 0; }
            virtual android::status_t notify_usbUnmount(const StorageInfo_Sp& info) { return 0; }
            virtual android::status_t notify_usbBadRemoval(const StorageInfo_Sp& info) { return 0; }
            virtual android::status_t notify_hubInsert() { return 0; }
            virtual android::status_t notify_hubExtract() { return 0; }
            virtual android::status_t notify_overCurrent() { return 0; }
            virtual android::status_t notify_iap2AuthResult(const CON_MGR_RESULT& res) { return 0; }
            virtual android::status_t notify_iapAuthResult(const IPOD_DEVICE_TYPE& type) { return 0; }
            virtual android::status_t notify_carplayAuthResult(const CON_MGR_RESULT& res) { return 0; }
            virtual android::status_t notify_usbCheckStatus(const USB_CHECK_STATUS& sts) { return 0; }
    };
    class SingletonSmtIConnectManagerProxy{
        public:
            static SingletonSmtIConnectManagerProxy* getInstance();
            static void delInstance();
            MOCK_METHOD2(getAndroidDevInfo,android::status_t(bool& , android::String8& ));
            MOCK_METHOD3(getIosDevInfo,android::status_t(bool& , bool& , android::String8& ));
        private:
            SingletonSmtIConnectManagerProxy();
            static SingletonSmtIConnectManagerProxy* instance;
    };
    class ConnectManagerProxyBase : public ServiceProxyBase
    {
        public:
            enum Method_Code
            {
                METHOD_FUNC = SERVICE_FIRST_TRANSACTION,
                METHOD_GET_IPOD_INFO,
                METHOD_GET_USB_INFO,
                METHOD_GET_AOA_DEV_INFO,
                METHOD_GET_AOA_SND_INFO,
                METHOD_SET_APP_SOURCE_STATUS,
                METHOD_IPOD_CLOSE_RESULT,
                METHOD_IAP_AUTH_RESULT,
                METHOD_CARPLAY_AUTH_RESULT,
                METHOD_DEBUG_RESET_AOA,
                METHOD_GET_ANDROID_DEV_INFO,
                METHOD_GET_IOS_DEV_CONN_STATUS,
                METHOD_GET_IOS_DEV_INFO,
                METHOD_GET_UNSUPPORT_TYPE,
                METHOD_GET_USB_DEV_INFO,
                METHOD_GET_CARLIFE_DEV_INFO,
                METHOD_GET_AAP_DEV_INFO,
                METHOD_GET_IAP_DEV_INFO,
                METHOD_GET_IPOD_DEV_INFO,
                METHOD_GET_IPOD_DEVICE_INFO,
                METHOD_GET_IPOD_DEV_STATUS,
                METHOD_GET_CARPLAY_INFO,
                METHOD_GET_CARPLAY_DEV_INFO,
                METHOD_REMOUNT_USB_DEVICE,

                METHOD_MAX
            };

            enum Command_Code
            {
                COMMAND_CMD = METHOD_MAX,
                COMMAND_REGISTER_PROXY,
                COMMAND_IAP_SET_DEV_NAME,
                COMMAND_CARLIFE_APP_LAUNCH,
                COMMAND_CARLIFE_EAP_START_CONNECT,
                COMMAND_CARLIFE_EAP_AUTH_RESULT,
                COMMAND_CLOSE_DATA_CONN,
                COMMAND_RESET_USB,
                COMMAND_LAUNCH_ANDROID_SOURCE,
                COMMAND_LAUNCH_IOS_SOURCE,
                COMMAND_ENABLE_USB_SOURCE,
                COMMAND_DISABLE_USB_SOURCE,
                COMMAND_ANDROID_SET_DEV_NAME,

                COMMAND_MAX
            };

            enum Notify_Code
            {
                NOTIFY_NOTIFY = COMMAND_MAX,
                NOTIFY_NOTIFY_IPOD_INSERT,
                NOTIFY_NOTIFY_IPOD_EXTRACT,
                NOTIFY_NOTIFY_IPOD_ROLE_SWITCH,
                NOTIFY_NOTIFY_CARLIFE_INSERT,
                NOTIFY_NOTIFY_CARLIFE_AOA_SWITCH,
                NOTIFY_NOTIFY_CARLIFE_EAP_AUTH_RESULT,
                NOTIFY_NOTIFY_CARLIFE_EXTRACT,
                NOTIFY_NOTIFY_AAP_AOA_SWITCH,
                NOTIFY_NOTIFY_AAP_EXTRACT,
                NOTIFY_NOTIFY_EA_SESSION_STATUS_CHANGED,
                NOTIFY_NOTIFY_USB_MOUNT,
                NOTIFY_NOTIFY_USB_UNMOUNT,
                NOTIFY_NOTIFY_USB_BAD_REMOVAL,
                NOTIFY_NOTIFY_HUB_INSERT,
                NOTIFY_NOTIFY_HUB_EXTRACT,
                NOTIFY_NOTIFY_OVER_CURRENT,
                NOTIFY_NOTIFY_IAP2AUTH_RESULT,
                NOTIFY_NOTIFY_IAP_AUTH_RESULT,
                NOTIFY_NOTIFY_CARPLAY_AUTH_RESULT,
                NOTIFY_NOTIFY_USB_CHECK_STATUS,

                NOTIFY_MAX
            };

        public:
            ConnectManagerProxyBase(IConnectManagerProxyReplier* replier, bool autoConnect = true);
            ~ConnectManagerProxyBase();

            virtual void onConnected();
            virtual void onDisconnected();

            android::status_t func(const int32_t& a, HFP_DIAL_RESULT& b);
            android::status_t cmd(const int32_t& a, const int32_t& b);
            android::status_t getIpodInfo(IPOD_DEVICE_TYPE& type, IpodInfo_Sp& info);
            android::status_t getUsbInfo(STORAGE_DEVICE_TYPE& type, StorageInfo_Sp& info);
            android::status_t getAoaDevInfo(bool& isInsert);
            android::status_t getAoaSndInfo(android::String8& pcm);
            android::status_t setAppSourceStatus(const bool& isSourceOn);
            android::status_t registerProxy(const PROXY_TYPE& type);
            android::status_t ipodCloseResult(const CON_MGR_RESULT& res);
            android::status_t iapAuthResult(const IPOD_DEVICE_TYPE& type, const CON_MGR_RESULT& res);
            android::status_t iapSetDevName(const android::String8& devName);
            android::status_t carplayAuthResult(const CON_MGR_RESULT& res);
            android::status_t carlifeAppLaunch();
            android::status_t carlifeEapStartConnect();
            android::status_t carlifeEapAuthResult(const CARLIFE_EAP_AUTH_RESULT& res);
            android::status_t debug_resetAoa();
            android::status_t closeDataConn();
            android::status_t resetUsb();
            android::status_t launchAndroidSource(const ANDROID_SOURCE_TYPE& type);
            android::status_t getAndroidDevInfo(bool& isConnected, android::String8& serialNum);
            android::status_t launchIosSource(const IOS_SOURCE_TYPE& type);
            android::status_t getIosDevConnStatus(bool& isConnected, int32_t& index, IOS_POPUP_STATUS& sts);
            android::status_t getIosDevInfo(bool& isConnected, bool& isCarplaySupp, android::String8& serialNum);
            android::status_t enableUsbSource(const USB_SOURCE_TYPE& type);
            android::status_t disableUsbSource(const USB_SOURCE_TYPE& type);
            android::status_t getUnsupportType(UNSUPPORT_USB_TYPE& port1Type, UNSUPPORT_USB_TYPE& port2Type);
            // following api is for last source
            android::status_t getUsbDevInfo(STORAGE_DEVICE_TYPE& type, StorageInfo_Sp& info, bool& isLastOn);
            android::status_t getCarlifeDevInfo(CARLIFE_TYPE& type, bool& isInsert, bool& isLastOn);
            android::status_t getAapDevInfo(bool& isInsert, bool& isLastOn);
            android::status_t getIapDevInfo(IpodInfo_Sp& info, bool& isHostMode);
            android::status_t getIpodDevInfo(IPOD_AUTH_STATE& authState, bool& isLastOn);
            android::status_t getIpodDeviceInfo(IpodInfo_Sp& info, IPOD_AUTH_STATE& authState, bool& isLastOn);
            android::status_t getIpodDevStatus(IpodInfo_Sp& info, IPOD_AUTH_STATE& authState, bool& isLastOn, USB_CHECK_STATUS& usbSts);
            android::status_t getCarplayInfo(IPOD_AUTH_STATE& authState, bool& isLastOn);
            android::status_t getCarplayDevInfo(IpodInfo_Sp& info, IPOD_AUTH_STATE& authState, bool& isLastOn);
            // for diag
            android::status_t remountUsbDevice(const int32_t& port);
            //for android
            android::status_t androidSetDevName(const android::String8& devName);
        private:
            virtual int onAsyncResponse(unsigned int code, const android::Parcel &reply);

        private:
            IConnectManagerProxyReplier* m_replier;
    };
}
#endif
/* EOF */
