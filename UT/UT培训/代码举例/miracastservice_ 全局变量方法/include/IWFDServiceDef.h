#ifndef __WFD_SVC_DEF_H__
#define __WFD_SVC_DEF_H__

namespace goni
{

	enum TouchType {
        TouchType_Press,     /**< Touch/Mouse down */
        TouchType_Release,   /**< Touch/Mouse up */
        TouchType_Move,     /**< Touch/Mouse Move */
        TouchType_Max       /**< default type */
    };
	
	struct TouchPoints {
        unsigned char   pointerId;
        unsigned int    x;
        unsigned int    y;
    };
}
	
#endif // ___WFD_SVC_DEF_H__