#include "View/Layouts/Constraints/gxConstraints.h"

// TODO: Move somewhere else?
template <typename MapType>
void EmptyMap( MapType& aMap )
{
    for ( typename MapType::iterator it = aMap.begin(); it != aMap.end(); ++it )
    {
        delete it->second;
    }
    aMap.clear();
}

gxConstraints::~gxConstraints()
{
    EmptyMap( mConstraints );
}

void gxConstraints::Set( gxConstraintKey& aKey,
                         gxConstraint*    aConstraint  )
{
    // Delete any previous constraint with this key
    delete mConstraints[ aKey ];
    
    // Set a new one
    mConstraints[ aKey ] = aConstraint;
}

gxConstraint* gxConstraints::Get( const gxConstraintKey& aKey ) const
{
    ConstIterator iConstraint = mConstraints.find( aKey );
    bool iFound = iConstraint != mConstraints.end();
    
    return iFound ? iConstraint->second : NULL;
}

gxConstraints::Map gxConstraints::Get( gxConstraintId aId )
{
    Map iFiltered;
    forEachConstraint( mConstraints, iConstraint )
    {
        if ( iConstraint->first.mConstraintId == aId )
        {
            iFiltered[iConstraint->first] = iConstraint->second;
        }
    }
    return iFiltered;
}

gxLayoutRegion::Type gxConstraints::GetRegion( gxViewElement* aLayoutee )
{
    gxRegionConstraint* iRegionConstraint = NULL;
    
    Get( aLayoutee, iRegionConstraint );
    
    if ( iRegionConstraint )
    {
        return iRegionConstraint->GetValue();
    } else {
        gxWarn( "No region constraint found" );
        return gxLayoutRegion::Center;
    }
}

int gxConstraints::GetFlex( gxViewElement* aLayoutee,
                            bool           aOnMajorAxis )
{
    gxSizeConstraint* iSizeConstraint = NULL;
    
    Get( aLayoutee, iSizeConstraint, aOnMajorAxis );
    
    if ( iSizeConstraint && iSizeConstraint->IsFlex() )
    {
        return iSizeConstraint->GetValue();
    } else {
        return 0;
    }
}
