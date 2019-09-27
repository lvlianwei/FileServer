#include "servicebase/Message.h"

namespace goni {

typedef enum
{
// p2p multi
MSG_P2P_POWER = 0x01,
MSG_P2P_CONNECT,
MSG_P2P_IP,
MSG_P2P_SIG,
MSG_P2P_LISTEN,
MS_BT_CONNECT,
MS_BT_DISCONNECT,
MSG_STA_IP,

MS_CARLIFE_CARPLAY_INSERT,
MS_CARLIFE_CARPLAY_EXTRACT
}WFD_MSG_IND;

typedef enum 
{
    MN_EVT_POWERON_CMD = 1,
    MN_EVT_POWEROFF_CMD,
    MN_EVT_SOURCE_CHANGE,
    MN_EVT_MIRROR_MODE,
    MN_EVT_SCREEN_MODE,
    MN_EVT_START_LISTEN,
    MN_EVT_STOP_LISTEN,
    MN_EVT_ADD_TAG,
    MN_EVT_START_SEARCH,
    MN_EVT_STOP_SEARCH,
    MN_EVT_ACCEPT_INVITATION,
    MN_EVT_DISCONNECT,
    MN_EVT_GET_P2P_SATE,

    MN_EVT_WFD_START,
    MN_EVT_WFD_START_MDNS,
    MN_EVT_WFD_DISCONECT,
    MN_EVT_WFD_PLAY,
    MN_EVT_WFD_PAUSE,
    MN_EVT_WFD_IDR,

    MN_EVT_WFD_SWITCH_REQ,
    MN_EVT_WFD_SWITCH_CMP,

    MN_EVT_WFD_SWITCH_SUCCESS,

    //APP
    MN_EVT_APP_GPSTIME,
    MN_EVT_APP_HARDKEY,
    MN_EVT_MULTI_MSG
}WFD_EVT_ID;

class WFDServiceMsg:public Message
{
public:
    WFDServiceMsg(WFD_EVT_ID id)
    :mId(id)
    , mAccept(false)
    , mPort(0)
    , mDevIP(0)
    , mLocalIP(0)
    , mLocalPort(0)
    , mString("")
    , mMode(0)
    , mParam(0)
    , macAddr(0)
    , mU64Param(0)
    , mProtocl(0)
    {}
    virtual ~WFDServiceMsg(){}

    WFD_EVT_ID funcId(){return mId;}
    void setAccpet(bool accept)
        {
        mAccept = accept;
        }
    void setRemotePort(const uint16_t port) {mPort = port;}
    void setRemoteIP(const uint32_t ip) {mDevIP = ip;}
    void setLocalIP(const uint32_t ip) {mLocalIP = ip;}
    void setLocalPort(const uint32_t port) {mLocalPort = port;}
    void setString(std::string& str) {mString = str;}
    void setMode(uint16_t mode) {mMode = mode;}
    void setInt32Parameter(const uint32_t param){mParam = param;}
    void setmacAddr(const uint64_t mac) {macAddr = mac;}
    void setUint16Value(const uint16_t& value) {mValue = value;}
    void setU64Parameter(const uint64_t param) {mU64Param = param;}
    void setTransProtocl(const int32_t protocl) {mProtocl = protocl;}

    bool getAccept(){return mAccept;}
    uint32_t getRemotePort(){return mPort;}
    uint32_t getRemoteIp(){return mDevIP;}
    uint32_t getLocalIP(){return mLocalIP;}
    uint32_t getLocalPort(){return mLocalPort;}
    std::string& getString(){return mString;}
    uint16_t getMode(){return mMode;}
    uint32_t getInt32Parameter(){return mParam;}
    uint64_t getmacAddr() {return macAddr;}
    uint16_t getUint16Value() {return mValue;}
    uint64_t getU64Parameter() {return mU64Param;}
    int32_t getProtocl() {return mProtocl;}



private:
    WFDServiceMsg(const WFDServiceMsg&);
    WFDServiceMsg& operator=(const WFDServiceMsg&);

private:
    WFD_EVT_ID     mId;
    bool mAccept;
    uint16_t mPort;
    uint32_t mDevIP;
    uint32_t mLocalIP;
    uint32_t mLocalPort;
    std::string mString;
    uint16_t mMode;
    uint32_t mParam;
    uint64_t macAddr;
    uint16_t mValue;
    uint64_t mU64Param;
    int32_t mProtocl;
    
  
};
}
