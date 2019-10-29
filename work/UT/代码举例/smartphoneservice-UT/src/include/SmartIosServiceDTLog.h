
/***********************************WFDServiceDTLog.h****************************************/
/**
* @file WFDServiceDTLog.h.h
* @brief Declaration file of class WFFDTLog
*/

#ifndef SMARTIOSSERVICE_DTLOG_H
#define SMARTIOSSERVICE_DTLOG_H


#include "ni_hallib_dt.h"
#include "ni_hallib.h"
#include "ncore/NCGlobalAPI.h"


namespace goni
{
class SMARTIOSDTLog
{
public:
    // dlopen libnhdtlib.so，to start client
    void start();

    // dlclose libnhdtlib.so，stop client
    void stop();


    void writeProc(uint32_t funcId, uint16_t subFuncId, uint32_t procId, const char* dataString, uint32_t dataSize);
    void DProc(uint32_t funcId,const char* fmt,...);
    void DProc(uint32_t funcId,uint16_t subFuncId,uint32_t procId,const char* fmt,...);


    void writeRst(uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize);
    void DRet(uint32_t funcId,const char* fmt,...);
    void DRet(uint32_t funcId,uint16_t subFuncId,const char* fmt,...);

    void writeError(uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize);
    void DErr(uint32_t funcId,const char* fmt,...);
    void DErr(uint32_t funcId,uint16_t subFuncId,const char* fmt,...);


    void writeInfo(uint32_t funcId, uint16_t subFuncId, const char* dataString, uint32_t dataSize);
    void DInfo(uint32_t funcId,const char* fmt,...);
    void DInfo(uint32_t funcId,uint16_t subFuncId,const char* fmt,...);

public:

    static SMARTIOSDTLog* instance;

    static SMARTIOSDTLog* getInstance();


private:

    static void*            s_pHandle;

    static ni_hallib_dt_t   s_device;
};

#define SMARTIOSDTLogInst SMARTIOSDTLog::getInstance()

} // end of namespace goni

#endif /* DTLOG_H */
/* EOF */




