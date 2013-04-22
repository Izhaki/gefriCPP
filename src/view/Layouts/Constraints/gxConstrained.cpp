#include "View/Layouts/Constraints/gxConstrained.h"
#include "View/Elements/gxViewElement.h"

// TODO: Move somewhere else?
template <typename MapType>
void ClearMap( MapType& aMap )
{
    for ( typename MapType::iterator it = aMap.begin(); it != aMap.end(); ++it )
    {
        delete it->second;
    }
    aMap.clear();
}

gxConstrained::~gxConstrained()
{
    ClearMap( mConstraintMap );
}

void gxConstrained::ResetBounds()
{
    Bounds = mLayoutee->GetBounds();
}

void gxConstrained::ApplyBounds()
{
    mLayoutee->SetBounds( Bounds );
}

gxConstraint* gxConstrained::GetConstraint( MapId aId )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aId );
    bool iConstraintFound = iConstraint != mConstraintMap.end();
    
    return iConstraintFound ? iConstraint->second : NULL;
}

void gxConstrained::AddConstraint( MapId         aId,
                                   gxConstraint* aConstraint )
{
    // If there's already a constraint, delete its contents.
    if ( GetConstraint( aId ) )
        delete mConstraintMap[ aId ];
    
    mConstraintMap[ aId ] = aConstraint;
}

gxConstraint::Type gxConstrained::GetInternalType( gxConstraint::Type aType )
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

gxConstrained::MapId gxConstrained::TypeToMapId( gxConstraint::Type aType,
                                                 bool               aOnMajorAxis)
{
    return aOnMajorAxis ? aType : -aType;
}

gxConstraint* gxConstrained::CreateConstraint( gxConstraint::Type aType,
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


void gxConstrained::Set( gxConstraint::Type aType,
                         int                aValue,
                         bool               aOnMajorAxis )
{
    gxConstraint*      iConstraint = CreateConstraint( aType, aValue );
    
    gxConstraint::Type iType       = GetInternalType( aType );
    
    MapId              aMapId      = TypeToMapId( iType, aOnMajorAxis );
    
    AddConstraint( aMapId, iConstraint );
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