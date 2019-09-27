#ifndef __SMT_DEVICE_INFO_H__
#define __SMT_DEVICE_INFO_H__

#include <vector>
#include "servicebase/ServiceBaseGlobal.h"
#include "SmartIosServiceServiceDefines.h"

namespace goni {
class SmtDeviceInfo : public android::RefBase
{
public:

    SmtDeviceInfo():
        reqType(),
        total(),
        index(),
        code(),
        pop(),
        popAndroid(),
        nameLen(),
        name()
    {
    }
    const SmtDevReqType& getReqType()
    {
        return reqType;
    }
    void setReqType(const SmtDevReqType& _reqType)
    {
        reqType = _reqType;
    }
    const uint32_t& getTotal()
    {
        return total;
    }
    void setTotal(const uint32_t& _total)
    {
        total = _total;
    }
    const uint32_t& getIndex()
    {
        return index;
    }
    void setIndex(const uint32_t& _index)
    {
        index = _index;
    }
    const uint32_t& getCode()
    {
        return code;
    }
    void setCode(const uint32_t& _code)
    {
        code = _code;
    }
    const SmtPopStatus& getPop()
    {
        return pop;
    }
    const SmtPopStatusAndroid& getPopAndorid()
    {
        return popAndroid;
    }
    void setPop(const SmtPopStatus& _pop)
    {
        pop = _pop;
    }
    void setPopAndroid(const SmtPopStatusAndroid& _pop)
    {
        popAndroid = _pop;
    }
    const uint32_t& getNameLen()
    {
        return nameLen;
    }
    void setNameLen(const uint32_t& _nameLen)
    {
        nameLen = _nameLen;
    }
    const android::String8& getName()
    {
        return name;
    }
    void setName(const android::String8& _name)
    {
        name = _name;
    }
    void readFromParcel(const android::Parcel& data)
    {
        reqType = static_cast<SmtDevReqType>(data.readInt32());
        total = data.readInt32();
        index = data.readInt32();
        code = data.readInt32();
        pop = static_cast<SmtPopStatus>(data.readInt32());
        nameLen = data.readInt32();
        name = data.readString8();
    }
    void readFromParcelAndorid(const android::Parcel& data)
    {
        reqType = static_cast<SmtDevReqType>(data.readInt32());
        total = data.readInt32();
        index = data.readInt32();
        code = data.readInt32();
        popAndroid = static_cast<SmtPopStatusAndroid>(data.readInt32());
        nameLen = data.readInt32();
        name = data.readString8();
    }
    void writeToParcel(android::Parcel& _data)
    {
        _data.writeInt32(static_cast<SmtDevReqType>(reqType));
        _data.writeInt32(total);
        _data.writeInt32(index);
        _data.writeInt32(code);
        _data.writeInt32(static_cast<SmtPopStatus>(pop));
        _data.writeInt32(nameLen);
        _data.writeString8(name);
    }
    void writeToParcelAndorid(android::Parcel& _data)
    {
        _data.writeInt32(static_cast<SmtDevReqType>(reqType));
        _data.writeInt32(total);
        _data.writeInt32(index);
        _data.writeInt32(code);
        _data.writeInt32(static_cast<SmtPopStatusAndroid>(popAndroid));
        _data.writeInt32(nameLen);
        _data.writeString8(name);
    }
private:
    SmtDevReqType reqType;

    uint32_t total;

    uint32_t index;

    uint32_t code;

    SmtPopStatus pop;
    
    SmtPopStatusAndroid popAndroid;

    uint32_t nameLen;

    android::String8 name;


};
typedef android::sp<SmtDeviceInfo> SmtDeviceInfo_Sp;
typedef std::vector<android::sp<SmtDeviceInfo> > SmtDeviceInfo_SpVec;

}
#endif