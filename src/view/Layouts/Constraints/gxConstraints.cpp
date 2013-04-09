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

gxConstraint* gxConstraints::GetConstraint( gxConstraintType aType )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aType );
    bool iConstraintFound = iConstraint != mConstraintMap.end();
    
    return iConstraintFound ? iConstraint->second : NULL;
}

void gxConstraints::AddConstraint( gxConstraintType aType,
                                   gxConstraint*    aConstraint )
{
    // If there's already a constraint, delete its contents.
    if ( GetConstraint( aType ) )
        delete mConstraintMap[ aType ];
    
    mConstraintMap[ aType ] = aConstraint;
}

gxConstraintType gxConstraints::GetInternalType( gxConstraintType aType,
                                                 bool             aOnMajorAxis )
{
    switch ( aType )
    {
        case gcPixels:
        case gcPercent: return aOnMajorAxis ? gcSizeX : gcSizeY;
        case gcFlex:    return gcSizeX;
            
        default:        return aType;
            
    }
}

void gxConstraints::Set( gxConstraintType aType,
                         int              aValue )
{
    gxConstraintType iType       = GetInternalType( aType );
    gxConstraint*    iConstraint = NULL;
    
    switch ( iType ) {
            
        case gcSizeX:
        case gcSizeY:
            iConstraint = new gxSizeConstraint( aType, aValue );
            break;
        case gcRegion:
            iConstraint = new gxRegionConstraint( (gxLayoutRegion::Type)aValue );
            
        default:
            break;
    }
    
    AddConstraint( iType, iConstraint );
}

void gxConstraints::Get( gxSizeConstraint*& iConstraint, bool aOnMajorAxis )
{
    // Flex can only exist on major axis, so first search the major axis size
    GetConstraint( gcSizeX, iConstraint );
    
    // If it isn't a flex, then search based on the actual requested axis
    if ( ! ( iConstraint && iConstraint->IsFlex() ) )
    {
        GetConstraint( aOnMajorAxis ? gcSizeX : gcSizeY, iConstraint );
    }
}

void gxConstraints::Get( gxRegionConstraint*& iConstraint )
{
    GetConstraint( gcRegion, iConstraint );
}
