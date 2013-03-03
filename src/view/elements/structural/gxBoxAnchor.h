#ifndef gxBoxAnchor_h
#define gxBoxAnchor_h

#include "view/Connections/gxAnchor.h"

class gxBoxAnchor: public gxAnchor
{
public:
    gxBoxAnchor( gxVisual* aOwner );
    
    virtual gxPoint GetPosition();
};


#endif // gxBoxAnchor_h
