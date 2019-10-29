/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: aidl/IConnectManager.aidl
 */
#ifndef TEST__CONNECT_MANAGER_SUB_H__
#define TEST__CONNECT_MANAGER_SUB_H__

#include <string>
#include "binder/Parcel.h"
#include "SubBase.h"
#include "servicebase/ServiceBaseDefines.h"
#include "servicebase/ServiceBaseGlobal.h"
#include "ConnectManagerServiceDefines.h"
#include "UsbInfo.h"
#include "IpodInfo.h"
#include "StorageInfo.h"
#include "AndroidInfo.h"
namespace goni {
    class ServiceBase;

    class IConnectManagerSub
    {
        public:
            virtual ~IConnectManagerSub() {}

            virtual android::status_t notify_unsupportUsbInsert(const UNSUPPORT_USB_TYPE& type) { return 0; }
            virtual android::status_t notify_unsupportUsbExtract() { return 0; }
            virtual android::status_t notify_overCurrent(const USB_PORT_NUMBER& number) { return 0; }
            // multicast
            virtual android::status_t notify_ipodInsert(const IpodInfo_Sp& info) { return 0; }
            virtual android::status_t notify_ipodExtract() { return 0; }
            virtual android::status_t notify_ipodRoleSwitch(const IpodInfo_Sp& info, const USB_ROLE_TYPE& type) { return 0; }
            virtual android::status_t notify_iap2AuthResult(const CON_MGR_RESULT& res, const bool& isLastOn) { return 0; }
            virtual android::status_t notify_iapAuthResult(const IPOD_DEVICE_TYPE& type, const bool& isLastOn) { return 0; }
            virtual android::status_t notify_carplayAuthResult(const CON_MGR_RESULT& res) { return 0; }
            virtual android::status_t notify_carlifeInsert(const bool& isLastOn) { return 0; }
            virtual android::status_t notify_carlifeAoaSwitch(const CON_MGR_RESULT& res) { return 0; }
            virtual android::status_t notify_carlifeExtract() { return 0; }
            virtual android::status_t notify_usbMount(const StorageInfo_Sp& info) { return 0; }
            virtual android::status_t notify_usbUnmount(const StorageInfo_Sp& info) { return 0; }
            virtual android::status_t notify_usbBadRemoval(const StorageInfo_Sp& info) { return 0; }
            virtual android::status_t notify_hubInsert(const bool& isLastOn) { return 0; }
            virtual android::status_t notify_hubExtract() { return 0; }
            virtual android::status_t notify_iosDevConnected(const int32_t& index, const IOS_POPUP_STATUS& sts) { return 0; }
            virtual android::status_t notify_iosDevDisconnected(const int32_t& index) { return 0; }
            virtual android::status_t notify_iap2Insert(const bool& isCarplaySupp, const android::String8& serialNum) { return 0; }
            virtual android::status_t notify_iap2Extract() { return 0; }
            virtual android::status_t notify_iap2AuthInfo(const android::String8& serialNum, const android::String8& devName) { return 0; }
            virtual android::status_t notify_androidInsert(const android::String8& serialNum) { return 0; }
            virtual android::status_t notify_androidExtract() { return 0; }
            virtual android::status_t notify_androidAuthInfo(const android::String8& serialNum, const android::String8& devName) { return 0; }

    };

    class ConnectManagerSub : public SubBase
    {
        public:
            enum Multicast_Code
            {
                MULTICAST_NOTIFY_UNSUPPORT_USB_INSERT = SERVICE_FIRST_TRANSACTION,
                MULTICAST_NOTIFY_UNSUPPORT_USB_EXTRACT,
                MULTICAST_NOTIFY_OVER_CURRENT,
                MULTICAST_NOTIFY_IPOD_INSERT,
                MULTICAST_NOTIFY_IPOD_EXTRACT,
                MULTICAST_NOTIFY_IPOD_ROLE_SWITCH,
                MULTICAST_NOTIFY_IAP2AUTH_RESULT,
                MULTICAST_NOTIFY_IAP_AUTH_RESULT,
                MULTICAST_NOTIFY_CARPLAY_AUTH_RESULT,
                MULTICAST_NOTIFY_CARLIFE_INSERT,
                MULTICAST_NOTIFY_CARLIFE_AOA_SWITCH,
                MULTICAST_NOTIFY_CARLIFE_EXTRACT,
                MULTICAST_NOTIFY_USB_MOUNT,
                MULTICAST_NOTIFY_USB_UNMOUNT,
                MULTICAST_NOTIFY_USB_BAD_REMOVAL,
                MULTICAST_NOTIFY_HUB_INSERT,
                MULTICAST_NOTIFY_HUB_EXTRACT,
                MULTICAST_NOTIFY_IOS_DEV_CONNECTED,
                MULTICAST_NOTIFY_IOS_DEV_DISCONNECTED,
                MULTICAST_NOTIFY_IAP2INSERT,
                MULTICAST_NOTIFY_IAP2EXTRACT,
                MULTICAST_NOTIFY_IAP2AUTH_INFO,
                MULTICAST_NOTIFY_ANDROID_INSERT,
                MULTICAST_NOTIFY_ANDROID_EXTRACT,
                MULTICAST_NOTIFY_ANDROID_AUTH_INFO,

                MULTICAST_MAX
            };

        public:
            ConnectManagerSub(IConnectManagerSub* replier, ServiceBase* owner);
            ~ConnectManagerSub();

            virtual int onMulticast(unsigned int code, const android::Parcel &data);

        private:
            IConnectManagerSub* m_replier;
            SenderId m_id;

    };
}
#endif
/*EOF*/
