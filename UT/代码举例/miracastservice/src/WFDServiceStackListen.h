
#ifndef WFDSERVICE_STACKLISTEN_H
#define WFDSERVICE_STACKLISTEN_H

#include "IWFDLibClient.h"
#include "utils/Mutex.h"
#include "utils/RefBase.h"
namespace goni{

class WFDServiceManager;
class WFDStackListener: public IWFDLibClient, public android::RefBase
{
    public:
        WFDStackListener(WFDServiceManager* center);
        ~WFDStackListener();

    public:
        virtual void notifyDisplayConnected(int error);

        virtual void notifyDisplaycCancelConnect(int error);

        virtual void notifyDisplayDisconnect(int error);

        virtual void notifyPlayResult(int error);

        virtual void notifySetUpResult(int error);
        
        virtual void notifyPauseResult(int error);

        virtual void notifyTearDownResult(int error);

        virtual void notifySelectedAudioFormat (unsigned int selectedFormat);

        virtual void notifySelectedVideoSize(unsigned int selectedSize);

        virtual void notifyRtpData(unsigned char* data, unsigned int size, int seq);

        virtual void notifyUIBCStreamAddress(unsigned int localIp,unsigned int localUIBCPort);

        virtual void notifyRtpStreamAddress(string& uri, unsigned int localRtpPort);

        virtual void notifyRtpStreamAddress(unsigned int localIp, unsigned int localRtpPort);

        virtual void audioRenderChanged(int error,Role target);

        virtual void notifyUIBCResult(bool result, unsigned int width, unsigned int height);

        virtual void notifyScreenInfo(unsigned char locked, unsigned char cross);

        virtual void notifyAppAvailableInd(uint error);

        virtual void notifyNaviVoiceInd(uint error);

        virtual void notifyGPSTimeInd(uint error, uint len, unsigned char* time);

        virtual void notifyCurrentAppChange(uint appId);

        virtual void notifyInvalidAppInd(uint state);

        virtual void notifyModeChangeSuccess(unsigned char mode);

        virtual void notifyRemoteBtMac(char macLen, char* macAddr);

        virtual void notifySendIDRResult(int error);

        virtual void notifyPeerDeviceHdcp(int error);

        virtual void notifyReceiverId(unsigned long long revId);

        uint64_t char2U64(const char *ptr);

        void onNaviVoiceLatency(Timer *timer);

        void onSendNaviState(int naviState);

        void notifyTranportSwitch(TransProtocl method);

        void notifySwitchCompleted(uint result);

        void notifyRemoteStaConnected(uint result);


    private:
        WFDServiceManager* mManager;
        mutable android::Mutex mSyncObj;
        WFDStackListener(WFDStackListener&);
        WFDStackListener& operator=(WFDStackListener&);
        goni::EasyTimer<WFDStackListener> m_timer;
        int mNaviState;
        int32_t mPlayRetry;
        int32_t mPauseRetry;
        int32_t mIDRRetry;

};

}

#endif
