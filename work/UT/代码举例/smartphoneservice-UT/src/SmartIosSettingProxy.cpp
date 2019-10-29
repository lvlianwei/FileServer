/*
 * SmartIosSettingProxy.cpp
 *
 *  Created on: 2017年4月23日
 *      Author: zjh
 */
#include "include/SmartIosServiceDefs.h"
#include "SmartIosSettingProxy.h"
#include<map>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include "servicebase/SystemLog.h"
using namespace std;
namespace goni {
DeclearModuleID(DTMODULEID_SMARTIOS);
/**
 *   control code and database version logic  
 *   1 first code version is equal database version
     2 when code version increase,code > database,need update database version to same
     3 when code version lower,code < database,we action is clear database,and update version to the same
 *
 *
 */
#define CURRENT_VERSION VERSION_2 //control codec version
#define SQL_MAX_LENGTH 1024
#define USE_SQLITE3_DB "sqlite3_db"
#define IPHONE_DB_DIR "/var/iphoneDevices.db"
//#define FULL_REPLACE_1 "replace1"
//#define FULL_REPLACE_DEBUG "replace debug"
#define TRUE 1
#define FALSE 0
    /**
     * @brief ,record select result count
     */
    int resultCount = 0;
    int resultCountOpe = 0;
    /**
     * @brief sqlite3_callback ,called when execute select sql statement
     *
     * @param para,call function gived param
     * @param column_num,column num
     * @param column_value,all column value,char 2 d array
     * @param column_name,all column name,char 2 d array
     *
     * @return 
     */
int sqlite3_callback(void * para,int column_num,char ** column_value,char ** column_name)    /* __0x408001_DTFUNCID__ */ {
    UNUSED(column_name);
    resultCount++;
    if((para != NULL) && (column_num == COLUMN_NUM) && (NULL != column_value[0])) {
        IosDeviceName *devname = (IosDeviceName*)para;
        int len = strlen(column_value[COLUMN_SERINUM]);
        if(len > SMT_IOS_DEVICE_SERIALNUM_MAX) {
            len = SMT_IOS_DEVICE_SERIALNUM_MAX;
        }
        memcpy(devname->format.serinum,column_value[COLUMN_SERINUM],len);
        devname->format.serinum[len] = '\0';
        devname->format.priority = atoi(column_value[COLUMN_PRIORITY]); 
        devname->format.popStatus = atoi(column_value[COLUMN_POPSTATUS]);
        len = strlen(column_value[COLUMN_DEVNAME]);
        if(len > SMT_IOS_DEVICE_NAME_MAX_LEN) {
            len = SMT_IOS_DEVICE_NAME_MAX_LEN;
        }
        memcpy(devname->format.deviceName,column_value[COLUMN_DEVNAME],len);
        devname->format.deviceName[len] = '\0';
        devname->format.nameIsValid = atoi(column_value[COLUMN_NAMEISVALID]);
        devname->format.index = atoi(column_value[COLUMN_INDEX]);
    }
    /*only get priority column,call wneh get max priority case*/
    else if(para != NULL && (column_num == 1) && (column_value[0] != NULL)) {
        IosDeviceName *devname = (IosDeviceName*)para;
        devname->format.priority = atoi(column_value[0]); 
    }
    return 0;        
}
int sqlite3_versionCb(void * param,int column_num,char ** column_value,char **column_name)    /* __0x408002_DTFUNCID__ */ {
    UNUSED(column_name);
    resultCount++;
    /*get db version info,only one column*/
    if(param != NULL && (column_value[0] != NULL) && (column_num == 1)) {
        /*
            *before called strncpy,param point memory area is initialization to 0,it length is 10
            *so most copy 9 bytes from column_value[0],left one byte for '\0'
            */
        strncpy((char*)param,column_value[0],9);
    }
    return 0;
}
#define DATA_DUM_LOG
void devName2String(IosDeviceName name,string& nameStr)    /* __0x408003_DTFUNCID__ */ {
    char str[SMT_IOS_SQL_DEVICE_NAME_MAX_LEN];
    char priority[2] = {0};
    sprintf(priority,"%d",name.format.priority - 1);
    str[0] = priority[0];
    char popStatus[2] = {0};
    sprintf(popStatus,"%d",name.format.popStatus);
    str[1] = popStatus[0];
    memcpy(&str[2],name.format.deviceName,SMT_IOS_DEVICE_NAME_MAX_LEN);
    nameStr = str;
}
void string2devName(string nameStr,IosDeviceName &name)    /* __0x408004_DTFUNCID__ */ {
    char priority[2] = {0};
    char popStatus[2] = {0};
    priority[0] = nameStr.c_str()[0];
    popStatus[0] = nameStr.c_str()[1];
    name.format.priority = atoi(priority) + 1;
    name.format.popStatus = atoi(popStatus);
    memcpy(name.format.deviceName,&nameStr.c_str()[2],SMT_IOS_DEVICE_NAME_MAX_LEN);
}
/**
    * @brief pop value array
    */
const uint8_t mPopStatusHighTable[] ={
    IOS_POPSTATUS_AUTOCARPLAY,
    IOS_POPSTATUS_AUTOWEBLINK
};
/**
    * @brief no pop value array
    */
const uint8_t mPopStatusLowTable[] ={/*IOS_POPSTATUS_INVALID,*/
    //IOS_POPSTATUS_NOCARLIFEMANULLY,
    //IOS_POPSTATUS_NOCARPLAYMANULLY
};

#ifdef UT_GTEST_FULL_ENG
void SmartIosSettingProxy::ForLocalFunc()
{
	char a[COLUMN_NUM][2] = {"2","2","3","4","5","6"};
    IosDeviceName paraptr;
    memset(&paraptr,2,sizeof(paraptr));
	string nameStr = "0";
	int column_num = 1;
	char aa;
	char* column_value[COLUMN_NUM] = {&aa,&aa,&aa,&aa,&aa,&aa};
	char* column_name = NULL;
	sqlite3_callback(&paraptr,column_num,column_value,&column_name);
	sqlite3_versionCb(&paraptr,column_num,column_value,&column_name);
	column_num = COLUMN_NUM;
	sqlite3_callback(&paraptr,column_num,column_value,&column_name);
	column_num = COLUMN_NAMEISVALID;
	sqlite3_versionCb(&paraptr,column_num,column_value,&column_name);
	sqlite3_callback(&paraptr,column_num,column_value,&column_name);
	IosDeviceName devname;
    memset(&devname,2,sizeof(devname));
	devName2String(devname,nameStr);
	string2devName(nameStr,devname);
	#if 0
	char *bb = "124ehkbg32wiu3d2bg9fd2u3h9u4hf9u433hgv97u43hvoiurnvoklfnbviuhbn9u43orerkgjvno3j";
	char* column_value1[COLUMN_NUM] = {bb,bb,bb,bb,bb,bb};
	sqlite3_callback(&paraptr,column_num,column_value1,&column_name);
	#endif
}
void SmartIosSettingProxy::ForSetLocalValue(int count)
{
	resultCountOpe = count;
}
int SmartIosSettingProxy::ForGetLocalValue()
{
	return resultCountOpe;
}
#endif

/********************************************************/
SmartIosSettingProxy* SmartIosSettingProxy::mInstance = NULL;

SmartIosSettingProxy::SmartIosSettingProxy()    /* __0x408005_DTFUNCID__ */
{
    // TODO Auto-generated constructor stub
    mdb = NULL;
}

SmartIosSettingProxy::~SmartIosSettingProxy()    /* __0x408006_DTFUNCID__ */ {
    // TODO Auto-generated destructor stub
}

SmartIosSettingProxy* SmartIosSettingProxy::getInstance()    /* __0x408007_DTFUNCID__ */
{
    if(mInstance == NULL){
        mInstance = new SmartIosSettingProxy();
        
        if (NULL == mInstance){
            DTLOG_PTRASSERT(mInstance);
        }
    }
    return mInstance;
}

void SmartIosSettingProxy::dbOperateResultCountClear(void){
    //Record the resultCount of the DB operate
    resultCountOpe = resultCount;
    //Clean the resultCount for the next DB operate
    resultCount = 0;
}

enum SMT_SQL_RET SmartIosSettingProxy::dbOperateRetJudgement(int ret)    /* __0x408023_DTFUNCID__ */{
    enum SMT_SQL_RET result = SMT_SQL_RET_SUCCESS;
    
    DTLOG_INFO(0x408023, "SmartIosSettingProxy::dbOperateRetJudgement ret = %d", ret);
    SMTLOGD("SmartIosSettingProxy::dbOperateRetJudgement, ret = %d", ret);
    switch (ret){
        case SQLITE_OK:
        case SQLITE_DONE:
        case SQLITE_ROW:
        case SQLITE_WARNING:
            result = SMT_SQL_RET_SUCCESS;
            break;
        case SQLITE_CANTOPEN:
        case SQLITE_CORRUPT:
        case SQLITE_INTERNAL:
        case SQLITE_NOMEM:
        case SQLITE_NOTADB:
        case SQLITE_PROTOCOL:
            SMTLOGD("SmartIosSettingProxy::dbOperateRetJudgement, Error need delete DB ret = %d", ret);
            result = SMT_SQL_RET_NEED_DELETE_DB;
            mdb = NULL;
            break;
        case SQLITE_FULL:
        case SQLITE_IOERR:
        case SQLITE_MISMATCH:
        case SQLITE_NOLFS:
        case SQLITE_RANGE:
            SMTLOGD("SmartIosSettingProxy::dbOperateRetJudgement, Error need reset DB ret = %d", ret);
            result = SMT_SQL_RET_NEED_RESET_DB;
            mdb = NULL;
            break;
        case SQLITE_ABORT:
        case SQLITE_INTERRUPT:
        case SQLITE_AUTH:
        case SQLITE_CONSTRAINT:
        case SQLITE_MISUSE:
        case SQLITE_NOTFOUND:
        case SQLITE_NOTICE:
        case SQLITE_SCHEMA:
        case SQLITE_BUSY:
        case SQLITE_LOCKED:
        case SQLITE_TOOBIG:
        case SQLITE_PERM:
        case SQLITE_READONLY:
        default:
            result = SMT_SQL_RET_FAIL;
            mdb = NULL;
            break;
    }
    
    DTLOG_INFO(0x408023, "SmartIosSettingProxy::dbOperateRetJudgement result = %d", result);
    
    //Record the resultCount of the DB operate
    dbOperateResultCountClear();
    return result;
}

void SmartIosSettingProxy::deleteTableFromDB(enum SMT_DB_TABLE_TYPE tableType)    /* __0x408008_DTFUNCID__ */{
    char sql[SQL_MAX_LENGTH] = {0};
    
    DTLOG_INFO(0x408008, "SmartIosSettingProxy::deleteTableFromDB tableType = %d", tableType);
    SMTLOGD("SmartIosSettingProxy::deleteTableFromDB");
    if (NULL != mdb){
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
            DTLOG_ERR(0x408008, "DB operate begin fail");
            SMTLOGD("SmartIosSettingProxy::deleteTableFromDB, begin fail");
            return;
        }
        
        switch (tableType){
            case SMT_DB_TABLE_TYPE_POP_IOS:
                snprintf(sql, SQL_MAX_LENGTH, "delete from popDevices");
                break;
            case SMT_DB_TABLE_TYPE_NO_POP_IOS:
                snprintf(sql, SQL_MAX_LENGTH, "delete from noPopDevices");
                break;
            case SMT_DB_TABLE_TYPE_POP_ANDROID:
                snprintf(sql, SQL_MAX_LENGTH, "delete from popDevicesAndr");
                break;
            case SMT_DB_TABLE_TYPE_NO_POP_ANDROID:
                snprintf(sql, SQL_MAX_LENGTH, "delete from noPopDevicesAndr");
                break;
            case SMT_DB_TABLE_TYPE_VERSION:
                snprintf(sql, SQL_MAX_LENGTH, "delete from versionInfo");
                break;
            default:
                return;
                break;
        }
        
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, sql, NULL, NULL, NULL))){
            DTLOG_ERR(0x408008, "DB operate fail");
            SMTLOGD("SmartIosSettingProxy::deleteTableFromDB, delete popDevices fail");
            return;
        }
        
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
            DTLOG_ERR(0x408008, "DB operate commit fail");
            SMTLOGD("SmartIosSettingProxy::deleteTableFromDB, commit fail");
            return;
        }
    }
    else{
        DTLOG_ERR(0x408008, "smartphone mdb is NULL");
        SMTLOGD("SmartIosSettingProxy::deleteTableFromDB, smartphone mdb is NULL");
        return;
    }
    
    return;
}

