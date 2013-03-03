#ifndef gxRectAnchor_h
#define gxRectAnchor_h

#include "View/Elements/Structural/Anchors/gxAnchor.h"

class gxRectAnchor: public gxAnchor
{
public:
    gxRectAnchor();
    
    virtual gxPoint GetPosition( const gxPoint& aReference );
    virtual gxPoint GetReference();    
};


#endif // gxRectAnchor_h
