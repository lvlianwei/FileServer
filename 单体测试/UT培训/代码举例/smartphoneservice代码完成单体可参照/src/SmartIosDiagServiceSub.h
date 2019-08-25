#ifndef SMART_IOS_DIAG_SERVICE_SUB_H
#define SMART_IOS_DIAG_SERVICE_SUB_H
/**
 * @file SmartIosDiagServiceSub.h
 * @brief 
 * @author jianglei
 * @version 1
 * @date 2017-07-27
 */
#include "sub/DiagSub.h"
namespace goni {
    class SmartIosDiagServiceSub : public IDiagSub {
          public:
	      SmartIosDiagServiceSub();
	      ~SmartIosDiagServiceSub();
	      //multicast
	      /**
	       * @brief broadcastDiagOn ,receive diag service diag on multicast
	       *
	       * @param eMode
	       *
	       * @return 
	       */
	      virtual android::status_t broadcastDiagOn(const DIAG_MODE& eMode);
	      /**
	       * @brief broadcastDiagInit ,receive diag service diag init multicast
	       *
	       * @return 
	       */
	      virtual android::status_t broadcastDiagInit();
    };

}
#endif
