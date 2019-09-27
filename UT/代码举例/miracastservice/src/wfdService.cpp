#include "wfdService.h"
#include "wfdServiceStub.h"
#include "WFDServiceMultiListen.h"
#include "wifiSub.h"
#include "BtSub.h"


namespace goni {

wfdService::wfdService()   /* __0x001000_DTFUNCID__ */
    : ServiceBase("WFDService")
    , mStub(NULL)
    , mMultiListener(NULL)
    , mWifiSub(NULL)
    , mBtSub(NULL)
    , mCarPlaySub(NULL)
    , mCarLifeSub(NULL)
{
}

wfdService::~wfdService()   /* __0x001001_DTFUNCID__ */
{
}

void wfdService::onStart()   /* __0x001002_DTFUNCID__ */
{
    mStub = new WFDServiceStub(this);
    registerStub(mStub);
    mMultiListener = new WFDMultiListener(mStub);
    mWifiSub = new wifiSub(mMultiListener.get(), this);
    mBtSub = new BtSub(mMultiListener.get(), this);
    mCarPlaySub = new media::CarplayServiceSub(mMultiListener.get(), this);
    mCarLifeSub = new CarLifeServiceSub(mMultiListener.get(), this);
    ServiceBase::onStart();
    mStub->initialize();
}

void wfdService::onStop()   /* __0x001003_DTFUNCID__ */
{
    registerStub(NULL);
    mCarLifeSub = NULL;
    mCarPlaySub = NULL;
    mBtSub = NULL;
    mWifiSub = NULL;
    mMultiListener = NULL;
    if (mStub != NULL) delete mStub;
    ServiceBase::onStop();
}

}
