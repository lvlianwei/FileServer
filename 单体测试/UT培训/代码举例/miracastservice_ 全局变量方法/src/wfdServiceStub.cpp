#include "wfdServiceStub.h"
#include "wfdService.h"
#include "WFDServiceDefs.h"
#include "stub/WFDServiceReplier.h"
#include "WFDServiceServiceDefines.h"
#include "WFDServiceManager.h"

namespace goni {

WFDServiceStub* stub;

WFDServiceStub::WFDServiceStub(wfdService* owner)
    : WFDServiceStubBase(owner)
{
    MCLOGD("WFDServiceStub Construct");
    stub = this;
    m_replier = new WFDServiceReplier(owner);
    m_manager = new WFDServiceManager(this, m_replier);
}

WFDServiceStub::~WFDServiceStub()
{
    MCLOGD("WFDServiceStub Destruct");
    if (m_manager != NULL) delete m_manager;
    if (m_replier != NULL) delete m_replier;
}


android::status_t WFDServiceStub::wfdStateSync(WFDDeviceState_Sp& deviceState)
{
    if (m_manager != NULL) {
        m_manager->wfdStateSync(deviceState);
    }
    return 0;
}

android::status_t WFDServiceStub:: wfdGetRemoteInfo(WFDRemoteDeviceInfo_Sp& remoteInfo)
{
    if (m_manager != NULL) {
        m_manager->wfdGetRemoteInfo(remoteInfo);
    }
    return 0;
}

android::status_t WFDServiceStub::wfdGetLocalDevice(uint16_t& nameLen, uint8_t& name)
{
    return 0;
}


android::status_t WFDServiceStub::wfd_powerOn(SenderId id)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {
        m_manager->wfd_powerOn();
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_powerOff(SenderId id)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {
        m_manager->wfd_powerOff();
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_sourceChange(SenderId id, const uint8_t& mode)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {
        m_manager->wfd_sourceChange(id, mode);
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_mirrorMode(SenderId id, const MirrorMode& mode)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {
        m_manager->wfd_mirrorMode(id, mode);
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_SreenMode(SenderId id, const ScreenMode& mode)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {
        m_manager->wfd_SreenMode(id, mode);
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_getGPSTime(SenderId id)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {
        m_manager->wfd_getGPSTime(id);
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_sendHardKey(SenderId id, const HardKey& key)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {        
        m_manager->wfd_sendHardKey(id, key);
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_startSearch(SenderId id)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {

    }
    return 0;
}

android::status_t WFDServiceStub::wfd_stopSearch(SenderId id)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {

    }
    return 0;
}

android::status_t WFDServiceStub::wfd_acceptInvitation(SenderId id, const bool& accpet)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {
        m_manager->wfd_acceptInvitation(id, accpet, 0);
    }

    return 0;
}

android::status_t WFDServiceStub::wfd_disconnect(SenderId id)
{
    MCLOGD("****%s****", __func__);
    if (m_manager != NULL) {
        m_manager->wfd_disconnect(id);
    }

    return 0;
}

android::status_t WFDServiceStub::wfd_enableWfd(SenderId id)
{
    MCLOGD("****%s****%d", __func__, __LINE__);
    if (m_manager != NULL) {
        m_manager->onCarLifeOrCarPlayExtract();
    }
    return 0;
}


android::status_t WFDServiceStub::wfd_disableWfd(SenderId id)
{
    MCLOGD("****%s****%d", __func__, __LINE__);
    if (m_manager != NULL) {
        m_manager->onCarLifeOrCarPlayInsert();
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_play(SenderId id)
{
    MCLOGD("****%s****%d", __func__, __LINE__);
    if (m_manager != NULL) {
        m_manager->wfd_play();
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_pause(SenderId id)
{
    MCLOGD("****%s****%d", __func__, __LINE__);
    if (m_manager != NULL) {
        m_manager->wfd_pause();
    }
    return 0;
}

android::status_t WFDServiceStub::wfd_sendUIBCData(SenderId id, const TouchType& type, const TouchPoints_SpVec & points)
{
    MCLOGD("****%s****", __func__);
    return 0;
}

android::status_t WFDServiceStub::onMultiListen(uint8_t opcode, void* msg)
{
    MCLOGD("*****%s*****", __func__);
    if (m_manager != NULL) {
        m_manager->onMsgReceived(opcode, msg);
        }
    return 0;
}

void WFDServiceStub::initialize()
{
    MCLOGD("*****%s*****", __func__);
    if (m_manager != NULL) {
        m_manager->initialize();
        }
}


}
