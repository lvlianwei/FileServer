/**
 * @file SmartIosDiagServiceSub.cpp
 * @brief 
 * @author jianglei
 * @version 1
 * @date 2017-07-27
 */
#include "SmartIosDiagServiceSub.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosSettingProxy.h"
#include "proxy/DiagProxyBase.h"
#include "servicebase/SystemLog.h"
namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

     SmartIosDiagServiceSub::SmartIosDiagServiceSub()    /* __0x403001_DTFUNCID__ */ {
         SMTLOGD("SmartIosDiagServiceSub constructor");
     }
     SmartIosDiagServiceSub::~SmartIosDiagServiceSub()    /* __0x403003_DTFUNCID__ */ {
         SMTLOGD("SmartIosDiagServiceSub desconstructor");
     }
     android::status_t SmartIosDiagServiceSub::broadcastDiagOn(const DIAG_MODE& eMode)    /* __0x403004_DTFUNCID__ */ {
         UNUSED(eMode);
         SMTLOGD("broadcast diag on");
	 //do nothing
	 return 0;
     }
     /**
      * @brief broadcastDiagInit ,receive diag service diag init multicat,clear database,send response  to diag service
      *
      * @return 
      */
     android::status_t SmartIosDiagServiceSub::broadcastDiagInit()    /* __0x403005_DTFUNCID__ */ {
         SMTLOGD("broadcast diag init");
         DTLOG_INFO(0x403005, "smrtios rcv broadcast diag init");
	 //1 clear database
         SmartIosSettingProxy::getInstance()->delAllDevice();
	 SmartIosSettingProxy::getInstance()->deInit();
	 //2 send response 
	 SMTLOGD("DiagProxybase resDiagInit,eservice %d,ret = %d",DIAG_SYSINIT_SERVICE_SMARTIOS,true);
	 IDiagProxyReplier proxyReplier;
	 DiagProxyBase proxy(&proxyReplier);
	 proxy.resDiagInit(DIAG_SYSINIT_SERVICE_SMARTIOS, true);
	 return 0;
     }
}
