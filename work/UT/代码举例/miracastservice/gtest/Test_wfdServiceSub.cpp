#include<gtest/gtest.h>
#include "sub/WFDServiceSub.h"
#include "servicebase/ServiceBase.h"
namespace goni {
    class Test_wfdServiceSub:public testing::Test {
        protected:
            static WFDServiceSub *sub;
            static void SetUpTestCase() {
                sub = new WFDServiceSub(new IWFDServiceSub,new ServiceBase("base"));
            }
            static void tearDownTestCase() {
                if(NULL != sub) {
                    delete sub;
                    sub = NULL;
                }
            }
    };
    WFDServiceSub * Test_wfdServiceSub::sub = NULL;
    TEST_F(Test_wfdServiceSub,onMulticast) {
        unsigned int code;
        android::Parcel data;
        code = WFDServiceSub::MULTICAST_WFD_APP_STATUS;
        data.writeInt32(0);
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_POWER_STATUS;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_INVITATION_IND;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_CONNECT_RESULT_IND;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_DISCONNECT_IND;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_BT_STATUS;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_START_LISTEN_IND;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_MAC_ADDR;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_P2P_VERSION;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_REMOTE_PIXES_INFO;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_REMOTE_SRCEEN_CHANGE;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_HIDPOINT;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_HARDKEY;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_GET_GPSTIME_IND;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_MODE_CHANGE_CFM;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_RECEIVER_ID;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_APP_DESK_IND;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_MODE_CHANGE_REQ;
        sub->onMulticast(code,data);
        code = WFDServiceSub::MULTICAST_WFD_LINK_QUILTY_IND;
        sub->onMulticast(code,data);
    }
}
