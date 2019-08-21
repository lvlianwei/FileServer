#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "servicebase/ServiceBase.h"
#include "binder/Parcel.h"
#include "SmartIosService.h"
#include "SmartIosServiceStub.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosConnManagerProxy.h"
#include "TimerManager.h"
#include<stdio.h>
namespace goni {
     class Test_smtIosService: public testing::Test {
           public:
	       static SmartIosService* service;
	       static TimerManager * manager;
	       static void SetUpTestCase() {
	            printf("##################smart ios service set up###############\n");
		    manager = new TimerManager;
		    service =  new SmartIosService();
	       }
	       static void TearDownTestCase() {
	            printf("##################smart ios service tear down###############\n");
	       }
     };
}
