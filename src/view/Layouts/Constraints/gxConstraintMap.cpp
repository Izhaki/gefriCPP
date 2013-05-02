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

gxConstraintMap::MapId gxConstraintMap::GetMapId( gxConstraint::Type aType,
                                                  bool               aOnMajorAxis)
{
    return aOnMajorAxis ? aType : -aType;
}

void gxConstraintMap::Add( gxConstraint::Type  aType,
                           gxConstraint::Value aValue,
                           bool                aOnMajorAxis )
{
    gxConstraint* iConstraint = gxConstraint::Create( aType, aValue );
    
    MapId         iMapId      = GetMapId( iConstraint->GetType(), aOnMajorAxis );
    
    Add( iMapId, iConstraint );
}

gxConstraint* gxConstraintMap::Get( gxConstraint::Type aType,
                                    bool aOnMajorAxis )
{
    MapId aMapId = GetMapId( aType, aOnMajorAxis );
    return Get( aMapId );
}

gxConstraint* gxConstraintMap::Get( MapId aId )
{
    ConstraintMap::iterator iConstraint = mConstraintMap.find( aId );
    bool iFound = iConstraint != mConstraintMap.end();
    
    return iFound ? iConstraint->second : NULL;
}

void gxConstraintMap::Add( MapId         aId,
                           gxConstraint* aConstraint )
{
    // If there's already a constraint, delete its contents.
    if ( Get( aId ) )
        delete mConstraintMap[ aId ];
    
    mConstraintMap[ aId ] = aConstraint;
}