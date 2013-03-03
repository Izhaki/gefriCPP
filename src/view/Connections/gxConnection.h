#ifndef gxConnection_h
#define gxConnection_h

#include "core/gxObject.h"
#include "View/Elements/Structural/Anchors/gxAnchor.h"

class gxConnection : public gxObject
{
public:
    gxConnection()
      : mSource     ( NULL ),
        mDestination( NULL ) {}

    /**
     * @brief Sets the source anchor for this connection.
     *
     * @param aAnchor The source anchor.
     */
    void SetSourceAnchor( gxAnchor* aAnchor );
    
    /**
     * @brief Sets the destination anchor for this connection.
     *
     * @param aAnchor The destination anchor.
     */
    void SetDestinationAnchor( gxAnchor* aAnchor );
    
    /**
     * @brief Invalidates this connection.
     *
     * Anchors will call this when they or they ancestors are invalidated.
     *
     * Subclasses should implement this by invalidating the visual.
     */
    virtual void InvalidateConnection() = 0;
protected:
    gxAnchor* mSource;
    gxAnchor* mDestination;
};

#endif // gxConnection_h
