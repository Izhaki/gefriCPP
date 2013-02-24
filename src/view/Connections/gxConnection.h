#ifndef gxConnection_h
#define gxConnection_h

#include "core/gxObject.h"
#include "view/Connections/gxAnchor.h"

class gxConnection : public gxObject
{
public:
    gxConnection()
      : mSource     ( NULL ),
        mDestination( NULL ) {}
    
    void SetSourceAnchor( gxAnchor* aAnchor );
    void SetDestinationAnchor( gxAnchor* aAnchor );
protected:
    gxAnchor* mSource;
    gxAnchor* mDestination;
};

#endif // gxConnection_h
