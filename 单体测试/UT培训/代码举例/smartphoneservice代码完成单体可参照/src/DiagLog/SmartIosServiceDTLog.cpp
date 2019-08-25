#include "SmartIosServiceDTLog.h"
#include<stdarg.h>
#include<stdio.h>
#define MAX_DT_LOG_LENGTH 100
#define USE_VA_LIST(tmpLog,len,fmt) ({\
   va_list arg;\
   va_start(arg,fmt);\
   len = vsnprintf(tmpLog,MAX_DT_LOG_LENGTH,fmt,arg);\
   va_end(arg);\
   if(len < 0)\
	  return;\
})
namespace goni {
   SMARTIOSDTLog* SMARTIOSDTLog::instance = NULL;
   void* SMARTIOSDTLog::s_pHandle = NULL;
   ni_hallib_dt_t SMARTIOSDTLog::s_device;
   SMARTIOSDTLog* SMARTIOSDTLog::getInstance() {
       if(instance == NULL) {
	      instance = new SMARTIOSDTLog;
	   }
	   return instance;
   }
   void SMARTIOSDTLog::start() {
     int iRet = ni_hallib_device_open(ni_hallib_dt_name,&s_device,sizeof(s_device));
	 if(NIHALLIB_ERROR_NONE == iRet) {
	    s_pHandle = s_device.start();
	 }
   }
   void SMARTIOSDTLog::stop() {
     if(NULL != s_pHandle) {
	    s_device.stop(s_pHandle);
		ni_hallib_device_close(&s_device);
		s_pHandle = NULL;
	 }
   }
   void SMARTIOSDTLog::writeProc(uint32_t funcId, uint16_t subFuncId, uint32_t procId, const char* dataString, uint32_t dataSize) {
     if(s_pHandle != NULL) {
	    s_device.writeProcLog(s_pHandle, DTMODULEID_SMARTIOS, funcId, subFuncId, procId, dataString, dataSize);
	 }
   }
   void SMARTIOSDTLog::DProc(uint32_t funcId,const char* fmt,...) {
	   int len = 0;
	   char tmpLog[MAX_DT_LOG_LENGTH] = {0};
	   USE_VA_LIST(tmpLog,len,fmt);
	   writeProc(funcId,0x00,0x00,tmpLog,len);
   }
   void SMARTIOSDTLog::DProc(uint32_t funcId,uint16_t subFuncId,uint32_t procId,const char* fmt,...) {
	   int len = 0;
	   char tmpLog[MAX_DT_LOG_LENGTH] = {0};
	   USE_VA_LIST(tmpLog,len,fmt);
	   writeProc(funcId,subFuncId,procId,tmpLog,len);
   }
   void SMARTIOSDTLog::writeRst(uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize) {
       if(s_pHandle != NULL) {
	      s_device.writeResultLog(s_pHandle, DTMODULEID_SMARTIOS, funcId, subFuncId, dataString, dataSize);
	   }
   }
   void SMARTIOSDTLog::DRet(uint32_t funcId,const char* fmt,...) {
	   int len = 0;
	   char tmpLog[MAX_DT_LOG_LENGTH] = {0};
	   USE_VA_LIST(tmpLog,len,fmt);
	   writeRst(funcId,0x00,tmpLog,len);
   }
   void SMARTIOSDTLog::DRet(uint32_t funcId,uint16_t subFuncId,const char* fmt,...) {
	   int len = 0;
	   char tmpLog[MAX_DT_LOG_LENGTH] = {0};
	   USE_VA_LIST(tmpLog,len,fmt);
	   writeRst(funcId,subFuncId,tmpLog,len);
   }
   void SMARTIOSDTLog::writeError(uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize) {
       if(s_pHandle != NULL) {
	      s_device.writeErrorLog(s_pHandle, DTMODULEID_SMARTIOS, funcId, subFuncId, dataString, dataSize);
	   }
   }
   void SMARTIOSDTLog::DErr(uint32_t funcId,const char* fmt,...) {
	   int len = 0;
	   char tmpLog[MAX_DT_LOG_LENGTH] = {0};
	   USE_VA_LIST(tmpLog,len,fmt);
	   writeError(funcId,0x00,tmpLog,len);
   }
   void SMARTIOSDTLog::DErr(uint32_t funcId,uint16_t subFuncId,const char* fmt,...) {
	   int len = 0;
	   char tmpLog[MAX_DT_LOG_LENGTH] = {0};
	   USE_VA_LIST(tmpLog,len,fmt);
	   writeError(funcId,subFuncId,tmpLog,len);
   }
   void SMARTIOSDTLog::writeInfo(uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize) {
       if(s_pHandle != NULL) {
	      s_device.writeInfoLog(s_pHandle, DTMODULEID_SMARTIOS, funcId, subFuncId, dataString, dataSize);
	   }
   }
   void SMARTIOSDTLog::DInfo(uint32_t funcId,const char* fmt,...) {
	   int len = 0;
	   char tmpLog[MAX_DT_LOG_LENGTH] = {0};
	   USE_VA_LIST(tmpLog,len,fmt);
	   writeInfo(funcId,0x00,tmpLog,len);
   }
   void SMARTIOSDTLog::DInfo(uint32_t funcId,uint16_t subFuncId,const char* fmt,...) {
	   int len = 0;
	   char tmpLog[MAX_DT_LOG_LENGTH] = {0};
	   USE_VA_LIST(tmpLog,len,fmt);
	   writeInfo(funcId,subFuncId,tmpLog,len);
   }
}
