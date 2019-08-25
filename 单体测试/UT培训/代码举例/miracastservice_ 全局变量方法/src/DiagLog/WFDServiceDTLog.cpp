
/***********************************WFDServiceDTLog.cpp****************************************/
/**
* @file WFDService_DTLog.cpp
* @brief Implementation file of class WFDDTLog.
*/
#include <stdio.h>
#include <stdarg.h>
#include "WFDServiceDTLog.h"

namespace goni
{
#define MAX_DT_LOG_LENGTH  100
void*          WFDDTLog::s_pHandler = NULL;
ni_hallib_dt_t WFDDTLog::s_device;

WFDDTLog* WFDDTLog::instance = NULL;

WFDDTLog* WFDDTLog::getInstance()
{
    if (instance == NULL) {
        instance  = new WFDDTLog();
    }

    return instance;
}

void WFDDTLog::start()
{
    int iRet = ni_hallib_device_open(ni_hallib_dt_name,&s_device,sizeof(s_device));
    if(NIHALLIB_ERROR_NONE == iRet)
        s_pHandler = s_device.start();
}

void WFDDTLog::stop()
{
    if(NULL != s_pHandler)
    {
        s_device.stop(s_pHandler);
        ni_hallib_device_close(&s_device);
        s_pHandler = NULL;
    }
}

void WFDDTLog::writeProc(DTMODULEID eModule, uint32_t funcId, uint16_t subFuncId, uint32_t procId, const char* dataString, uint32_t dataSize)
{
    if(NULL != s_pHandler)
        s_device.writeProcLog(s_pHandler, eModule, funcId, subFuncId, procId, dataString, dataSize);
    return;
}

void WFDDTLog::writeRet(DTMODULEID eModule, uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize)
{
    if(NULL != s_pHandler)
        s_device.writeResultLog(s_pHandler, eModule, funcId, subFuncId, dataString, dataSize);
    return;
}

void WFDDTLog::writeError(DTMODULEID eModule, uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize)
{
    if(NULL != s_pHandler)
        s_device.writeErrorLog(s_pHandler, eModule, funcId, subFuncId, dataString, dataSize);
    return;
}

void WFDDTLog::writeInfo(DTMODULEID eModule, uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize)
{
    if(NULL != s_pHandler)
        s_device.writeInfoLog(s_pHandler, eModule, funcId, subFuncId, dataString, dataSize);
    return;
}

void WFDDTLog::DProc(uint32_t funcId, const char* fmt, ...)
{
    va_list argp;
    int len = 0;
    char tmpLog[MAX_DT_LOG_LENGTH] = {0};
    va_start( argp, fmt );
    len = vsnprintf(tmpLog, sizeof(tmpLog), fmt, argp);
    va_end( argp );
    if(len < 0)
        return;
    writeProc(DTMODULEID_WFDSERVICE, funcId, 0x00, 0x00,tmpLog, len);
}

void WFDDTLog::DProc(uint32_t funcId, uint16_t subFuncId, uint16_t procId, const char* fmt, ...)
{
    va_list argp;
    int len = 0;
    char tmpLog[MAX_DT_LOG_LENGTH] = {0};
    va_start( argp, fmt );
    len = vsnprintf(tmpLog, sizeof(tmpLog), fmt, argp);
    va_end( argp );
    if(len < 0)
        return;
    writeProc(DTMODULEID_WFDSERVICE, funcId, subFuncId, procId, tmpLog, len);
}

void WFDDTLog::DInfo(uint32_t funcId, const char* fmt, ...)
  {
    va_list argp;
    int len = 0;
    char tmpLog[MAX_DT_LOG_LENGTH] = {0};
    va_start( argp, fmt );
    len = vsnprintf(tmpLog, sizeof(tmpLog), fmt, argp);
    va_end( argp );
    if(len < 0)
        return;
    writeInfo(DTMODULEID_WFDSERVICE, funcId, 0x00, tmpLog, len);
  }

void WFDDTLog::DInfo(uint32_t funcId, uint16_t subFuncId,const char* fmt, ...)
{
    va_list argp;
    int len = 0;
    char tmpLog[MAX_DT_LOG_LENGTH] = {0};
    va_start( argp, fmt );
    len = vsnprintf(tmpLog, sizeof(tmpLog), fmt, argp);
    va_end( argp );
    if(len < 0)
        return;
    writeInfo(DTMODULEID_WFDSERVICE, funcId, subFuncId, tmpLog, len);
}

void WFDDTLog::DRet(uint32_t funcId, uint16_t subFuncId, const char* fmt, ...)
{
    va_list argp;
    int len = 0;
    char tmpLog[MAX_DT_LOG_LENGTH] = {0};
    va_start( argp, fmt );
    len = vsnprintf(tmpLog, sizeof(tmpLog), fmt, argp);
    va_end( argp );
    if(len < 0)
        return;
    writeRet(DTMODULEID_WFDSERVICE, funcId, subFuncId, tmpLog, len);
}

void WFDDTLog::DRet(uint32_t funcId, const char* fmt, ...)
{
    va_list argp;
    int len = 0;
    char tmpLog[MAX_DT_LOG_LENGTH] = {0};
    va_start( argp, fmt );
    len = vsnprintf(tmpLog, sizeof(tmpLog), fmt, argp);
    va_end( argp );
    if(len < 0)
        return;
    writeRet(DTMODULEID_WFDSERVICE, funcId, 0x00, tmpLog, len);
}
void WFDDTLog::DErr(uint32_t funcId, const char* fmt, ...)
  {
    va_list argp;
    int len = 0;
    char tmpLog[MAX_DT_LOG_LENGTH] = {0};
    va_start( argp, fmt );
    len = vsnprintf(tmpLog, sizeof(tmpLog), fmt, argp);
    va_end( argp );
    if(len < 0)
        return;
    writeError(DTMODULEID_WFDSERVICE, funcId, 0x00, tmpLog, len);
  }

void WFDDTLog::DErr(uint32_t funcId, uint16_t subFuncId,const char* fmt, ...)
{
    va_list argp;
    int len = 0;
    char tmpLog[MAX_DT_LOG_LENGTH] = {0};
    va_start( argp, fmt );
    len = vsnprintf(tmpLog, sizeof(tmpLog), fmt, argp);
    va_end( argp );
    if(len < 0)
        return;
    writeError(DTMODULEID_WFDSERVICE, funcId, subFuncId, tmpLog, len);
}

} // end of namespace goni

/* EOF */