void SmartIosSettingProxy::cleanTablesWhenOpeErr(enum SMT_SQL_RET result, enum SMT_DB_TABLE_TYPE tableType)    /* __0x408009_DTFUNCID__ */{
    if ((SMT_SQL_RET_NEED_RESET_DB == result) || (SMT_SQL_RET_FAIL == result)){
        DTLOG_INFO(0x408009, "SmartIosSettingProxy::cleanTablesWhenOpeErr result = %d", result);
        deleteTableFromDB(tableType);
    }
    
    return;
}

void SmartIosSettingProxy::closeDB()    /* __0x40800A_DTFUNCID__ */{
    DTLOG_INFO(0x40800A, "SmartIosSettingProxy::closeDB");
    SMTLOGD("SmartIosSettingProxy::closeDB");
    enum SMT_SQL_RET result;
    
    if (NULL != mdb){
        result = dbOperateRetJudgement(sqlite3_close(mdb));
        
        switch (result){
            case SMT_SQL_RET_NEED_DELETE_DB:
            case SMT_SQL_RET_FAIL:
            case SMT_SQL_RET_NEED_RESET_DB:
                mdb = NULL;
                return;
                break;
            case SMT_SQL_RET_SUCCESS:
            default:
                break;
        }
    }
    else{
        DTLOG_ERR(0x40800A, "smartphone mdb is NULL");
        SMTLOGD("SmartIosSettingProxy::closeDB, mdb is NULL");
        return;
    }
    
    mdb = NULL;
    return;
}
/**
    * @brief deInit ,close db
    */
void SmartIosSettingProxy::deInit()    /* __0x40800B_DTFUNCID__ */ {
    DTLOG_INFO(0x40800B, "SmartIosSettingProxy::closeDB");
    SMTLOGD("SmartIosSettingProxy::deInit");
#if 0
    if(mdb) {
        if(SQLITE_OK == sqlite3_close(mdb)) {
            SMTLOGD("close sqlite db success");
            mdb = NULL;
        }
        else {
            SMTLOGD("close sqlite db faild");
        }
    }
#endif
    closeDB();
}
/**
    * @brief initSqlite3DB ,open db
    */
void SmartIosSettingProxy::initSqlite3DB()    /* __0x40800C_DTFUNCID__ */ {
    DTLOG_INFO(0x40800C, "SmartIosSettingProxy::initSqlite3DB");
    enum SMT_SQL_RET result;
    //open iphone db
    result = dbOperateRetJudgement(sqlite3_open(IPHONE_DB_DIR,&mdb));
        
    switch (result){
        case SMT_SQL_RET_NEED_DELETE_DB:
        case SMT_SQL_RET_NEED_RESET_DB:
        case SMT_SQL_RET_FAIL:
            DTLOG_INFO(0x40800C, "DB open fail, close and remove DB");
            closeDB();
            
            int ret;
            ret = remove(IPHONE_DB_DIR);
            if (0 != ret ){
                DTLOG_ERR(0x40800C, "DB file remover fail");
                SMTLOGD("SmartIosSettingProxy::initSqlite3DB, DB file delete fail");
                
                return;
            }
            
            //Creat DB file again
            result = dbOperateRetJudgement(sqlite3_open(IPHONE_DB_DIR, &mdb));
            
            if (SMT_SQL_RET_SUCCESS != result){
                DTLOG_INFO(0x40800C, "DB open fail again");
                //Open DB file fail again
                return;
            }
            break;
        case SMT_SQL_RET_SUCCESS:
        default:
            break;
    }
    
    if (NULL == mdb){
        SMTLOGD("smartios mdb is NULL");
        DTLOG_ERR(0x40800C, "smartphone mdb is NULL");
        
        return;
    }
    //increase write speed
    SMTLOGD("current code version is %s",CURRENT_VERSION);
    char sql[SQL_MAX_LENGTH] = {0};
    char * errMsg = NULL;
    char dbVersion[10] = {0};
    snprintf(dbVersion,10,"1.0");
    
    //select versionInfo table is or not exist
    snprintf(sql,SQL_MAX_LENGTH,"select * from sqlite_master where type = 'table' and name = 'popDevices'");
    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg));
    if(SMT_SQL_RET_SUCCESS == result) {
        SMTLOGD("resultCountOpe = %d",resultCountOpe);
        if(resultCountOpe == 0) {
            DTLOG_INFO(0x40800C, "the table popDevices is not exist");
            SMTLOGD("the table popDevices is not exist");
            snprintf(sql,SQL_MAX_LENGTH,"create table popDevices(serinum varchar(40) primary key,priority integer,popStatus integer,devname varchar(64),nameIsValid integer,nonameindex integer)");
            result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
            if(SMT_SQL_RET_SUCCESS == result) {
                DTLOG_INFO(0x40800C, "create table popDevices success");
                SMTLOGD("create table popDevices success");
            }
            else {
                DTLOG_INFO(0x40800C, "create table pop Devices faild");
                SMTLOGD("create table pop Devices faild,errMsg %s",errMsg);
                cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
        
                return;
            }
        }
        else {
            SMTLOGD("the table popDevices is exist");
            snprintf(sql,SQL_MAX_LENGTH,"select * from popDevices");
            result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg));
            if(SMT_SQL_RET_SUCCESS == result) {
                if(resultCountOpe > SMT_IOS_POP_DEVICE_MAX) {
                    DTLOG_ERR(0x40800C, "popDevices count > %d,the count is error!", SMT_IOS_POP_DEVICE_MAX);
                    SMTLOGD("popDevices count > %d,the count is error,",SMT_IOS_POP_DEVICE_MAX);
                    DTLOG_INFO(0x40800C, "delete all pop devices");
                    SMTLOGD("delete all pop devices");
                    snprintf(sql,SQL_MAX_LENGTH,"delete from popDevices");
                    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == result) {
                        DTLOG_INFO(0x40800C, "delete all pop devices success");
                        SMTLOGD("delete all pop devices success");
                    }
                    else {
                        DTLOG_ERR(0x40800C, "delete all pop device faild");
                        SMTLOGD("delete all pop device faild,errMsg %s",errMsg);
                        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
                        return;
                    }
                }
                else {
                    DTLOG_INFO(0x40800C, "popDevice count = %d\n", resultCountOpe);
                    SMTLOGD("popDevice count = %d\n",resultCountOpe);
                }
            }
            else {
                DTLOG_INFO(0x40800C, "select from popDevices faild");
                SMTLOGD("select from popDevices faild,errmsg %s",errMsg);
                cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
                return;
            }
        }
    }
    else {
        DTLOG_ERR(0x40800C, "select from sqlite_master faild");
        SMTLOGD("select from sqlite_master faild,errMsg %s",errMsg);
        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
        
        return;
    }


    snprintf(sql,SQL_MAX_LENGTH,"select * from sqlite_master where type = 'table' and name = 'noPopDevices'");
    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg));
    if(SMT_SQL_RET_SUCCESS == result) {
        SMTLOGD("resultCountOpe = %d",resultCountOpe);
        if(resultCountOpe == 0) {
            DTLOG_INFO(0x40800C, "the table nopopDevices is not exist");
            SMTLOGD("the table nopopDevices is not exist");
            snprintf(sql,SQL_MAX_LENGTH,"create table noPopDevices(serinum varchar(40) primary key,priority integer,popStatus integer,devname varchar(64),nameIsValid integer,nonameindex integer)");
            result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
            if(SMT_SQL_RET_SUCCESS == result) {
                DTLOG_INFO(0x40800C, "create table nopopDevices success");
                SMTLOGD("create table nopopDevices success");
            }
            else {
                DTLOG_ERR(0x40800C, "create table nopopDevices faild");
                SMTLOGD("create table nopopDevices faild,errMsg %s",errMsg);
                cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                return;
            } 
        }
        else {
            DTLOG_INFO(0x40800C, "the table nopopDevices is exist");
            SMTLOGD("the table nopopDevices is exist");
        }
    }
    else {
        DTLOG_ERR(0x40800C, "select from sqlite_master faild");
        SMTLOGD("select from sqlite_master faild,errMsg %s",errMsg);
        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_NO_POP_IOS);
        return;
    }
    
    
    //select versionInfo table is or not exist
    snprintf(sql,SQL_MAX_LENGTH,"select * from sqlite_master where type = 'table' and name = 'popDevicesAndr'");
    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg));
    if(SMT_SQL_RET_SUCCESS == result) {
        SMTLOGD("resultCountOpe = %d",resultCountOpe);
        if(resultCountOpe == 0) {
            DTLOG_INFO(0x40800C, "the table popDevicesAndr is not exist");
            SMTLOGD("the table popDevicesAndr is not exist");
            snprintf(sql,SQL_MAX_LENGTH,"create table popDevicesAndr(serinum varchar(40) primary key,priority integer,popStatus integer,devname varchar(64),nameIsValid integer,nonameindex integer)");
            result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
            if(SMT_SQL_RET_SUCCESS == result) {
                DTLOG_INFO(0x40800C, "create table popDevicesAndr success");
                SMTLOGD("create table popDevicesAndr success");
            }
            else {
                DTLOG_ERR(0x40800C, "create table pop Devices faild");
                SMTLOGD("create table pop Devices faild,errMsg %s",errMsg);
                cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
        
                return;
            }
        }
        else {
            DTLOG_INFO(0x40800C, "the table popDevicesAndr is exist");
            SMTLOGD("the table popDevicesAndr is exist");
            snprintf(sql,SQL_MAX_LENGTH,"select * from popDevicesAndr");
            result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg));
            if(SMT_SQL_RET_SUCCESS == result) {
                if(resultCountOpe > SMT_IOS_POP_DEVICE_MAX) {
                    DTLOG_ERR(0x40800C, "popDevicesAndr count > %d,the count is error!", SMT_IOS_POP_DEVICE_MAX);
                    SMTLOGD("popDevicesAndr count > %d,the count is error,",SMT_IOS_POP_DEVICE_MAX);
                    DTLOG_INFO(0x40800C, "delete all pop devices");
                    SMTLOGD("delete all pop devices");
                    snprintf(sql,SQL_MAX_LENGTH,"delete from popDevicesAndr");
                    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == result) {
                        DTLOG_INFO(0x40800C, "delete all Android pop devices success");
                        SMTLOGD("delete all pop devices success");
                    }
                    else {
                        DTLOG_ERR(0x40800C, "delete all Android pop device faild");
                        SMTLOGD("delete all pop device faild,errMsg %s",errMsg);
                        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
                        return;
                    }
                }
                else {
                    DTLOG_INFO(0x40800C, "popDevicesAndr count = %d\n", resultCountOpe);
                    SMTLOGD("popDevices count = %d\n",resultCountOpe);
                }
            }
            else {
                DTLOG_ERR(0x40800C, "select from popDevicesAndr faild");
                SMTLOGD("select from popDevicesAndr faild,errmsg %s",errMsg);
                cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
                return;
            }
        }
    }
    else {
        DTLOG_ERR(0x40800C, "select from sqlite_master faild");
        SMTLOGD("select from sqlite_master faild,errMsg %s",errMsg);
        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
        
        return;
    }


    snprintf(sql,SQL_MAX_LENGTH,"select * from sqlite_master where type = 'table' and name = 'noPopDevicesAndr'");
    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg));
    if(SMT_SQL_RET_SUCCESS == result) {
        SMTLOGD("resultCountOpe = %d",resultCountOpe);
        if(resultCountOpe == 0) {
            DTLOG_INFO(0x40800C, "the table noPopDevicesAndr is not exist");
            SMTLOGD("the table noPopDevicesAndr is not exist");
            snprintf(sql,SQL_MAX_LENGTH,"create table noPopDevicesAndr(serinum varchar(40) primary key,priority integer,popStatus integer,devname varchar(64),nameIsValid integer,nonameindex integer)");
            result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
            if(SMT_SQL_RET_SUCCESS == result) {
                DTLOG_INFO(0x40800C, "create table noPopDevicesAndr success");
                SMTLOGD("create table noPopDevicesAndr success");
            }
            else {
                DTLOG_ERR(0x40800C, "create table noPopDevicesAndr faild");
                SMTLOGD("create table noPopDevicesAndr faild,errMsg %s",errMsg);
                cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                return;
            } 
        }
        else {
            DTLOG_INFO(0x40800C, "the table noPopDevicesAndr is exist");
            SMTLOGD("the table noPopDevicesAndr is exist");
        }
    }
    else {
        DTLOG_ERR(0x40800C, "select from sqlite_master faild");
        SMTLOGD("select from sqlite_master faild,errMsg %s",errMsg);
        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_NO_POP_IOS);
        return;
    }
    
    
    snprintf(sql,SQL_MAX_LENGTH,"select * from sqlite_master where type = 'table' and name = 'versionInfo'");
    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg));
    if(SMT_SQL_RET_SUCCESS == result) {
        if(resultCountOpe == 0) {
            DTLOG_INFO(0x40800C, "the table versionInfo is not exist");
            SMTLOGD("the table versionInfo is not exist");
            snprintf(sql,SQL_MAX_LENGTH,"create table versionInfo(version varchar(20))");
            result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
            if(SMT_SQL_RET_SUCCESS == result) {
                DTLOG_INFO(0x40800C, "create table versionInfo success");
                SMTLOGD("create table versionInfo success");
            }
            else {
                DTLOG_ERR(0x40800C, "create table versionInfo faild");
                SMTLOGD("create table versionInfo faild,errMsg %s",errMsg);
                cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_VERSION);
                return;
            }
        }
        else {
            DTLOG_INFO(0x40800C, "the table versionInfo is exist");
            SMTLOGD("the table versionInfo is exist");
            snprintf(sql,SQL_MAX_LENGTH,"select * from versionInfo");
            result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_versionCb,(void*)dbVersion,&errMsg));
            if(SMT_SQL_RET_SUCCESS == result) {
                DTLOG_INFO(0x40800C, "dbVersion is %s", dbVersion);
                SMTLOGD("dbVersion is %s",dbVersion);
            }
            else {
                DTLOG_ERR(0x40800C, "select from versionInfo faild");
                SMTLOGD("select faild,errMsg %s",errMsg);
                cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_VERSION);
                return;
            }
        }
    }
    else {
        DTLOG_ERR(0x40800C, "select * from sqlite_master faild");
        SMTLOGD("select * from sqlite_master faild,errMsg %s",errMsg);
        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_VERSION);
        return;
    }
    //when code version less than database,need clear database
    if(strcmp(CURRENT_VERSION,dbVersion) < 0) {
        DTLOG_INFO(0x40800C, "code version is less than db version,need clear db");
        SMTLOGD("code version is less than db version,need clear db");
        delAllDevice();
        snprintf(sql,SQL_MAX_LENGTH,"insert into versionInfo values('%s')",CURRENT_VERSION);
        result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
        if(SMT_SQL_RET_SUCCESS == result) {
            DTLOG_INFO(0x40800C, "insert %s into versioninfo success", CURRENT_VERSION);
            SMTLOGD("insert %s into versioninfo success",CURRENT_VERSION);
        }
        else {
            DTLOG_ERR(0x40800C, "insert into versionInfo falid");
            SMTLOGD("insert falid,errMsg %s",errMsg);
            cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_VERSION);
            return;
        }
    }//when code version more than database,need update database version to last
    else if(strcmp(CURRENT_VERSION,dbVersion) > 0) {
        snprintf(sql,SQL_MAX_LENGTH,"insert into versionInfo values('%s')",CURRENT_VERSION);
        result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
        if(SMT_SQL_RET_SUCCESS == result) {
            DTLOG_INFO(0x40800C, "insert %s into versioninfo success", CURRENT_VERSION);
            SMTLOGD("insert %s into versioninfo success",CURRENT_VERSION);
        }
        else {
            DTLOG_ERR(0x40800C, "insert into versionInfo falid");
            SMTLOGD("insert falid,errMsg %s",errMsg);
            cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_VERSION);
            return;
        }
    }
    else {
        DTLOG_INFO(0x40800C, "code version == database version,do nothing");
        SMTLOGD("code version == database version,do nothing");
    }
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
#if 0
    char sql[SQL_MAX_LENGTH] = {0};
    char *errMsg = NULL;
    if (NULL != mdb){
        //begin transaction 
        if(sqlite3_exec(mdb,"begin",0,0,0) == SQLITE_OK) {
            SMTLOGD("begin success");
        }
        else {
            SMTLOGD("begin faild");
        }
        //1 delete pop devices
        snprintf(sql,SQL_MAX_LENGTH,"delete from popDevices");
        if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
            SMTLOGD("delete pop devices success");
        }
        else {
            SMTLOGD("delete pop devices faild,errMsg %s",errMsg);
        }
        //2 delete no pop devices
        snprintf(sql,SQL_MAX_LENGTH,"delete from noPopDevices");
        if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
            SMTLOGD("delete no pop device success");
        }
        else {
            SMTLOGD("delete no pop device faild,errMsg %s",errMsg);
        }
        snprintf(sql,SQL_MAX_LENGTH,"select * from sqlite_master where type = 'table' and name = 'versionInfo'");
        if(SQLITE_OK == sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg)) {
            if(resultCountOpe) {
                SMTLOGD("the table versionInfo is exist");
                resultCountOpe = 0;
                snprintf(sql,SQL_MAX_LENGTH,"delete from versionInfo");
                if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
                    SMTLOGD("delete versionInfo suceess");
                }
                else {
                    SMTLOGD("delete versionInfo faild,errMsg %s",errMsg);
                }
            }
        }
        else {
            SMTLOGD("select sqlite_master faild,errMsg %s",errMsg);
        }
        //commit transaction
        if(sqlite3_exec(mdb,"commit",0,0,0) == SQLITE_OK) {
            SMTLOGD("commit success");
        }
        else {
            SMTLOGD("commit faild");
        }
    }
    else {
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
#endif
    DTLOG_INFO(0x408010, "martIosSettingProxy::delAllDevice");
    deleteTableFromDB(SMT_DB_TABLE_TYPE_POP_IOS);
    deleteTableFromDB(SMT_DB_TABLE_TYPE_NO_POP_IOS);
    deleteTableFromDB(SMT_DB_TABLE_TYPE_POP_ANDROID);
    deleteTableFromDB(SMT_DB_TABLE_TYPE_NO_POP_ANDROID);
    deleteTableFromDB(SMT_DB_TABLE_TYPE_VERSION);
    
}
/**
    * @brief delSingleDevice ,del single device
    *
    * @param index,device priority in table
    */
