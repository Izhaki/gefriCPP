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

gxConstraintBase* gxConstraints::GetConstraint( ConstriantId aId )
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
        
    mConstraintMap[ gxRegionConstraintId ] = new gxRegion::Constraint( aRegion );
}

/*
gxConstraint* gxConstraints::Get( const char* aConstraintName )
{
    return mConstraintMap[1];
}
*/

/*
gxRegion gxConstraints::GetRegion()
{
    gxConstraintBase* iConstraint = GetConstraint( gxRegionConstraintId );
    if ( iConstraint )
    {
        gxRegion::Constraint* iRegionConstraint;
        iRegionConstraint = static_cast<gxRegion::Constraint*>( iConstraint );
        return iRegionConstraint->GetValue();
    } else {
        return gxRegion::Undefined;
    }
}
*/