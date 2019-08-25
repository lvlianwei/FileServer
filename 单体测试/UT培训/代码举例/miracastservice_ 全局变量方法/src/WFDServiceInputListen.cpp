#include "WFDServiceInputListen.h"
#include "WFDServiceDefs.h"
#include "WFDServiceManager.h"
#include "wfdServiceStub.h"
#include "servicebase/SystemLog.h"
#include "WFDLib.h"
namespace goni{

DeclearModuleID(DTMODULEID_WFDSERVICE);

WFDInputListener::WFDInputListener(WFDServiceManager* manager)/* __0x003000_DTFUNCID__ */
:wfdManager(manager)
, mSyncObj()
, hidSendFlag(true)
, firstHidPoint(true)
{
    mKey.state= TOUCH_IDLE;
    memset(mKey.data, 0, sizeof(mKey.data));
    mHidKey.state = HID_NULL;
    memset(mHidKey.data, 0, sizeof(mHidKey.data));
}

WFDInputListener::~WFDInputListener()/* __0x003001_DTFUNCID__ */
{
    if (m_timer.isActive())
        m_timer.stop();
    if (m_hidTimer.isActive())
        m_hidTimer.stop();
    if (m_hidReleaseTimer.isActive())
        m_hidReleaseTimer.stop();
}

void WFDInputListener::onConnected()/* __0x003002_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    if (wfdManager != NULL) {
        wfdManager->onInputManagerConnected();
    }
}

void WFDInputListener::onDisconnected()/* __0x003003_DTFUNCID__ */
{
}


void WFDInputListener::clearData()/* __0x003004_DTFUNCID__ */
{
    android::AutoMutex sync(mSyncObj);
    MCLOGD("*****%s*****", __func__);
    mKey.state= TOUCH_IDLE;
    memset(mKey.data, 0, sizeof(mKey.data));
    mHidKey.state= HID_NULL;
    memset(mHidKey.data, 0, sizeof(mHidKey.data));
    if (m_timer.isActive()) m_timer.stop();
    if (m_hidTimer.isActive()) m_hidTimer.stop();
    if (m_hidReleaseTimer.isActive())  m_hidReleaseTimer.stop();
    firstHidPoint = true;
    hidSendFlag = true;

}

android::status_t WFDInputListener::hardKey(const HARD_KEY_VALUE& value)/* __0x003005_DTFUNCID__ */
{
    return WFD_SERVICE_ERR_OK;
}
android::status_t WFDInputListener::touchKey(const TouchEvent_SpVec & events)/* __0x003006_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    android::AutoMutex sync(mSyncObj);
    WFDDeviceState_Sp deviceState = new WFDDeviceState();
    if(NULL == wfdManager){
        DTLOG_PTRASSERT(wfdManager);
        return WFD_SERVICE_ERR_FAILED;
    }
    wfdManager->wfdStateSync(deviceState);
    MCLOGD("*****%s***** hid status = %d, app status = %d", __func__, deviceState->getHid(), deviceState->getAppState());

#ifdef WFD_APP
    if (1 == events.size() && events[0] != NULL) {
        if (deviceState->getHid() == HID_CONNECTED && hidSendFlag){
            return sendToHID(events);
        }
        else {
            MCLOGD("*****%s***** HID is not connected", __func__);
            DTLOG_INFO(0x003006, "touchKey, HID is not connected");
            return WFD_SERVICE_ERR_FAILED;
        }
    }
    else {
        if((deviceState->getHid() == HID_CONNECTED) && (mHidKey.state == HID_DOWN)) {
            addHidUpKey();
        }

        if (deviceState->getAppState() == APP_AVAILABLE){
            return sendToApp(events);
        }
        else{
            MCLOGD("*****%s***** APP is not connected",  __func__);
            DTLOG_INFO(0x003006, "touchKey, APP is not connected");
            return WFD_SERVICE_ERR_FAILED;
        }

    }
#else
    if (deviceState->getAppState() == APP_AVAILABLE){
        return sendToApp(events);
    }
    else{
        MCLOGD("*****%s***** APP is not connected",  __func__);
        DTLOG_INFO(0x003006, "touchKey, APP is not connected");
        return WFD_SERVICE_ERR_FAILED;
    }
#endif

}

android::status_t WFDInputListener::sendToHID(const TouchEvent_SpVec & events)/* __0x003007_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    if (firstHidPoint) {
        if (!m_hidTimer.isActive()) {
            m_hidTimer.start(WFD_TIME_50MS, true, this, &WFDInputListener::onHidTimer);
        }
        return WFD_SERVICE_ERR_OK;
    }
    HIDKEY pressed = HID_NULL;
    switch(events[0]->getState()) {
        case TOUCH_DOWN:
            pressed = HID_DOWN;
            break;
        case TOUCH_UP:
            pressed = HID_UP;
            break;
        case TOUCH_MOVE:
            pressed = HID_DOWN;
        default:
            break;
    }
    if (wfdManager == NULL) {
        DTLOG_PTRASSERT(wfdManager);
        return WFD_SERVICE_ERR_FAILED;
    }
    WFDServiceStub* sub = wfdManager->getServiceStub();
    if (sub == NULL) {
        return WFD_SERVICE_ERR_FAILED;
    }

    if (mHidKey.state == HID_UP && pressed == HID_UP) return WFD_SERVICE_ERR_OK;
    mHidKey.state = pressed;
    mHidKey.data[0] = events[0]->getX();
    mHidKey.data[1] = events[0]->getY();
    if (m_hidReleaseTimer.isActive()) m_hidReleaseTimer.stop();
    m_hidReleaseTimer.start(WFD_TIME_1SEC*WFD_SEC2MSEC, true, this, &WFDInputListener::onHidReleaseTimer);
    int ret = sub->wfdHIDPoint(static_cast<uint32_t>(pressed), static_cast<uint32_t>(events[0]->getX()), static_cast<uint32_t>(events[0]->getY()));
    if(BS_NO_ERROR != ret){
        DTLOG_RET(0x003007, "sendToHID:wfdHIDPoint failed  ret = %d",ret);
    }
    return WFD_SERVICE_ERR_OK;
}


android::status_t WFDInputListener::sendToApp(const TouchEvent_SpVec & events)/* __0x003008_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    multiKey keyInfo;
    keyInfo.state = TOUCH_IDLE;
    keyInfo.dataLen = 0;
    memset(&keyInfo.data, 0 ,4);
    bool sendFlag = false;
    hidSendFlag = false;
#ifdef WFD_APP
    if (m_timer.isActive()) m_timer.stop();
    m_timer.start(WFD_TIME_100MS, true, this, &WFDInputListener::onOneShotTimer);
#endif

    if (events.size() == 1){
        switch(events[0]->getState()) {
            case TOUCH_DOWN:
                keyInfo.state = TOUCH_DOWN;
                break;
            case TOUCH_UP:
                keyInfo.state = TOUCH_UP;
                break;
            case TOUCH_MOVE:
                keyInfo.state = TOUCH_MOVE;
                break;
            default:
                keyInfo.state = TOUCH_IDLE;
                break;
        }
        keyInfo.dataLen = 2;
        keyInfo.data[0]= events[0]->getX();
        keyInfo.data[1]= events[0]->getY();

    }
    else if (events.size() == 2){

        if (events[0]->getState() == TOUCH_UP || events[1]->getState() == TOUCH_UP){
            keyInfo.state = TOUCH_UP;
        }
        else if (events[0]->getState() == TOUCH_DOWN || events[1]->getState() == TOUCH_DOWN) {
            keyInfo.state = TOUCH_DOWN;
        }
        else if (events[0]->getState() == TOUCH_MOVE && events[1]->getState() == TOUCH_MOVE){
            keyInfo.state = TOUCH_MOVE;
        }
        else {
            keyInfo.state = TOUCH_IDLE;
        }
        keyInfo.dataLen = 4;
        keyInfo.data[0]= events[0]->getX();
        keyInfo.data[1]= events[0]->getY();
        keyInfo.data[2]= events[1]->getX();
        keyInfo.data[3]= events[1]->getY();
    }
    else {
        MCLOGD("*****%s*****, unsupport more than two touch point", __func__);
        DTLOG_INFO(0x003008, "*****%s*****, unsupport more than two touch point", __func__);
        return WFD_SERVICE_ERR_FAILED;
    }

    if ((keyInfo.state != mKey.state) && (keyInfo.state != TOUCH_IDLE)) {
        sendFlag = true;        
    }

    for (int i = 0; i < keyInfo.dataLen; i++) {
        if(abs(keyInfo.data[i]-mKey.data[i]) > FILTER_VALUE) {
            sendFlag = true;
            break;
        }
    }
    if (sendFlag != true) {
        MCLOGD("*****%s*****, filter, id = %d, x1= %x, y1=%x, x2=%x, y2=%x",__func__, mKey.state, mKey.data[0], mKey.data[1], mKey.data[2], mKey.data[3]);
        DTLOG_INFO(0x003008,"*****%s*****, filter, id = %d, x1= %x, y1=%x, x2=%x, y2=%x",__func__, mKey.state, mKey.data[0], mKey.data[1], mKey.data[2], mKey.data[3]);
    }
    else {
        mKey.state = keyInfo.state;
        mKey.dataLen = keyInfo.dataLen;
        memcpy(&mKey.data, &keyInfo.data, sizeof(keyInfo.data));
        MCLOGD("*****%s*****, transfer, id = %d, , dataLen = %d, x1= %x, y1=%x, x2=%x, y2=%x",__func__, mKey.state, mKey.dataLen, mKey.data[0], mKey.data[1], mKey.data[2], mKey.data[3]);
        sendToWFDStack(mKey);
    }
    return WFD_SERVICE_ERR_OK;
}

android::status_t WFDInputListener::sendToWFDStack(const multiKey &Key)/* __0x003009_DTFUNCID__ */
{
    MCLOGD("*****%s*****", __func__);
    if (wfdManager == NULL) 
    {
        DTLOG_PTRASSERT(wfdManager);
        return WFD_SERVICE_ERR_FAILED;
    }
    WFDLib* wfdStack = wfdManager->getWFDLib();
    if (wfdStack == NULL) {
        DTLOG_PTRASSERT(wfdStack);
        return WFD_SERVICE_ERR_FAILED;
    }
    wfd_uibc_data_t input;
    input.category = WFD_UIBC_CATEGORY_GENERIC;
    if (Key.state == TOUCH_UP) {
        input.generic.type = WFD_GITI_LEFT_MOUSE_UP;
    } else if (Key.state == TOUCH_DOWN) {
        input.generic.type = WFD_GITI_LEFT_MOUSE_DOWN;
    } else if (Key.state == TOUCH_MOVE) {
        input.generic.type = WFD_GITI_MOUSE_MOVE;
    }else {
        MCLOGD("*****%s*****, not support touch", __func__);
        DTLOG_INFO(0x003009,"*****%s*****, not support touch", __func__);
        return WFD_SERVICE_ERR_FAILED;
    }
    for (int j = 0; j<(Key.dataLen/2); j++) {
        wfd_uibc_point_t* uibcPoint = new wfd_uibc_point_t();
        uibcPoint->pointerId = static_cast<unsigned char>(j);
        if (j ==0) {
            uibcPoint->x = Key.data[0];
            uibcPoint->y = Key.data[1];
        }
        if (j ==1) {
            uibcPoint->x = Key.data[2];
            uibcPoint->y = Key.data[3];
        }
        input.generic.points.append(uibcPoint);
    }
    wfdStack->sendUIBCData(input);
    input.generic.points.clearData();
    return WFD_SERVICE_ERR_OK;
}

android::status_t WFDInputListener::addHidUpKey()/* __0x00300A_DTFUNCID__ */
{
    MCLOGD("*****func=%s*****, Line = %d", __func__, __LINE__);
    WFDServiceStub* sub = wfdManager->getServiceStub();
    if (sub == NULL) {
        DTLOG_PTRASSERT(sub);
        return WFD_SERVICE_ERR_FAILED;
    }
    mHidKey.state = HID_UP;
    if (m_hidReleaseTimer.isActive()) m_hidReleaseTimer.stop();
    m_hidReleaseTimer.start(WFD_TIME_1SEC*WFD_SEC2MSEC, true, this, &WFDInputListener::onHidReleaseTimer);
    int ret = sub->wfdHIDPoint(static_cast<uint32_t>(mHidKey.state), static_cast<uint32_t>(mHidKey.data[0]), static_cast<uint32_t>(mHidKey.data[1]));
    if(BS_NO_ERROR != ret){
        DTLOG_INFO(0x00300A, "addHidUpKey:wfdHIDPoint failed  ret = %d",ret);
    }
    return WFD_SERVICE_ERR_OK;
}

void WFDInputListener::onOneShotTimer(Timer* timer)/* __0x00300B_DTFUNCID__ */
{
    android::AutoMutex sync(mSyncObj);
    MCLOGD("*****func=%s*****, Line = %d", __func__, __LINE__);
    hidSendFlag = true;
}

void WFDInputListener::onHidTimer(Timer* timer)/* __0x00300C_DTFUNCID__ */
{
    android::AutoMutex sync(mSyncObj);
    MCLOGD("*****func=%s*****, Line = %d", __func__, __LINE__);
    firstHidPoint = false;
}

void WFDInputListener::onHidReleaseTimer(Timer *timer)/* __0x00300D_DTFUNCID__ */
{
    android::AutoMutex sync(mSyncObj);
    MCLOGD("*****func=%s*****, Line = %d", __func__, __LINE__);
    firstHidPoint = true;
}

}
