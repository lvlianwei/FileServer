/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: frameworks/service/miracastservice/aidl/IWFDService.aidl
 */
#ifndef __WFDService_SERVICE_DEFINES_H__
#define __WFDService_SERVICE_DEFINES_H__

#include <vector>
#include "utils/String8.h"
#include "utils/String16.h"

namespace goni {

enum WFD_SVC_ERROR_CODE 
{
    WFD_SVC_SUCCESS,
    WFD_SVC_FAILED,
    WFD_SVC_INVALID_PARAM,
    WFD_SVC_ILLAGE_STATUS,
    WFD_SVC_OPERATION_ERROR,
    WFD_SVC_TIMEOUT_ERROR,
};

enum wfdSvcState 
{
    WFD_POWER_OFF,
    WFD_POWER_ON,
    WFD_LISTENING,
    WFD_CONNECTING,
    WFD_CONNECTED,
    WFD_STATE_INVALID,
};

enum WFD_CONNETED_STATE 
{
    WFD_CONNECTED_FAILED,
    WFD_CONNECTED_SUCCESS,
};

// touch type
enum TouchType 
{
    TouchType_Press,
    /**< Touch/Mouse down */
    TouchType_Release,
    /**< Touch/Mouse up */
    TouchType_Move,
    /**< Touch/Mouse Move */
    TouchType_Max,
};

//DA mirror mode 
enum MirrorMode 
{
    NOWORK= 0x00,
    MIRROR,
    APP,     //only mirror

    MIRROR_INVALID,     // mirror through APP

};

//App state
enum AppState 
{
    APP_UNAVAILABLE,
    APP_AVAILABLE,
    APP_UNSUPPORT,
    APP_STATCHANGE,
};

//DA Srceen Mode
enum ScreenMode 
{
    Screen_Horizontal,
    Screen_Vertial,
};

enum HardKey 
{
    HOME_DOWN,
    HOME_UP,
    MENU_DOWN,
    MENU_UP,
    BACK_DOWN,
    BACK_UP,
    PRE_TRACK_DOWN,
    PRE_TRACK_UP,
    NEXT_TRACK_DOWN,
    NEXT_TRACK_UP,
};


}/*namespace goni*/
#endif
/* EOF */