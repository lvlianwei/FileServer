#include "Test_wfdService.h"
#include<pthread.h>
namespace goni {
    wfdService* Test_wfdService::service = NULL;
    TimerManager* Test_wfdService::manager = NULL;
    void* callbackFunc(void *msg) {
        printf("**********************************in pthread callback************************\n");
        Test_wfdService::service->onStart();
        Test_wfdService::service->onStop();
        Test_wfdService::service->onStart();
        printf("******************wfd sedrvice start success*************************\n");
    }
    TEST_F(Test_wfdService,onStart) {
        printf("*****************************************wfd service onstart******************************\n");
        // service->onStart();
        pthread_t pid;
        if(pthread_create(&pid,0,callbackFunc,0) != 0) {
            printf("**************create pthread faild**************\n");
        }
    }
    TEST_F(Test_wfdService,delayFunc) {
        int icount = 0;
        while(icount < 20) {
            usleep(50000);
            icount++;
        }
        printf("***************************delay complete*******************\n");
    }
}