void SmartIosSettingProxy::delSingleDevice(int index)    /* __0x408011_DTFUNCID__ */ {
	UNUSED(index);
#if 0
    char sql[SQL_MAX_LENGTH] = {0};
    char * errMsg = NULL;
    //begin transaction
    snprintf(sql,SQL_MAX_LENGTH,"begin");
    if (NULL != mdb){
        if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
            SMTLOGD("begin success");
        }
        else {
            SMTLOGD("begin faild");
        }
        snprintf(sql,SQL_MAX_LENGTH,"delete from popDevices where priority = '%d'",index);
        if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
            SMTLOGD("delete success");
        }
        else {
            SMTLOGD("delete faild,errMsg %s",errMsg);
        }
        updatePopStatusDevicesPriority(index);
        snprintf(sql,SQL_MAX_LENGTH,"commit");
        if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
            SMTLOGD("commit success");
        }
        else {
            SMTLOGD("commit faild");
        }
    }
    else {
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
#endif
}
void SmartIosSettingProxy::updatePopStatusDevicesPriority(int priority)    /* __0x408012_DTFUNCID__ */ { 
    char sql[SQL_MAX_LENGTH] = {0};
    char * errMsg = NULL;
    enum SMT_SQL_RET result;
    
    if (NULL != mdb){
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
            DTLOG_ERR(0x408012, "DB operate begin fail");
            SMTLOGD("SmartIosSettingProxy::updatePopStatusDevicesPriority, begin fail");
            return;
        }
        
        snprintf(sql,SQL_MAX_LENGTH,"update popDevices set priority = priority - '%d' where priority > '%d'",1,priority);
        result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
        if(SMT_SQL_RET_SUCCESS == result) {
            SMTLOGD("update other pop device priority success");
        }
        else {
            DTLOG_ERR(0x408012, "update other pop device priority faild");
            SMTLOGD("update other pop device priority faild,errMsg %s",errMsg);
            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                DTLOG_ERR(0x408012, "DB operate roolback fail");
                SMTLOGD("SmartIosSettingProxy::updatePopStatusDevicesPriority, rollback fail");
            }
            cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
            return;
        }
        
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
            DTLOG_ERR(0x408012, "DB operate commit fail");
            SMTLOGD("SmartIosSettingProxy::updatePopStatusDevicesPriority, commit fail");
            return;
        }
    }
    else {
        DTLOG_ERR(0x408012, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
}
void SmartIosSettingProxy::updateNoPopStatusDevicesPriority(int priority, SmtDeviceType deviceType)    /* __0x408013_DTFUNCID__ */ {
    SMTLOGD("line %d,priority %d\n",__LINE__,priority);
    char sql[SQL_MAX_LENGTH] = {0};
    char * errMsg = NULL;
    enum SMT_SQL_RET result;
    
    if (NULL != mdb){
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
            DTLOG_ERR(0x408013, "DB operate begin fail");
            SMTLOGD("SmartIosSettingProxy::updateNoPopStatusDevicesPriority, begin fail");
            return;
        }
        
        if (SMT_DEVICE_TYPE_IOS == deviceType){
            snprintf(sql,SQL_MAX_LENGTH,"update noPopDevices set priority = priority - '%d' where priority > '%d'",1,priority);
        }
        else{
            snprintf(sql,SQL_MAX_LENGTH,"update noPopDevicesAndr set priority = priority - '%d' where priority > '%d'",1,priority);
        }
        result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
        if(SMT_SQL_RET_SUCCESS == result) {
            SMTLOGD("update other no pop device priority success");
        }
        else {
            DTLOG_ERR(0x408013, "update other no pop device priority faild");
            SMTLOGD("update other no pop device priority faild,errMsg %s",errMsg);
            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                DTLOG_ERR(0x408013, "DB operate rollback fail");
                SMTLOGD("SmartIosSettingProxy::updateNoPopStatusDevicesPriority, rollback fail");
            }
            cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_NO_POP_IOS);
            return;
        }
        
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
            DTLOG_ERR(0x408013, "DB operate commit fail");
            SMTLOGD("SmartIosSettingProxy::updateNoPopStatusDevicesPriority, commit fail");
            return;
        }
    }
    else {
        DTLOG_ERR(0x408013, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
}
int SmartIosSettingProxy::getPopDeviceMaxPriority(SmtDeviceType deviceType)    /* __0x408014_DTFUNCID__ */ {
    int priority = 0;//no device
    char sql[SQL_MAX_LENGTH] = {0};
    IosDeviceName devname;
    memset(&devname,0,sizeof(devname));
    char * errMsg = NULL;
    enum SMT_SQL_RET result;
    
    if (NULL != mdb){
        if (SMT_DEVICE_TYPE_IOS == deviceType){
            snprintf(sql,SQL_MAX_LENGTH,"select max(priority) from popDevices");
        }
        else{
            snprintf(sql,SQL_MAX_LENGTH,"select max(priority) from popDevicesAndr");
        }
        result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&devname,&errMsg));
        if(SMT_SQL_RET_SUCCESS == result) {
            SMTLOGD("%d,select success",__LINE__);
            priority = devname.format.priority;
            SMTLOGD("resultCountOpe = %d",resultCountOpe);
        }
        else {
            DTLOG_ERR(0x408014, "select max(priority) fail");
            SMTLOGD("%d,select faild,err %s",__LINE__,errMsg);
            cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
            return priority;
        }
    }
    else {
        DTLOG_ERR(0x408014, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }

    SMTLOGD("pop devices max priority = %d\n",priority);
    return priority;
}
int SmartIosSettingProxy::getNoPopStatusDeviceMaxPriority(SmtDeviceType deviceType)    /* __0x408015_DTFUNCID__ */ {
    int priority = 0;//no device
    char sql[SQL_MAX_LENGTH] = {0};
    IosDeviceName devname;
    memset(&devname,0,sizeof(devname));
    char * errMsg = NULL;
    enum SMT_SQL_RET result;
    
    if (NULL != mdb){
        if (SMT_DEVICE_TYPE_IOS == deviceType){
            snprintf(sql,SQL_MAX_LENGTH,"select max(priority) from noPopDevices");
        }
        else{
            snprintf(sql,SQL_MAX_LENGTH,"select max(priority) from noPopDevicesAndr");
        }
        result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&devname,&errMsg));
        if(SMT_SQL_RET_SUCCESS == result) {
            SMTLOGD("%d,select success",__LINE__);
            priority = devname.format.priority;
            SMTLOGD("resultCountOpe = %d",resultCountOpe);
        }
        else {
            DTLOG_ERR(0x408015, "select max(priority) fail");
            SMTLOGD("%d,select faild,err %s",errMsg);
            cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_NO_POP_IOS);
            return priority;
        }
    }
    else {
        DTLOG_ERR(0x408015, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }

    SMTLOGD("no pop devices max priority = %d\n",priority);
    return priority;
}

