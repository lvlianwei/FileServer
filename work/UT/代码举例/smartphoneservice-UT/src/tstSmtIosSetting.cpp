#include "include/SmartIosServiceDefs.h""
#include"SmartIosSettingProxy.h"
using namespace goni;
using namespace android;
#define SmartIosSettingProxyInst SmartIosSettingProxy::getInstance()
#define serinum1 "1111111111111111111"
#define serinum2 "2222222222222222222"
#define serinum3 "3333333333333333333"
#define serinum4 "4444444444444444444"
#define serinum5 "5555555555555555555"
#define serinum6 "6666666666666666666"
typedef unsigned char uint8_t;
int main() {
    uint8_t popStatus;
    int s1Index = SmartIosSettingProxyInst->iapDeviceInsert(serinum1,&popStatus);
    SMTLOGD("s1Index = %d\n",s1Index);
    int s2Index = SmartIosSettingProxyInst->iapDeviceInsert(serinum2,&popStatus);
    SMTLOGD("s2Index = %d\n",s2Index);
#if 0
    int s3Index = SmartIosSettingProxyInst->iapDeviceInsert(serinum3,&popStatus);
    SMTLOGD("s3Index = %d\n",s3Index);
    int s4Index = SmartIosSettingProxyInst->iapDeviceInsert(serinum4,&popStatus);
    SMTLOGD("s4Index = %d\n",s4Index);
    int s5Index = SmartIosSettingProxyInst->iapDeviceInsert(serinum5,&popStatus);
    SMTLOGD("s5Index = %d\n",s5Index);
    int s6Index = SmartIosSettingProxyInst->iapDeviceInsert(serinum6,&popStatus);
    SMTLOGD("s6Index = %d\n",s6Index);
#endif
    SmtSetType setType = SMT_IOS_POPUP_SET;
    SmtPopStatus status = SMT_AUTOCARPLAY;
    SmartIosSettingProxyInst->setPopStatusReq(setType,s1Index,status);
    SmartIosSettingProxyInst->setPopStatusReq(setType,s2Index,status);
#if 0
    SmartIosSettingProxyInst->setPopStatusReq(setType,s3Index,status);
    SmartIosSettingProxyInst->setPopStatusReq(setType,s4Index,status);
    SmartIosSettingProxyInst->setPopStatusReq(setType,s5Index,status);
#endif
    return 0;
}
