#include<iostream>
#include<gtest/gtest.h>
#include "wfdServiceStub.h"
#include "wfdService.h"
namespace goni {
    class Test_wfdServiceStubEnv {
        private:
            WFDServiceStub * stub;
        public:
            Test_wfdServiceStubEnv() {
                stub = new WFDServiceStub(new wfdService);
            }
            ~Test_wfdServiceStubEnv() {
                delete stub;
                stub = 0;
            }
            static Test_wfdServiceStubEnv env;
    };
}
