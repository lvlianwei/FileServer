#include"Test_smtIosService.h"
#include "SmartIosDiagServiceSub.h"
#include "include/SmartIosServiceDefs.h"
#include "SmartIosSettingProxy.h"
#include "proxy/DiagProxyBase.h"
#include "include/SmartIosServiceDTLog.h"
#include "SmartIosMessage.h"
#include "include/SmartIosServiceDefs.h"
#include <string.h>
#include "SmtConState.h"
#include "SmtDeviceInfo.h"
#include "SmtPopState.h"

using testing::_;
using testing::Return;
using testing::AtLeast;

namespace goni {
    TimerManager* Test_smtIosService::manager = NULL;
    SmartIosService * Test_smtIosService::service = NULL;
    TEST_F(Test_smtIosService,onstart) {
        EXPECT_CALL(*(SingletonSmtIService::getInstance()),checkServiceDiedBefore(_)).WillOnce(Return(true));
        service->onStart();
        service->onStop();
        EXPECT_CALL(*(SingletonSmtIService::getInstance()),checkServiceDiedBefore(_)).WillOnce(Return(false));
        service->onStart();
        printf("###############smt ios service start##################\n");
        SingletonSmtIService::delInstance();
    }
    class Test_SmartIosDiagServiceSub:public testing::Test {
        public:
            static SmartIosDiagServiceSub *sub;
            static void SetUpTestCase() {
                sub = new SmartIosDiagServiceSub;
            }
            static void TearDownTestCase() {
                if(NULL != sub) {
                    delete sub;
                    sub = NULL;
                }
            }
    };
    SmartIosDiagServiceSub * Test_SmartIosDiagServiceSub::sub = NULL;
    TEST_F(Test_SmartIosDiagServiceSub,broadcastDiagOn) {
        const DIAG_MODE eMode =DIAG_MODE_NORMAL;
        EXPECT_EQ(0,sub -> broadcastDiagOn(eMode));
        const DIAG_MODE eMode1 =DIAG_MODE_SERVICE;
        EXPECT_EQ(0,sub -> broadcastDiagOn(eMode1));
        const DIAG_MODE eMode2 =DIAG_MODE_DEVELOP;
        EXPECT_EQ(0,sub -> broadcastDiagOn(eMode2));
        const DIAG_MODE eMode3 =DIAG_MODE_PANA;
        EXPECT_EQ(0,sub -> broadcastDiagOn(eMode3));
        const DIAG_MODE eMode4 =DIAG_MODE_HONDA;
        EXPECT_EQ(0,sub -> broadcastDiagOn(eMode4));
    }
    TEST_F(Test_SmartIosDiagServiceSub,broadcastDiagInit) {
        const DIAG_MODE eMode =DIAG_MODE_NORMAL;
        EXPECT_EQ(0,sub -> broadcastDiagInit());
    }
    class Test_SmartIosMessage:public testing::Test {
        public:
            static SmartIosMessage *msg;
            static SmartIosMessage *msg1;
            static void SetUpTestCase() {
                SmartIosMessage::DevInfoInd ind={0};
                memset(&ind,0,sizeof(ind));
                msg = new SmartIosMessage(ind);
                SmartIosMessage::SMART_EVENT_ID id=SmartIosMessage::SMT_POPSTATUS_IND_EVENT;
                msg1 = new SmartIosMessage(id);
            }
            static void TearDownTestCase() {
                if(NULL != msg) {
                    delete msg;
                    msg = NULL;
                }
                if(NULL != msg1) {
                    delete msg1;
                    msg1 = NULL;
                }
            }
    };
    SmartIosMessage *Test_SmartIosMessage::msg = NULL;
    SmartIosMessage *Test_SmartIosMessage::msg1 = NULL;
    TEST_F(Test_SmartIosMessage,getDevConStatusInd) {
        EXPECT_TRUE(NULL != msg -> getDevConStatusInd());
    }
    TEST_F(Test_SmartIosMessage,getDevInfoInd) {
        EXPECT_TRUE(NULL != msg -> getDevInfoInd());
    }
    TEST_F(Test_SmartIosMessage,getPopStatusInd) {
        EXPECT_TRUE(NULL != msg -> getPopStatusInd());
    }
    class Test_SmtConState:public testing::Test {
        public:
            static SmtConState *state;
            static void SetUpTestCase() {
                state = new SmtConState;
            }
            static void TearDownTestCase() {
                if(NULL != state) {
                    delete state;
                    state = NULL;
                }
            }
    };
    SmtConState * Test_SmtConState::state = NULL;

