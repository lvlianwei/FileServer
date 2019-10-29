#ifndef __WIFI_ADDR_ST_H__
#define __WIFI_ADDR_ST_H__

#include <vector>
#include "servicebase/ServiceBaseGlobal.h"
#include "WFDServiceServiceDefines.h"

namespace goni {
class WifiAddrST : public android::RefBase
{
public:

    WifiAddrST():
        addr()
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
    void readFromParcel(const android::Parcel& data)
    {
        addr = data.readInt64();
    }
    void writeToParcel(android::Parcel& _data)
    {
        _data.writeInt64(addr);
    }
private:
    uint64_t addr;


};
typedef android::sp<WifiAddrST> WifiAddrST_Sp;
typedef std::vector<android::sp<WifiAddrST> > WifiAddrST_SpVec;

}
#endif