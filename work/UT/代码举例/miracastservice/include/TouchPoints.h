#ifndef __TOUCH_POINTS_H__
#define __TOUCH_POINTS_H__

#include <vector>
#include "servicebase/ServiceBaseGlobal.h"
#include "WFDServiceServiceDefines.h"

namespace goni {
class TouchPoints : public android::RefBase
{
public:

    TouchPoints():
        pointerId(),
        x(),
        y()
    {
    }
    const uint8_t& getPointerId()
    {
        return pointerId;
    }
    void setPointerId(const uint8_t& _pointerId)
    {
        pointerId = _pointerId;
    }
    const uint32_t& getX()
    {
        return x;
    }
    void setX(const uint32_t& _x)
    {
        x = _x;
    }
    const uint32_t& getY()
    {
        return y;
    }
    void setY(const uint32_t& _y)
    {
        y = _y;
    }
    void readFromParcel(const android::Parcel& data)
    {
        pointerId = data.readInt32();
        x = data.readInt32();
        y = data.readInt32();
    }
    void writeToParcel(android::Parcel& _data)
    {
        _data.writeInt32(pointerId);
        _data.writeInt32(x);
        _data.writeInt32(y);
    }
private:
    uint8_t pointerId;

    uint32_t x;

    uint32_t y;


};
typedef android::sp<TouchPoints> TouchPoints_Sp;
typedef std::vector<android::sp<TouchPoints> > TouchPoints_SpVec;

}
#endif