bool SmartIosSettingProxy::deleteNoPopDevice(uint8_t index, SmtDeviceType deviceType)    /* __0x408016_DTFUNCID__ */ {
    char sql[SQL_MAX_LENGTH] = {0};
    char *errMsg = NULL;
    enum SMT_SQL_RET result;
    
    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
        DTLOG_ERR(0x408016, "DB operate begin fail");
        SMTLOGD("SmartIosSettingProxy::deleteNoPopDevice, begin fail");
        return false;
    }
          
    if (SMT_DEVICE_TYPE_IOS == deviceType){
        snprintf(sql,SQL_MAX_LENGTH,"delete from noPopDevices where priority = '%d'",index - SMT_IOS_POP_DEVICE_MAX);
    }
    else{
        snprintf(sql,SQL_MAX_LENGTH,"delete from noPopDevicesAndr where priority = '%d'",index - SMT_IOS_POP_DEVICE_MAX);
    }
    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
    if(SMT_SQL_RET_SUCCESS == result) {
        SMTLOGD("delete success");
    }
    else {
        DTLOG_ERR(0x408016, "delete faild");
        SMTLOGD("delete faild");
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
            DTLOG_ERR(0x408016, "DB operate rollback fail");
            SMTLOGD("SmartIosSettingProxy::deleteNoPopDevice, rollback fail");
        }
        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_NO_POP_IOS);
        return false;
    }
    
    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
        DTLOG_ERR(0x408016, "DB operate commit fail");
        SMTLOGD("SmartIosSettingProxy::deleteNoPopDevice, commit fail");
        return false;
    }
    
    return true;
}

bool SmartIosSettingProxy::insertPopDevice(IosDeviceName* devname, SmtPopStatus setting, int maxPriority, SmtDeviceType deviceType)    /* __0x408017_DTFUNCID__ */ {
    char * sql2 = NULL;
    char *errMsg = NULL;
    enum SMT_SQL_RET result;
    
    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
        DTLOG_ERR(0x408017, "DB operate begin fail");
        SMTLOGD("SmartIosSettingProxy::insertPopDevice, begin fail");
        return false;
    }
    
    if (SMT_DEVICE_TYPE_IOS == deviceType){
        sql2 = sqlite3_mprintf("insert into popDevices values('%q','%d','%d','%q','%d','%d')", devname->format.serinum,maxPriority + 1, setting, devname->format.deviceName,NAME_IS_VALID,0);
    }
    else{
        sql2 = sqlite3_mprintf("insert into popDevicesAndr values('%q','%d','%d','%q','%d','%d')", devname->format.serinum,maxPriority + 1, setting, devname->format.deviceName,NAME_IS_VALID,0);
    }
    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
    if(SMT_SQL_RET_SUCCESS == result) {
        SMTLOGD("insert into popdevices success");
    }
    else {
        DTLOG_ERR(0x408017, "insert into popDevices table faild");
        SMTLOGD("insert into popDevices table faild,errMsg %s",errMsg);
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
            DTLOG_ERR(0x408017, "DB operate rollback fail");
            SMTLOGD("SmartIosSettingProxy::insertPopDevice, rollback fail");
        }
        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
        
        sqlite3_free(sql2);
        return false;
    }
    
    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
        DTLOG_ERR(0x408017, "DB operate commit fail");
        SMTLOGD("SmartIosSettingProxy::insertPopDevice, commit fail");
        sqlite3_free(sql2);
        return false;
    }
    sqlite3_free(sql2);
    
    return true;
}

bool SmartIosSettingProxy::insertPopDeviceNoName(IosDeviceName* devname, SmtPopStatus setting, int maxPriority, SmtDeviceType deviceType)    /* __0x408018_DTFUNCID__ */ {
    
    char sql[SQL_MAX_LENGTH] = {0};
    char *errMsg = NULL;
    enum SMT_SQL_RET result;
    
    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
        DTLOG_ERR(0x408018, "DB operate begin fail");
        SMTLOGD("SmartIosSettingProxy::insertPopDeviceNoName, begin fail");
        return false;
    }
    
    IosDeviceName name;
    int maxIndex = 0;
    memset(&name,0,sizeof(name));
    if (SMT_DEVICE_TYPE_IOS == deviceType){
        snprintf(sql,SQL_MAX_LENGTH,"select max(nonameindex) from popDevices where nameIsValid = '%d'",NAME_IS_INVALID);
    }
    else{
        snprintf(sql,SQL_MAX_LENGTH,"select max(nonameindex) from popDevicesAndr where nameIsValid = '%d'",NAME_IS_INVALID);
    }
    result = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&name,&errMsg));
    if(SMT_SQL_RET_SUCCESS == result) {
        SMTLOGD("resultCountOpe = %d",resultCountOpe);
        maxIndex = name.format.priority;
        SMTLOGD("select nameIsInvalid max index success,maxindex %d",maxIndex);
        char invalidname[SMT_IOS_DEVICE_NAME_MAX_LEN] = {0};
        if (SMT_DEVICE_TYPE_IOS == deviceType){
            snprintf(invalidname,SMT_IOS_DEVICE_NAME_MAX_LEN,"%s%d","iPhone",maxIndex + 1);
        }
        else{
            snprintf(invalidname,SMT_IOS_DEVICE_NAME_MAX_LEN,"%s%d","Android Phone",maxIndex + 1);
        }
        SMTLOGD("invalidname is %s",invalidname);
        char * sql2 = NULL;
        SMTLOGD("devname->foramt.serinum %s,len = %d",devname->format.serinum,strlen((char*)devname->format.serinum));
        if (SMT_DEVICE_TYPE_IOS == deviceType){
            sql2 = sqlite3_mprintf("insert into popDevices values('%q','%d','%d','%q','%d','%d')",devname->format.serinum,maxPriority + 1,setting,invalidname,NAME_IS_INVALID,maxIndex + 1);
        }
        else{
            sql2 = sqlite3_mprintf("insert into popDevicesAndr values('%q','%d','%d','%q','%d','%d')",devname->format.serinum,maxPriority + 1,setting,invalidname,NAME_IS_INVALID,maxIndex + 1);
        }
        result = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
        if(SMT_SQL_RET_SUCCESS == result) {
            SMTLOGD("insert into popdevices success");
        }
        else {
            DTLOG_ERR(0x408018, "insert into popdevices fail");
            cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
            
            sqlite3_free(sql2);
            return false;
        }
        sqlite3_free(sql2);
    }
    else {
        SMTLOGD("select maxindex faild,errMsg %s",errMsg);
        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
            DTLOG_ERR(0x408018, "DB operate rollback fail");
            SMTLOGD("SmartIosSettingProxy::insertPopDeviceNoName, rollback fail");
        }
        cleanTablesWhenOpeErr(result, SMT_DB_TABLE_TYPE_POP_IOS);
        return false;
    }
    
    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
        DTLOG_ERR(0x408018, "DB operate commit fail");
        SMTLOGD("SmartIosSettingProxy::insertPopDeviceNoName, commit fail");
        return false;
    }
    
    return true;
}

/**
    * @brief replacePopDevice ,when pop list full,replace pop device
    *
    * @param serialNum
    * @param popValue
    * @param devname
    * @param nameIsValid
    * @param nonameindex
    */
