
#ifndef TEST_SMARTIOS_SETTINGPROXY_H_
#define TEST_SMARTIOS_SETTINGPROXY_H_
#include <vector>
#include<sqlite3.h>
#include<string>
#include "SmartIosServiceServiceDefines.h"
#include<gtest/gtest.h>
#include<gmock/gmock.h>

namespace Test {
#define  SMT_IOS_DEVICE_NAME_MAX_LEN 64
    /*priority:1 byte, popstatus : 1byte*/
#define	SMT_IOS_SQL_DEVICE_NAME_MAX_LEN         (SMT_IOS_DEVICE_NAME_MAX_LEN+2)
#define SMT_IOS_PRIORITY_INVALID 0
#define SMT_IOS_POP_PRIORITY_START              0x01                                    /*valid device to device info start*/
#define SMT_IOS_POP_PRIORITY_END                0x05                                    /*valid device to device info end*/
#define SMT_IOS_POP_PRIORITY_DEVICE_MAX         5                                       /*device with priority max number*/
#define SMT_IOS_NOPOP_PRIORITY_START            0x01                                    /*valid device to device info start*/
#define SMT_IOS_NOPOP_PRIORITY_END              0x0A                                    /*valid device to device info end*/
#define SMT_IOS_NOPOP_PRIORITY_DEVICE_MAX       0x0A                                    /*device with priority max number*/
#define SMT_IOS_POP_INDEX_START                 0x01                                    /*low pop status device index start*/
#define SMT_IOS_POP_INDEX_END                   0x05                                    /*low pop status device index end*/
#define SMT_IOS_NOPOP_INDEX_START               0x06                                    /*low pop status device index start*/
#define SMT_IOS_NOPOP_INDEX_END                 0x0F                                    /*low pop status device index end*/
#define SMT_IOS_POP_DEVICE_MAX                  5                                       /*device with priority max number*/
#define SMT_IOS_NOPOP_DEVICE_MAX                10                                      /*device with priority max number*/
#define SMT_IOS_DEVICE_INDEX_INVALID            0
#define SMT_IOS_DEVICE_INDEX_START              1                                       /*IOS Device in database start*/
#define SMT_IOS_DEVICE_INDEX_MAX                15                                      /*IOS Device in database end*/
#define SMT_IOS_DEVICE_COUNT_MAX                16                                      /*max device in list include one invalid device which index is 0*/
#define SMT_IOS_DEVICE_SERIALNUM_MAX            40                                      /*max string + '\0' */
#define SMT_IOS_DUMP_SQL
#define SMT_IOS_NOUPDATE                        0
#define SMT_IOS_UPDATE                          1
#define SMT_IOS_DEVICE_INDEX_BEGIN(x)           (x == TRUE) ? SMT_IOS_POP_INDEX_START : SMT_IOS_NOPOP_INDEX_START
#define SMT_IOS_DEVICE_INDEX_END(x)             (x == TRUE) ? SMT_IOS_POP_INDEX_END : SMT_IOS_NOPOP_INDEX_END
#define SMT_IOS_DEVICE_TYPE_MAX(x)              (x == TRUE) ? SMT_IOS_POP_DEVICE_MAX : SMT_IOS_NOPOP_DEVICE_MAX

    //code version
#define VERSION_1 "1.0"
#define VERSION_2 "2.0"
#define VERSION_3 "3.0"
#define VERSION_4 "4.0"
#define VERSION_5 "5.0"
    /*column name enum*/
    enum ColumnName {
        COLUMN_SERINUM,
        COLUMN_PRIORITY,
        COLUMN_POPSTATUS,
        COLUMN_DEVNAME,
        COLUMN_NAMEISVALID,
        COLUMN_INDEX,
        COLUMN_NUM
    };
    /* transaction opcode*/
    enum TransOpcode {
        TRANS_POPUP_SET,
        TRANS_MANU_SET,
        TRANS_DEL_SIN_DEVICE
    };
    enum nameIsValidValue {
        NAME_IS_VALID,
        NAME_IS_INVALID
    };
    /*IOS Pop Status*/
    enum IosPopStatus
    {
        IOS_POPSTATUS_INVALID,
        IOS_POPSTATUS_AUTOCARPLAY,
        IOS_POPSTATUS_AUTOWEBLINK
    };

    enum IosSelectSource
    {
        IosSelectCarplay,
        IosSelectCarlife,
        IosSelectIpod,
    };

    /*Get Ios Device Info Request type*/
    enum IosDevInfoReqType
    {
        IosReqAll,
        IosReqSingle
    };

