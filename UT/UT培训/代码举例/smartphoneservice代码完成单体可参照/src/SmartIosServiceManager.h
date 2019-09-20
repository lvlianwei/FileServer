#ifndef SMARTIOSSERVICE_MANAGER_H
#define SMARTIOSSERVICE_MANAGER_H

#include "utils/List.h"
#include "servicebase/MessageHandler.h"
#include "servicebase/LooperThread.h"
#include "include/SmartIosServiceServiceDefines.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosMessage.h"
#include "include/SmartIosTypeDefines.h"
//#include "SmartIosRemoteDeviceInfo.h"
//#include "SmartIosDeviceState.h"
//#include "SmartIosServiceMsg.h"
#ifdef UT_GTEST_FULL_ENG
#include "testTimer.h"
#else
#include "servicebase/Timer.h"
#endif
#define LAUNCH_RESULT_CHECK_TIME 20000/*20s*/
#ifdef UT_GTEST_FULL_ENG
namespace Test{
	class SmartIosSettingProxy;
}
using namespace Test;
#endif

namespace goni
{
class SmartIosServiceStub;
class Message;
class SmartIosServiceReplier;
class SmartIosServiceStub;

#ifndef UT_GTEST_FULL_ENG
class SmartIosSettingProxy;
#endif
class SmartIosConManagerProxy;
class SmartIosMessage;
class SmartIosServiceManager
{
    public:

        SmartIosServiceManager(SmartIosServiceStub* sub, SmartIosServiceReplier* replier);
        ~SmartIosServiceManager();
        void run();

        SmartIosServiceReplier* getServiceReplier();
        SmartIosServiceStub* getServiceStub();
        SmartIosConManagerProxy* getConMngProxy();

        /**
            * @brief initialize ,prepare resource,such as open database,new connproxy
            */
        void initialize();
        /**
            * @brief deInit release resource
            */
        void deInit();
        /**
            * @brief smt_launchSource ,launch source req
            *
            * @param id reserved for replier
            * @param index ,reserved 
            * @param source selectd source carplay or weblink
            *
            * @return 
            */
        android::status_t smt_launchSource(SenderId id, const uint8_t& index, const SmtIosSource& source);
        /**
            * @brief smt_launchSource ,launch Android source req
            *
            * @param id reserved for replier
            * @param index ,reserved 
            * @param source selectd source aap or weblink
            *
            * @return 
            */
        android::status_t smt_launchSource_Android(SenderId id, const uint8_t& index, const SmtAndroidSource& source);
        /**
            * @brief smt_setPopStatus ,set pop status req
            *
            * @param id reserved for replier
            * @param setType 0,pop up set,1 manu set
            * @param index,the device priority in table
            * @param pop ,pop value
            *
            * @return 
            */
        android::status_t smt_setPopStatus(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatus& pop);
        android::status_t smt_setPopStatusAndroid(SenderId id, const SmtSetType& setType, const uint8_t& index, const SmtPopStatusAndroid& pop);
        /**
            * @brief smt_getDeviceInfo ,get pop device info
            *
            * @param id reserved for replier
            * @param reqType 0 all pop dev info,1 single pop dev info
            * @param index,reserved for single device 
            *
            * @return 
            */
        android::status_t smt_getDeviceInfo(SenderId id, const SmtDevReqType& reqType, const uint8_t& index);
        android::status_t smt_getDeviceInfoAndroid(SenderId id, const SmtDevReqType& reqType, const uint8_t& index);
        /**
            * @brief smt_delSingleDevice del single device 
            *
            * @param id reserved for replier
            * @param index,device priority
            *
            * @return 
            */
        android::status_t smt_delSingleDevice(SenderId id,const uint8_t& index);
        android::status_t smt_delAllDevice(SenderId id);
        /**
            * @brief getDevConnectInfo ,IF for funcmng,to get dev connect info
            *
            * @param connState,connect or disConnect
            * @param index,device priority
            * @param popStatus,device pop status
            *
            * @return 
            */
        android::status_t getDevConnectInfo(uint8_t& connState,uint8_t& index,uint8_t& popStatus);
        android::status_t getDevConnectInfoAndroid(uint8_t& connState,uint8_t& index,uint8_t& popStatus);
        void notifyLaunchResult(smtLaunchState state);
        static SmartIosServiceManager * getInstance();
        static SmartIosServiceManager * manager;
        uint8_t mConnState;
        uint8_t mConnStateAndroid;
        uint8_t mIndex;
        uint8_t mIndexAndroid;
        uint8_t mPopStatus;
        uint8_t mPopStatusAndroid;
    public:
        void onIapDeviceInsert(bool isCarplaySupp,android::String8 serialNumber);
        void onIapExact();
        void onAndroidDeviceInsert(android::String8 serialNumber);
        void onAndroidExact();
        void onIap2AuthInfo(const android::String8& serialNum, const android::String8& devName);
        void onAndroidAuthInfo(const android::String8& serialNum, const android::String8& devName);

        void onMsgReceived(uint8_t opcode, void* msg);

    private:

        /**
        * @brief handler manager message
        */
        class SmartIosManagerHandler : public goni::MessageHandler {
            public:
                SmartIosManagerHandler(SmartIosServiceManager* manager);
                ~SmartIosManagerHandler();
                virtual void onReceiveMessage(const android::sp<goni::Message> &msg);
            private:
                SmartIosServiceManager* mOwner;
                SenderId mid;
            private:
                void onLaunchSourceReqHandler(const SmartIosMessage::LaunchSourceReq* req);
                void onLaunchSourceReqHandlerAndroid(const SmartIosMessage::LaunchSourceReqAndroid* req);
                void onSetPopStatusReqHandler(const SmartIosMessage::SetPopStatusReq* req);
                void onSetPopStatusReqHandlerAndroid(const SmartIosMessage::SetPopStatusReqAndroid* req);
                void onGetDevInfoReqHandler(const SmartIosMessage::GetDevInfoReq* req, SmtDeviceType deviceType);
                void onIapDeviceInsertHandler(const SmartIosMessage::IapDevInsertInd* ind);
                void onAndroidDeviceInsertHandler(const SmartIosMessage::AndroidDevInsertInd* ind);
                void onAndroidExactHandler(void);
                void onDevAutoInfoHandler(const SmartIosMessage::devAutoInfo* devinfo, SmtDeviceType deviceType);

                void onDelSingleDeviceHandler(const SmartIosMessage::delSingleDeviceReq * req);
                void onDelAllDeviceHandler(const SmartIosMessage::delAllDeviceReq* req);
                void onIapExactHandler(void);
                void onLaunchResultNotify(const SmartIosMessage::IosLaunchResult* result);
        };

        LooperThread mThread;
        SmartIosServiceReplier* mReplier;
        SmartIosServiceStub* mStub;
        SmartIosConManagerProxy* mConProxy;
            EasyTimer<SmartIosServiceManager> mTimer;
            void onLaunchResultCheckTime(Timer* timer);
	public:
        void setLaunchState(smtLaunchState state) {
            mLaunchState = state;
        }
    private:
        smtLaunchState mLaunchState;
    private:
    SmartIosServiceManager(const SmartIosServiceManager& );
    SmartIosServiceManager &operator=(const SmartIosServiceManager&);

};



}

#endif//SmartIosSERVICE_MANAGER_H
