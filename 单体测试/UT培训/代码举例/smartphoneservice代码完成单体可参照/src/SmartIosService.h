#ifndef __SMARTIOSSERVICE_H__
#define __SMARTIOSSERVICE_H__

#include "servicebase/ServiceBase.h"
#include "binder/Parcel.h"

namespace goni {

class SmartIosServiceStub;
class SmartConnectManagerListener;
class ConnectManagerSub;
class SmartIosDiagServiceSub;
class DiagSub;
class SmartIosService : public ServiceBase
{
public:
    SmartIosService();
    ~SmartIosService();

    virtual void onStart();
    virtual void onStop();
    virtual void initialize();

private:
    SmartIosServiceStub* mStub;
    //SmartConnectManagerListener* mConnectMultiListner;
    SmartConnectManagerListener* multiListner;
    android::sp<ConnectManagerSub>  mConnSub;
    SmartIosDiagServiceSub* diagListen;
    android::sp<DiagSub> mDiagSub;


};
}

#endif
