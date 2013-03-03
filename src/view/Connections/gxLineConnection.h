#ifndef gxLineConnection_h
#define gxLineConnection_h

#include "View/Elements/Visual/shapes/gxLine.h"
#include "View/Connections/gxConnection.h"

class gxLineConnection: public gxLine,
                        public gxConnection
{
public:
    gxLineConnection()
    {
        mFlags.Unset( gxViewElement::Relative );
    }
    
    virtual void InvalidateConnection()
    {
        gxLine::Invalidate();
    }
protected:
    virtual void Validate();    
};

#endif // gxLineConnection_h
