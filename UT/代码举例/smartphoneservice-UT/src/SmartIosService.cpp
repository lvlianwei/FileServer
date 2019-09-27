
#include "servicebase/ServiceBase.h"
#include "binder/Parcel.h"
#include "SmartIosService.h"
#include "SmartIosServiceStub.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosConnManagerProxy.h"
#include "SmartIosDiagServiceSub.h"
#include "SmartIosSettingProxy.h"
#include "cutils/properties.h"
#include "servicebase/SystemLog.h"
#include <sys/resource.h>
namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

    SmartIosService :: SmartIosService()    /* __0x405001_DTFUNCID__ */
    : ServiceBase("SmartIosService")
    ,mStub(NULL)
    ,multiListner(NULL)
    ,mConnSub(NULL)
    ,diagListen(NULL)
    ,mDiagSub(NULL)
    {

    }
    SmartIosService :: ~SmartIosService()    /* __0x405002_DTFUNCID__ */ {
    }

    void SmartIosService :: onStart() {
        const char* key = "sys.bootmode";
        char value[PROPERTY_VALUE_MAX] = {0};
        property_get(key,value,"acc");
        DTLOG_INFO(0x405002, "key %s,value %s", key, value);
        SMTLOGD("key %s,value %s",key,value);
        SmartIosSettingProxy::getInstance()->initSqlite3DB();
        android::sp<android::IServiceManager> sm = android::defaultServiceManager();
        bool diedBefore = sm->checkServiceDiedBefore("SmartIosService");
        if(diedBefore) {
            DTLOG_INFO(0x405002, "SmartIosService died before");
            SMTLOGD("SmartIosService died before");
        }
        else {
            if(strcmp(value,"bon") == 0) {
                DTLOG_INFO(0x405002, "value == bon");
                SmartIosSettingProxy::getInstance()->delAllDevice(); 
            }
        }
        mStub = new SmartIosServiceStub(this);
        if (NULL == mStub){
            DTLOG_PTRASSERT(mStub);
        }
        else{
            registerStub(mStub);
        }
        /**
        *  listen connect manager multicast
        */
        multiListner = new SmartConnectManagerListener(mStub);
        if (NULL == multiListner){
            DTLOG_PTRASSERT(multiListner);
        }
        else{
            mConnSub = new ConnectManagerSub(multiListner, this);
        }
        /**
        *  listen diag service multicast
        */
        diagListen = new SmartIosDiagServiceSub();
        if (NULL == diagListen){
            DTLOG_PTRASSERT(diagListen);
        }
        else{
            mDiagSub = new DiagSub(diagListen,this);
        }
        ServiceBase::onStart();
        SMTLOGD("SmartIosService onStart");
        if (NULL != mStub){
            mStub->initialize();
        }
    }
    void SmartIosService :: onStop()    /* __0x405003_DTFUNCID__ */ {
        DTLOG_INFO(0x405003, "SmartIosService :: onStop");
        registerStub(NULL);
        if(multiListner != NULL) {
            delete multiListner;
            multiListner = NULL;
        }
        mConnSub = NULL;
        if(diagListen != NULL) {
            delete diagListen;
            diagListen = NULL;
        }
        mDiagSub = NULL;
        if(mStub != NULL) {
            mStub->deInit();
            delete mStub;
            mStub = NULL;
        }
        ServiceBase::onStop();
        SMTLOGD("SmartIosService onStop");
    }
    
    void SmartIosService::initialize()
    {
        // set main thread priority
        setpriority(PRIO_PROCESS, 0, goni::THREAD_PRIORITY_BACKGROUND);

        ServiceBase::initialize();
    }

}
