#include "View/Layouts/Constraints/gxConstraintMap.h"

#include "View/Layouts/Constraints/gxSizeConstraint.h"
#include "View/Layouts/Constraints/gxRegionConstraint.h"

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

gxConstraintMap::~gxConstraintMap()
{
    ClearMap( mConstraintMap );
}

gxConstraintMap::MapId gxConstraintMap::TypeToMapId( gxConstraint::Type aType,
                                                     bool               aOnMajorAxis)
{
    return aOnMajorAxis ? aType : -aType;
}

void gxConstraintMap::Add( gxConstraint::Type aType,
                          int                aValue,
                          bool               aOnMajorAxis )
{
    gxConstraint* iConstraint = CreateConstraint( aType, aValue );
    
    MapId         aMapId      = TypeToMapId( iConstraint->GetType(), aOnMajorAxis );
    
    Add( aMapId, iConstraint );
}

gxConstraint* gxConstraintMap::Get( gxConstraint::Type aType,
                                    bool aOnMajorAxis )
{
    MapId aMapId = TypeToMapId( aType, aOnMajorAxis );
    return Get( aMapId );
}

gxConstraint* gxConstraintMap::Get( MapId aId )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aId );
    bool iConstraintFound = iConstraint != mConstraintMap.end();
    
    return iConstraintFound ? iConstraint->second : NULL;
}

void gxConstraintMap::Add( MapId         aId,
                           gxConstraint* aConstraint )
{
    // If there's already a constraint, delete its contents.
    if ( Get( aId ) )
        delete mConstraintMap[ aId ];
    
    mConstraintMap[ aId ] = aConstraint;
}

gxConstraint* gxConstraintMap::CreateConstraint( gxConstraint::Type aType,
                                                 int                aValue )
{
    switch ( aType )
    {
        case gxConstraint::Pixels:
        case gxConstraint::Percent:
        case gxConstraint::Flex:
            return new gxSizeConstraint( aType, aValue );
        case gxConstraint::Region:
            return new gxRegionConstraint( (gxLayoutRegion::Type)aValue );
            
        default:
            gxWarn( "No constraint of this type found" );
            return NULL;
    }
}