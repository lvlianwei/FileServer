#include "SmartIosServiceDefs.h"
#include "testSmartIosSettingProxy.h"
#include<map>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include "servicebase/SystemLog.h"
using namespace std;
namespace Test {
    SingletonForSmartIosSettingProxy::SingletonForSmartIosSettingProxy(){
    }


    SingletonForSmartIosSettingProxy* SingletonForSmartIosSettingProxy::instance = NULL;
    SingletonForSmartIosSettingProxy* SingletonForSmartIosSettingProxy::getInstance(){
        if (NULL == instance)
        {
            instance = new SingletonForSmartIosSettingProxy();
        }
        return instance;
    }
    void SingletonForSmartIosSettingProxy::delInstance(){
        if (NULL != instance)
        {
            delete instance;
            instance = NULL;
        }
    }

    /********************************************************/
    SmartIosSettingProxy* SmartIosSettingProxy::mInstance = NULL;

    SmartIosSettingProxy::SmartIosSettingProxy()    /* __0x408005_DTFUNCID__ */
    {
        // TODO Auto-generated constructor stub
        // mdb = NULL;
    }

    SmartIosSettingProxy::~SmartIosSettingProxy()    /* __0x408006_DTFUNCID__ */ {
        // TODO Auto-generated destructor stub
    }

    SmartIosSettingProxy* SmartIosSettingProxy::getInstance()    /* __0x408007_DTFUNCID__ */
    {
        if(mInstance == NULL){
            mInstance = new SmartIosSettingProxy();

            if (NULL == mInstance){

            }
        }
        return mInstance;
    }

    void SmartIosSettingProxy::dbOperateResultCountClear(void){

    }

    enum SMT_SQL_RET SmartIosSettingProxy::dbOperateRetJudgement(int ret)    /* __0x408023_DTFUNCID__ */{
        UNUSED(ret);
        return SMT_SQL_RET_SUCCESS;
    }

    void SmartIosSettingProxy::deleteTableFromDB(enum SMT_DB_TABLE_TYPE tableType)    /* __0x408008_DTFUNCID__ */{
        UNUSED(tableType);
        return;
    }

    void SmartIosSettingProxy::cleanTablesWhenOpeErr(enum SMT_SQL_RET result, enum SMT_DB_TABLE_TYPE tableType)    /* __0x408009_DTFUNCID__ */{
        UNUSED(result);
        UNUSED(tableType);
        return;
    }

    void SmartIosSettingProxy::closeDB()    /* __0x40800A_DTFUNCID__ */{

        return;
    }
    /**
     * @brief deInit ,close db
     */
    void SmartIosSettingProxy::deInit()    /* __0x40800B_DTFUNCID__ */ {

        closeDB();
    }
    /**
     * @brief initSqlite3DB ,open db
     */
    void SmartIosSettingProxy::initSqlite3DB()    /* __0x40800C_DTFUNCID__ */ {

        return ;
    }
    /**
     * @brief clearNoCompleteData ,reserved for setting service IF
     */
    void SmartIosSettingProxy::clearNoCompleteData()    /* __0x40800D_DTFUNCID__ */ {

    }
    /**
     * @brief resetSettingDB ,reserved for setting service IF
     */
    void SmartIosSettingProxy::resetSettingDB()    /* __0x40800E_DTFUNCID__ */ {

    }
    /**
     * @brief resetSqliteDB ,reset sqlite3 db,clear all data
     */
    void SmartIosSettingProxy::resetSqliteDB()    /* __0x40800F_DTFUNCID__ */ {

    }
    /**
     * @brief delAllDevice ,del all pop device
     */
    void SmartIosSettingProxy::delAllDevice()    /* __0x408010_DTFUNCID__ */ {
        return ;

    }
    /**
     * @brief delSingleDevice ,del single device
     *
     * @param index,device priority in table
     */
    void SmartIosSettingProxy::delSingleDevice(int index)    /* __0x408011_DTFUNCID__ */ {
        UNUSED(index);
        return ;
    }
    void SmartIosSettingProxy::updatePopStatusDevicesPriority(int priority)    /* __0x408012_DTFUNCID__ */ { 
        UNUSED(priority);

        return ;
    }
    int SmartIosSettingProxy::getPopDeviceMaxPriority(goni::SmtDeviceType deviceType)    /* __0x408014_DTFUNCID__ */ {
        UNUSED(deviceType);

        int priority = 0;//no device
        return priority;
    }
    int SmartIosSettingProxy::getNoPopStatusDeviceMaxPriority(goni::SmtDeviceType deviceType)    /* __0x408015_DTFUNCID__ */ {
        UNUSED(deviceType);
        return 0;
    }

