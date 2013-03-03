#ifndef gxAnchor_h
#define gxAnchor_h

#include "core/gxObject.h"
#include "core/observer/gxObserver.h"
#include "core/geometry/gxGeometry.h"
#include "view/Elements/Visual/gxVisual.h"
#include "View/Elements/Structural/gxChangeNotifier.h"

// Forward declaration
class gxConnection;

class gxAnchor: public gxObject
{
    gxDeclareObserver( gxAnchor )
public:
    gxAnchor( gxVisual* aVisual );
    ~gxAnchor();
    
    void SetConnection( gxConnection* aConnection );
    
    /*
     * @brief Returns the position of the connection anchor in absolute 
     * coordinates.
     *
     * @return The anchor's position
     */
    virtual gxPoint GetPosition() = 0;
protected:
    gxVisual*         mVisual;
    gxChangeNotifier* mNotifier;
    gxConnection*     mConnection;
    
    virtual void OnVisualChanged( bool aDeleted );
};

#endif // gxAnchor_h
