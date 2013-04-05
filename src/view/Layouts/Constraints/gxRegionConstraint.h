#ifndef gxRegionConstraint_h
#define gxRegionConstraint_h

#include "core/gxAssert.h"
#include "View/Layouts/Constraints/gxPrimitiveConstraint.h"

enum gxLayoutRegion {
    grCenter,
    grNorth,
    grEast,
    grSouth,
    grWest
};

typedef gxPrimitiveConstraint<gxLayoutRegion> gxRegionConstraint;

#endif //gxRegionConstraint_h
