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

typedef gxPrimitiveConstraint< gxLayoutRegion::Type > gxRegionConstraint;

#endif //gxRegionConstraint_h
