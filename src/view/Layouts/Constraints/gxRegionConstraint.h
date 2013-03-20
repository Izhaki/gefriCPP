#ifndef gxRegionConstraint_h
#define gxRegionConstraint_h

#include "core/gxAssert.h"

enum gxRegion
{
    Center,
    North,
    East,
    South,
    West
};

class gxAbstractRegionConstraint
{
public:
    virtual gxRegion GetRegion() { Assert(); return gxRegion::Center; }    
    virtual void SetRegion( gxRegion aRegion ) { Assert(); }
private:
    void Assert()
    {
        gxASSERT( true, "No region constraints for this layout" );
    }
};

class gxRegionConstraint: virtual public gxAbstractRegionConstraint
{
public:
    virtual gxRegion GetRegion()
    {
        return mRegion;
    }
    
    virtual void SetRegion( gxRegion aRegion )
    {
        mRegion = aRegion;
    }
private:
    gxRegion mRegion;
};



#endif //gxRegionConstraint_h
