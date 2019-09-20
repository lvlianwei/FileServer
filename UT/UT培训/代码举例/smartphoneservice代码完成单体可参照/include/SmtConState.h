#ifndef __SMT_CON_STATE_H__
#define __SMT_CON_STATE_H__

#include <vector>
#include "servicebase/ServiceBaseGlobal.h"
#include "SmartIosServiceServiceDefines.h"

namespace goni {
class SmtConState : public android::RefBase
{
public:

    SmtConState():
        cState(),
        cStateAndroid(),
        index(),
        indexAndroid(),
        pop(),
        popAndroid(),
        isCarplaySupp(),
        isAAPSupp()
    {
    }
    const SmtConnectState& getCState()
    {
        return cState;
    }
    const SmtConnectState& getCStateAndroid()
    {
        return cStateAndroid;
    }
    void setCState(const SmtConnectState& _cState)
    {
        cState = _cState;
    }
    void setCStateAndroid(const SmtConnectState& _cState)
    {
        cStateAndroid = _cState;
    }
    const uint32_t& getIndex()
    {
        return index;
    }
    const uint32_t& getIndexAndroid()
    {
        return indexAndroid;
    }
    void setIndex(const uint32_t& _index)
    {
        index = _index;
    }
    void setIndexAndroid(const uint32_t& _index)
    {
        indexAndroid = _index;
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
    const bool& getIsCarplaySupp()
    {
        return isCarplaySupp;
    }
    const bool& getIsAAPSupp()
    {
        return isAAPSupp;
    }
    void setIsCarplaySupp(const bool& _isCarplaySupp)
    {
        isCarplaySupp = _isCarplaySupp;
    }
    void setIsAAPSupp(const bool& _isAAPSupp)
    {
        isAAPSupp = _isAAPSupp;
    }
    void readFromParcel(const android::Parcel& data)
    {
        cState = static_cast<SmtConnectState>(data.readInt32());
        index = data.readInt32();
        pop = static_cast<SmtPopStatus>(data.readInt32());
        isCarplaySupp = data.readInt32();
    }
    void readFromParcelAndorid(const android::Parcel& data)
    {
        cStateAndroid = static_cast<SmtConnectState>(data.readInt32());
        indexAndroid = data.readInt32();
        popAndroid = static_cast<SmtPopStatusAndroid>(data.readInt32());
        isAAPSupp = data.readInt32();
    }
    void writeToParcel(android::Parcel& _data)
    {
        _data.writeInt32(static_cast<SmtConnectState>(cState));
        _data.writeInt32(index);
        _data.writeInt32(static_cast<SmtPopStatus>(pop));
        _data.writeInt32(isCarplaySupp);
    }
    void writeToParcelAndorid(android::Parcel& _data)
    {
        _data.writeInt32(static_cast<SmtConnectState>(cStateAndroid));
        _data.writeInt32(indexAndroid);
        _data.writeInt32(static_cast<SmtPopStatusAndroid>(popAndroid));
        _data.writeInt32(isAAPSupp);
    }
private:
    SmtConnectState cState;
    SmtConnectState cStateAndroid;

    uint32_t index;
    uint32_t indexAndroid;

    SmtPopStatus pop;
    SmtPopStatusAndroid popAndroid;

    bool isCarplaySupp;
    bool isAAPSupp;


};
typedef android::sp<SmtConState> SmtConState_Sp;
typedef std::vector<android::sp<SmtConState> > SmtConState_SpVec;

}
#endif