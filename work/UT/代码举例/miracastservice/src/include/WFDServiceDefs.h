#ifndef __WFDSERVICE_DEFS_H__
#define __WFDSERVICE_DEFS_H__

#include "cutils/log.h"
#include "WFDServiceServiceDefines.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "wfdservice"

#define MCLOGE(...) ALOGE(__VA_ARGS__)
#define MCLOGD(...) ALOGD(__VA_ARGS__)
#define MCASSERT(cond, ...) ALOG_ASSERT(cond, ## __VA_ARGS__)

//typedef void (*handlerCbFunc)(uint8_t opcode, void *msg);

#define WFD_ACTION_OK 0
#define WFD_ACTION_NG 1

#define BT_UNCONNETED 0
#define BT_CONNECTED 1

#define HID_UNCONNETED 0
#define HID_CONNECTED 1

#define P2P_UNCONNECTED 0
#define P2P_CONNECTED 1
#define P2P_CONNECTING 2
#define P2P_DISCONNECTING 3

#define STA_UNCONNECTED 0
#define STA_CONNECTED 1

#define WFD_SERVICE_UNCONNECTED 0
#define WFD_SERVICE_CONNECTED 1

#define FILTER_VALUE 10

#define WFD_SERVICE_ERR_OK 0
#define WFD_SERVICE_ERR_FAILED 1

#define WFD_SOURCE_OFF 0
#define WFD_SOURCE_ON 1
#define WFD_SOURCE_CHANGE 2


#define WIFI_POWER_OFF 0
#define WIFI_POWER_ON 1


#define WIFI_STATE_DISCONNECTTED 0
#define WIFI_STATE_CONNECTTED 1


#define WIFI_TAG_MIRACAST 0x02
#define WIFI_TAG_MIRRORLINK 0x03

const unsigned int WFD_TIME_30SEC = 30;
const unsigned int WFD_TIME_60SEC = 60;
const unsigned int WFD_TIME_1SEC = 1;
const unsigned int WFD_SEC2MSEC = 1000;
const unsigned int WFD_TIME_100MS = 100;
const unsigned int WFD_TIME_50MS = 50;

const int PREPARE_RETRY_TIMES  = 3;

const int APP_ON_DESK = 0x01;
const int APP_NO_DESK = 0x00;

const int NAVI_VOICE_ON = 0x01;
const int NAVI_VOICE_OFF = 0x02;

const int TRANS_SWITCH_UDP = 0x00;
const int TRANS_SWITCH_TCP = 0x01;

const int TCP_PORT = 20000;
const int UDP_PORT = 15550;

typedef enum
{
    WFD_DT_MANAGER,
    WFD_DT_INPPUTMANAGER,
    WFD_DT_AVCTR,
    WFD_DT_STACK,
    WFD_DT_WIFI,
    WFD_DT_SETTING,
    WFD_DT_MULTI,
    WFD_DT_PLAER
}WFD_DT_SUBID;


const int NAVI_NULL = 0x00;
const int NAVI_BEGIN = 0x01;
const int NAVI_END = 0x02;
const int NAVI_ENDING = 0x12;
const int MAX_RETRY_TIME = 0x03;


#endif // __WFDSERVICE_DEFS_H__