    bool SmartIosSettingProxy::deleteNoPopDevice(uint8_t index, goni::SmtDeviceType deviceType)    /* __0x408016_DTFUNCID__ */ {
        UNUSED(index);
        UNUSED(deviceType);
        return true;
    }

    bool SmartIosSettingProxy::insertPopDevice(IosDeviceName* devname, goni::SmtPopStatus setting, int maxPriority, goni::SmtDeviceType deviceType)    /* __0x408017_DTFUNCID__ */ {
        UNUSED(devname);
        UNUSED(setting);
        UNUSED(maxPriority);
        UNUSED(deviceType);
        return true;
    }

    bool SmartIosSettingProxy::insertPopDeviceNoName(IosDeviceName* devname, goni::SmtPopStatus setting, int maxPriority, goni::SmtDeviceType deviceType)    /* __0x408018_DTFUNCID__ */ {
        UNUSED(setting);
        UNUSED(devname);
        UNUSED(maxPriority);
        UNUSED(deviceType);
        return true;
    }
    void SmartIosSettingProxy::replacePopDevice(const char * serialNum,uint8_t popValue, const char * devname,uint8_t nameIsValid,uint8_t nonameindex, goni::SmtDeviceType deviceType)    /* __0x408019_DTFUNCID__ */ {
        UNUSED(popValue);
        UNUSED(devname);
        UNUSED(nameIsValid);
        UNUSED(nonameindex);
        UNUSED(serialNum);
        UNUSED(deviceType);
        return ;

    }

    void SmartIosSettingProxy::replaceNoPopDevice(const char * serialNum,uint8_t popValue,const char * devname,uint8_t nameIsValid,uint8_t nonameindex,uint8_t& index,  goni::SmtDeviceType deviceType)    /* __0x40801A_DTFUNCID__ */ {
        UNUSED(popValue);
        UNUSED(devname);
        UNUSED(nameIsValid);
        UNUSED(nonameindex);
        UNUSED(serialNum);
        UNUSED(index);
        UNUSED(deviceType);
    }

    int SmartIosSettingProxy::setPopStatusReq(goni::SmtSetType setType, uint8_t index, goni::SmtPopStatus setting, goni::SmtDeviceType deviceType)    /* __0x40801B_DTFUNCID__ */
    {
        UNUSED(setType);
        UNUSED(index);
        UNUSED(setting);
        UNUSED(deviceType);
        return 0;
    }

    uint8_t SmartIosSettingProxy::iapDeviceInsert(const char* serialNum, uint8_t* selectStatus, goni::SmtDeviceType deviceType)    /* __0x40801C_DTFUNCID__ */
    {
        return (SingletonForSmartIosSettingProxy::getInstance())->iapDeviceInsert(serialNum,selectStatus,deviceType);
    }

    bool SmartIosSettingProxy::isPopDeviceBySerinum(const char * serinum)    /* __0x40801D_DTFUNCID__ */ {
        UNUSED(serinum);
        return false;
    }
    bool SmartIosSettingProxy::isPopStatusValidHigh(uint8_t pop)    /* __0x40801E_DTFUNCID__ */
    {
        UNUSED(pop);

        return false;
    }
    bool SmartIosSettingProxy::isPopStatusValidLow(uint8_t pop)    /* __0x40801F_DTFUNCID__ */
    {
        UNUSED(pop);

        return false;
    }

    uint8_t SmartIosSettingProxy::getSerialNumIndex(std::string serialNum)    /* __0x408020_DTFUNCID__ */
    {
        UNUSED(serialNum);

        uint8_t i = 0;
        uint8_t index = SMT_IOS_DEVICE_INDEX_INVALID;
        return index;
    }
    void SmartIosSettingProxy::setDeviceName(const char * serinum,const char * devname, goni::SmtDeviceType deviceType)    /* __0x408021_DTFUNCID__ */ {
        UNUSED(serinum);
        UNUSED(devname);
        UNUSED(deviceType);
    }

    bool SmartIosSettingProxy::getDeviceInfo(goni::SmtDevReqType reqType, uint8_t index, std::vector<IosDeviceName*>  *mDevList, goni::SmtDeviceType deviceType)    /* __0x408022_DTFUNCID__ */
    {
        return (SingletonForSmartIosSettingProxy::getInstance())->getDeviceInfo(reqType,index,mDevList,deviceType);
    }
} /* namespace goni */
