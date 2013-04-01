#ifndef gxRegionConstraint_h
#define gxRegionConstraint_h

#include "core/gxAssert.h"
#include "View/Layouts/Constraints/gxPrimitiveConstraint.h"

enum gxRegion {
    Undefined,
    Center,
    North,
    East,
    South,
    West
};

typedef gxPrimitiveConstraint<gxRegion> gxRegionConstraint;

#endif //gxRegionConstraint_h