void SmartIosSettingProxy::replacePopDevice(const char * serialNum,uint8_t popValue, const char * devname,uint8_t nameIsValid,uint8_t nonameindex, SmtDeviceType deviceType)    /* __0x408019_DTFUNCID__ */ {
    SMTLOGD("pop device is full");
    char sql[SQL_MAX_LENGTH] = {0};
    char * errMsg = NULL;
    char **result = NULL;
    int nRow = 0;
    int nCol = 0;
    char* sql2 = NULL;
    enum SMT_SQL_RET resultRet;
    
    if (NULL != mdb){
        if (SMT_DEVICE_TYPE_IOS == deviceType){
            snprintf(sql,SQL_MAX_LENGTH,"select * from popDevices");
        }
        else{
            snprintf(sql,SQL_MAX_LENGTH,"select * from popDevicesAndr");
        }
        resultRet = dbOperateRetJudgement(sqlite3_get_table(mdb,sql,&result,&nRow,&nCol,&errMsg));
        if(SMT_SQL_RET_SUCCESS == resultRet) {
            SMTLOGD("sqlite get table success");
            int index = nCol;
            
            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
                DTLOG_ERR(0x408019, "DB operate begin fail");
                SMTLOGD("SmartIosSettingProxy::replacePopDevice, begin fail");
                return;
            }
            
            for(int i = 0; i < nRow; ++i) {
                IosDeviceName name;
                memset(&name, 0, sizeof(IosDeviceName));
                memcpy(name.format.serinum,result[index],SMT_IOS_DEVICE_SERIALNUM_MAX);
                name.format.serinum[SMT_IOS_DEVICE_SERIALNUM_MAX] = '\0';
                name.format.priority = atoi(result[index + 1]);
                name.format.popStatus = atoi(result[index + 2]);
                memcpy(name.format.deviceName,result[index + 3],SMT_IOS_DEVICE_NAME_MAX_LEN);
                name.format.nameIsValid = atoi(result[index + 4]);
                name.format.index = atoi(result[index + 5]);
                index += nCol;
                if(name.format.priority > SMT_IOS_POP_INDEX_START) {
                    if (SMT_DEVICE_TYPE_IOS == deviceType){
                        snprintf(sql,SQL_MAX_LENGTH,"update popDevices set priority = priority - '%d' where serinum = '%s'",1,name.format.serinum);
                    }
                    else{
                        snprintf(sql,SQL_MAX_LENGTH,"update popDevicesAndr set priority = priority - '%d' where serinum = '%s'",1,name.format.serinum);
                    }
                    resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == resultRet) {
						printf("---------------------------------SMT_SQL_RET_SUCCESS--------------------------\n");
                        SMTLOGD("update pop device priority success");
                    }
                    else {
                        DTLOG_ERR(0x408019, "update pop device priority faild");
                        SMTLOGD("update pop device priority faild,errMsg %s",errMsg);
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                            DTLOG_ERR(0x408019, "DB operate rollback fail");
                            SMTLOGD("SmartIosSettingProxy::replacePopDevice, rollback fail");
                        }
                        cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
                        return;
                    }
                }
                else {
                    if (SMT_DEVICE_TYPE_IOS == deviceType){
                        sql2 = sqlite3_mprintf("update popDevices set serinum = '%q',priority = '%d',popStatus = '%d',devname = '%q',nameIsValid = '%d',nonameindex = '%d' where serinum = '%q'",serialNum,SMT_IOS_POP_INDEX_END,popValue,devname,nameIsValid,nonameindex,name.format.serinum);
                    }
                    else{
                        sql2 = sqlite3_mprintf("update popDevicesAndr set serinum = '%q',priority = '%d',popStatus = '%d',devname = '%q',nameIsValid = '%d',nonameindex = '%d' where serinum = '%q'",serialNum,SMT_IOS_POP_INDEX_END,popValue,devname,nameIsValid,nonameindex,name.format.serinum);
                    }
                    resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == resultRet) {
                        SMTLOGD("update success");
                    }
                    else {
                        DTLOG_ERR(0x408019, "update pop device priority faild");
                        SMTLOGD("update faild,errMsg %s",errMsg);
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                            DTLOG_ERR(0x408019, "DB operate rollback fail");
                            SMTLOGD("SmartIosSettingProxy::replacePopDevice, rollback fail");
                        }
                        cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
                        sqlite3_free(sql2);
                        return;
                    }
                    sqlite3_free(sql2);
                }
            }
            
            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
                DTLOG_ERR(0x408019, "DB operate commit fail");
                SMTLOGD("SmartIosSettingProxy::replacePopDevice, commit fail");
                return;
            }
            
            sqlite3_free_table(result);
        }
        else {
            DTLOG_ERR(0x408019, "DB selete fail");
            cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
            return;
        }
    }
    else {
        DTLOG_ERR(0x408019, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
    
}

/**
    * @brief replaceNoPopDevice ,when no pop device list full,replace no pop device
    *
    * @param serialNum
    * @param popValue
    * @param devname
    * @param nameIsValid
    * @param nonameindex
    * @param index
    */
void SmartIosSettingProxy::replaceNoPopDevice(const char * serialNum,uint8_t popValue,const char * devname,uint8_t nameIsValid,uint8_t nonameindex,uint8_t& index,  SmtDeviceType deviceType)    /* __0x40801A_DTFUNCID__ */ {
    UNUSED(popValue);
    UNUSED(devname);
    UNUSED(nameIsValid);
    UNUSED(nonameindex);
	UNUSED(index);
    char sql[SQL_MAX_LENGTH] = {0};
    char *errMsg = NULL;
    SMTLOGD("no pop device is full");
    char **result = NULL;
    int nRow = 0;
    int nCol = 0;
    char* sql2 = NULL;
    enum SMT_SQL_RET resultRet;
    
    if (NULL != mdb){
        if (SMT_DEVICE_TYPE_IOS == deviceType){
            snprintf(sql,SQL_MAX_LENGTH,"select * from noPopDevices");
        }
        else{
            snprintf(sql,SQL_MAX_LENGTH,"select * from noPopDevicesAndr");
        }
        resultRet = dbOperateRetJudgement(sqlite3_get_table(mdb,sql,&result,&nRow,&nCol,&errMsg));
        if(SMT_SQL_RET_SUCCESS == resultRet) {
            SMTLOGD("sqlite get table success");
            int elemIndex = nCol;
            
            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
                DTLOG_ERR(0x40801A, "DB operate begin fail");
                SMTLOGD("SmartIosSettingProxy::replaceNoPopDevice, begin fail");
                return;
            }
            for(int i = 0; i < nRow; ++i) {
                IosDeviceName name;
                memset(&name,0,sizeof(IosDeviceName));
                memcpy(name.format.serinum,result[elemIndex],SMT_IOS_DEVICE_SERIALNUM_MAX);
                name.format.serinum[SMT_IOS_DEVICE_SERIALNUM_MAX] = '\0';
                name.format.priority = atoi(result[elemIndex + 1]);
                name.format.popStatus = atoi(result[elemIndex + 2]);
                memcpy(name.format.deviceName,result[elemIndex + 3],SMT_IOS_DEVICE_NAME_MAX_LEN);
                name.format.nameIsValid = atoi(result[elemIndex + 4]);
                name.format.index = atoi(result[elemIndex + 5]);
                elemIndex += nCol;
                SMTLOGD("serinum %s,prirority %d,popStatus %d,deviceName %s,nameIsValid %d,index %d",name.format.serinum,name.format.priority,name.format.popStatus,name.format.deviceName,name.format.nameIsValid,name.format.index);
                if(name.format.priority > SMT_IOS_NOPOP_PRIORITY_START) {
                    if (SMT_DEVICE_TYPE_IOS == deviceType){
                        snprintf(sql,SQL_MAX_LENGTH,"update noPopDevices set priority = priority - '%d' where serinum = '%s'",1,name.format.serinum);
                    }
                    else{
                        snprintf(sql,SQL_MAX_LENGTH,"update noPopDevicesAndr set priority = priority - '%d' where serinum = '%s'",1,name.format.serinum);
                    }
                    resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == resultRet) {
						printf("-------------------------------SMT_SQL_RET_SUCCESS-------------------------------------\n");
                        SMTLOGD("update no pop device priority success");
                    }
                    else {
                        DTLOG_ERR(0x40801A, "update no pop device priority faild");
                        SMTLOGD("update no pop device priority faild,errMsg %s",errMsg);
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                            DTLOG_ERR(0x40801A, "DB operate rollback fail");
                            SMTLOGD("SmartIosSettingProxy::replaceNoPopDevice, rollback fail");
                        }
                        sqlite3_free_table(result);
                        cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                        return;
                    }
                }
                else {
                    if (SMT_DEVICE_TYPE_IOS == deviceType){
                        sql2 = sqlite3_mprintf("update noPopDevices set serinum = '%q',priority = '%d',popStatus = '%d',devname = '%q',nameIsValid = '%d',nonameindex = '%d' where serinum = '%q'",serialNum,SMT_IOS_NOPOP_PRIORITY_END,IOS_POPSTATUS_INVALID,"iphone",NAME_IS_INVALID,0,name.format.serinum);
                    }
                    else{
                        sql2 = sqlite3_mprintf("update noPopDevicesAndr set serinum = '%q',priority = '%d',popStatus = '%d',devname = '%q',nameIsValid = '%d',nonameindex = '%d' where serinum = '%q'",serialNum,SMT_IOS_NOPOP_PRIORITY_END,IOS_POPSTATUS_INVALID,"iphone",NAME_IS_INVALID,0,name.format.serinum);
                    }
                    resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == resultRet) {
                        SMTLOGD("update success");
                    }
                    else {
                        DTLOG_ERR(0x40801A, "update faild");
                        SMTLOGD("update faild,errMsg %s",errMsg);
                        cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                            SMTLOGD("SmartIosSettingProxy::replaceNoPopDevice, rollback fail");
                        }
                        sqlite3_free_table(result);
                        sqlite3_free(sql2);
                        return;
                    }
                    sqlite3_free(sql2);
                }
            }
            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
                DTLOG_ERR(0x40801A, "DB operate commit faild");
                SMTLOGD("SmartIosSettingProxy::replaceNoPopDevice, commit fail");
                sqlite3_free_table(result);
                return;
            }
            
            sqlite3_free_table(result);
        }
        else {
            DTLOG_ERR(0x40801A, "sqlite get table faild");
            SMTLOGD("sqlite get table faild,errMsg %s",errMsg);
            cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
            return;
        }
    }
    else {
        DTLOG_ERR(0x40801A, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
        
}
//set priority logic
//1. when insert a new device，if device list is not full，get the max priortiy ，if is empty，set 0，
//then the new device priority is max priority + 1
//2. if device list is full，find the priority equal 1 position，in the position insert new serinum，then priority set max，other device
// priorit all need minus one
//3. when delete a device，other device waht priority more than deleted devices need minus one，because a device deleted，
//the after it into the device list device need minus one

//pop up set is divided into 4 situation
//1 the dev is pop device and setting is pop value,only need update popStatus
//2 the dev is pop device and setting is no pop value,need pop device -> no pop device
//3 the dev is no pop device and setting is no pop value,only need update popStatus
//4 the dev is no pop device and setting is pop value,need no pop device -> pop device

/**
    *
    *   index explain:
    *   for pop device,index equal priority,value range is [1,5]
    *   for no pop device,index  > priority,and index = priority + 5(pop device max num),value range is [6,15]
    */
int SmartIosSettingProxy::setPopStatusReq(SmtSetType setType, uint8_t index, SmtPopStatus setting, SmtDeviceType deviceType)    /* __0x40801B_DTFUNCID__ */
{
    std::vector<SmartIosIosDevInfo*> mDeviceList;
    SmartIosIosDevInfo* mSelectDev = NULL;
    std::vector<uint16_t> mIndexList;
    int newIndex = index;
    enum SMT_SQL_RET resultRet;
    
    SMTLOGD("SmartIosSettingProxy setPopStatusReq setType = %d,index %d, setting %d", setType,index, setting);
    //pop set,index = index
    if (NULL != mdb){
        if(setType == SMT_IOS_POPUP_SET) {
            SMTLOGD("line %d,pop set",__LINE__);
            SMTLOGD("use sqlite3 db");
            char sql[SQL_MAX_LENGTH] = {0};
            char *errMsg = NULL;
            IosDeviceName devname;
            
            //no pop device
            if((index >= SMT_IOS_NOPOP_INDEX_START) && (index <= SMT_IOS_NOPOP_INDEX_END)) {
                if(isPopStatusValidHigh(setting)) {
                    if (SMT_DEVICE_TYPE_IOS == deviceType){
                        snprintf(sql,SQL_MAX_LENGTH,"select * from noPopDevices where priority = '%d'",index-SMT_IOS_POP_DEVICE_MAX);
                    }
                    else{
                        snprintf(sql,SQL_MAX_LENGTH,"select * from noPopDevicesAndr where priority = '%d'",index-SMT_IOS_POP_DEVICE_MAX);
                    }
                    resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&devname,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == resultRet) {
                        SMTLOGD("resultCountOpe = %d",resultCountOpe);
                        if(resultCountOpe == 0) {
                            DTLOG_ERR(0x40801B, "not the no pop device");
                            SMTLOGD("not the no pop device");
                            return index;
                        }
                        else {
                            SMTLOGD("line %d,serinum %s,priority %d,pop %d,name %s,nameisValid %d,index %d",__LINE__,devname.format.serinum,devname.format.priority,devname.format.popStatus,devname.format.deviceName,devname.format.nameIsValid,devname.format.index);
                        }
                    }
                    else {
                        DTLOG_ERR(0x40801B, "select faild");
                        SMTLOGD("select faild,errMsg %s",errMsg);
                        cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                        return index;
                    }
                    
                    bool ret;
                    //Delete nopopdevice
                    ret = deleteNoPopDevice(index, deviceType);
                    
                    if (true != ret){
                        DTLOG_ERR(0x40801B, "deleteNoPopDevice return false");
                        return index;
                    }
                    
                    //update no pop devices priority
                    updateNoPopStatusDevicesPriority(index - SMT_IOS_POP_DEVICE_MAX, deviceType);
                    //insert the device into popDevices table
                    int maxPriority = getPopDeviceMaxPriority(deviceType);
                    if(maxPriority < SMT_IOS_POP_PRIORITY_END) {
                        newIndex = maxPriority + 1;
                        DTLOG_INFO(0x40801B, "pop device is not full");
                        SMTLOGD("pop device is not full");
                        
                        if(devname.format.nameIsValid == NAME_IS_VALID) { 
                            SMTLOGD("the devname is valid");
                            ret = insertPopDevice(&devname, setting, maxPriority, deviceType);
                            
                            if (true != ret){
                                DTLOG_ERR(0x40801B, "insertPopDevice return false");
                                newIndex = index;    
                                return index;
                            }
                        }//name is invalid
                        else {
                            SMTLOGD("the name is invalid");
                            ret =  insertPopDeviceNoName(&devname, setting, maxPriority, deviceType);
                            
                            if (true != ret){
                                DTLOG_ERR(0x40801B, "insertPopDeviceNoName return false");
                                newIndex = index;    
                                return index;
                            }
                        }
                    }//pop device is full,replace priority =  1 device 
                    else {
                        SMTLOGD("the pop device is full");
                        newIndex = SMT_IOS_POP_PRIORITY_END; 
                        if(devname.format.nameIsValid == NAME_IS_VALID) {
                            SMTLOGD("the devname is valid");
                            replacePopDevice((char*)devname.format.serinum,setting,(char*)devname.format.deviceName,NAME_IS_VALID,0, deviceType);
                        }//name is invlaid
                        else {
                            SMTLOGD("the devname is invalid");
                            IosDeviceName name;
                            int maxIndex = 0;
                            memset(&name,0,sizeof(name));
                            if (SMT_DEVICE_TYPE_IOS == deviceType){
                                snprintf(sql,SQL_MAX_LENGTH,"select max(nonameindex) from popDevices where nameIsValid = '%d'",NAME_IS_INVALID);
                            }
                            else{
                                snprintf(sql,SQL_MAX_LENGTH,"select max(nonameindex) from popDevicesAndr where nameIsValid = '%d'",NAME_IS_INVALID);
                            }
                            resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&name,&errMsg));
                            if(SMT_SQL_RET_SUCCESS == resultRet) {
                                SMTLOGD("resultCountOpe = %d",resultCountOpe);
                                maxIndex = name.format.priority;
                                SMTLOGD("select nameIsInvalid max index success,maxindex %d",maxIndex);
                                char invalidname[SMT_IOS_DEVICE_NAME_MAX_LEN] = {0};
                                if (SMT_DEVICE_TYPE_IOS == deviceType){
                                    snprintf(invalidname,SMT_IOS_DEVICE_NAME_MAX_LEN,"%s%d","iPhone",maxIndex + 1);
                                }
                                else{
                                    snprintf(invalidname,SMT_IOS_DEVICE_NAME_MAX_LEN,"%s%d","Android Phone",maxIndex + 1);
                                }
                                SMTLOGD("invalidname is %s",invalidname);
                                replacePopDevice((char*)devname.format.serinum,setting,invalidname,NAME_IS_INVALID,maxIndex + 1, deviceType);
                            }
                            else {
                                DTLOG_ERR(0x40801B, "sqlite3_exec find the max noname index fail");
                                SMTLOGD("sqlite3_exec find the max noname index fail");
                                cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
                                return index;
                            }
                                            
                        }
                    }
                }
                else {
#if 0 //Unused in 18HPMDA
                    snprintf(sql,SQL_MAX_LENGTH,"update noPopDevices set popStatus = '%d' where priority = '%d'",setting,index-SMT_IOS_POP_DEVICE_MAX);
                    if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
                        SMTLOGD("set nopopStatus %d success",setting);
                    }
                    else {
                        SMTLOGD("set nopopStatus %d faild,errMsg %s",setting,errMsg);
                    }
#endif
                }
            }
            //the device is pop device
            else {
                if(isPopStatusValidHigh(setting)) {
                    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
                        DTLOG_ERR(0x40801B, "DB operate begin fail");
                        SMTLOGD("SmartIosSettingProxy::setPopStatusReq, begin fail");
                        return index;
                    }
                    
                    if (SMT_DEVICE_TYPE_IOS == deviceType){
                        snprintf(sql,SQL_MAX_LENGTH,"update popDevices set popStatus = '%d' where priority = '%d'",setting,index);
                    }
                    else{
                        snprintf(sql,SQL_MAX_LENGTH,"update popDevicesAndr set popStatus = '%d' where priority = '%d'",setting,index);
                    }
                    resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == resultRet) {
                        SMTLOGD("update pop value success,index %d,popValue %d",index,setting);
                    }
                    else {
                        DTLOG_ERR(0x40801B, "update pop value faild");
                        SMTLOGD("update pop value faild,errMsg %s",errMsg);
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                            DTLOG_ERR(0x40801B, "DB operate rollback fail");
                            SMTLOGD("SmartIosSettingProxy::setPopStatusReq, rollback fail");
                        }
                        cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
                        return index;
                    }
                    
                    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
                        DTLOG_ERR(0x40801B, "DB operate commit fail");
                        SMTLOGD("SmartIosSettingProxy::setPopStatusReq, commit fail");
                        return index;
                    }
                }
                //pop device -> no pop device
                //1 select pop device info,delete pop device ,update other pop device priority
                //2 insert the device into no pop device table
                else {
#if 0//Unused in 18HPMDA
                    snprintf(sql,SQL_MAX_LENGTH,"begin");
                    if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
                        SMTLOGD("begin success");
                    }
                    else {
                        SMTLOGD("begin faild");
                        return newIndex;
                    }
                    snprintf(sql,SQL_MAX_LENGTH,"select * from popDevices where priority = '%d'",index);
                    if(SQLITE_OK == sqlite3_exec(mdb,sql,sqlite3_callback,&devname,&errMsg)) {
                        if(resultCountOpe != 0) {
                            SMTLOGD("this is pop device");
                            resultCountOpe = 0;
                        }
                        else {
                            SMTLOGD("is not pop device");
                            return newIndex;
                        }
                    }
                    else {
                        SMTLOGD("select faild,errMsg %s",errMsg);
                        return newIndex;
                    }
                    snprintf(sql,SQL_MAX_LENGTH,"delete from popDevices where priority = '%d'",index);
                    if(SQLITE_OK == sqlite3_exec(mdb,sql,NULL,NULL,&errMsg)) {
                        SMTLOGD("delete pop device success");
                    }
                    else {
                        SMTLOGD("delete faild");
                    }
                    updatePopStatusDevicesPriority(index);
                    int maxNoPopIndex = getNoPopStatusDeviceMaxPriority();
                    char *sql2 = NULL;
                    if(maxNoPopIndex < SMT_IOS_NOPOP_DEVICE_MAX) {
                        newIndex = maxNoPopIndex + 1 + SMT_IOS_POP_DEVICE_MAX;
                        SMTLOGD("no pop device is not full");
                        sql2 = sqlite3_mprintf("insert into noPopDevices values('%q','%d','%d','%q','%d','%d')",devname.format.serinum,maxNoPopIndex + 1,setting,devname.format.deviceName,devname.format.nameIsValid,devname.format.index);
                        if(SQLITE_OK == sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg)) {
                            SMTLOGD("insert into no pop device success");
                        }
                        else {
                            SMTLOGD("insert into no pop device faild");
                            return newIndex;
                        }
                    }
                    else {
                        SMTLOGD("no pop device is full");
                        newIndex = SMT_IOS_NOPOP_PRIORITY_END + SMT_IOS_POP_DEVICE_MAX;
                        uint8_t mIndex = 0;
                        replaceNoPopDevice((char*)devname.format.serinum,setting,(char*)devname.format.deviceName,devname.format.nameIsValid,devname.format.index,mIndex);
                    }
