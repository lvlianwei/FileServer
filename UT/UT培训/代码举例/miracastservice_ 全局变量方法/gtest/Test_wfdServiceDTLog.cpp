#include<stdio.h>
#include<gtest/gtest.h>
#include "WFDServiceDTLog.h"
namespace goni {
    class Test_WFDDTLog:public testing::Test {
        public:
            static WFDDTLog * log;
            static void SetUpTestCase() {
                printf("*****************************Test wfdDTLog setup************************\n");
                log = WFDDTLog::getInstance();
            }
            static void TearDownTestCase() {
                printf("*****************************Test wfdDTLog teardown**********************\n");
                delete log;
            }
    };
    WFDDTLog* Test_WFDDTLog::log = NULL;
    TEST_F(Test_WFDDTLog,start) {
        log->start();
    }
    TEST_F(Test_WFDDTLog,writeProc) {
        uint32_t funcId;
        uint16_t subFuncId;
        uint32_t procId;
        char * dataString = NULL;
        uint32_t datasize = 0;
        DTMODULEID eModule;
        log->DProc(funcId,subFuncId,procId,dataString,datasize);
        log->writeProc(eModule,funcId,subFuncId,procId,dataString,datasize);
        log->writeRet(eModule,funcId,subFuncId,dataString,datasize);
        log->writeError(eModule,funcId,subFuncId,dataString,datasize);
        log->writeInfo(eModule,funcId,subFuncId,dataString,datasize);
        log->DProc(funcId,dataString);
        log->DInfo(funcId,dataString);
        log->DRet(funcId,dataString);
        log->DErr(funcId,dataString);
    }
    TEST_F(Test_WFDDTLog,writeRst) {
        uint32_t funcId;
        uint16_t subFuncId;
        char * dataString = NULL;
        uint16_t datasize = 0;
        log->DRet(funcId,subFuncId,dataString,datasize);
        log->DErr(funcId,subFuncId,dataString,datasize);
        log->DInfo(funcId,subFuncId,dataString,datasize);
    }

    TEST_F(Test_WFDDTLog,stop) {
        log->stop();
    }
}
