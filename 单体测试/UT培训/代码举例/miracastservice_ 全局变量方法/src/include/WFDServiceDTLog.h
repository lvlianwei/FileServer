
/***********************************WFDServiceDTLog.h****************************************/
/**
* @file WFDServiceDTLog.h.h
* @brief Declaration file of class WFFDTLog
*/

#ifndef WFDSERVICE_DTLOG_H
#define WFDSERVICE_DTLOG_H


#include "ni_hallib_dt.h"
#include "ni_hallib.h"
#include "ncore/NCGlobalAPI.h"


namespace goni
{
class WFDDTLog
{
public:
    // open lib libnhdtlib.so,start client
    void start();

    // close lib libnhdtlib.so,stop client
    void stop();

    // the interface of trace the procedure
    void writeProc(DTMODULEID eModule, uint32_t funcId, uint16_t subFuncId, uint32_t procId, const char* dataString, uint32_t dataSize);

    // the interface of trace the result
    void writeRet(DTMODULEID eModule, uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize);

    // the interface of trace the error
    void writeError(DTMODULEID eModule, uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize);

    // the interface of trace the info
    void writeInfo(DTMODULEID eModule, uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize);
    void DProc(uint32_t funcId, const char* fmt, ...);
    void DProc(uint32_t funcId, uint16_t subFuncId, uint16_t procId,const char* fmt, ...);
    void DInfo(uint32_t funcId, const char* fmt, ...);
    void DInfo(uint32_t funcId, uint16_t subFuncId,const char* fmt, ...);
    void DRet(uint32_t funcId, uint16_t subFuncId, const char* fmt, ...);
    void DRet(uint32_t funcId, const char* fmt, ...);
    void DErr(uint32_t funcId, const char* fmt, ...);
    void DErr(uint32_t funcId, uint16_t subFuncId,const char* fmt, ...);

public:

    static WFDDTLog* instance;

    static WFDDTLog* getInstance();


private:

    static void*            s_pHandler;

    static ni_hallib_dt_t   s_device;
};

#define WFDDTLogInst WFDDTLog::getInstance()

} // end of namespace goni

#endif /* DTLOG_H */
/* EOF */




