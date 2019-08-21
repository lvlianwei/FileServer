/**
 * Copyright @ 2017 - 2019 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file SystemLog.h
 * @brief Declaration file System Log (Data Log Service Wrap)
 */

#ifndef SYSTEMLOG_H

#include "ni_hallib_dt.h"
#include "utils/Mutex.h"
#include "servicebase/ServiceBaseGlobal.h"

#ifndef __cplusplus
#   error This file need compile with c++ compiler
#endif

#ifndef __DISABLE_DTLOG

namespace goni {

class SystemLog {
private:
    SystemLog ();
    SystemLog (const SystemLog&);
    virtual ~SystemLog ();
public:
    static SystemLog& instance () {
        android::Mutex::Autolock _l(m_autolock);
        static SystemLog* pInst = new SystemLog ();
        /* there is tiny posiable pInst is null */
        return *pInst;
    }

    void Proc (DTMODULEID modelID, uint32_t funcId, const char* fmt, ...);
    void Info (DTMODULEID modelID, uint32_t funcId, const char* fmt, ...);
    void Ret  (DTMODULEID modelID, uint32_t funcId, const char* fmt, ...);
    void Err  (DTMODULEID modelID, uint32_t funcId, const char* fmt, ...);

private:
    void* m_pHandler;
    ni_hallib_dt_t m_device;
    static android::Mutex m_autolock;
};

} //namespace

/** 
 * @brief Condiction assert
 * @code {.cpp}
 * DTLOG_ASSERT(pDevice == NULL, BT device pointer is NULL);
 * @endcode
 */
#define DTLOG_ASSERT(condiction, info)                   \
    do{ \
        if (!!(condiction)) { \
            goni::SystemLog::instance().Err(DTLOG__GetModeID(), 0, "ERROR:[%s] "#info"\n", __func__); \
        } \
    }while(0);

/** 
 * @brief Pointer assert
 * @code {.cpp}
 * DTLOG_ASSERT(pDevice == NULL);
 * @endcode
 */
#define DTLOG_PTRASSERT(x) \
    do{ \
        if ((x) == NULL) { \
            goni::SystemLog::instance().Err(DTLOG__GetModeID(), 0, "ERROR:[%s] ptr "#x" is NULL\n", __func__); \
        } \
    }while(0);

/** 
 * @brief Pointer assert
 * @code {.cpp}
 * DTLOG_PROC(100, "run function [%s] at lines [%d]", __func__, __line__);
 * @endcode
 */
#define DTLOG_PROC(funcID, ...) \
    do{ \
        goni::SystemLog::instance().Proc(DTLOG__GetModeID(), funcID, __VA_ARGS__); \
    }while (0);
    
/** 
 * @brief record a error log
 * @code {.cpp}
 * DTLOG_ERR(100, "run function [%s] at lines [%d]", __func__, __line__);
 * @endcode
 */
#define DTLOG_ERR(funcID, ...) \
    do { \
        goni::SystemLog::instance().Err(DTLOG__GetModeID(), funcID, __VA_ARGS__); \
    }while (0);

/** 
 * @brief record a result of funciton
 * @code {.cpp}
 * DTLOG_RET(100, "run function [%s] at lines [%d]", __func__, __line__);
 * @endcode
 */
#define DTLOG_RET(funcID, ...) \
    do { \
        goni::SystemLog::instance().Ret(DTLOG__GetModeID(), funcID, __VA_ARGS__); \
    }while (0);

/** 
 * @breif record a information
 * @code {.cpp}
 * DTLOG_INFO(100, "run function [%s] at lines [%d]", __func__, __line__);
 * @endcode
 */
#define DTLOG_INFO(funcID, ...) \
    do { \
        goni::SystemLog::instance().Info(DTLOG__GetModeID(), funcID, __VA_ARGS__); \
    }while (0);

/** 
 * @brief This should be placed at the top part of a source file, to declear a model ID
 * @code {.cpp}
 * DeclearFunctionID(DTMODULEID_FUNCMNG);
 *
 * typedef enum DTMODULEID
 * {
 *     DTMODULEID_DIAG = 0,   ///< DiagService trace
 *     DTMODULEID_FUNCMNG,   ///< Funcmng trace
 *     DTMODULEID_WIFISERVICE,   ///< WifiService trace
 *     DTMODULEID_SYSD,   ///< sysd trace
 *     DTMODULEID_CONNECTMANAGER,   ///< connect manager trace
 *     DTMODULEID_WFDSERVICE,  ///< WfdService trace
 *     DTMODULEID_BTSERVICE,  ///< btservice trace
 *     DTMODULEID_BTSPECIAL,  ///< btservice special trace
 *     DTMODULEID_MEDIAPLAYER, ///< mediaplayer
 *     DTMODULEID_AUDIOSERVER, ///< audioserver
 *     DTMODULEID_MEDIAUSB, ///< mediausb
 *     DTMODULEID_MEDIAIPOD, ///< mediaipod
 *     DTMODULEID_CARPLAY, ///< carplay
 *     DTMODULEID_CARLIFE, ///< carlife
 *     DTMODULEID_SETTING, ///< setting
 *     DTMODULEID_WEBLINK, ///< web link
 *     DTMODULEID_VRSERVICE, ///< vr service
 *     DTMODULEID_HDCPSERVICE, ///< hdcpservice
 *     DTMODULEID_ISC, ///< ISC trace
 *     DTMODULEID_SERVICEBASE, ///< Service base trace
 *     DTMODULEID_SMARTIOS, ///< Smart ios trace
 *     DTMODULEID_MAX,
 * 
 *     DTMODULEID_TEST, // TODO: for test, must be deleted
 * } ni_hallib_dtmodule_id;
 * @endcode
 *
 * @ref DTMODULEID
 */
#define DeclearFunctionID(modeID) \
    static DTMODULEID DTLOG__GetModeID () { \
        return modeID; \
    }

#define DeclearModuleID(modeID) \
    static DTMODULEID DTLOG__GetModeID () { \
        return modeID; \
    }

#else //__DISABLE_DTLOG

#define DTLOG_ASSERT(condiction, info) while(0){};
#define DTLOG_PTRASSERT(x) while(0){};
#define DTLOG_PROC(funcID, ...) while(0){};
#define DTLOG_ERR(funcID, ...) while(0){};
#define DTLOG_RET(funcID, ...) while(0){};
#define DTLOG_INFO(funcID, ...) while(0){};

#endif //__DISABLE_DTLOG
 

#endif //SYSTEMLOG_H
