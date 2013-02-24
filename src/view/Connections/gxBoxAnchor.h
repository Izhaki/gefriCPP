#include "view/Connections/gxAnchor.h"
#include "view/Elements/Visual/gxVisual.h"

#ifndef gxBoxAnchor_h
#define gxBoxAnchor_h

class gxBoxAnchor: public gxAnchor
{
public:    
    gxBoxAnchor( gxVisual* aOwner );
    
    virtual gxPoint GetPosition();
private:
    gxVisual* mOwner;
};


#endif // gxBoxAnchor_h