    enum SMT_SQL_RET{
        SMT_SQL_RET_SUCCESS,
        SMT_SQL_RET_FAIL,
        SMT_SQL_RET_NEED_RESET_DB,
        SMT_SQL_RET_NEED_DELETE_DB
    };

    enum SMT_DB_TABLE_TYPE{
        SMT_DB_TABLE_TYPE_POP_IOS,
        SMT_DB_TABLE_TYPE_NO_POP_IOS,
        SMT_DB_TABLE_TYPE_POP_ANDROID,
        SMT_DB_TABLE_TYPE_NO_POP_ANDROID,
        SMT_DB_TABLE_TYPE_VERSION
    };

    /*the data structure  in database for key device name */
    union IosDeviceName{
        uint8_t data[SMT_IOS_SQL_DEVICE_NAME_MAX_LEN];
        struct{
            uint8_t priority;
            uint8_t popStatus;
            uint8_t deviceName[SMT_IOS_DEVICE_NAME_MAX_LEN + 1];
            uint8_t serinum[SMT_IOS_DEVICE_SERIALNUM_MAX + 1];
            uint8_t nameIsValid;
            uint8_t index;
        }format;
    };

    struct SmartIosIosDevInfo{
        uint8_t update;				/*need update databe flag*/
        uint8_t index;					/*index in database*/
        IosDeviceName devInfo;
    };

    /*database key name*/
    struct IosDataBaseKey{
        std::string deviceName;			/*device name key data->IosDeviceName*/
        std::string serialNum;				/*serial number key*/
    };

