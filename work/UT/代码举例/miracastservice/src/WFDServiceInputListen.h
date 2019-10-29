#ifndef WFDSERVICE_INPUTLISTEN_H
#define WFDSERVICE_INPUTLISTEN_H
#include "proxy/InputManagerProxyBase.h"
#include "utils/Mutex.h"
#include "servicebase/Timer.h"

namespace goni{

typedef struct {
    TOUCH_STATE state;
    uint16_t dataLen;
    uint16_t data[4];
}multiKey;

typedef enum {
    HID_UP = 0x00,
    HID_DOWN = 0x01,
    HID_NULL = 0x02
}HIDKEY;

typedef struct {
    HIDKEY state;
    uint16_t data[2];

}hidKey;

class WFDServiceManager;

class WFDInputListener : public IInputManagerProxyReplier, public android::RefBase
{
public:

WFDInputListener(WFDServiceManager* manager);
~WFDInputListener();
    virtual void onConnected();

    virtual void onDisconnected();
    
    virtual android::status_t hardKey(const HARD_KEY_VALUE& value);

    virtual android::status_t touchKey(const TouchEvent_SpVec& events);

    void clearData();
    
    android::status_t sendToHID(const TouchEvent_SpVec & events);
    android::status_t sendToApp(const TouchEvent_SpVec & events);
    android::status_t sendToWFDStack(const multiKey & Key);
    android::status_t addHidUpKey();
    void onOneShotTimer(Timer *timer);
    void onHidTimer(Timer *timer);
    void onHidReleaseTimer(Timer *timer);

private:
    WFDServiceManager* wfdManager;
    mutable android::Mutex mSyncObj;
    multiKey mKey;
    hidKey mHidKey;
    goni::EasyTimer<WFDInputListener> m_timer;
    goni::EasyTimer<WFDInputListener> m_hidTimer;
    goni::EasyTimer<WFDInputListener> m_hidReleaseTimer;
    bool hidSendFlag;
    bool firstHidPoint;
    WFDInputListener(WFDInputListener&);
    WFDInputListener& operator=(WFDInputListener&);



};

}

#endif //WFDSERVICE_INPUTLISTEN_H
