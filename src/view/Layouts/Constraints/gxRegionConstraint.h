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

class gxRegionConstraint: public gxConstraint
{
public:
    gxRegionConstraint( gxRegion aRegion ) :
        mRegion( aRegion )
    {}
    
    gxRegion GetValue()
    {
        return mRegion;
    }    
private:
    gxRegion mRegion;
};



#endif //gxRegionConstraint_h
