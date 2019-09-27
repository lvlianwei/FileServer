#ifndef SEARCH_POP_DEVICE_BY_SERINUM_H
#define SEARCH_POP_DEVICE_BY_SERINUM_H
/**
 * @file SmartIosTool.h
 * @brief 
 * @author jianglei
 * @version 1.0
 * @date 2017-07-27
 */
#include "include/SmartIosServiceDefs.h"
#include "SmartIosSettingProxy.h"
#include<sqlite3.h>
namespace goni {
class SmartIosTool {
    private:
	SmartIosTool(){}
	SmartIosTool(SmartIosTool& tool);
	SmartIosTool& operator=(SmartIosTool& tool);
	sqlite3 * mdb;
    public:
	/**
	 * @brief searchPopDevice search pop device pop value by serinum
	 *
	 * @param serinum,the device serinum
	 *
	 * @return ,if device is exist,return it pop value
	 */
          IosPopStatus searchPopDevice(const char * serinum);
	  /**
	   * @brief print ,print all pop device info
	   */
	  void print();
	  /**
	   * @brief deleteAllDevice ,del all pop device 
	   */
	  void deleteAllDevice();
	  static SmartIosTool* getInstance();
	  static SmartIosTool * tool;
};
}
#endif
