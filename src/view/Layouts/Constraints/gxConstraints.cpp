#include "View/Layouts/Constraints/gxConstraints.h"
#include "View/Elements/gxViewElement.h"

void gxConstraints::Reset()
{
    Bounds = Rect;
}

void gxConstraints::Apply()
{
    Element->SetBounds( Bounds );
}

gxConstraint* gxConstraints::GetConstraint( ConstriantId aId )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aId );
    
    if ( iConstraint != mConstraintMap.end() )
        return iConstraint->second;
    else
        return NULL;
}

void gxConstraints::Set( gxRegion aRegion )
{
    // If already set, delete the previous
    if ( GetConstraint( gxRegionConstraintId ) )
        delete mConstraintMap[ gxRegionConstraintId ];
        
    mConstraintMap[ gxRegionConstraintId ] = new gxRegionConstraint( aRegion );
}

/*
gxConstraint* gxConstraints::Get( const char* aConstraintName )
{
    return mConstraintMap[1];
}
*/

gxRegion gxConstraints::GetRegion()
{
    gxConstraint* iConstraint = GetConstraint( gxRegionConstraintId );
    if ( iConstraint )
    {
        gxRegionConstraint* iRegionConstraint;
        iRegionConstraint = static_cast<gxRegionConstraint*>( iConstraint );
        return iRegionConstraint->GetValue();
    } else {
        return gxRegion::Undefined;
    }
}
