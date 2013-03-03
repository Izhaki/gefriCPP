#ifndef gxBoxAnchor_h
#define gxBoxAnchor_h

#include "View/Elements/Structural/Anchors/gxAnchor.h"

class gxBoxAnchor: public gxAnchor
{
public:
    gxBoxAnchor();
    
    virtual gxPoint GetPosition( const gxPoint& aReference );
    virtual gxPoint GetReference();    
};


#endif // gxBoxAnchor_h
