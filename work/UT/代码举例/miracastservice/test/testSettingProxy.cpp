#include"testSettingProxy.h"
#include "testDefine.h"
namespace goni{
    extern bool UTretvalue ;
    extern bool UTcompvalue ;
	 bool SettingProxy::get(const std::string &type, const std::string &key, std::string &value)
	{
			 if(UTcompvalue)
				value = "on";
			 else
				value = "value";
			 return UTretvalue;
	}
	 bool SettingProxy::getSettingReadyStatus()
	{
				 return UTretvalue;
	}

}
