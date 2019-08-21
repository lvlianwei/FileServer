#include<gtest/gtest.h>
#include<iostream>
#define private public
#include "WFDServiceManager.h"
#include "include/wfdService.h"
#include "wfdServiceStub.h"
#include "stub/WFDServiceReplier.h"
#include "servicebase/ServiceBase.h"
#include "wifiServiceDefines.h"
#include "WFDServiceDefs.h"
#include "Message.h"
#include "TimerManager.h"
#include<pthread.h>
#include<unistd.h>
using namespace std;
#define WFD_UIBC
namespace goni {
    void * create_serviceMgr(void*msg);
    class Test_wfdServiceMgr:public testing::Test {
        public:
            static WFDServiceManager *mgr;
            static WFDServiceStub *stub;
            static WFDServiceReplier *replier;
            static TimerManager * manager;
            static pthread_t pid;
            static void SetUpTestCase() {
                printf("********************************Test_wfdServiceMgr setup****************************\n");
# if 0
                if(pthread_create(&pid,NULL,create_serviceMgr,NULL) == 0) {
                    cout << "*******************create thread success******************" << endl;
                }
#endif
            }
            static void TearDownTestCase() {
                printf("************************************Test_wfdServiceMgr teardown***********************************\n");
            }
    };
}
