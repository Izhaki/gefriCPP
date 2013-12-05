#include "View/Layouts/Constraints/gxConstraints.h"
#include "Core/gxLog.h"

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
    // Delete any previous constraint with this key (this will work fine if the
    // key does not exist as the defualt value will be null, which delete
    // handles well.
    delete mConstraints[ aKey ];
    
    // Set the new one
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
    Map iResult;
    forEachConstraint( mConstraints, iConstraint )
    {
        // If the constraint has the same id as the requested one...
        if ( iConstraint->first.mConstraintId == aId )
        {
            // Add it to the result
            iResult[ iConstraint->first ] = iConstraint->second;
        }
    }
    return iResult;
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

void gxConstraints::Remove( gxViewElement* aLayoutee )
{
    gxViewElement* iLayoutee;
    
    for ( Iterator it = mConstraints.begin(); it != mConstraints.end(); )
    {
        iLayoutee = it->first.mLayoutee;
        if ( iLayoutee == aLayoutee )
        {
            delete it->second;
            mConstraints.erase( it++ );
        } else {
            ++it;
        }
    }
}
