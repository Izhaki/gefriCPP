#include "View/Layouts/Constraints/gxConstraints.h"
#include "View/Elements/gxViewElement.h"

//TODO: Destructor

void gxConstraints::Reset()
{
//!    Bounds = Rect;
    Bounds = mElement->GetBounds();
}

void gxConstraints::Apply()
{
    mElement->SetBounds( Bounds );
}

gxConstraintBase* gxConstraints::GetConstraint( ConstriantId aId )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aId );
    
    if ( iConstraint != mConstraintMap.end() )
        return iConstraint->second;
    else
        return NULL;
}

void gxConstraints::Set( gxString aConstraintName,
                         int      aValue )
{
    if ( aConstraintName == "Flex" )
    {
        // If already set, delete the previous
        if ( GetConstraint( gxFlexConstraintId ) )
            delete mConstraintMap[ gxFlexConstraintId ];
        
        mConstraintMap[ gxFlexConstraintId ] = new gxSizeConstraint( gxSizeConstraint::Flex, aValue );
    }
}


void gxConstraints::Set( gxRegion aRegion )
{
    // If already set, delete the previous
    if ( GetConstraint( gxRegionConstraintId ) )
        delete mConstraintMap[ gxRegionConstraintId ];
        
    mConstraintMap[ gxRegionConstraintId ] = new gxRegionConstraint( aRegion );
}

gxRegion gxConstraints::GetRegion()
{
    gxConstraintBase* iConstraint = GetConstraint( gxRegionConstraintId );
    if ( iConstraint )
    {
        gxRegionConstraint* iRegionConstraint;
        iRegionConstraint = static_cast<gxRegionConstraint*>( iConstraint );
        return iRegionConstraint->GetValue();
    } else {
        return gxRegion::Undefined;
    }
}
