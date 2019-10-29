#include<stdio.h>
#include<stdlib.h>
#include<gtest/gtest.h>
#include "wfdService.h"
#include "TimerManager.h"
namespace goni {
    class Test_wfdService:public testing::Test {
        public:
            static wfdService * service;
            static TimerManager * manager;
            static void SetUpTestCase() {
                printf("************************************Test wfdService setup***********************\n");
                manager = new TimerManager;
                service = new wfdService;
            }
            static void tearDownTestCase() {
                printf("*****************************************Test wfdService teardown*********************\n");
            }
    };
}
