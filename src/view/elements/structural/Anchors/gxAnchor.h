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
     * @return The anchor's position
     */
    virtual gxPoint GetPosition() = 0;
protected:
    gxConnection*     mConnection;
    
    virtual void OnAncestorChanged(  bool aDeleted = false  );
};

#endif // gxAnchor_h
