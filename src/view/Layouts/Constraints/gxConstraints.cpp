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

gxConstraint* gxConstraints::GetConstraint( MapId aId )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aId );
    bool iConstraintFound = iConstraint != mConstraintMap.end();
    
    return iConstraintFound ? iConstraint->second : NULL;
}

void gxConstraints::AddConstraint( MapId         aId,
                                   gxConstraint* aConstraint )
{
    // If there's already a constraint, delete its contents.
    if ( GetConstraint( aId ) )
        delete mConstraintMap[ aId ];
    
    mConstraintMap[ aId ] = aConstraint;
}

gxConstraint::Type gxConstraints::GetInternalType( gxConstraint::Type aType )
{
    switch ( aType )
    {
        case gxConstraint::Pixels:
        case gxConstraint::Percent:
        case gxConstraint::Flex:
            return gxConstraint::Size;
            
        default:
            return aType;
    }
}

gxConstraints::MapId gxConstraints::TypeToMapId( gxConstraint::Type aType,
                                                 bool               aOnMajorAxis)
{
    return aOnMajorAxis ? aType : -aType;
}

gxConstraint* gxConstraints::CreateConstraint( gxConstraint::Type aType,
                                               int                aValue )
{
    gxConstraint::Type iType = GetInternalType( aType );
    
    switch ( iType ) {
            
        case gxConstraint::Size:
            return new gxSizeConstraint( aType, aValue );
        case gxConstraint::Region:
            return new gxRegionConstraint( (gxLayoutRegion::Type)aValue );
            
        default:
            // TODO: Assert
            return NULL;
    }
}


void gxConstraints::Set( gxConstraint::Type aType,
                         int                aValue,
                         bool               aOnMajorAxis )
{
    gxConstraint*      iConstraint = CreateConstraint( aType, aValue );
    
    gxConstraint::Type iType       = GetInternalType( aType );
    
    MapId              aMapId      = TypeToMapId( iType, aOnMajorAxis );
    
    AddConstraint( aMapId, iConstraint );
}

/*
void gxConstraints::Get( gxSizeConstraint*& iConstraint, bool aOnMajorAxis )
{
    gxConstraint::Type iType = gxSizeConstraint::Id;
    
    // First search the major axis (flex can only be on major axis).
    MapId aId = TypeToMapId( gxConstraint::Size, true );
    GetConstraint( aId, iConstraint );
    
    bool iFlexFound = iConstraint && iConstraint->IsFlex();
    
    // If no flex was found an we are required to search the minor axis
    if ( !iFlexFound && !aOnMajorAxis )
    {
        // Search the minor axis
        aId = TypeToMapId( gxConstraint::Size, false );
        GetConstraint( aId, iConstraint );
    }
}

void gxConstraints::Get( gxRegionConstraint*& iConstraint )
{
    GetConstraint( gxConstraint::Region, iConstraint );
}
*/