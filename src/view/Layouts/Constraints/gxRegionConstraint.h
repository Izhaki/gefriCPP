#ifndef gxRegionConstraint_h
#define gxRegionConstraint_h

#include "core/gxAssert.h"
#include "View/Layouts/Constraints/gxPrimitiveConstraint.h"

namespace gxLayoutRegion {
    enum Type {
        Center,
        North,
        East,
        South,
        West
    };
}

class gxRegionConstraint : public gxPrimitiveConstraint< gxLayoutRegion::Type >
{
public:
    static const gxConstraint::Type Id = Region;
    virtual gxConstraint::Type GetType() { return Region; }
    
    gxRegionConstraint( gxLayoutRegion::Type aRegion ) :
        gxPrimitiveConstraint< gxLayoutRegion::Type >( aRegion )
    {}
    
    gxRegionConstraint( gxConstraint::Value aRegion ) :
        gxPrimitiveConstraint< gxLayoutRegion::Type >( (gxLayoutRegion::Type)aRegion )
    {}
    
};

#endif //gxRegionConstraint_h
