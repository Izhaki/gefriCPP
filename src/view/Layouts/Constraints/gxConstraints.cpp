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

void gxConstraints::Set( gxViewElement* aLayoutee,
                         gxConstraint*  aConstraint,
                         bool           aOnMajorAxis)
{
    gxConstraintKey iKey( aLayoutee, aConstraint->GetType(), aOnMajorAxis );
    Set( iKey, aConstraint );
}


void gxConstraints::Set( gxConstraintKey& aKey,
                         gxConstraint*    aConstraint  )
{
    // Delete any previous constraint with this key
    delete mConstraints[ aKey ];
    
    // Set a new one
    mConstraints[ aKey ] = aConstraint;
}

gxConstraint* gxConstraints::Get( gxConstraintKey& aKey )
{
    Constraints::iterator iConstraint = mConstraints.find( aKey );
    bool iFound = iConstraint != mConstraints.end();
    
    return iFound ? iConstraint->second : NULL;
}