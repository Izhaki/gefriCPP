#ifndef gxRegionConstraint_h
#define gxRegionConstraint_h

#include "core/gxAssert.h"
#include "View/Layouts/Constraints/gxConstraints.h"

class gxRegion
{
public:
    enum values
    {
        Undefined,
        Center,
        North,
        East,
        South,
        West
    } mRegion;
    
    gxRegion():
        mRegion( Undefined )
    {}
    
    gxRegion( values aRegion ):
        mRegion( aRegion )
    {}
    
    operator values& ()       { return mRegion; }
    operator values  () const { return mRegion; }
    
    static const ConstriantId id = gxRegionConstraintId;
    
    typedef gxConstraint<gxRegion> Constraint;
};

/*
enum gxRegion
{
    Undefined,
    Center,
    North,
    East,
    South,
    West
};
*/

/*
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
*/



#endif //gxRegionConstraint_h
