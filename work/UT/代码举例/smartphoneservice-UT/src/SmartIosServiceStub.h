/*
 * SmartIosServiceStub.h
 *
 *  Created on: 2017年5月5日
 *      Author: zjh
 */

#ifndef FRAMEWORKS_SERVICE_SMARTPHONESERVICE_B_SMARTIOSSTUB_H_
#define FRAMEWORKS_SERVICE_SMARTPHONESERVICE_B_SMARTIOSSTUB_H_

#include "src/stub/SmartIosServiceStubBase.h"
#include "include/SmartIosTypeDefines.h"
namespace goni {
    class SmartIosServiceReplier;
    class SmartIosService;
    class SmartIosServiceManager;

    class SmartIosServiceStub: public SmartIosServiceStubBase {
        public:
            SmartIosServiceStub(SmartIosService* owner);
            virtual ~SmartIosServiceStub();
        public:
            void notifyLaunchResult(smtLaunchState state);
            virtual android::status_t smt_launchSource(SenderId id, const uint8_t& index, const SmtIosSource& source);
            virtual android::status_t smt_launchSource_Android(SenderId id, const uint8_t& index, const SmtAndroidSource& source);
            virtual android::status_t smt_setPopStatus(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatus& pop);
            virtual android::status_t smt_setPopStatusAndroid(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatusAndroid& pop);
            virtual android::status_t smt_getDeviceInfo(SenderId id, const SmtDevReqType& reqType, const uint8_t& index);
            virtual android::status_t smt_getDeviceInfoAndroid(SenderId id, const SmtDevReqType& reqType, const uint8_t& index);
            virtual android::status_t smt_delSingleDevice(SenderId id, const uint8_t& index);
            virtual android::status_t smt_delAllDevices(SenderId id);
            virtual android::status_t smt_getDevConnectInfo(uint8_t& connState, uint8_t& index, uint8_t& popStatus);
            virtual android::status_t smt_getDevConnectInfoAndroid(uint8_t& connState, uint8_t& index, uint8_t& popStatus);
            virtual void onIap2Insert(bool isCarplaySupp,const android::String8& serialNumber);
            virtual void onIap2Exact(void);
            virtual void onAndroidInsert(const android::String8& serialNumber);
            virtual void onAndroidExact(void);
            virtual void onIap2AuthInfo(const android::String8& serialNum, const android::String8& devName);
            virtual void onAndroidAuthInfo(const android::String8& serialNum, const android::String8& devName);
        private:
            SmartIosServiceReplier* mReplier;
            SmartIosServiceManager* mManager;
        public:
            android::status_t onMultiListen(uint8_t opcode, void* msg);
            void initialize();
            void deInit();
    };

} /* namespace goni */

#endif /* FRAMEWORKS_SERVICE_SMARTPHONESERVICE_B_SMARTIOSSTUB_H_ */
