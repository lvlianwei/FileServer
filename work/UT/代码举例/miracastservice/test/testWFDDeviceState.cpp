#include "testWFDDeviceState.h"
#include "testDefine.h"
namespace goni
{
	extern bool UTcompvalue ;
	const wfdSvcState& WFDDeviceState::getSvcState()
    {
    	printf("----------testWFDDeviceState::getSvcState--------------\n");
   		if(UTcompvalue)
			{svcState = WFD_CONNECTED;printf("11111111111111111111111111111111111111111\n");}
		else
			{svcState = WFD_POWER_OFF;printf("00000000000000000000000000000000000000000\n");}
        return svcState;
    }
}