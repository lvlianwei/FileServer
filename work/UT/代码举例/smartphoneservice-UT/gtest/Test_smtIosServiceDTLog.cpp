#include<gtest/gtest.h>
#include"SmartIosServiceDTLog.h"
#include<stdarg.h>
#include<stdio.h>
#include"Test_smtIosService.h"
namespace goni{
	class Test_SMARTIOSDTLog:public testing::Test{
	  public:
		static SMARTIOSDTLog *log;
		static void SetUpTestCase(){
		  printf("*****************************Test SMARTIOSDTLog setup************************\n");
		  log = SMARTIOSDTLog::getInstance();
		}
		static void TearDownTestCase(){
		  printf("*****************************Test SMARTIOSDTLog setup************************\n");
		  delete log;
		}
	};
	SMARTIOSDTLog* Test_SMARTIOSDTLog::log = NULL;
	TEST_F(Test_SMARTIOSDTLog,start){
		log->start();
	}
	TEST_F(Test_SMARTIOSDTLog,DProc) {
         uint32_t funcId;
         uint16_t subFuncId;
         uint32_t procId;
         char * dataString = NULL;
         uint32_t datasize = 0;
	log->DProc(funcId,subFuncId,procId,dataString,datasize);
    }
    TEST_F(Test_SMARTIOSDTLog,writeError) {
         uint32_t funcId;
         uint16_t subFuncId;
         char * dataString = "sdfgey";
         uint16_t datasize = 0;
	log->DRet(funcId,subFuncId,dataString,datasize);
	log->DRet(funcId,dataString);
	log->DErr(funcId,dataString);
	log->DErr(funcId,subFuncId,dataString);
	log->DInfo(funcId,subFuncId,dataString,datasize);
	log->writeError(funcId,subFuncId,dataString,datasize);
    }
    TEST_F(Test_SMARTIOSDTLog,stop) {
        log->stop();
    }
	TEST_F(Test_SMARTIOSDTLog,writeProc) {
         uint32_t funcId;
         uint16_t subFuncId;
         uint32_t procId;
         char * dataString = NULL;
         uint32_t datasize = 0;
		log->writeProc(funcId,subFuncId,procId,dataString,datasize);
    }
	TEST_F(Test_SMARTIOSDTLog,DProc2) {
         uint32_t funcId;
         const char * dataString = "asdfasf";
		 log->DProc(funcId,dataString);
    }
	TEST_F(Test_SMARTIOSDTLog,writeRst) {
         uint32_t funcId;
         uint16_t subFuncId;
         char * dataString = NULL;
         uint16_t datasize = 0;
		 log->writeRst(funcId,subFuncId,dataString,datasize);
    }
	TEST_F(Test_SMARTIOSDTLog,DRet) {
         uint32_t funcId;
         uint16_t subFuncId;
         const char * dataString = "rcfgbh";
         uint16_t datasize = 0;
		 log->writeRst(funcId,subFuncId,dataString,datasize);
    }
}
