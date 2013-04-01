#include "View/Layouts/Constraints/gxConstraints.h"
#include "View/Elements/gxViewElement.h"

//TODO: Destructor

void gxConstraints::Reset()
{
    Bounds = mElement->GetBounds();
}

void gxConstraints::Apply()
{
    mElement->SetBounds( Bounds );
}

gxConstraint* gxConstraints::GetConstraint( ID aId )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aId );
    bool iConstraintFound = iConstraint != mConstraintMap.end();
    
    return iConstraintFound ? iConstraint->second : NULL;
}

void gxConstraints::AddConstraint( ID                aId,
                                   gxConstraint* aConstraint )
{
    // If there's already a constraint, delete its contents.
    if ( GetConstraint( aId ) )
        delete mConstraintMap[ aId ];
    
    mConstraintMap[ aId ] = aConstraint;
}

void gxConstraints::Set( gxString aConstraintName,
                         int      aValue )
{
    if ( aConstraintName == "Pixels"  ||
         aConstraintName == "Percent" ||
         aConstraintName == "Flex" ) {
        gxSizeConstraint::Type iType;

        if ( aConstraintName == "Pixels" ) {
            iType = gxSizeConstraint::Pixels;
        } else if ( aConstraintName == "Flex" ) {
            iType = gxSizeConstraint::Flex;
        } else if ( aConstraintName == "Percent" ) {
            iType = gxSizeConstraint::Percent;
        }
        
        AddConstraint( SizeMajor, new gxSizeConstraint( iType, aValue ) );
    }
}

void gxConstraints::Get( gxSizeConstraint*& iConstraint, bool aOnMajorAxis )
{
    // Flex can only exist on major axis, so first search the major axis size
    GetConstraint( SizeMajor, iConstraint );
    
    // If it isn't a flex, then search based on the actual requested axis
    if ( iConstraint && iConstraint->GetType() != gxSizeConstraint::Flex )
    {
        GetConstraint( aOnMajorAxis ? SizeMajor : SizeMinor, iConstraint );
    }
}

void gxConstraints::Set( gxRegion aRegion )
{
    AddConstraint( Region, new gxRegionConstraint( aRegion ) );
}

gxRegion gxConstraints::GetRegion()
{
    gxRegionConstraint* iConstraint = NULL;
    GetConstraint( Region, iConstraint );
    
    return iConstraint ? iConstraint->GetValue() : gxRegion::Undefined;    
}
