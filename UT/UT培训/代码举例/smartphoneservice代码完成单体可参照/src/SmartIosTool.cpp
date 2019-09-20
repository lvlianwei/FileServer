/**
 * @file SmartIosTool.cpp
 * @brief 
 * @author jianglei
 * @version 1
 * @date 2017-07-27
 */
#include "SmartIosTool.h"
#include<string.h>
#include "servicebase/SystemLog.h"
namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);

#define IPHONE_DB_DIR "/var/iphoneDevices.db" 
#define SQL_MAX_LEN 1024
#define CURRENT_VERSION VERSION_1
/**
    * @brief record select result count
    */
int resultCount = 0;
/**
    * @brief sqlite3_callback ,called when execute select sql statement
    *
    * @param para
    * @param column_num
    * @param column_value
    * @param column_name
    *
    * @return 
    */
static int sqlite3_callback(void * para,int column_num,char ** column_value,char ** column_name)    /* __0x409001_DTFUNCID__ */ {
    UNUSED(column_name);
    resultCount++;
    if(para != NULL && (column_num == 6)) {
        IosDeviceName *devname = (IosDeviceName*)para;
        memcpy(devname->format.serinum,column_value[0],SMT_IOS_DEVICE_SERIALNUM_MAX);
        devname->format.serinum[SMT_IOS_DEVICE_SERIALNUM_MAX] = '\0';
        devname->format.priority = atoi(column_value[1]); 
        devname->format.popStatus = atoi(column_value[2]);
        memcpy(devname->format.deviceName,column_value[3],SMT_IOS_DEVICE_NAME_MAX_LEN);
        devname->format.deviceName[SMT_IOS_DEVICE_NAME_MAX_LEN] = '\0';
        devname->format.nameIsValid = atoi(column_value[4]);
        devname->format.index = atoi(column_value[5]);
    }
    return 0;
}
SmartIosTool* SmartIosTool::tool = NULL;
SmartIosTool* SmartIosTool::getInstance()     /* __0x409002_DTFUNCID__ */{
    if(tool == NULL) {
        tool = new SmartIosTool;
    }
    return tool;
}
/**
    * @brief searchPopDevice ,search pop device popstatus by serinum
    *
    * @param serinum
    *
    * @return if device exist return it pop value 
    */
IosPopStatus SmartIosTool::searchPopDevice(const char *serinum)     /* __0x409003_DTFUNCID__ */ {
    SMTLOGD("serinum is %s",serinum);
    IosPopStatus status = IOS_POPSTATUS_INVALID;
    IosDeviceName devname;
    memset(&devname,0,sizeof(IosDeviceName));
    if(serinum == NULL) {
        SMTLOGD("serinum is null");
        return status;
    }
    //1 open db
    if(SQLITE_OK == sqlite3_open(IPHONE_DB_DIR,&mdb)) {
        SMTLOGD("sqlite3 open database success");
    }
    else {
        SMTLOGD("sqlite3 open faild");
        return status;
    }
    //2 search pop device
    if(strcmp(CURRENT_VERSION,VERSION_1) == 0) {
        SMTLOGD("current db version is version_1");
        char sql[SQL_MAX_LEN];
        char * errMsg = NULL;
        snprintf(sql,SQL_MAX_LEN,"select * from popDevices where serinum = '%s'",serinum);
        if(SQLITE_OK == sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&devname,&errMsg)) {
            if(resultCount != 0) {
                SMTLOGD("find the pop device,popStatus %d,devname %s",devname.format.popStatus,devname.format.deviceName);
                status = (IosPopStatus)devname.format.popStatus;
                resultCount = 0;
            }
            else {
                SMTLOGD("no find the pop device");
            }
        }
        else {
            SMTLOGD("search faild,errMsg %s",errMsg);
        }
    }
    //3 close db,return popStatus
    if(mdb) {
        sqlite3_close(mdb);
        mdb = NULL;
    }
    return status;
}
/**
    * @brief print print all pop device info
    */
void SmartIosTool::print()     /* __0x409004_DTFUNCID__ */ {
    char sql[SQL_MAX_LEN] = {0};
    char * errMsg = NULL;
    char ** result = NULL;
    int nRow = 0;
    int nCol = 0;
    snprintf(sql,SQL_MAX_LEN,"select * from popDevices");
    //1 open db
    if(SQLITE_OK == sqlite3_open(IPHONE_DB_DIR,&mdb)) {
        SMTLOGD("open db success");
    }
    else {
        SMTLOGD("open db faild");
        return;
    }
    // 2 search device
    if(strcmp(CURRENT_VERSION,VERSION_1) == 0) {
        SMTLOGD("current db version is version_1");
        if(SQLITE_OK == sqlite3_get_table(mdb,sql,&result,&nRow,&nCol,&errMsg)) {
            SMTLOGD("sqlite3 get table success");
            SMTLOGD("row %d,col %d",nRow,nCol);
            int index = nCol;
            for(int i = 0; i < nRow; ++i) {
            SMTLOGD("serinum %s,priority %s,popStatus %s,devname %s,nameIsValid %s,nonameIndex %s",result[index],result[index + 1],result[index + 2],result[index + 3],result[index + 4],result[index + 5]);
            index += nCol;
            }
            sqlite3_free_table(result);
        }
        else {
            SMTLOGD("sqlite3 get table faild,errMsg %s",errMsg);
        }
    }
    //3close db
    if(SQLITE_OK == sqlite3_close(mdb)) {
        SMTLOGD("close db success");
    }
    else {
        SMTLOGD("close faild");
    }
}
/**
    * @brief deleteAllDevice ,del all pop device
    */
void SmartIosTool::deleteAllDevice()     /* __0x409005_DTFUNCID__ */ {
    char sql[SQL_MAX_LEN] = {0};
    char * errMsg = NULL;
    //1 open db
    if(SQLITE_OK == sqlite3_open(IPHONE_DB_DIR,&mdb)) {
        SMTLOGD("open db success");
    }
    else {
        SMTLOGD("open db faild");
        return;
    }
    //2 delete device
    if(strcmp(CURRENT_VERSION,VERSION_1) == 0) {
        SMTLOGD("db version is version_1");
        snprintf(sql,SQL_MAX_LEN,"delete from popDevices");
        if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
            SMTLOGD("delete pop device success");
        }
        else {
            SMTLOGD("delete pop device faild,errMsg %s",errMsg);
        }
        snprintf(sql,SQL_MAX_LEN,"delete from noPopDevices");
        if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
            SMTLOGD("delete pop device success");
        }
        else {
            SMTLOGD("delete pop device faild,errMsg %s",errMsg);
        }
    }
    //3 close db
    if(SQLITE_OK == sqlite3_close(mdb)) {
        SMTLOGD("close db success");
    }
    else {
        SMTLOGD("close db faild");
    }
}
}
