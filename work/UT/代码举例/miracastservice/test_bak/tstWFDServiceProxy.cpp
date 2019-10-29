#include "proxy/WFDServiceProxyBase.h"
#include "servicebase/ServiceBase.h"
#include "servicebase/ServiceProcess.h"
#include "sub/WFDServiceSub.h"
#include "WFDServiceDefs.h"

using namespace goni;

class tstWfdReplier : public IWFDServiceProxyReplier
{
    public:
    tstWfdReplier()
    {

    }
    
    virtual ~tstWfdReplier()
    {
    }
    virtual android::status_t wfdPowerStatus(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdSearchResultInd(const WFDDeviceInfo_Sp & deviceInfo)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdSearchFinishedInd(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdInvitationInd(const WFDDeviceInfo_Sp & deviceInfo)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdConnectResultInd(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdDisconnectInd(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdAppStatus(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdInvalidAppInd(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdCurrentAppChangeInd(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }

    virtual android::status_t wfdBtStatus(const uint32_t& bt, const uint32_t& hid)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    
    virtual android::status_t wfdGetGPSTimeInd(const uint32_t& err, const uint32_t& len, const std::vector<uint8_t>& time)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    
    virtual android::status_t wfdNaviVoiceInd(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }

    virtual android::status_t wfdSourceChangeCfm(const uint32_t& err, const uint32_t& currentMode)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdLocalDeviceInd(const uint16_t& nameLen, const std::vector<uint8_t>& name)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    virtual android::status_t wfdStartListenInd(const uint32_t& err)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }

    virtual android::status_t wfdMacAddr(const uint32_t& len, const std::vector<uint8_t>& mac)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }
    
    virtual android::status_t wfdP2pVersion(const uint32_t& len, const android::String8& version)
        {
        MCLOGD("*****%s*****", __func__);
        return 0;
        }

};

IWFDServiceProxyReplier* replier;

WFDServiceProxyBase* proxy;

class wfdTestService : public ServiceBase
{
public:
    wfdTestService()
    :ServiceBase("wfdTest")
    {
        MCLOGD("**********%s*******\n", __func__);
        mProxy = new WFDServiceProxyBase(new tstWfdReplier());
        instance = this;

        MCLOGD("**********%s*******\n", __func__);
    }

    ~wfdTestService()
    {
        delete mProxy;
    }

    void onStart()
    {
        MCLOGD("**********%s*******\n", __func__);
        ServiceBase::onStart();
        mSub = new goni::WFDServiceSub(new wfdTestSub(), this);

        int isQuit = 0;
        char input[3] = { 0 };
        while (!isQuit)
        {
            memset(input, 0x00, sizeof(input));
            greetings();
            MyGetLine(input, 2);
            int choice = checkInput(input);
            switch(choice)
            {
            case 1:
                MCLOGD("send wfd power on command \r\n");
                mProxy->wfd_powerOn();
                break;
            case 2:
                mProxy->wfd_powerOff();
                break;
            case 3:
                break;
            case 4:
            {
                MCLOGD("pls input the source change mode 0=off, 1=on \r\n");
                memset(input, 0x00, sizeof(input));
                MyGetLine(input, 2);
                int select = checkInput(input);
                mProxy->wfd_sourceChange((uint8_t)select);
                break;
            }
            case 5:
            {
                MCLOGD("pls input the source change mode 0=no_work, 1=mirror,2=APP, other = nowork \r\n");
                memset(input, 0x00, sizeof(input));
                MyGetLine(input, 2);
                int select = checkInput(input);
                mProxy->wfd_mirrorMode((MirrorMode)select);
                break;
            }
            case 6:
            {
                MCLOGD("pls input the screen mode 0=Horizontal, 1=Screen_Vertial \r\n");
                memset(input, 0x00, sizeof(input));
                MyGetLine(input, 2);
                int select = checkInput(input);
                mProxy->wfd_SreenMode((ScreenMode)select);
                break;
            }
            case 7:
                mProxy->wfd_getGPSTime();
                break;
            case 8:
            {
                memset(input, 0x00, sizeof(input));
                MyGetLine(input, 2);
                int select = checkInput(input);
                mProxy->wfd_sendHardKey((HardKey)select);
                break;
            }
            case 9:
                mProxy->wfd_disconnect();
                break;
            case 10:
                mProxy->wfd_play();
                break;
            case 11:
                mProxy->wfd_pause();
            default:
                break;
            }
        }
    }
    public:
        void greetings();
        void MyGetLine(char *p, int len);
        int checkInput(char *p);

    private:
    goni::WFDServiceProxyBase* mProxy;
    goni::WFDServiceSub* mSub;

    static wfdTestService* instance;

    private:
        class wfdTestSub:public goni::IWFDServiceSub
        {
            public:
             android::status_t wfdPowerStatus(const uint32_t& err)
                {
                    MCLOGD("*****%s*****err = %x", __func__, err);
                    return 0;
                }
             
            android::status_t wfdInvitationInd(const WFDDeviceInfo_Sp& deviceInfo)
                {
                    MCLOGD("*****%s*****", __func__);
                    return 0;
                }
            
            android::status_t wfdConnectResultInd(const uint32_t& err)
                {
                    MCLOGD("*****%s*****, err = %x", __func__, err);
                    return 0;
                }
            
            android::status_t wfdDisconnectInd(const uint32_t& err)
                {
                    MCLOGD("*****%s*****", __func__);
                    return 0;
                }
            
            android::status_t wfdBtStatus(const uint32_t& bt, const uint32_t& hid)
                {
                    MCLOGD("*****%s*****, bt = %d, hid = %d", __func__, bt, hid);
                    return 0;
                }
            
            android::status_t wfdStartListenInd(const uint32_t& err)
                {
                    MCLOGD("*****%s*****, err = %x", __func__, err);
                    return 0;
                }
            
            android::status_t wfdMacAddr(const uint32_t& len, const uint64_t& mac)
                {
                    MCLOGD("*****%s*****", __func__);
                    return 0;
                }
            
            android::status_t wfdP2pVersion(const uint32_t& len, const android::String8& version)
                {
                    MCLOGD("*****%s*****", __func__);
                    return 0;
                }
            
            // send to Bt	
             android::status_t wfdRemotePixesInfo(const wfdSvcState& wfdState, const uint32_t& width, const uint32_t& height)
                {
                    MCLOGD("*****%s*****", __func__);
                    return 0;
                }
            
             android::status_t wfdRemoteSrceenChange(const bool& locked, const ScreenMode& mode)
                {
                    MCLOGD("*****%s*****, locked = %d, mode = %d", __func__, locked, mode);
                    return 0;
                }
             
             android::status_t wfdHIDPoint(const uint32_t& pressed, const uint32_t& width, const uint32_t& height)
                {
                    MCLOGD("*****%s*****, pressed = %d, width = %d, height = %d", __func__, pressed, width, height);
                    return 0;
                }
             
             android::status_t wfdHardkey(const HardKey& key)
                {
                    MCLOGD("*****%s*****, key = %d", __func__, key);
                    return 0;
                }
        };
};


void wfdTestService::greetings()
{
    printf("----------------------------\r\n");
    printf(" 1. Power On\r\n");
    printf(" 2. Power off\r\n");
    printf(" 3. listen\r\n");
    printf(" 4. Source change\r\n");
    printf(" 5. mirror mode \r\n");
    printf(" 6. screen change\r\n");
    printf(" 7. get GPS time \r\n");
    printf(" 8. send Hard Key\r\n");
    printf(" 9. disconnect \r\n");
    printf(" 10. send play\r\n");
    printf(" 11. send pause\r\n");
    printf("----------------------------\r\n");
}

void wfdTestService::MyGetLine(char *p, int len)
{
    if (NULL == p) {
        return;
    }
    int cnt = 0;
    while (1) {
        char c = getchar();
        if (c == '\n') {
            break;
        }
        else {
            if (cnt < len) {
                p[cnt] = c;
                cnt++;
            }
            else {
                printf("Input too long \n");
                p[0] = '\0';
                while (1) {
                    c = getchar();
                    if (c == '\n' || c == EOF) {
                        break;
                    }
                }
                break;
            }
        }

    }
}


int wfdTestService::checkInput(char *p)
{
    if (p == NULL) {
        return 0;
    }
    else {
        unsigned int i;
        for (i = 0; i < strlen(p); i++) {
            if (p[i] == '\0') {
                break;
            }
            if (p[i] < '0' || p[i] > '9') {
                return -1;
            }
            if (p[i] >= '0' && p[i] <= '9') {
                continue;
            }

        }
        switch (strlen(p)) {
        case 3:
            return ((p[0]-'0')*100+(p[1]-'0')*10+p[2]-'0');
        case 2:
            return ((p[0]-'0')*10+(p[1]-'0'));
        case 1:
            return (p[0]-'0');
        default:
            return -1;
        }
    }

}

void gotoCmd(int cmd)
{
    switch (cmd) {
    case 1:
        printf("send wfd power on command \r\n");
        //char* name = "TST_WFD";
        proxy->wfd_powerOn();
        break;
    case 2:
        proxy->wfd_powerOff();
        break;
    case 3:
        break;
    default:
        break;
    }
}
wfdTestService* wfdTestService::instance = NULL;

int main(int argc, char *argv[])
{
    printf("enter main \r\n");
    UNUSED(argc);
    UNUSED(argv);

    ServiceProcess process("testWfdService");
    wfdTestService s;
    process.addService(&s);
    process.initialize();
    process.exec();
    process.finalize();

    return 0;
#if 0
    replier = new tstWfdReplier();
    proxy = new WFDServiceProxyBase(replier);
    char input[3] = { 0 };
    while (1) {
        memset(input, 0x00, sizeof(input));
        greetings();
        MyGetLine(input, 2);
        int choice = checkInput(input);
        if (choice >= 1 && choice <= 3) {
            gotoCmd(choice);
        }
    }
#endif

}
