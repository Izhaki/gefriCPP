#ifndef gxLineConnection_h
#define gxLineConnection_h

#include "View/Elements/Visual/shapes/gxLine.h"
#include "View/Connections/gxConnection.h"

class gxLineConnection: public gxLine,
                        public gxConnection
{
public:
    // TODO: this should really be replace by absolute positioning
    gxLineConnection()
    {
//        mTransformFlags.Unset( gxTransFlags::Scale | gxTransFlags::Scroll | gxTransFlags::Translate );
    }
protected:
    virtual void Validate();
};

#endif // gxLineConnection_h
