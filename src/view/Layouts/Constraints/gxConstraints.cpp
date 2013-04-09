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

gxConstraint* gxConstraints::GetConstraint( gxConstraint::Type aType )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aType );
    bool iConstraintFound = iConstraint != mConstraintMap.end();
    
    return iConstraintFound ? iConstraint->second : NULL;
}

void gxConstraints::AddConstraint( gxConstraint::Type aType,
                                   gxConstraint*      aConstraint )
{
    // If there's already a constraint, delete its contents.
    if ( GetConstraint( aType ) )
        delete mConstraintMap[ aType ];
    
    mConstraintMap[ aType ] = aConstraint;
}

gxConstraint::Type gxConstraints::GetInternalType( gxConstraint::Type aType,
                                                   bool               aOnMajorAxis )
{
    switch ( aType )
    {
        case gxConstraint::Pixels:
        case gxConstraint::Percent: return aOnMajorAxis ? gxConstraint::SizeX : gxConstraint::SizeY;
        case gxConstraint::Flex:    return gxConstraint::SizeX;
            
        default:        return aType;
            
    }
}

void gxConstraints::Set( gxConstraint::Type aType,
                         int                aValue )
{
    gxConstraint::Type iType       = GetInternalType( aType );
    gxConstraint*      iConstraint = NULL;
    
    switch ( iType ) {
            
        case gxConstraint::SizeX:
        case gxConstraint::SizeY:
            iConstraint = new gxSizeConstraint( aType, aValue );
            break;
        case gxConstraint::Region:
            iConstraint = new gxRegionConstraint( (gxLayoutRegion::Type)aValue );
            
        default:
            break;
    }
    
    AddConstraint( iType, iConstraint );
}

void gxConstraints::Get( gxSizeConstraint*& iConstraint, bool aOnMajorAxis )
{
    // Flex can only exist on major axis, so first search the major axis size
    GetConstraint( gxConstraint::SizeX, iConstraint );
    
    // If it isn't a flex, then search based on the actual requested axis
    if ( ! ( iConstraint && iConstraint->IsFlex() ) )
    {
        GetConstraint( aOnMajorAxis ? gxConstraint::SizeX : gxConstraint::SizeY, iConstraint );
    }
}

void gxConstraints::Get( gxRegionConstraint*& iConstraint )
{
    GetConstraint( gxConstraint::Region, iConstraint );
}
