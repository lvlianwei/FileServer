#ifndef TEST_ANDROID_ISERVICE_MANAGER_H
#define TEST_ANDROID_ISERVICE_MANAGER_H

#include <binder/IInterface.h>
#include <binder/IPermissionController.h>
#include <utils/Vector.h>
#include <utils/String16.h>
#include<gtest/gtest.h>
#include<gmock/gmock.h>

namespace android {

    // ----------------------------------------------------------------------
    class SingletonSmtIService{
        public:
            static SingletonSmtIService* getInstance();
            static void delInstance();
            MOCK_METHOD1(checkServiceDiedBefore,bool(const char*));
        private:
            SingletonSmtIService();
            //SingletonSmtIService(const SingletonSmtIService&) = delete;
            //SingletonSmtIService& operator= (const SingletonSmtIService) = delete;
            static SingletonSmtIService* instance;
    };

    class IServiceManager : public IInterface
    {
        public:
            IServiceManager(){}

            enum Service_Status{
                SERVICE_STATUS_IDLE = 0,
                SERVICE_STATUS_START,
                SERVICE_STATUS_STOP,

                SERVICE_STATUS_MAX
            };

            enum Sysd_Event {
                SYSD_BASIC_SERVICES_READY = 0X100,
                SYSD_ALL_SERVICES_READY,
                SYSD_ALL_SERVICES_TERMINATE
            };


            bool checkServiceDiedBefore( const char* name);
            IBinder* onAsBinder();

            enum {
                GET_SERVICE_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
                CHECK_SERVICE_TRANSACTION,
                ADD_SERVICE_TRANSACTION,
                LIST_SERVICES_TRANSACTION,
                REQ_START_SERVICE_TRANSACTION,
                REQ_STOP_SERVICE_TRANSACTION,
                SERVICE_STATUS_CHANGED,
                NOTIFY_ACC_OFF_TRANSACTION,
                ADD_LOCAL_SERVICE_TRANSACTION,
                ADD_SUBSCRIBER_TRANSACTION,
                REMOVE_SUBSCRIBER_TRANSCATION,
                ADD_PUBLISHER_TRANSACTION,
                REMOVE_PUBLISHER_TRANSACTION,
                SYNC_COMPLETE_TRANSACTION,
                CHECK_SERVICE_DIED_BEFORE_TRANSACTION,
            };

    };

    sp<IServiceManager> defaultServiceManager();


} // namespace android
using namespace android;

#endif // ANDROID_ISERVICE_MANAGER_H

