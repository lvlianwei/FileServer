#ifndef __WFDREMOTE_DEVICE_INFO_H__
#define __WFDREMOTE_DEVICE_INFO_H__

#include <vector>
#include "servicebase/ServiceBaseGlobal.h"
#include "WFDServiceServiceDefines.h"

namespace goni {
class WFDRemoteDeviceInfo : public android::RefBase
{
public:

    WFDRemoteDeviceInfo():
        svcState(),
        appState(),
        width(),
        height(),
        locked(),
        mode()
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
    const uint32_t& getWidth()
    {
        return width;
    }
    void setWidth(const uint32_t& _width)
    {
        width = _width;
    }
    const uint32_t& getHeight()
    {
        return height;
    }
    void setHeight(const uint32_t& _height)
    {
        height = _height;
    }
    const bool& getLocked()
    {
        return locked;
    }
    void setLocked(const bool& _locked)
    {
        locked = _locked;
    }
    const ScreenMode& getMode()
    {
        return mode;
    }
    void setMode(const ScreenMode& _mode)
    {
        mode = _mode;
    }
    void readFromParcel(const android::Parcel& data)
    {
        svcState = static_cast<wfdSvcState>(data.readInt32());
        appState = static_cast<AppState>(data.readInt32());
        width = data.readInt32();
        height = data.readInt32();
        locked = data.readInt32();
        mode = static_cast<ScreenMode>(data.readInt32());
    }
    void writeToParcel(android::Parcel& _data)
    {
        _data.writeInt32(static_cast<wfdSvcState>(svcState));
        _data.writeInt32(static_cast<AppState>(appState));
        _data.writeInt32(width);
        _data.writeInt32(height);
        _data.writeInt32(locked);
        _data.writeInt32(static_cast<ScreenMode>(mode));
    }
private:
    wfdSvcState svcState;

    AppState appState;

    uint32_t width;

    uint32_t height;

    bool locked;

    ScreenMode mode;


};
typedef android::sp<WFDRemoteDeviceInfo> WFDRemoteDeviceInfo_Sp;
typedef std::vector<android::sp<WFDRemoteDeviceInfo> > WFDRemoteDeviceInfo_SpVec;

}
#endif