#endif
                }
            }
        }
        //manu set,index = priority
        else {
            SMTLOGD("line %d,manu set\n",__LINE__);
            char sql[SQL_MAX_LENGTH] = {0};
            char *errMsg = NULL;
            
            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
                DTLOG_ERR(0x40801B, "DB operate begin fail");
                SMTLOGD("SmartIosSettingProxy::setPopStatusReq, begin fail");
                return index;
            }
        
            if (SMT_DEVICE_TYPE_IOS == deviceType){
                snprintf(sql,SQL_MAX_LENGTH,"update popDevices set popStatus = '%d' where priority = '%d'",setting,index);
            }
            else{
                snprintf(sql,SQL_MAX_LENGTH,"update popDevicesAndr set popStatus = '%d' where priority = '%d'",setting,index);
            }
            resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,NULL,NULL,&errMsg));
            if(SMT_SQL_RET_SUCCESS == resultRet) {
                SMTLOGD("update success");
            }
            else {
                DTLOG_ERR(0x40801B, "update faild");
                SMTLOGD("update faild,errMsg %s",errMsg);
                if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                    DTLOG_ERR(0x40801B, "DB operate rollback fail");
                    SMTLOGD("SmartIosSettingProxy::setPopStatusReq, rollback fail");
                }
                cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
                return index;
            }
            
            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
                DTLOG_ERR(0x40801B, "DB operate commit fail");
                SMTLOGD("SmartIosSettingProxy::setPopStatusReq, commit fail");
                return index;
            }
        }
    }
    else {
        DTLOG_ERR(0x40801B, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
    return newIndex;
}
/**
    * @brief iapDeviceInsert ,analysis new insert device info
    *
    * @param serialNum,new insert device seirnum
    * @param selectStatus,the device pop value
    *
    * @return,device priority 
    */
uint8_t SmartIosSettingProxy::iapDeviceInsert(const char* serialNum, uint8_t* selectStatus, SmtDeviceType deviceType)    /* __0x40801C_DTFUNCID__ */
{
    uint8_t i = 0;
    uint8_t index = SMT_IOS_DEVICE_INDEX_INVALID;
    bool exist =  false;
    uint8_t first_blank_posion = SMT_IOS_DEVICE_INDEX_INVALID;
    std::string strSerial;
    enum SMT_SQL_RET resultRet;
    
    strSerial.append(serialNum);
    SMTLOGD("iapDeviceInsert, device serialNum is %s", serialNum);
    *selectStatus = IOS_POPSTATUS_INVALID;

    if(strlen(serialNum) == 0)
    {
        DTLOG_ERR(0x40801C, "iapDeviceInsert serialNum error length is 0");
        SMTLOGD("iapDeviceInsert serialNum error length is 0");
        return SMT_IOS_DEVICE_INDEX_INVALID;
    } 
    SMTLOGD("use sqlite3 db");
    char sql[SQL_MAX_LENGTH];
    char * errMsg = NULL;
    IosDeviceName devname;
    memset(&devname,0,sizeof(devname));
    if (SMT_DEVICE_TYPE_IOS == deviceType){
        snprintf(sql,SQL_MAX_LENGTH,"select * from popDevices where serinum = '%s'",serialNum);
    }
    else{
        snprintf(sql,SQL_MAX_LENGTH,"select * from popDevicesAndr where serinum = '%s'",serialNum);
    }

    if (NULL != mdb){
        resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&devname,&errMsg));
        if(SMT_SQL_RET_SUCCESS == resultRet) {
            SMTLOGD("reusltCount = %d",resultCountOpe);
			#ifdef UT_GTEST_FULL_ENG
			if(ForGetLocalValue() == 0) {
			#else
            if(resultCountOpe == 0) {
			#endif
                SMTLOGD("the device not pop device");
                if (SMT_DEVICE_TYPE_IOS == deviceType){
                    snprintf(sql,SQL_MAX_LENGTH,"select * from noPopDevices where serinum = '%s'",serialNum);
                }
                else{
                    snprintf(sql,SQL_MAX_LENGTH,"select * from noPopDevicesAndr where serinum = '%s'",serialNum);
                }
                resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&devname,&errMsg));
                if(SMT_SQL_RET_SUCCESS == resultRet) {
					#ifdef UT_GTEST_FULL_ENG
					if(ForGetLocalValue() == 0) {
					#else
                    if(resultCountOpe == 0) {
					#endif
                        SMTLOGD("the device is also not no pop device");
                        snprintf(sql,SQL_MAX_LENGTH,"select * from noPopDevices");
                        resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&devname,&errMsg));
                        if(SMT_SQL_RET_SUCCESS == resultRet) {
                            if(resultCountOpe == 0) {
                                SMTLOGD("no pop devices is empty");
                                char * sql2 = NULL;
                                if (SMT_DEVICE_TYPE_IOS == deviceType){
                                    sql2 = sqlite3_mprintf("insert into noPopDevices values('%q','%d','%d','%q','%d','%d')",serialNum,SMT_IOS_NOPOP_PRIORITY_START,IOS_POPSTATUS_INVALID,"iphone",NAME_IS_INVALID,0);
                                }
                                else{
                                    sql2 = sqlite3_mprintf("insert into noPopDevicesAndr values('%q','%d','%d','%q','%d','%d')",serialNum,SMT_IOS_NOPOP_PRIORITY_START,IOS_POPSTATUS_INVALID,"iphone",NAME_IS_INVALID,0);
                                }
                                resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
                                if(SMT_SQL_RET_SUCCESS == resultRet) {
                                    SMTLOGD("insert success");
                                    index = SMT_IOS_NOPOP_PRIORITY_START + SMT_IOS_POP_DEVICE_MAX;
                                }
                                else {
                                    DTLOG_ERR(0x40801C, "insert faild");
                                    SMTLOGD("insert faild,errMsg %s",errMsg);
                                    cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                                    sqlite3_free(sql2);
                                    return SMT_IOS_DEVICE_INDEX_INVALID;
                                }
                                sqlite3_free(sql2);
                            }
                            else if(resultCountOpe == SMT_IOS_NOPOP_DEVICE_MAX) {
                                SMTLOGD("no pop device is full");
                                //replace priority = 1 device
                                //begin transaction
                                replaceNoPopDevice(serialNum,IOS_POPSTATUS_INVALID,"iphone",NAME_IS_INVALID,0,index, deviceType);
                            }
                            else {
                                if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
                                    DTLOG_ERR(0x40801C, "DB operate begin fail");
                                    SMTLOGD("SmartIosSettingProxy::iapDeviceInsert, begin fail");
                                    return index;
                                }
                                
                                SMTLOGD("0 < pop devices < 10");
                                int pri = getNoPopStatusDeviceMaxPriority(deviceType);
                                char * sql2 = NULL;
                                if (SMT_DEVICE_TYPE_IOS == deviceType){
                                    sql2 = sqlite3_mprintf("insert into noPopDevices values('%q','%d','%d','%q','%d','%d')",serialNum,pri + 1,IOS_POPSTATUS_INVALID,"iphone",NAME_IS_INVALID,0);
                                }
                                else{
                                    sql2 = sqlite3_mprintf("insert into noPopDevicesAndr values('%q','%d','%d','%q','%d','%d')",serialNum,pri + 1,IOS_POPSTATUS_INVALID,"iphone",NAME_IS_INVALID,0);
                                }
                                SMTLOGD("line %d,sql2 %s",__LINE__,sql2);
                                resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
                                if(SMT_SQL_RET_SUCCESS == resultRet) {
                                    SMTLOGD("line %d,insert success",__LINE__);
                                    index = pri + 1 + SMT_IOS_POP_DEVICE_MAX;
                                }
                                else {
                                    DTLOG_ERR(0x40801C, "insert faild");
                                    SMTLOGD("line %d,insert faild,errMsg %s",__LINE__,errMsg);
                                    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                                        DTLOG_ERR(0x40801C, "DB operate rollback fail");
                                        SMTLOGD("SmartIosSettingProxy::iapDeviceInsert, rollback fail");
                                    }
                                    cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                                    return SMT_IOS_DEVICE_INDEX_INVALID;
                                }
                                
                                if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
                                    DTLOG_ERR(0x40801C, "DB operate commit fail");
                                    SMTLOGD("SmartIosSettingProxy::iapDeviceInsert, commit fail");
                                    return index;
                                }
                                sqlite3_free(sql2);
                            }
                        }
                        else {
                            DTLOG_ERR(0x40801C, "DB operate selete fail");
                            SMTLOGD("aild,err %s",errMsg);
                            cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                            return SMT_IOS_DEVICE_INDEX_INVALID;
                        }
                    }
                    else {
                        SMTLOGD("the device is no pop device");
                        DTLOG_INFO(0x40801C, "the device is no pop device,priority %d, popStatus %d", devname.format.priority, devname.format.popStatus);
                        SMTLOGD("priority %d,popStatus %d,devnmae %s",devname.format.priority,devname.format.popStatus,devname.format.deviceName);
                        index = devname.format.priority + SMT_IOS_POP_DEVICE_MAX;
                        *selectStatus = devname.format.popStatus;
                    }
                }
                else {
                    DTLOG_ERR(0x40801C, "DB operate selete fail");
                    SMTLOGD("select faild,errMsg %s",errMsg);
                    cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                    return SMT_IOS_DEVICE_INDEX_INVALID;
                }
            }
            else {
                SMTLOGD("the device is pop device");
                DTLOG_INFO(0x40801C, "the device is pop device,priority %d, popStatus %d", devname.format.priority, devname.format.popStatus);
                SMTLOGD("priority %d,popStatus %d,devnmae %s",devname.format.priority,devname.format.popStatus,devname.format.deviceName);
                index = devname.format.priority;
                *selectStatus = devname.format.popStatus;
            }
        }
        else {
            DTLOG_ERR(0x40801C, "DB operate selete fail");
            SMTLOGD("select faild,errMsg %s",errMsg);
            cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
            return SMT_IOS_DEVICE_INDEX_INVALID;
        }
    }
    else {
        DTLOG_ERR(0x40801C, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
    return index;
}
/**
    * @brief isPopDeviceBySerinum ,judge the device is or not pop device
    *
    * @param serinum,the device serinum
    *
    * @return 
    */
bool SmartIosSettingProxy::isPopDeviceBySerinum(const char * serinum)    /* __0x40801D_DTFUNCID__ */ {
    char sql[SQL_MAX_LENGTH] = {0};
    char * errMsg = NULL;
    enum SMT_SQL_RET resultRet;
    
    snprintf(sql,SQL_MAX_LENGTH,"select * from popDevices where serinum = '%s'",serinum);
    if (NULL != mdb){
        resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,NULL,&errMsg));
        if(SMT_SQL_RET_SUCCESS == resultRet) {
            if(resultCountOpe != 0) {
                SMTLOGD("is pop device,serinum = %s",serinum);
                return true;
            }
            else {
                SMTLOGD("is not pop device,serinum = '%s'",serinum);
                return false;
            }
        }
        else {
            DTLOG_ERR(0x40801D, "select pop device faild");
            SMTLOGD("select pop device faild,errMsg %s",errMsg);
            cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
            return false;
        }
    }
    else {
        DTLOG_ERR(0x40801D, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
    
    return false;
}
bool SmartIosSettingProxy::isPopStatusValidHigh(uint8_t pop)    /* __0x40801E_DTFUNCID__ */
{
    uint8_t size = sizeof(mPopStatusHighTable);
    for(uint8_t i = 0 ; i < size; i++)
    {
        if(pop == mPopStatusHighTable[i])
        {
            return TRUE;
        }
    }
    
    DTLOG_ERR(0x40801E, "isPopStatusValidHigh return false");
    return FALSE;
}
bool SmartIosSettingProxy::isPopStatusValidLow(uint8_t pop)    /* __0x40801F_DTFUNCID__ */
{
    uint8_t size = sizeof(mPopStatusLowTable);
    for(uint8_t i = 0 ; i < size; i++)
    {
        if(pop == mPopStatusLowTable[i])
        {
            return TRUE;
        }
    }
    DTLOG_ERR(0x40801F, "isPopStatusValidLow return false");
    return FALSE;
}
/**
    * @brief getSerialNumIndex ,reserved for setting service IF
    *
    * @param serialNum
    *
    * @return 
    */
uint8_t SmartIosSettingProxy::getSerialNumIndex(std::string serialNum)    /* __0x408020_DTFUNCID__ */
{
    UNUSED(serialNum);

    uint8_t i = 0;
    uint8_t index = SMT_IOS_DEVICE_INDEX_INVALID;
    return index;
}
/**
* @brief setDeviceName ,set device really name
*
* @param serinum
* @param devname,really name
*/
void SmartIosSettingProxy::setDeviceName(const char * serinum,const char * devname, SmtDeviceType deviceType)    /* __0x408021_DTFUNCID__ */ {
    SMTLOGD("SmartIosSettingProxy::setDeviceName,serinum %s length %d,devname %s length %d\n",serinum,strlen(serinum),devname,strlen(devname));
    char sql[SQL_MAX_LENGTH] = {0};
    char * errMsg = NULL;
    IosDeviceName name;
    memset(&name,0,sizeof(name));
    bool nameFlag = true;
    int len = strlen(devname);
    int i;
    enum SMT_SQL_RET resultRet;
    
    for(i = 0; i < len; ++i) {
        if(devname[i] != ' ') {
        break;
        }
    }
    if(i >= len) {
        DTLOG_INFO(0x408021, "nameFlag = false");
        nameFlag = false;
    }
    if (SMT_DEVICE_TYPE_IOS == deviceType){
        snprintf(sql,SQL_MAX_LENGTH,"select * from popDevices where serinum = '%s'",serinum);
    }
    else{
        snprintf(sql,SQL_MAX_LENGTH,"select * from popDevicesAndr where serinum = '%s'",serinum);
    }
    if (NULL != mdb){
        resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&name,&errMsg));
        if(SMT_SQL_RET_SUCCESS == resultRet) {
			#ifdef UT_GTEST_FULL_ENG
			if(ForGetLocalValue() == 0) {
			#else
            if(resultCountOpe == 0)  {
			#endif
                SMTLOGD("the device is not pop device");
                snprintf(sql,SQL_MAX_LENGTH,"select * from noPopDevices where serinum = '%s'",serinum);
                resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&name,&errMsg));
                if(SMT_SQL_RET_SUCCESS == resultRet) {
                    if(resultCountOpe == 0) {
                        SMTLOGD("the device is also not no pop device");
                    }
                    else {
                        if(nameFlag) {
                            SMTLOGD("name.format.deviceName %s length %d",name.format.deviceName,strlen((char*)name.format.deviceName));
                            if(strcmp(devname,(char*)name.format.deviceName) != 0) {
                                
                                if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
                                    DTLOG_ERR(0x408021, "DB operate begin fail");
                                    SMTLOGD("SmartIosSettingProxy::setDeviceName, begin fail");
                                    return;
                                }
                                
                                char *sql2 = NULL;
                                if (SMT_DEVICE_TYPE_IOS == deviceType){
                                    sql2 = sqlite3_mprintf("update noPopDevices set devname = '%q',nameIsValid = '%d' where serinum = '%q'",devname,NAME_IS_VALID,serinum);
                                }
                                else{
                                    sql2 = sqlite3_mprintf("update noPopDevicesAndr set devname = '%q',nameIsValid = '%d' where serinum = '%q'",devname,NAME_IS_VALID,serinum);
                                }
                                SMTLOGD("line %d,sql2 %s",__LINE__,sql2);
                                resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
                                if(SMT_SQL_RET_SUCCESS == resultRet) {
                                    SMTLOGD("update success");
                                }
                                else {
                                    DTLOG_ERR(0x408021, "update faild");
                                    SMTLOGD("update faild,errMsg %s",errMsg);
                                    if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                                        DTLOG_ERR(0x408021, "DB operate rollback fail");
                                        SMTLOGD("SmartIosSettingProxy::setDeviceName, rollback fail");
                                    }
                                    cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                                    sqlite3_free(sql2);
                                    return;
                                }
                                
                                if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
                                    DTLOG_ERR(0x408021, "DB operate commit fail");
                                    SMTLOGD("SmartIosSettingProxy::setDeviceName, commit fail");
                                    sqlite3_free(sql2);
                                    return;
                                }
                                sqlite3_free(sql2);
                            }//devname is same not need update
                            else {
                                DTLOG_INFO(0x408021, "devname is same,not need update");
                                SMTLOGD("devname is same,not need update");
                            }
                        }
                        else {
                            DTLOG_ERR(0x408021, "devname is same,not need update");
                            SMTLOGD("the devname character is all blank space");
                        }
                    }

                }
                else {
                    DTLOG_ERR(0x408021, "select faild");
                    SMTLOGD("select faild,errMsg %s",errMsg);
                    cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_NO_POP_IOS);
                    
                    return;
                }
            }
            else {
                SMTLOGD("the device is pop device");
                SMTLOGD("name.format.deviceName %s length %d",name.format.deviceName,strlen((char*)name.format.deviceName));
                if(nameFlag) {
                    if(strcmp(devname,(char*)name.format.deviceName) != 0) {
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
                            DTLOG_ERR(0x408021, "DB operate begin fail");
                            SMTLOGD("SmartIosSettingProxy::setDeviceName, begin fail");
                            return;
                        }
                        char * sql2 = NULL;
                        if (SMT_DEVICE_TYPE_IOS == deviceType){
                            sql2 = sqlite3_mprintf("update popDevices set devname = '%q',nameIsValid = '%d' where serinum = '%q'",devname,NAME_IS_VALID,serinum);
                        }
                        else{
                            sql2 = sqlite3_mprintf("update popDevicesAndr set devname = '%q',nameIsValid = '%d' where serinum = '%q'",devname,NAME_IS_VALID,serinum);
                        }
                        resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
                        if(SMT_SQL_RET_SUCCESS == resultRet) {
                            SMTLOGD("update success");
                        }
                        else {
                            DTLOG_ERR(0x408021, "update faild");
                            SMTLOGD("update faild,errMsg %s",errMsg);
                            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                                DTLOG_ERR(0x408021, "DB operate rollback fail");
                                SMTLOGD("SmartIosSettingProxy::setDeviceName, rollback fail");
                            }
                            cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
                            sqlite3_free(sql2);
                            return;
                        }
                        
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
                            DTLOG_ERR(0x408021, "DB operate commit fail");
                            SMTLOGD("SmartIosSettingProxy::setDeviceName, commit fail");
                            sqlite3_free(sql2);
                            return;
                        }
                        sqlite3_free(sql2);
                    }
                    else {
                        DTLOG_INFO(0x408021, "the devname is same,not need update");
                        SMTLOGD("the devname is same,not need update");
                    }
                }
                else {
                    //Device name is empty, do nothing
#if 0 //18HPMDA JIRA HPM18-40237 Bug fix
                    char * errMsg = NULL;
                    DTLOG_ERR(0x408021, "the devname character is all blank space");
                    SMTLOGD("the devname character is all blank space");
                    IosDeviceName name;
                    int maxIndex = 0;
                    memset(&name,0,sizeof(name));
                    
                    if (SMT_DEVICE_TYPE_IOS == deviceType){
                        snprintf(sql,SQL_MAX_LENGTH,"select max(nonameindex) from popDevices where nameIsValid = '%d'",NAME_IS_INVALID);
                    }
                    else{
                        snprintf(sql,SQL_MAX_LENGTH,"select max(nonameindex) from popDevicesAndr where nameIsValid = '%d'",NAME_IS_INVALID);
                    }
                    resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql,sqlite3_callback,(void*)&name,&errMsg));
                    if(SMT_SQL_RET_SUCCESS == resultRet) {
                        char invalidname[SMT_IOS_DEVICE_NAME_MAX_LEN + 1] = {0};
                        snprintf(invalidname,SMT_IOS_DEVICE_NAME_MAX_LEN,"iphone%d",maxIndex + 1);
                        SMTLOGD("invalidname is %s",invalidname);
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "begin", NULL, NULL, NULL))){
                            DTLOG_ERR(0x408021, "DB operate begin fail");
                            SMTLOGD("SmartIosSettingProxy::setDeviceName, begin fail");
                            return;
                        }
                        
                        char *sql2 = NULL;
                        if (SMT_DEVICE_TYPE_IOS == deviceType){
                            sql2 = sqlite3_mprintf("update popDevices set devname = '%q',nameIsValid = '%d',nonameindex = '%d' where serinum = '%q'",invalidname,NAME_IS_INVALID,maxIndex + 1,serinum);
                        }
                        else{
                            sql2 = sqlite3_mprintf("update popDevicesAndr set devname = '%q',nameIsValid = '%d',nonameindex = '%d' where serinum = '%q'",invalidname,NAME_IS_INVALID,maxIndex + 1,serinum);
                        }
                        resultRet = dbOperateRetJudgement(sqlite3_exec(mdb,sql2,NULL,NULL,&errMsg));
                        if(SMT_SQL_RET_SUCCESS == resultRet) {
                            SMTLOGD("update success");
                        }
                        else {
                            DTLOG_ERR(0x408021, "update faild");
                            SMTLOGD("update faild,errmsg %s",errMsg);
                            if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "rollback", NULL, NULL, NULL))){
                                DTLOG_ERR(0x408021, "DB operate rollback fail");
                                SMTLOGD("SmartIosSettingProxy::setDeviceName, rollback fail");
                            }
                            cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
                            sqlite3_free(sql2);
                            return;
                        }
                        
                        if (SMT_SQL_RET_SUCCESS != dbOperateRetJudgement(sqlite3_exec(mdb, "commit", NULL, NULL, NULL))){
                            DTLOG_ERR(0x408021, "DB operate commit fail");
                            SMTLOGD("SmartIosSettingProxy::setDeviceName, commit fail");
                            sqlite3_free(sql2);
                            return;
                        }
                        sqlite3_free(sql2);
                    }
                    else {
                        DTLOG_ERR(0x408021, "select max(nonameindex) faild");
                        SMTLOGD("select max(nonameindex) faild,errMsg %s",errMsg);
                        cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
                        
                        return;
                    }
