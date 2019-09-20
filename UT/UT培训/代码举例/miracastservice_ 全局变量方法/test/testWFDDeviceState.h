#ifndef __WFDDEVICE_STATE_H__
#define __WFDDEVICE_STATE_H__

#include <vector>
#include "servicebase/ServiceBaseGlobal.h"
#include "WFDServiceServiceDefines.h"

namespace goni {
class WFDDeviceState : public android::RefBase
{
public:

    WFDDeviceState():
        svcState(),
        appState(),
        bt(),
        hid(),
        sourceState()
    {
    }
    const wfdSvcState& getSvcState()
    {
        return svcState;
    }
    void setSvcState(const wfdSvcState& _svcState)
    {
        svcState = _svcState;
    }
    const AppState& getAppState()
    {
        return appState;
    }
    void setAppState(const AppState& _appState)
    {
        appState = _appState;
    }
    const uint32_t& getBt()
    {
        return bt;
    }
    void setBt(const uint32_t& _bt)
    {
        bt = _bt;
    }
    const uint32_t& getHid()
    {
        return hid;
    }
    void setHid(const uint32_t& _hid)
    {
        hid = _hid;
    }
    const uint16_t& getSourceState()
    {
        return sourceState;
    }
    void setSourceState(const uint16_t& _sourceState)
    {
        sourceState = _sourceState;
    }
    void readFromParcel(const android::Parcel& data)
    {
        svcState = static_cast<wfdSvcState>(data.readInt32());
        appState = static_cast<AppState>(data.readInt32());
        bt = data.readInt32();
        hid = data.readInt32();
        sourceState = data.readInt32();
    }
    void writeToParcel(android::Parcel& _data)
    {
        _data.writeInt32(static_cast<wfdSvcState>(svcState));
        _data.writeInt32(static_cast<AppState>(appState));
        _data.writeInt32(bt);
        _data.writeInt32(hid);
        _data.writeInt32(sourceState);
    }
private:
    wfdSvcState svcState;

    AppState appState;

    uint32_t bt;

    uint32_t hid;

    uint16_t sourceState;


};
typedef android::sp<WFDDeviceState> WFDDeviceState_Sp;
typedef std::vector<android::sp<WFDDeviceState> > WFDDeviceState_SpVec;

}
#endif