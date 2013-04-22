#include "View/Layouts/Constraints/gxConstrained.h"
#include "View/Elements/gxViewElement.h"

gxConstrained::~gxConstrained()
{
}

void gxConstrained::ResetBounds()
{
    Bounds = mLayoutee->GetBounds();
}

void gxConstrained::ApplyBounds()
{
    mLayoutee->SetBounds( Bounds );
}

void gxConstrained::Set( gxConstraint::Type aType,
                         int                aValue,
                         bool               aOnMajorAxis )
{
    mConstraintMap.Set( aType, aValue, aOnMajorAxis );
}

int gxConstrained::GetFlex( bool aOnMajorAxis )
{
    gxSizeConstraint* iSizeConstraint = NULL;
    
    Get( iSizeConstraint, aOnMajorAxis );
    
    if ( iSizeConstraint && iSizeConstraint->IsFlex() )
    {
        return iSizeConstraint->GetValue();
    } else {
        return 0;
    }
}

gxLayoutRegion::Type gxConstrained::GetRegion()
{
    gxRegionConstraint* iRegionConstraint = NULL;
    
    Get( iRegionConstraint );
    
    if ( iRegionConstraint )
    {
        return iRegionConstraint->GetValue();
    } else {
        gxWarn( "No region constraint found" );
        return gxLayoutRegion::Center;
    }
}