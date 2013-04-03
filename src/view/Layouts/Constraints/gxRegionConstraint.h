#ifndef gxRegionConstraint_h
#define gxRegionConstraint_h

#include "core/gxAssert.h"
#include "View/Layouts/Constraints/gxPrimitiveConstraint.h"

typedef char gxLayoutRegion;

gxLayoutRegion const GxCenter    = 1;
gxLayoutRegion const GxNorth     = 2;
gxLayoutRegion const GxEast      = 3;
gxLayoutRegion const GxSouth     = 4;
gxLayoutRegion const GxWest      = 5;

typedef gxPrimitiveConstraint<gxLayoutRegion> gxRegionConstraint;

#endif //gxRegionConstraint_h
