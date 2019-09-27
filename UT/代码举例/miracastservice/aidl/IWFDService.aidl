enum WFD_SVC_ERROR_CODE
{
	WFD_SVC_SUCCESS,
	WFD_SVC_FAILED,
	WFD_SVC_INVALID_PARAM,
	WFD_SVC_ILLAGE_STATUS,
	WFD_SVC_OPERATION_ERROR,
	WFD_SVC_TIMEOUT_ERROR
};

enum wfdSvcState
{
	WFD_POWER_OFF,
	WFD_POWER_ON,
	WFD_LISTENING,
	WFD_CONNECTING,
	WFD_CONNECTED,
	WFD_STATE_INVALID
};
enum WFD_CONNETED_STATE
{
	WFD_CONNECTED_FAILED,
	WFD_CONNECTED_SUCCESS
};

// touch type
enum TouchType {
	TouchType_Press,     /**< Touch/Mouse down */
	TouchType_Release,   /**< Touch/Mouse up */
	TouchType_Move,     /**< Touch/Mouse Move */
	TouchType_Max       /**< default type */
};

//DA mirror mode 
enum MirrorMode {
	NOWORK = 0x00,
	MIRROR, //only mirror
	APP,     // mirror through APP
	MIRROR_INVALID
};

//App state
enum AppState {
	APP_UNAVAILABLE,
	APP_AVAILABLE,
	APP_UNSUPPORT,
	APP_STATCHANGE
};

//DA Srceen Mode
enum ScreenMode {
	Screen_Horizontal,
	Screen_Vertial
};

enum HardKey {
	HOME_DOWN,
	HOME_UP,
	MENU_DOWN,
	MENU_UP,
	BACK_DOWN,
	BACK_UP,
	PRE_TRACK_DOWN,
	PRE_TRACK_UP,
	NEXT_TRACK_DOWN,
	NEXT_TRACK_UP
};

	
// point struct
parcelable TouchPoints {
	uint8   pointerId;
	uint    x;
	uint    y;
};

// wifi Address struct
parcelable WifiAddrST
{
	uint64   addr;
};

parcelable WFDDeviceInfo
{
	uint64 addr;
	uint16 nameLen;
	string deviceName;
};

parcelable WFDDeviceState
{
	wfdSvcState svcState;
	AppState appState;
	uint bt;
	uint hid;
	uint16 sourceState;
};

parcelable WFDRemoteDeviceInfo
{
	wfdSvcState svcState;
	AppState appState;
	uint width;
	uint height;
	bool locked;
	ScreenMode mode;
};

interface IWFDService
{

	void wfdStateSync(out WFDDeviceState deviceState) ;
	void wfdGetRemoteInfo(out WFDRemoteDeviceInfo remoteInfo);
	void wfdGetLocalDevice(out uint16 nameLen, out uint8* name);

//General
	in wfd_powerOn();	
	in wfd_powerOff();
	in wfd_sourceChange(uint8 mode) ;
	in wfd_mirrorMode(MirrorMode mode);
	in wfd_SreenMode(ScreenMode mode);
	in wfd_getGPSTime();
	in wfd_sendHardKey(HardKey key);
		
// p2p
	in wfd_startSearch();
	in wfd_stopSearch();

	in wfd_acceptInvitation(bool accpet); // 
	in wfd_disconnect();

	in wfd_enableWfd();
	in wfd_disableWfd();

	in wfd_play();
	in wfd_pause();
	
// wfd stack

	in wfd_sendUIBCData(TouchType type,  TouchPoints[] points);

// reply	
			
	out wfdSearchResultInd(WFDDeviceInfo deviceInfo);

	out wfdSearchFinishedInd(uint err);

	out wfdInvalidAppInd(uint err);

	out wfdCurrentAppChangeInd(uint err);

	out wfdNaviVoiceInd(uint err);
	
	out wfdSourceChangeCfm(uint err, uint currentMode);

	out wfdLocalDeviceInd(uint16 nameLen, uint8[] name);


// multicast

	multicast wfdAppStatus(uint err);

	multicast wfdPowerStatus(uint err);

	multicast wfdInvitationInd(WFDDeviceInfo deviceInfo);

	multicast wfdConnectResultInd(uint err);

	multicast wfdDisconnectInd(uint err);

	multicast wfdBtStatus(uint bt, uint hid);

	multicast wfdStartListenInd(uint err); 

	multicast wfdMacAddr(uint len, uint64 mac);

	multicast wfdP2pVersion(uint len, string version);

	multicast wfdGetGPSTimeInd(uint err, uint len, string time);

// send to Bt	
	multicast wfdRemotePixesInfo(wfdSvcState wfdState, uint width, uint height);

	multicast wfdRemoteSrceenChange(bool locked, ScreenMode mode);

	multicast wfdHIDPoint(uint pressed, uint width, uint height);

	multicast wfdHardkey(HardKey key);

	multicast wfdModeChangeCfm(uint mode);

	multicast wfdReceiverId(uint len, uint64 receiverId);

	multicast wfdAppDeskInd(uint deskFlag);

	multicast wfdModeChangeReq(uint appId);

	multicast wfdLinkQuiltyInd(int sig);

}

