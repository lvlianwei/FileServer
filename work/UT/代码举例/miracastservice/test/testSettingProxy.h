/**
 * Copyright @ 2013 - 2015 Suntec Software(Shanghai) Co., Ltd.
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
 * @file SettingProxy.h
 * @brief for SettingProxy
 *
 * @attention used for C++ only.
 */

#ifndef TESTSETTINGPROXY_H
#define TESTSETTINGPROXY_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include <list>
#include <string>
#include <servicebase/ServiceBaseDefines.h>
//#include "testDefine.h"

namespace goni
{
    //extern bool UTretvalue ;
    //extern bool UTcompvalue ;

    class SettingListener;

    class SettingProxy
    {
    public:
        explicit SettingProxy(const std::string &name);
        SettingProxy();
        virtual ~SettingProxy();
        /**
         * [listenKey add filter to event system ]
         * @param [in]  key [key]
         * @return  true is success, other is fail
         */
        virtual bool listenKey(const std::string &key);

        /**
         * [listenKey add filter to event system ]
         * @param [in] keyList [key list]
         * @return  true is success, other is fail
         */
        virtual bool listenKey(const std::list<std::string> &keyList);

        /**
         * [unlistenKey remove filter from event system]
         * @param [in] key [key]
         * @return true is success, other is fail
         */
        virtual bool unlistenKey(const std::string &key);

        /**
         * [unlistenKey remove filter from event system]
         * @param [in] keyList [key list]
         * @return true is success, other is fail
         */
        virtual bool unlistenKey(const std::list<std::string> &keyList);

        /**
         * [onNotifyUpdate notify by service]
         *
         * @param [in] key : key
         * @param [in] value : value
         *
         * @return true is success, other is fail
         */
        virtual void onNotifyUpdate(const std::string &key, const std::string &value);

        /**
         * [get the current value or default value  ]
         *
         * @param [in] type :  value or default_value
         * @param [in] key : key 
         * @param [out] value : value
         *
         * @return true is success, other is fail
         */
        virtual bool get(const std::string &type, const std::string &key, std::string &value);

        /**
         * [get value ]
         *
         * @param [in] key : key 
         * @param [out] value : value
         *
         * @return true is success, other is fail
         */
        virtual bool get(const std::string &key, std::string &value);

        /**
         * [set value]
         *
         * @param [in] key : key 
         * @param [in] value : value
         *
         * @return true is success, other is fail
         */
        virtual bool set(const std::string &key, const std::string &value);
        /**
         * [remove setting]
         *
         * @param [in] key : key
         *
         * @return true is success, other is fail
         */
        virtual bool remove(const std::string &key);
        /**
         * [get setting ready status]
         *
         * @return true is ready, other is unready
         */
        virtual bool getSettingReadyStatus();

    private:
        android::sp<SettingListener> m_spListener;
        bool m_settingReadyStatus;

    private:
        SettingProxy(const SettingProxy &);
        SettingProxy &operator=(const SettingProxy &);
    };

}

extern "C" {
    goni::SettingProxy* CreateInstance(const std::string &name);
    void DestoryInstance(goni::SettingProxy* obj);
}

#endif // SETTINGPROXY_H
