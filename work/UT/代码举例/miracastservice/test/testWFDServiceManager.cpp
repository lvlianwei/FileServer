#include"testWFDServiceManager.h"
#include "testDefine.h"
namespace goni{
    extern bool UTretvalue ;
    extern bool UTcompvalue ;
    WFDServiceStub* WFDServiceManager::getServiceStub()
    {
    	//if(UTretvalue == 1)
			//return mStub;
		//else
		printf("----------------testWFDManger:getServiceStub----------------\n");
			return mStub;
			
    }
}