    struct IosSqlData{
        std::string key;				/*serial number key*/
        std::string content;
    };
    class SingletonForSmartIosSettingProxy{
        public:
            static SingletonForSmartIosSettingProxy* getInstance();
            static void delInstance();
            MOCK_METHOD3(iapDeviceInsert,uint8_t(const char* ,  uint8_t* , goni::SmtDeviceType));
            MOCK_METHOD4(getDeviceInfo,bool(goni::SmtDevReqType , uint8_t , std::vector<IosDeviceName*>  *, goni::SmtDeviceType));
        private:
            SingletonForSmartIosSettingProxy();
            //SingletonForSmartIosSettingProxy(const SingletonForSmartIosSettingProxy&) = delete;
            //SingletonForSmartIosSettingProxy& operator= (const SingletonForSmartIosSettingProxy) = delete;
            static SingletonForSmartIosSettingProxy* instance;
    };
    class SmartIosSettingProxy {
        public:
            virtual ~SmartIosSettingProxy();
            /**
             * @brief getInstance ,get setting instance
             *
             * @return,static instance 
             */
            static SmartIosSettingProxy* getInstance();
            /**
             * @brief setPopStatusReq ,set device pop status
             *
             * @param setType,0: pop up set,1: manu set
             * @param index,device priority in database
             * @param setting,pop value
             */
            virtual int setPopStatusReq(goni::SmtSetType setType,  uint8_t index, goni::SmtPopStatus setting, goni::SmtDeviceType deviceType);
            /**
             * @brief iapDeviceInsert ,called when iphone insert
             *
             * @param serialNum,iphone serinum
             * @param selectStatus,to obtain iphone pop status
             *
             * @return,device priority in database 
             */
            virtual uint8_t  iapDeviceInsert(const char* serialNum,  uint8_t* selectStatus, goni::SmtDeviceType deviceType);
            /**
             * @brief getDeviceInfo ,get device info
             *
             * @param reqType,0: get all pop device info,1: get single pop device info
             * @param index,used when get single pop device info
             * @param mDevList,container to save device info
             *
             * @return 
             */
            virtual bool getDeviceInfo(goni::SmtDevReqType reqType, uint8_t index, std::vector<IosDeviceName*>  *mDevList, goni::SmtDeviceType deviceType);
            /**
             * @brief setDeviceName ,set iphone device really name
             *
             * @param serinum,device serinum
             * @param devname,really name
             */
            virtual void setDeviceName(const char * serinum,const char * devname, goni::SmtDeviceType deviceType);
            /**
             * @brief delSingleDevice ,del single pop device
             *
             * @param index,the device priority in database
             */
            virtual void delSingleDevice(int index);
            /**
             * @brief delAllDevice ,del all pop device,called when reset Factory setting
             */
            virtual void delAllDevice();
            /**
             * @brief resetSettingDB reserved for setting IF
             */
            virtual void resetSettingDB();
            /**
             * @brief resetSqliteDB reset sqlite3 database,clear all data
             */
            virtual void resetSqliteDB();
            /**
             * @brief clearNoCompleteData reserved for setting IF
             */
            virtual void clearNoCompleteData();
            /**
             * @brief initSqlite3DB ,init database,open db,crate table
             */
            virtual void dbOperateResultCountClear(void);
            virtual enum SMT_SQL_RET dbOperateRetJudgement(int ret);
            virtual void deleteTableFromDB(enum SMT_DB_TABLE_TYPE tableType);
            virtual void cleanTablesWhenOpeErr(enum SMT_SQL_RET result, enum SMT_DB_TABLE_TYPE tableType);
            virtual void closeDB();
            virtual void initSqlite3DB();
            /**
             * @brief deInit close database,release resource
             */
            virtual void deInit();
        private:
            SmartIosSettingProxy();
            static SmartIosSettingProxy* mInstance;
            /**
             * @brief isPopStatusValidHigh ,judge the pop is or not pop value
             *
             * @param pop,wait judge 
             *
             * @return ,if yes return true,or return faild
             */
            virtual bool isPopStatusValidHigh(uint8_t pop);
            /**
             * @brief isPopStatusValidLow ,judge the pop is or not no pop vlaue
             *
             * @param pop,wait judge
             *
             * @return yes return true,no return false
             */
            virtual bool isPopStatusValidLow(uint8_t pop);
            /**
             * @brief getSerialNumIndex ,reserved for setting IF
             *
             * @param serialNum
             *
             * @return 
             */
            virtual uint8_t getSerialNumIndex(std::string serialNum);
            /**
             * @brief getNoPopStatusDeviceMaxPriority ,get current all no pop deviec max priority
             *
             * @return max priority
             */
            virtual int getNoPopStatusDeviceMaxPriority(goni::SmtDeviceType deviceType);
            /**
             * @brief getPopDeviceMaxPriority ,get current all pop device max priority
             *
             * @return max priority
             */
            virtual int getPopDeviceMaxPriority(goni::SmtDeviceType deviceType);
            /**
             * @brief updateNoPopStatusDevicesPriority ,when del a device,update other no pop device priority
             *
             * @param priority deleted device's priority
             */
            virtual void updateNoPopStatusDevicesPriority(int priority, goni::SmtDeviceType deviceType){UNUSED(priority);UNUSED(deviceType);}
            /**
             * @brief updatePopStatusDevicesPriority ,when del a pop device,update other pop device priority
             *
             * @param priority,deleted device's priority
             */
            virtual void updatePopStatusDevicesPriority(int priority);
            /**
             * @brief isPopDeviceBySerinum ,judge the deive is or not pop deivce by serinum
             *
             * @param serinum,device's serinum
             *
             * @return ,yes return true,no return no
             */
            virtual bool isPopDeviceBySerinum(const char * serinum);
            /**
             * @brief replacePopDevice ,when pop list full,replace pop deivce
             *
             * @param serialNum,new device serinum
             * @param popValue,new device popValue
             * @param devname,new device devname
             * @param nameIsValid,new device nameIsValid flag
             * @param nonameindex,new device nonameindex
             */
            virtual void replacePopDevice(const char * serialNum,uint8_t popValue,const char* devname,uint8_t nameIsValid,uint8_t nonameindex, goni::SmtDeviceType deviceType);
            /**
             * @brief replaceNoPopDevice ,when no pop list full,replace no pop device
             *
             * @param serialNum
             * @param popValue
             * @param devname
             * @param nameIsValid
             * @param nonameindex
             * @param index
             */
            virtual void replaceNoPopDevice(const char* serialNum,uint8_t popValue,const char * devname,uint8_t nameIsValid,uint8_t nonameindex,uint8_t& index, goni::SmtDeviceType deviceType);
            virtual bool deleteNoPopDevice(uint8_t index, goni::SmtDeviceType deviceType);
            virtual bool insertPopDevice(IosDeviceName* devname, goni::SmtPopStatus setting, int maxPriority, goni::SmtDeviceType deviceType);
            virtual bool insertPopDeviceNoName(IosDeviceName* devname, goni::SmtPopStatus setting, int maxPriority, goni::SmtDeviceType deviceType);

        public:
        private:
            //SmartIosSettingProxy(const SmartIosSettingProxy& )=delete;
            //SmartIosSettingProxy &operator=(const SmartIosSettingProxy&)=delete;
        private:
    };

} 
using namespace Test;

#endif /* APPLICATION_FUNCMNG_SYSTEM_SMTSETTINGPROXY_H_ */
