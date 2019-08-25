/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/smartphoneservice/aidl/ISMTService.aidl
 */
#ifndef TEST__SmartIosService_SERVICE_DEFINES_H__
#define TEST__SmartIosService_SERVICE_DEFINES_H__

#include <vector>
#include "utils/String8.h"
#include "utils/String16.h"

#ifndef UNUSED
#define UNUSED(x) (x)
#endif

namespace Test {

enum SMT_SVC_ERROR_CODE 
{
    SMT_SVC_SUCCESS,
    SMT_SVC_FAILED,
    SMT_SVC_INVALID_PARAM,
    SMT_SVC_ILLAGE_STATUS,
    SMT_SVC_OPERATION_ERROR,
    SMT_SVC_TIMEOUT_ERROR,
};

enum SmtConnectState 
{
    SMT_DISCONNECT,
    SMT_CONNECTED,
};

enum SMT_DEV_IAP2_INSERT_STATE 
{
    SMT_DEV_IAP2_EXTRACT,
    SMT_DEV_IPA2_INSERT,
};

enum SMT_DEV_ANDROID_INSERT_STATE
{
    SMT_DEV_ANDROID_EXTRACT,
    SMT_DEV_ANDROID_INSERT
};

enum SmtDeviceType 
{
    SMT_DEVICE_TYPE_IOS,
    SMT_DEVICE_TYPE_ANDROID
};

enum SmtPopStatus 
{
    SMT_POP_INVALID,
    SMT_AUTOCARPLAY,
    SMT_AUTOWEBLINK
};

enum SmtPopStatusAndroid 
{
    SMT_ANDROID_POP_INVALID,
    SMT_ANDROID_AUTOAAP,
    SMT_ANDROID_AUTOWEBLINK
};

enum SmtSetType 
{
    SMT_IOS_POPUP_SET,
    SMT_IOS_MANU_SET,
};

enum SmtDevReqType 
{
    SMT_IOS_DEV_ALL_REQ,
    SMT_IOS_DEV_SINGLE_REQ,
};

enum SmtIosSource 
{
    SMT_IOS_SOURCE_CARPLAY,
    SMT_IOS_SOURCE_WEBLINK,
    SMT_IOS_SOURCE_IPOD,
};

enum SmtAndroidSource 
{
    SMT_ANDROID_SOURCE_AAP,
    SMT_ANDROID_SOURCE_WEBLINK
};


}/*namespace goni*/
using namespace Test;
#endif
/* EOF */
