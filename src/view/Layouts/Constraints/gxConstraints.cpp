#include "View/Layouts/Constraints/gxConstraints.h"
#include "View/Elements/gxViewElement.h"

//TODO: Destructor

void gxConstraints::Reset()
{
    Bounds = mLayoutee->GetBounds();
}

void gxConstraints::Apply()
{
    mLayoutee->SetBounds( Bounds );
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

int gxConstraints::GetFlex( bool aOnMajorAxis )
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

gxLayoutRegion::Type gxConstraints::GetRegion()
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