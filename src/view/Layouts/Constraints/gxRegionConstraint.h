#ifndef gxRegionConstraint_h
#define gxRegionConstraint_h

#include "core/gxAssert.h"
#include "View/Layouts/Constraints/gxConstraints.h"

enum gxRegion
{
    Undefined,
    Center,
    North,
    East,
    South,
    West
};

typedef gxConstraint<gxRegion> gxRegionConstraint;

#endif //gxRegionConstraint_h
