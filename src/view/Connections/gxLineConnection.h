#ifndef gxLineConnection_h
#define gxLineConnection_h

#include "View/Elements/Visual/shapes/gxLine.h"
#include "View/Connections/gxConnection.h"

class gxLineConnection: public gxLine,
                        public gxConnection
{
public:
    gxLineConnection();
    
    virtual void InvalidateConnection();
protected:
    virtual void DoValidate();
    
    // Connections use absolute positioning
    virtual bool IsRelative() { return false; }
};

#endif // gxLineConnection_h
