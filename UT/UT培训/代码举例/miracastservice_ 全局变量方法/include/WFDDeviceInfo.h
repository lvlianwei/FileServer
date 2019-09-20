#ifndef __WFDDEVICE_INFO_H__
#define __WFDDEVICE_INFO_H__

#include <vector>
#include "servicebase/ServiceBaseGlobal.h"
#include "WFDServiceServiceDefines.h"

namespace goni {
class WFDDeviceInfo : public android::RefBase
{
public:

    WFDDeviceInfo():
        addr(),
        nameLen(),
        deviceName()
    {
    }
    const uint64_t& getAddr()
    {
        return addr;
    }
    void setAddr(const uint64_t& _addr)
    {
        addr = _addr;
    }
    const uint16_t& getNameLen()
    {
        return nameLen;
    }
    void setNameLen(const uint16_t& _nameLen)
    {
        nameLen = _nameLen;
    }
    const android::String8& getDeviceName()
    {
        return deviceName;
    }
    void setDeviceName(const android::String8& _deviceName)
    {
        deviceName = _deviceName;
    }
    void readFromParcel(const android::Parcel& data)
    {
        addr = data.readInt64();
        nameLen = data.readInt32();
        deviceName = data.readString8();
    }
    void writeToParcel(android::Parcel& _data)
    {
        _data.writeInt64(addr);
        _data.writeInt32(nameLen);
        _data.writeString8(deviceName);
    }
private:
    uint64_t addr;

    uint16_t nameLen;

    android::String8 deviceName;


};
typedef android::sp<WFDDeviceInfo> WFDDeviceInfo_Sp;
typedef std::vector<android::sp<WFDDeviceInfo> > WFDDeviceInfo_SpVec;

}
#endif