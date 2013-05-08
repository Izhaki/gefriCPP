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
    gxRegionConstraint( gxLayoutRegion::Type aRegion ) :
        gxPrimitiveConstraint< gxLayoutRegion::Type >( aRegion )
    {}
};

#endif //gxRegionConstraint_h