    TEST_F(Test_SmtConState,setCState) {
        const SmtConnectState _cState =SMT_CONNECTED;
        state -> setCState(_cState);
        EXPECT_TRUE(SMT_CONNECTED == state -> getCState());
        const SmtConnectState _cState1 =SMT_DISCONNECT;
        state -> setCState(_cState1);
        EXPECT_TRUE(SMT_DISCONNECT == state -> getCState());
    }
    TEST_F(Test_SmtConState,getPop) {

        const uint32_t _index=1;
        state -> setIndex(_index);
        EXPECT_TRUE(1 == state -> getIndex());
        const SmtPopStatus _pop = SMT_POP_INVALID;
        state->setPop(_pop);
        EXPECT_TRUE(SMT_POP_INVALID == state -> getPop());
        const bool bl=1;
        state->setIsCarplaySupp(bl);
        EXPECT_TRUE(state -> getIsCarplaySupp());
        state->setIsAAPSupp(bl);
        EXPECT_TRUE(state -> getIsCarplaySupp());
    }
    class Test_SmtDeviceInfo:public testing::Test {
        public:
            static SmtDeviceInfo *type;
            static void SetUpTestCase() {
                type = new SmtDeviceInfo;
            }
            static void TearDownTestCase() {
                if(NULL != type) {
                    delete type;
                    type = NULL;
                }
            }
    };
    SmtDeviceInfo * Test_SmtDeviceInfo::type = NULL;

    TEST_F(Test_SmtDeviceInfo,reqgetTotal) {
        type -> getTotal();

        type -> getCode();
        const uint32_t _index=1;
        type -> setIndex(_index);
        EXPECT_TRUE(1 == type -> getIndex());
        const SmtPopStatus _pop = SMT_POP_INVALID;
        type->setPop(_pop);
        EXPECT_TRUE(SMT_POP_INVALID == type -> getPop());
        const SmtPopStatusAndroid pop = SMT_ANDROID_AUTOAAP;
        type->setPopAndroid(pop);
        EXPECT_TRUE(SMT_ANDROID_AUTOAAP == type -> getPopAndorid());
        android::Parcel data;
        type->readFromParcelAndorid(data);
    }
    TEST_F(Test_SmtDeviceInfo,setReqType) {
        const SmtDevReqType _reqType=SMT_IOS_DEV_ALL_REQ;
        type -> setReqType(_reqType);
        EXPECT_TRUE(SMT_IOS_DEV_ALL_REQ == type -> getReqType());
        const SmtDevReqType _reqType1=SMT_IOS_DEV_SINGLE_REQ;
        type -> setReqType(_reqType1);
        EXPECT_TRUE(SMT_IOS_DEV_SINGLE_REQ == type -> getReqType());
    }
    TEST_F(Test_SmtDeviceInfo,setTotal) {
        const uint32_t _total=1;
        type -> setTotal(_total);
        EXPECT_EQ(1,type -> getTotal());
    }
    TEST_F(Test_SmtDeviceInfo,setCode) {
        const uint32_t _total=1;
        type -> setCode(_total);
        EXPECT_EQ(1,type -> getCode());
    }
    TEST_F(Test_SmtDeviceInfo,setNameLen) {
        const uint32_t _total=1;
        type -> setNameLen(_total);
        EXPECT_EQ(1,type -> getNameLen());
    }
    TEST_F(Test_SmtDeviceInfo,setName) {
        const android::String8 _name("adfha");
        type -> setName(_name);
        EXPECT_STREQ("adfha",type -> getName());
    }

    class Test_SmtPopState:public testing::Test {
        public:
            static SmtPopState *pop;
            static void SetUpTestCase() {
                pop = new SmtPopState;
            }
            static void TearDownTestCase() {
                if(NULL != pop) {
                    delete pop;
                    pop = NULL;
                }
            }
    };
    SmtPopState * Test_SmtPopState::pop = NULL;

    TEST_F(Test_SmtPopState,popsetSetType) {
        const SmtSetType _reqType=SMT_IOS_POPUP_SET;
        pop -> setSetType(_reqType);
        EXPECT_EQ(SMT_IOS_POPUP_SET,pop -> getSetType());
        const SmtSetType _reqType1=SMT_IOS_MANU_SET;
        pop -> setSetType(_reqType1);
        EXPECT_EQ(SMT_IOS_MANU_SET,pop -> getSetType());
    }
    TEST_F(Test_SmtPopState,popsetPop) {
        const SmtPopStatus _pop = SMT_POP_INVALID;
        pop->setPop(_pop);
        EXPECT_EQ(SMT_POP_INVALID,pop -> getPop());
    }
    TEST_F(Test_SmtPopState,popsetIndex) {
        const uint32_t _index=1;
        pop -> setIndex(_index);
        EXPECT_EQ(1,pop -> getIndex());
    }
    TEST_F(Test_SmtPopState,readFromParcelAndorid) {
        android::Parcel data;
        pop ->readFromParcelAndorid(data);
    }
}
