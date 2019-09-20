#ifndef __SMT_POP_STATE_H__
#define __SMT_POP_STATE_H__

#include <vector>
#include "servicebase/ServiceBaseGlobal.h"
#include "SmartIosServiceServiceDefines.h"

namespace goni {
class SmtPopState : public android::RefBase
{
public:

    SmtPopState():
        setType(),
        index(),
        pop(),
        popAndroid()
    {
    }
    const SmtSetType& getSetType()
    {
        return setType;
    }
    void setSetType(const SmtSetType& _setType)
    {
        setType = _setType;
    }
    const uint32_t& getIndex()
    {
        return index;
    }
    void setIndex(const uint32_t& _index)
    {
        index = _index;
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
    void readFromParcel(const android::Parcel& data)
    {
        setType = static_cast<SmtSetType>(data.readInt32());
        index = data.readInt32();
        pop = static_cast<SmtPopStatus>(data.readInt32());
    }
    void readFromParcelAndorid(const android::Parcel& data)
    {
        setType = static_cast<SmtSetType>(data.readInt32());
        index = data.readInt32();
        popAndroid = static_cast<SmtPopStatusAndroid>(data.readInt32());
    }
    void writeToParcel(android::Parcel& _data)
    {
        _data.writeInt32(static_cast<SmtSetType>(setType));
        _data.writeInt32(index);
        _data.writeInt32(static_cast<SmtPopStatus>(pop));
    }
    void writeToParcelAndorid(android::Parcel& _data)
    {
        _data.writeInt32(static_cast<SmtSetType>(setType));
        _data.writeInt32(index);
        _data.writeInt32(static_cast<SmtPopStatusAndroid>(popAndroid));
    }
    
private:
    SmtSetType setType;

    uint32_t index;

    SmtPopStatus pop;
    SmtPopStatusAndroid popAndroid;


};
typedef android::sp<SmtPopState> SmtPopState_Sp;
typedef std::vector<android::sp<SmtPopState> > SmtPopState_SpVec;

}
#endif