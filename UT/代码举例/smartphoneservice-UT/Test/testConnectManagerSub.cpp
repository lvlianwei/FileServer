/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: aidl/IConnectManager.aidl
 */
#include "testConnectManagerSub.h"
#include "servicebase/ServiceBase.h"
namespace goni {

    ConnectManagerSub::ConnectManagerSub(IConnectManagerSub *replier, ServiceBase* owner)
        : SubBase(owner, "ConnectManager", "multicast")
          , m_replier(replier)
    {
    }

    ConnectManagerSub::~ConnectManagerSub()
    {
    }

    int ConnectManagerSub::onMulticast(unsigned int code, const android::Parcel &data)
    {
        switch(code) {
            case MULTICAST_NOTIFY_UNSUPPORT_USB_INSERT:
                {
                    UNSUPPORT_USB_TYPE type = static_cast<UNSUPPORT_USB_TYPE>(data.readInt32());
                    m_replier->notify_unsupportUsbInsert(type);
                    break;
                }
            case MULTICAST_NOTIFY_UNSUPPORT_USB_EXTRACT:
                {
                    m_replier->notify_unsupportUsbExtract();
                    break;
                }
            case MULTICAST_NOTIFY_OVER_CURRENT:
                {
                    USB_PORT_NUMBER number = static_cast<USB_PORT_NUMBER>(data.readInt32());
                    m_replier->notify_overCurrent(number);
                    break;
                }
            case MULTICAST_NOTIFY_IPOD_INSERT:
                {
                    IpodInfo_Sp info(new IpodInfo);
                    info->readFromParcel(data);
                    m_replier->notify_ipodInsert(info);
                    break;
                }
            case MULTICAST_NOTIFY_IPOD_EXTRACT:
                {
                    m_replier->notify_ipodExtract();
                    break;
                }
            case MULTICAST_NOTIFY_IPOD_ROLE_SWITCH:
                {
                    IpodInfo_Sp info(new IpodInfo);
                    info->readFromParcel(data);
                    USB_ROLE_TYPE type = static_cast<USB_ROLE_TYPE>(data.readInt32());
                    m_replier->notify_ipodRoleSwitch(info, type);
                    break;
                }
            case MULTICAST_NOTIFY_IAP2AUTH_RESULT:
                {
                    CON_MGR_RESULT res = static_cast<CON_MGR_RESULT>(data.readInt32());
                    bool isLastOn = data.readInt32();
                    m_replier->notify_iap2AuthResult(res, isLastOn);
                    break;
                }
            case MULTICAST_NOTIFY_IAP_AUTH_RESULT:
                {
                    IPOD_DEVICE_TYPE type = static_cast<IPOD_DEVICE_TYPE>(data.readInt32());
                    bool isLastOn = data.readInt32();
                    m_replier->notify_iapAuthResult(type, isLastOn);
                    break;
                }
            case MULTICAST_NOTIFY_CARPLAY_AUTH_RESULT:
                {
                    CON_MGR_RESULT res = static_cast<CON_MGR_RESULT>(data.readInt32());
                    m_replier->notify_carplayAuthResult(res);
                    break;
                }
            case MULTICAST_NOTIFY_CARLIFE_INSERT:
                {
                    bool isLastOn = data.readInt32();
                    m_replier->notify_carlifeInsert(isLastOn);
                    break;
                }
            case MULTICAST_NOTIFY_CARLIFE_AOA_SWITCH:
                {
                    CON_MGR_RESULT res = static_cast<CON_MGR_RESULT>(data.readInt32());
                    m_replier->notify_carlifeAoaSwitch(res);
                    break;
                }
            case MULTICAST_NOTIFY_CARLIFE_EXTRACT:
                {
                    m_replier->notify_carlifeExtract();
                    break;
                }
            case MULTICAST_NOTIFY_USB_MOUNT:
                {
                    StorageInfo_Sp info(new StorageInfo);
                    info->readFromParcel(data);
                    m_replier->notify_usbMount(info);
                    break;
                }
            case MULTICAST_NOTIFY_USB_UNMOUNT:
                {
                    StorageInfo_Sp info(new StorageInfo);
                    info->readFromParcel(data);
                    m_replier->notify_usbUnmount(info);
                    break;
                }
            case MULTICAST_NOTIFY_USB_BAD_REMOVAL:
                {
                    StorageInfo_Sp info(new StorageInfo);
                    info->readFromParcel(data);
                    m_replier->notify_usbBadRemoval(info);
                    break;
                }
            case MULTICAST_NOTIFY_HUB_INSERT:
                {
                    bool isLastOn = data.readInt32();
                    m_replier->notify_hubInsert(isLastOn);
                    break;
                }
            case MULTICAST_NOTIFY_HUB_EXTRACT:
                {
                    m_replier->notify_hubExtract();
                    break;
                }
            case MULTICAST_NOTIFY_IOS_DEV_CONNECTED:
                {
                    int32_t index = data.readInt32();
                    IOS_POPUP_STATUS sts = static_cast<IOS_POPUP_STATUS>(data.readInt32());
                    m_replier->notify_iosDevConnected(index, sts);
                    break;
                }
            case MULTICAST_NOTIFY_IOS_DEV_DISCONNECTED:
                {
                    int32_t index = data.readInt32();
                    m_replier->notify_iosDevDisconnected(index);
                    break;
                }
            case MULTICAST_NOTIFY_IAP2INSERT:
                {
                    bool isCarplaySupp = data.readInt32();
                    android::String8 serialNum = data.readString8();
                    m_replier->notify_iap2Insert(isCarplaySupp, serialNum);
                    break;
                }
            case MULTICAST_NOTIFY_IAP2EXTRACT:
                {
                    m_replier->notify_iap2Extract();
                    break;
                }
            case MULTICAST_NOTIFY_IAP2AUTH_INFO:
                {
                    android::String8 serialNum = data.readString8();
                    android::String8 devName = data.readString8();
                    m_replier->notify_iap2AuthInfo(serialNum, devName);
                    break;
                }
            case MULTICAST_NOTIFY_ANDROID_INSERT:
                {
                    android::String8 serialNum = data.readString8();
                    m_replier->notify_androidInsert(serialNum);
                    break;
                }
            case MULTICAST_NOTIFY_ANDROID_EXTRACT:
                {
                    m_replier->notify_androidExtract();
                    break;
                }
            case MULTICAST_NOTIFY_ANDROID_AUTH_INFO:
                {
                    android::String8 serialNum = data.readString8();
                    android::String8 devName = data.readString8();
                    m_replier->notify_androidAuthInfo(serialNum, devName);
                    break;
                }
        }

        return 0;
    }
}
/* EOF */
