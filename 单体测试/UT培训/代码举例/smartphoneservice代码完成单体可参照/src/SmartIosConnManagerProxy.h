/*
 * SmartIosConMngReply.h
 *
 *  Created on: 2017年4月13日
 *      Author: zjh
 */

#ifndef SMARTIOS_CONMANAGERREPLY_H_
#define SMARTIOS_CONMANAGERREPLY_H_

#include "servicebase/Message.h"

#ifdef UT_GTEST_FULL_ENG
#include "testConnectManagerSub.h"
#include "testConnectManagerProxyBase.h"
#include "testIServiceManager.h"
#else
#include "sub/ConnectManagerSub.h"
#include "proxy/ConnectManagerProxyBase.h"
#include "binder/IServiceManager.h"
#endif
#include "SmartIosServiceServiceDefines.h"
#include "include/SmartIosTypeDefines.h"


namespace goni
{

class SmartIosServiceManager;
class SmartIosConMngReply: public IConnectManagerProxyReplier {
public:
	SmartIosConMngReply(SmartIosServiceManager* serviceManager);
	virtual ~SmartIosConMngReply();

public:
		virtual void onConnected();

	    virtual void onDisconnected();

	    virtual android::status_t notify(const int32_t& a, const int32_t& b) {
                UNUSED(a);
                UNUSED(b);
                return 0;
            }
	    virtual android::status_t notify_ipodInsert(const IpodInfo_Sp & info) {
                UNUSED(info);
                return 0;
            }
	    virtual android::status_t notify_ipodExtract() { return 0; }
	    virtual android::status_t notify_ipodRoleSwitch(const USB_ROLE_TYPE& type) {
                UNUSED(type);
                return 0;
            }
	    virtual android::status_t notify_carlifeInsert() { return 0; }
	    virtual android::status_t notify_carlifeAoaSwitch(const CON_MGR_RESULT& res) {
                UNUSED(res);
                return 0;
            }
	    virtual android::status_t notify_carlifeEapAuthResult(const CON_MGR_RESULT& res){
                UNUSED(res);
                return 0;
            }
	    virtual android::status_t notify_carlifeExtract() { return 0; }
	    virtual android::status_t notify_usbMount(const StorageInfo_Sp & info) {
                UNUSED(info);
                return 0;
            }
	    virtual android::status_t notify_usbUnmount(const StorageInfo_Sp & info) {
                UNUSED(info);
                return 0;
            }
	    virtual android::status_t notify_usbBadRemoval(const StorageInfo_Sp & info) {
                UNUSED(info);
                return 0;
            }
	    virtual android::status_t notify_hubInsert() { return 0; }
	    virtual android::status_t notify_hubExtract() { return 0; }
	    virtual android::status_t notify_overCurrent() { return 0; }
	    virtual android::status_t notify_iap2AuthResult(const CON_MGR_RESULT& res){
                UNUSED(res);
                return 0;
            }
	    virtual android::status_t notify_iapAuthResult(const IPOD_DEVICE_TYPE& type){
                UNUSED(type);
                return 0;
            }
	    virtual android::status_t notify_carplayAuthResult(const CON_MGR_RESULT& res){
                UNUSED(res);
                return 0;
            }
	    virtual android::status_t notify_usbCheckStatus(const USB_CHECK_STATUS& sts) {
                UNUSED(sts);
                return 0;
            }
            virtual android::status_t notify_androidInsert(const android::String8& serialNum){
                UNUSED(serialNum);
                return 0;
            };
private:
	    SmartIosServiceManager* serviceManage;

};
class SmartIosConManagerProxy: public ConnectManagerProxyBase {
    public:
        SmartIosConManagerProxy(SmartIosServiceManager* serviceManage);
        ~SmartIosConManagerProxy();
    public:
        virtual void launchIosSourceReq(SmtIosSource source);
        virtual void launchAndroidSourceReq(SmtAndroidSource source);
    private:
        SmartIosConManagerProxy(const SmartIosConManagerProxy& );
        SmartIosConManagerProxy &operator=(const SmartIosConManagerProxy&);
    private:
        //SmartIosServiceManager* serviceManage;
};
class SmartIosServiceStub;
/**
 * @brief receive connect manager multicast
 */
class SmartConnectManagerListener : public IConnectManagerSub{
public:
	virtual android::status_t notify_unsupportUsbInsert(const UNSUPPORT_USB_TYPE& type) {
            UNUSED(type);
            return 0;
        }
	virtual android::status_t notify_unsupportUsbExtract() { return 0; }
	virtual android::status_t notify_overCurrent() { return 0; }
	// multicast
	virtual android::status_t notify_ipodInsert(const IpodInfo_Sp& info) {
            UNUSED(info);
            return 0;
        }
	virtual android::status_t notify_ipodExtract() { return 0; }
	virtual android::status_t notify_ipodRoleSwitch(const IpodInfo_Sp& info, const USB_ROLE_TYPE& type) {
            UNUSED(info);
            UNUSED(type);
            return 0;
        }
	virtual android::status_t notify_iap2AuthResult(const CON_MGR_RESULT& res, const bool& isLastOn){
            UNUSED(res);
            UNUSED(isLastOn);
            return 0;
        }
	virtual android::status_t notify_iapAuthResult(const IPOD_DEVICE_TYPE& type, const bool& isLastOn);
	virtual android::status_t notify_carplayAuthResult(const CON_MGR_RESULT& res){
            UNUSED(res);
            return 0;
        }
	virtual android::status_t notify_carlifeInsert(const bool& isLastOn) {
            UNUSED(isLastOn);
            return 0;
        }
	virtual android::status_t notify_carlifeAoaSwitch(const CON_MGR_RESULT& res) {
            UNUSED(res);
            return 0;
        }
	virtual android::status_t notify_carlifeExtract() { return 0; }
	virtual android::status_t notify_usbMount(const StorageInfo_Sp& info) {
            UNUSED(info);
            return 0;
        }
	virtual android::status_t notify_usbUnmount(const StorageInfo_Sp& info) {
            UNUSED(info);
            return 0;
        }
	virtual android::status_t notify_usbBadRemoval(const StorageInfo_Sp& info) {
            UNUSED(info);
            return 0;
        }
	virtual android::status_t notify_hubInsert(const bool& isLastOn) {
            UNUSED(isLastOn);
            return 0;
        }
	virtual android::status_t notify_hubExtract() { return 0; }
	virtual android::status_t notify_iosDevConnected(const int32_t& index, const IOS_POPUP_STATUS& sts) {
            UNUSED(index);
            UNUSED(sts);
            return 0;
        }
	virtual android::status_t notify_iosDevDisconnected(const int32_t& index) {
            UNUSED(index);
            return 0;
        }
	/**
	 * @brief notify_iap2Insert ,receive ipa2 insert multicast
	 *
	 * @param serialNum,the ipa2 device serinum
	 *
	 * @return 
	 */
	virtual android::status_t notify_iap2Insert(const bool& isCarplaySupp,const android::String8& serialNum);
	/**
	 * @brief notify_iap2Extract ,receive ipa2 extract multicast
	 *
	 * @return 
	 */
	virtual android::status_t notify_iap2Extract();
	/**
	 * @brief notify_androidInsert ,receive android insert multicast
	 *
	 * @param serialNum,the android device serinum
	 *
	 * @return 
	 */
	virtual android::status_t notify_androidInsert(const android::String8& serialNum);
	/**
	 * @brief notify_androidExtract ,receive android extract multicast
	 *
	 * @return 
	 */
	virtual android::status_t notify_androidExtract();
	/**
	 * @brief notify_iap2AuthInfo ,receive ipa2 auth info multicast
	 *
	 * @param serialNum,device serinum
	 * @param devName,device really name
	 *
	 * @return 
	 */
	virtual android::status_t notify_iap2AuthInfo(const android::String8& serialNum, const android::String8& devName);
        virtual android::status_t notify_androidAuthInfo(const android::String8& serialNum, const android::String8& devName);
public:
	SmartConnectManagerListener(SmartIosServiceStub* stub);
private:
	SmartIosServiceStub* mStub;

};
}
#endif /* APPLICATION_FUNCMNG_SYSTEM_FCONMANAGERREPLY_H_ */
