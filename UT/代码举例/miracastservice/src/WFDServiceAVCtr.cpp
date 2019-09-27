#include "WFDServiceAVCtr.h"
#include "WFDServiceDefs.h"
#include "WFDServicePlayCallback.h"
#include "looper/MRunnableLooper.h"
#include "utils/NMMPUtils.h"
#include "MediaTokenDef.h"
#include "servicebase/SystemLog.h"
namespace goni{

DeclearModuleID(DTMODULEID_WFDSERVICE);

WFDServiceAVCtr::WFDServiceAVCtr(WFDServiceManager* manager)/* __0x002000_DTFUNCID__ */
: mWorkThread(NULL)
, mMediaPlayer(NULL)
, mCallback(NULL)
, mManager(manager)
, mLocalIp(0)
, mLocalPort(0)
, mHdcpSupport(0)
, mState(PLAYER_STATE_NULL)
, mProtocl(TRANS_SWITCH_UDP)
{
    MCLOGD("WFDServiceAVCtr Construct");
}

WFDServiceAVCtr::~WFDServiceAVCtr()/* __0x002001_DTFUNCID__ */
{
}

bool WFDServiceAVCtr::onStart()/* __0x002002_DTFUNCID__ */
{
    MCLOGD("WFDServiceAVCtr onStart");
    android::AutoMutex sync(mSyncObj);
    if (NULL == mWorkThread) {
        mWorkThread = new media::NMMPRunnableThread();
        if (NULL == mWorkThread) {
            DTLOG_PTRASSERT(mWorkThread);
            return false;
            }
    }

    if (NULL == mMediaPlayer) {
        mWorkThread->startThread("wfdservice.callback");
        media::NMMPRunnableLooper workLooper = mWorkThread->looper();

        if (NULL == mMediaPlayer){
            mCallback = new WFDServicePlayCallback(mManager, this);
        }
        mMediaPlayer = new media::NMMPClassicPlayer(workLooper, mCallback);
        if (NULL == mMediaPlayer) {
            DTLOG_PTRASSERT(mMediaPlayer);
            return false;
        }
    }
    return true;
}

void WFDServiceAVCtr::initialize()/* __0x002003_DTFUNCID__ */
{
    media::NMMP_FeatureMap feature;
    feature.insert(media::NMMPFeatureValuesPair(NMMP_FEATURE_KEY_PLAYERTYPE,NMMP_FEATURE_VAL_PLAYERTYPE_STREAMPLAYER));
    int value = mMediaPlayer->initialize(&feature, 99, NMMP_CATEGORY_ID_MIRACAST);
    MCLOGD("WFDServiceAVCtr initialize::initialize result = %d", value);
    DTLOG_INFO(0x002003, "WFDServiceAVCtr initialize::initialize result = %d", value);
}

void WFDServiceAVCtr::finalize()/* __0x002004_DTFUNCID__ */
{
    MCLOGD("WFDServiceAVCtr finalize");
    if (NULL != mMediaPlayer) {
        mMediaPlayer->stop();
        mMediaPlayer->finalize();

        delete mMediaPlayer;
        mMediaPlayer = NULL;
    }

    if (NULL != mCallback) {
        delete mMediaPlayer;
        mMediaPlayer = NULL;
    }

    if (NULL != mWorkThread) {
        mWorkThread->stopThread();

        delete mWorkThread;
        mWorkThread = NULL;
    }
    mState = PLAYER_STATE_NULL;
}

void WFDServiceAVCtr::setUri(uint32_t localIp, uint32_t localPort, uint32_t hdcpSupport)/* __0x002005_DTFUNCID__ */
{
    MCLOGD("*****%s*****localPort = %d, hdcpSupport = %d",__func__, localPort, hdcpSupport);
    DTLOG_INFO(0x002005, "setUri localPort = %d, hdcpSupport = %d", localPort, hdcpSupport);
    if ((localIp != 0) && (localPort != 0)) {
        mLocalIp = localIp;
        mLocalPort = localPort;
        mHdcpSupport = hdcpSupport;
    }
    media::NMMP_AudioDevice audioDevice;
    audioDevice.streamType = NMMP_DEVICE_ID_AUDIO_REAR;
    std::string audioToken = MIRACAST_MEDIA_TOKEN;
    media::NMMP_PropertyMap property;
    media::NMMPPropSetAudioDevice(audioDevice, property);
    media::NMMPPropSetAudioToken(audioToken, property);
    std::string key = NMMP_PROPERTY_KEY_MIRACAST_HDCP;
    media::NMMPPropSet(key, &mHdcpSupport, sizeof(INT32), property);
    if (mMediaPlayer != NULL) {
        int ret = mMediaPlayer->setProperty(property);
        if(ret<0){
            DTLOG_RET(0x002005,"setProperty failed! ret = %d",ret);
        }
    }
    prepare();
}

void WFDServiceAVCtr::prepare()/* __0x002006_DTFUNCID__ */
{
    MCLOGD("WFDServiceAVCtr prepare");
    std::string ipStr("");
    char ip[20] = {0};
    sprintf(ip, "%d.%d.%d.%d", (mLocalIp >> 24)&0x000000FF, (mLocalIp >> 16)&0x000000FF,
            (mLocalIp >> 8)&0x000000FF, mLocalIp&0x000000FF);
    ipStr.assign(ip, sizeof(ip));

    std::string mediaPath("");
    char charPath[40] = { 0 };
#if 0
    sprintf(charPath, "udp://%s:%u", ipStr.c_str(), mLocalPort);
#endif
    if (mLocalPort == UDP_PORT) {
        sprintf(charPath, "udp://%s:%u", ipStr.c_str(), mLocalPort);
    }
    else {
        sprintf(charPath, "tcp://%s:%u", ipStr.c_str(), mLocalPort);
    }
    mediaPath.assign(charPath, sizeof(charPath));

    MCLOGD("setDataSource mediapath = %s", mediaPath.c_str());
    if (NULL != mMediaPlayer) {
        setPlayerState(PLAYER_STATE_PREPARE);
        int ret = mMediaPlayer->prepare(mediaPath);
        MCLOGD("result = %d", ret);
        DTLOG_INFO(0x002006, "WFDServiceAVCtr prepare, ret = %d", ret);
    }
}

void WFDServiceAVCtr::play()/* __0x002007_DTFUNCID__ */
{
    MCLOGD("WFDServiceAVCtr play");
    if (NULL != mMediaPlayer) {
        int ret = mMediaPlayer->play();
        MCLOGD("result = %d", ret);
        DTLOG_INFO(0x002007, "WFDServiceAVCtr play, ret = %d", ret);
    }
}

void WFDServiceAVCtr::pause()/* __0x002008_DTFUNCID__ */
{
    MCLOGD("WFDServiceAVCtr pause");
    if (NULL != mMediaPlayer) {
        int ret = mMediaPlayer->pause();
        MCLOGD("result = %d", ret);
        DTLOG_INFO(0x002008, "WFDServiceAVCtr pause, ret = %d", ret);
    }
}

int WFDServiceAVCtr::stop()/* __0x002009_DTFUNCID__ */
{
    MCLOGD("WFDServiceAVCtr stop");
    android::AutoMutex sync(mSyncObj);
    int64_t ret = 0;
    if (NULL != mMediaPlayer) {
        ret = mMediaPlayer->stop();
        mState = PLAYER_STATE_STOP;
        MCLOGD("result = %d", ret);
        DTLOG_INFO(0x002009, "WFDServiceAVCtr stop, ret = %d", ret);
    }
    return ret;

}

#if 0
void WFDServiceAVCtr::tranSwitchReq(int protocl)
{
    MCLOGD("=========%s============protocl = %d", __func__, protocl);
    mLocalPort = (protocl == TRANS_SWITCH_UDP) ? UDP_PORT:TCP_PORT;
    //setUri(mLocalIp, port, mHdcpSupport, protocl);
    media::NMMP_PropertyMap property;

    std::string ipStr("");
    char ip[20] = {0};
    sprintf(ip, "%d.%d.%d.%d", (mLocalIp >> 24)&0x000000FF, (mLocalIp >> 16)&0x000000FF,
            (mLocalIp >> 8)&0x000000FF, mLocalIp&0x000000FF);
    ipStr.assign(ip, sizeof(ip));

    std::string mediaPath("");
    char charPath[40] = { 0 };
    if (protocl == TRANS_SWITCH_UDP) {
        sprintf(charPath, "udp://%s:%u", ipStr.c_str(), mLocalPort);
    }
    else {
        sprintf(charPath, "tcp://%s:%u", ipStr.c_str(), mLocalPort);
    }
    mediaPath.assign(charPath, sizeof(charPath));

    media::NMMPPropSetMediaPath(mediaPath, property);
    int ret = mMediaPlayer->setProperty(property);
    if (ret < 0) {
        MCLOGD("ret = %d, transport switch failed", ret);
    }

}
#endif

void WFDServiceAVCtr::tranSwitchReq(int protocl)
{
    MCLOGD("=========%s============protocl = %d", __func__, protocl);
    mLocalPort = (protocl == TRANS_SWITCH_UDP) ? UDP_PORT:TCP_PORT;
    int err = stop();
    if (err < 1) {
        MCLOGD("tranSwitchReq stop failed");
    }
    setUri(mLocalIp, mLocalPort, mHdcpSupport);
}


void WFDServiceAVCtr::tranSwitchCmp(uint32_t result)
{
    MCLOGD("=========%s============result = %d", __func__, result);
}

int WFDServiceAVCtr::getAudioLatency()
{
    media::NMMP_PropertyMap property;
    media::NMMPPropSet(NMMP_PROPERTY_KEY_AUDIO_LATENCY, property);
    INT32 latency = 0;
    if (NULL != mMediaPlayer) {
        int ret = mMediaPlayer->getProperty(property, TRUE);
        media::NMMPPropGet(property, NMMP_PROPERTY_KEY_AUDIO_LATENCY, (VOID*)(&latency), sizeof(latency));
        if(ret < 0){
            DTLOG_RET(0x00200A, "WFDServiceAVCtr getAudioLatency, ret = %d", ret);
        }
    }
    return latency;
}

PLAYERSTATE WFDServiceAVCtr::getPlayerState()/* __0x00200B_DTFUNCID__ */
{
    MCLOGD("*****%s*****, state = %d",__func__, mState);
    DTLOG_INFO(0x00200B, "WFDServiceAVCtr getPlayerState, state = %d", mState);
    android::AutoMutex sync(mSyncObj);
    return mState;
}

void WFDServiceAVCtr::setPlayerState(PLAYERSTATE state)/* __0x00200C_DTFUNCID__ */
{
    MCLOGD("*****%s*****, Prestate = %d, state = %d",__func__, mState, state);
    DTLOG_INFO(0x00200C, "WFDServiceAVCtr setPlayerState, Prestate = %d, state = %d", mState, state);
    android::AutoMutex sync(mSyncObj);
    mState = state;
}

}
