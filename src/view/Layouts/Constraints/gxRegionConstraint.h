#ifndef gxRegionConstraint_h
#define gxRegionConstraint_h

#include "core/gxAssert.h"
#include "View/Layouts/Constraints/gxPrimitiveConstraint.h"

enum gxLayoutRegion {
    GrCenter,
    GrNorth,
    GrEast,
    GrSouth,
    GrWest
};

typedef gxPrimitiveConstraint<gxLayoutRegion> gxRegionConstraint;

#endif //gxRegionConstraint_h
