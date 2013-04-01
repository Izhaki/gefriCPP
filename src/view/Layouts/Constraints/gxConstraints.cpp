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

gxConstraintBase* gxConstraints::GetConstraint( ID aId )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aId );
    
    if ( iConstraint != mConstraintMap.end() )
        return iConstraint->second;
    else
        return NULL;
}

void gxConstraints::AddConstraint( ID                aId,
                                   gxConstraintBase* aConstraint )
{
    if ( GetConstraint( aId ) )
        delete mConstraintMap[ aId ];
    
    mConstraintMap[ aId ] = aConstraint;
}

void gxConstraints::Set( gxString aConstraintName,
                         int      aValue )
{
    if ( aConstraintName == "Flex" )
    {
        AddConstraint( SizeMajor, new gxSizeConstraint( gxSizeConstraint::Flex, aValue ) );
    }
}


void gxConstraints::Set( gxRegion aRegion )
{
    AddConstraint( Region, new gxRegionConstraint( aRegion ) );
}

gxRegion gxConstraints::GetRegion()
{
    gxConstraintBase* iConstraint = GetConstraint( Region );
    if ( iConstraint )
    {
        gxRegionConstraint* iRegionConstraint;
        iRegionConstraint = static_cast<gxRegionConstraint*>( iConstraint );
        return iRegionConstraint->GetValue();
    } else {
        return gxRegion::Undefined;
    }
}
