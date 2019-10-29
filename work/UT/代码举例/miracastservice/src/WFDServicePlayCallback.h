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
 * @file WFDServicePlayCallback.h
 *
 * @brief WFDServicePlayCallback is a callback from media player
 *
 */

#ifndef WFDSERVICEPLAYCALLBACK_H
#define WFDSERVICEPLAYCALLBACK_H

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "mediaplayer/NMMPClassicPlayer.h"
#include "types/TypesDefine.h"

namespace goni
{
class WFDServiceManager;
class WFDServiceAVCtr;

//class NMMiracastAudioVideoCtrl;

/**
 * @class NMMiracastPlayerCallback class
 *
 * @brief NMMiracastPlayerCallback is due to listen media player
 *
 */
class WFDServicePlayCallback : public media::NMMPClassicPlayerDelegation
{

public:
    WFDServicePlayCallback(WFDServiceManager* manager, WFDServiceAVCtr* player);
    virtual ~WFDServicePlayCallback();

        /**
     * to notify that the play status has been updated.
     * @param[out] status, play status
     *                     refer to the definition of NMMP_PlayStatus in NMMediaPlayerDef.h.
     * @param[out] mask
     * @return none
     */
    virtual VOID playStatusChanged(const media::NMMP_PlayStatus &status, INT32 mask);
    /**
     * to notify that the current media info has been updated.
     * @param[out] info, media information
     *                     refer to the definition of NMMP_MediaInfo in NMMediaPlayerDef.h.
     * @param[out] mask
     * @return none
     */
    virtual VOID mediaInfoUpdated(const media::NMMP_MediaInfo &info, INT32 mask);

    /**
     * to notify that the connection status between classic-player and MediaService has been changed.
     * @return none
     */
    virtual VOID onConnected();
    virtual VOID onDisconnected();
    virtual VOID onConnectError(INT32 connErrId);
        /**
     * ack to user to notify the result of NMMPClassicPlayer::prepare()
     * @param[in] retCode, result of the request, possible values are listed below:
     *                     NMMP_Ret_NoError: successful
     *                     NMMP_Ret_Err_Failed: failed for other reasons
     * @param[in] seqId, the seqId indicates which request gose with this ack
     * @return none
     */
    virtual VOID ackPrepare(INT32 retCode, INT64 seqId);

    /**
     * ack to user to notify the result of NMMPClassicPlayer::play()
     * @param[in] retCode, result of the request, possible values are listed below:
     *                     NMMP_Ret_NoError: successful
     *                     NMMP_Ret_Err_Failed: failed for other reasons
     * @param[in] seqId, the seqId indicates which request gose with this ack
     * @return none
     */
    virtual VOID ackPlay(INT32 retCode, INT64 seqId);


private:
    WFDServicePlayCallback(const WFDServicePlayCallback& other);
    WFDServicePlayCallback& operator= (const WFDServicePlayCallback& other);
    WFDServiceManager* mManager;
    WFDServiceAVCtr* mPlayer;
    int retryTimes;
};


}

#endif /* NMMIRACASTPLAYERCALLBACK_H */
/* EOF */