#endif //18HPMDA JIRA HPM18-40237 Bug fix
                }
            }
        }
        else {
            DTLOG_ERR(0x408021, "select faild");
            cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
            SMTLOGD("line %d,select faild,errMsg %s",__LINE__,errMsg);
            
            return;
        }
    }
    else {
        DTLOG_ERR(0x408021, "smartphone mdb is NULL");
        SMTLOGD("smartphone mdb is NULL");
        //reopen DB
        initSqlite3DB();
    }
}
/**
* @brief getDeviceInfo ,get pop device info
*
* @param reqType,0 all,1 single
* @param index,reserved for sing
* @param mDevList container to save pop info
*
* @return 
*/
bool SmartIosSettingProxy::getDeviceInfo(SmtDevReqType reqType, uint8_t index, std::vector<IosDeviceName*>  *mDevList, SmtDeviceType deviceType)    /* __0x408022_DTFUNCID__ */
{
    UNUSED(index);
    char sql[SQL_MAX_LENGTH] = {0};
    char * errMsg = NULL;
    char **result = NULL;
    int nRow = 0;
    int nCol = 0;
    enum SMT_SQL_RET resultRet;
    
    if (SMT_DEVICE_TYPE_IOS == deviceType){
        snprintf(sql,SQL_MAX_LENGTH,"select * from popDevices");
    }
    else{
        snprintf(sql,SQL_MAX_LENGTH,"select * from popDevicesAndr");
    }
    resultRet = dbOperateRetJudgement(sqlite3_get_table(mdb,sql,&result,&nRow,&nCol,&errMsg));
    if(SMT_SQL_RET_SUCCESS == resultRet) {
        SMTLOGD("get table success");
        SMTLOGD("nrow %d,ncol %d",nRow,nCol);
        int index = nCol;
        for(int i = 0; i < nRow; ++i) {
            if(reqType == SMT_IOS_DEV_ALL_REQ) {
                IosDeviceName* device = new IosDeviceName;
                memset(device,0,sizeof(IosDeviceName));
                SMTLOGD("seirnum %s,priority %s,popStatus %s,devname %s",result[index],result[index + 1],result[index + 2],result[index + 3]);
                memcpy(device->format.serinum,result[index],SMT_IOS_DEVICE_SERIALNUM_MAX);
                device->format.serinum[SMT_IOS_DEVICE_SERIALNUM_MAX] = '\0';
                device->format.priority = atoi(result[index + 1]);
                device->format.popStatus = atoi(result[index + 2]);
                memcpy(device->format.deviceName,result[index + 3],SMT_IOS_DEVICE_NAME_MAX_LEN);
                mDevList->push_back(device);
                index += nCol;
            }
            else {
                IosDeviceName* device = new IosDeviceName;
                memset(device,0,sizeof(IosDeviceName));
                memcpy(device->format.serinum,result[index],SMT_IOS_DEVICE_SERIALNUM_MAX);
                device->format.serinum[SMT_IOS_DEVICE_SERIALNUM_MAX] = '\0';
                device->format.priority = atoi(result[index + 1]);
                device->format.popStatus = atoi(result[index + 2]);
                memcpy(device->format.deviceName,result[index + 3],SMT_IOS_DEVICE_NAME_MAX_LEN);
                mDevList->push_back(device);
                break; 
            }
        }
        sqlite3_free_table(result);
    }
    else {
        DTLOG_ERR(0x408022, "get table faild");
        SMTLOGD("get table faild,errMsg %s",errMsg);
        cleanTablesWhenOpeErr(resultRet, SMT_DB_TABLE_TYPE_POP_IOS);
        return false;
    }
    if(mDevList->size() != 0){
        return true;
    }
    
    DTLOG_INFO(0x408022, "mDevList->size() == 0");
    return false;
}
} /* namespace goni */
