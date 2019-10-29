#ifndef __WFDSERVICE_H__
#define __WFDSERVICE_H__

#include "servicebase/ServiceBase.h"
#include "binder/Parcel.h"
#include "CarplayServiceSub.h"
#include "CarLifeServiceSub.h"

namespace goni {

class WFDServiceStub;
class WFDMultiListener;
class wifiSub;
class BtSub;
//class media::CarplayServiceSub;
//class CarLifeServiceSub;

class wfdService : public ServiceBase
{
public:
    wfdService();
    ~wfdService();

    virtual void onStart();
    virtual void onStop();

private:
    WFDServiceStub* mStub;
    android::sp<WFDMultiListener> mMultiListener;
    android::sp<wifiSub> mWifiSub;
    android::sp<BtSub> mBtSub;
    android::sp<media::CarplayServiceSub> mCarPlaySub;
    android::sp<CarLifeServiceSub> mCarLifeSub;
};
}

#endif
