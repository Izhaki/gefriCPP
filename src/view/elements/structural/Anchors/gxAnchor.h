#ifndef gxAnchor_h
#define gxAnchor_h

#include "View/Elements/Structural/gxStructural.h"
#include "core/geometry/gxGeometry.h"
#include "view/Elements/Visual/gxVisual.h"

// Forward declaration
class gxConnection;

class gxAnchor: public gxStructural
{
public:
    gxAnchor();
    ~gxAnchor();
    
    void SetConnection( gxConnection* aConnection );
    
    /*
     * @brief Returns the position of the connection anchor in absolute
     * coordinates.
     *
     * @param aReference The reference point for the intersection with this
     * anchor. For line connection this will be the other anchor.
     *
     * @return The anchor's position
     */
    virtual gxPoint GetPosition( const gxPoint& aReference ) = 0;
    
    /*
     * @brief Returns the anchor's reference point in absolute coordinates.
     * 
     * As connections are made between two anchors, each anchor needs its
     * peers reference position to work out itself. A box anchor, for example,
     * will need to know where is the other end of the its line connection to 
     * calculate where the connection intersects with the box bounds.
     *
     * @return The anchor's feference point
     */
    virtual gxPoint GetReference() = 0;
protected:
    gxConnection* mConnection;
    
    virtual void OnAncestorInvalid();
};

#endif // gxAnchor_h
