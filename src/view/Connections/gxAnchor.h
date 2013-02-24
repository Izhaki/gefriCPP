#ifndef gxAnchor_h
#define gxAnchor_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"

class gxAnchor: public gxObject
{
public:    
    /*
     * @brief Returns the position of the connection anchor in absolute 
     * coordinates.
     *
     * @return The anchor's position
     */
    virtual gxPoint GetPosition() = 0;
};

#endif // gxAnchor_h
