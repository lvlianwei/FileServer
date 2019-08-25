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
 * @file WFDSERVICEAVCTR_H
 * @brief Declaration file of class WFDSERVICEAVCTR.
 *
 */

#ifndef WFDSERVICEAVCTR_H
#define WFDSERVICEAVCTR_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "mediaplayer/NMMPPubDef.h"
#include "mediaplayer/NMMPClassicPlayer.h"
#include "utils/NMMPRunnableThread.h"
#include "utils/Mutex.h"

//class NMMPClassicPlayer;
//class NMMPRunnableThread;

namespace goni
{

typedef enum {
    PLAYER_STATE_NULL = 0,
    PLAYER_STATE_INIT,
    PLAYER_STATE_PREPARE,
    PLAYER_STATE_PLAYING,
    PLAYER_STATE_STOP
}PLAYERSTATE;

class WFDServicePlayCallback;
class WFDServiceManager;
class WFDServiceAVCtr: public android::RefBase
{
    public:
        WFDServiceAVCtr(WFDServiceManager* manager);
        virtual ~WFDServiceAVCtr();
        bool onStart();
        void initialize();
        void finalize();
        

        // mediaplayer command
        void setUri(uint32_t localIp, uint32_t localPort, uint32_t hdcpSupport);
        void prepare();
        void play();
        void pause();
        int stop();
        void tranSwitchReq(int protocl);
        void tranSwitchCmp(uint32_t result);

        PLAYERSTATE getPlayerState();
        void setPlayerState(PLAYERSTATE state);
        int getAudioLatency();
        int getProtocl(){return mProtocl;}
        void setProtocl(int protocl){mProtocl = protocl;}


    private:
        media::NMMPRunnableThread * mWorkThread;
        media::NMMPClassicPlayer* mMediaPlayer;
        WFDServicePlayCallback* mCallback;
        std::string mPath;
        WFDServiceManager* mManager;
        uint32_t mLocalIp;
        uint32_t mLocalPort;
        uint32_t mHdcpSupport;
        PLAYERSTATE mState;
        mutable android::Mutex mSyncObj;
        int mProtocl;

    private:
        WFDServiceAVCtr(const WFDServiceAVCtr&);
        WFDServiceAVCtr& operator=(const WFDServiceAVCtr&);
    };
} 
#endif /* WFDSERVICEAVCTR_H*/
/* EOF */
