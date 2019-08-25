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

#include "NMMPClassicPlayer.h"

namespace goni
{


//class NMMiracastAudioVideoCtrl;

/**
 * @class NMMiracastPlayerCallback class
 *
 * @brief NMMiracastPlayerCallback is due to listen media player
 *
 */
class WFDServicePlayCallbak : public NMStreamMediaPlayerDelegation
{

public:
    explicit WFDServicePlayCallbak(NMMiracastAudioVideoCtrl * ctrl);
    ~WFDServicePlayCallbak();

    /**
     * to notify that playback state/speed has been changed
     * @param[in] state, playback state.
     *                  refer to the definition of NMMediaPlayer_PlaybackState in NMMediaPlayerDef.h.
     * @param[in] speed, playback speed. [-64000 ~ 64000], 1000 for normal playback speed and 0 for pause.
     *                  speed is meaningful only in the following playback state:
     *                  NMMediaPlayer_PlaybackState_Paused: speed is 0
     *                  NMMediaPlayer_PlaybackState_Playing: speed [-64000 ~ 0) & (0 ~ 64000]
     * @param[in] errorId, error code.
     * @param[in] dataSourceKey, identification of data source.
     * @return none
     */
    virtual VOID stateChanged(NMMediaPlayer_PlaybackState state, INT32 speed,
            NMMediaPlayer_ErrorCode errorId, INT64 dataSourceKey);

    /**
     * to notify that the connection status between classic-player and MediaService has been changed.
     * @param[in] status, connection status.
     *                    refer to the definition of NMMediaPlayer_ConnectStatus in NMMediaPlayerDef.h.
     *                    NMStreamMediaPlayer::initialize() is available only in NMMediaPlayer_Connected
     *                    status.
     *                    possible status are listed below:
     *                    NMMediaPlayer_DisConnected: no connection is established.
     *                    NMMediaPlayer_Connected: connection is established
     *                    NMMediaPlayer_ConnectError: error occured during connecting to MediaService.
     * @return none
     */
    virtual VOID connectNotify(NMMediaPlayer_ConnectStatus status);

    /**
     * ack to user to notify the result of NMStreamMediaPlayer::initialize()
     * @param[in] retCode, result of the request, possible values are listed below:
     *                     NMMediaPlayer_Ret_NoError: successful
     *                     NMMediaPlayer_Ret_Err_InstanceLimited: the number of player exceeds the limit.
     *                     NMMediaPlayer_Ret_Err_UnexpectedFeature: unexpected feature specified
     *                     NMMediaPlayer_Ret_Err_Failed: failed for other reasons
     * @param[in] callId, the callId indicates which request gose with this ack
     * @param[in] isReInitialize, TRUE: the backend player is already initialized before the initialize req.
     *                            FALSE:
     * @return none
     */
    virtual VOID ackInitialize(INT32 retCode, INT64 callId, NC_BOOL isReInitialize);

    /**
     * ack to user to notify the result of NMStreamMediaPlayer::finalize()
     * @param[in] retCode, result of the request, possible values are listed below:
     *                     NMMediaPlayer_Ret_NoError: successful
     *                     NMMediaPlayer_Ret_Err_Failed: failed for other reasons
     * @param[in] callId, the callId indicates which request gose with this ack
     * @return none
     */
    virtual VOID ackFinalize(INT32 retCode, INT64 callId);

    /**
     * ack to user to notify the result of NMStreamMediaPlayer::prepare()
     * @param[in] retCode, result of the request, possible values are listed below:
     *                     NMMediaPlayer_Ret_NoError: successful
     *                     NMMediaPlayer_Ret_Err_Failed: failed for other reasons
     * @param[in] callId, the callId indicates which request gose with this ack
     * @return none
     */
    virtual VOID ackPrepare(INT32 retCode, INT64 callId);

    /**
     * ack to user to notify the result of NMStreamMediaPlayer::play()
     * @param[in] retCode, result of the request, possible values are listed below:
     *                     NMMediaPlayer_Ret_NoError: successful
     *                     NMMediaPlayer_Ret_Err_Failed: failed for other reasons
     * @param[in] callId, the callId indicates which request gose with this ack
     * @return none
     */
    virtual VOID ackPlay(INT32 retCode, INT64 callId);

    /**
     * ack to user to notify the result of NMStreamMediaPlayer::stop()
     * @param[in] retCode, result of the request, possible values are listed below:
     *                     NMMediaPlayer_Ret_NoError: successful
     *                     NMMediaPlayer_Ret_Err_Failed: failed for other reasons
     * @param[in] callId, the callId indicates which request gose with this ack
     * @return none
     */
    virtual VOID ackStop(INT32 retCode, INT64 callId);

    /**
     * to notify that the current media info has been updated.
     * @param[out] info, media information
     *                     refer to the definition of NMMediaPlayer_MediaInfo in NMMediaPlayerDef.h.
     * @return none
     */
    virtual VOID mediaInfoUpdated(const NMMediaPlayer_MediaInfo &info);

private:
    WFDServicePlayCallbak(const WFDServicePlayCallbak& other);
    WFDServicePlayCallbak& operator= (const WFDServicePlayCallbak& other);
    //NMMiracastAudioVideoCtrl * m_ctrl;
};



}

#endif /* NMMIRACASTPLAYERCALLBACK_H */
/* EOF */

