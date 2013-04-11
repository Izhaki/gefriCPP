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

//typedef gxPrimitiveConstraint< gxLayoutRegion::Type > gxRegionConstraint;

class gxRegionConstraint : public gxPrimitiveConstraint< gxLayoutRegion::Type >
{
public:
    static const gxConstraint::Type Id = Region;
    
    gxRegionConstraint( gxLayoutRegion::Type aType) :
        gxPrimitiveConstraint< gxLayoutRegion::Type >( aType )
    {}
};

#endif //gxRegionConstraint_h
