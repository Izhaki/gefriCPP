#include "View/Layouts/gxConstraintLayout.h"
#include "View/Elements/gxViewElement.h"

gxConstraintLayout::gxConstraintLayout()
{
}

gxConstraintLayout::gxConstraintLayout( bool aOnMajorAxis ):
    gxLayout( aOnMajorAxis )
{
}

gxConstraintLayout::~gxConstraintLayout()
{
    // Empty the layout data list
    while( !mConstraineds.empty() )
    {
        delete mConstraineds.front(), mConstraineds.pop_front();
    }
}

void gxConstraintLayout::Init()
{
    forEachConstrained( iConstrained )
    {
        (*iConstrained)->ResetBounds();
    }
}

void gxConstraintLayout::Apply()
{
    forEachConstrained( iConstrained )
    {
        (*iConstrained)->ApplyBounds();
    }
}

void gxConstraintLayout::SetConstraint( gxViewElement*      aLayoutee,
                                        gxConstraint::Type  aType,
                                        gxConstraint::Value aValue,
                                        bool                aOnMajorAxis )
{
    // Warn if the layout does not accepts the provided constraint type
    gxAssert( IsSupportedConstraint( aType ) , "Constraint type is not accepted by this layout" );
    
    // Get the constrainst of the view element and set the new constraint
    GetConstrained( aLayoutee )->Set( aType, aValue );
    
    gxConstraint* iConstraint = gxConstraint::Create( aType, aValue );
    
    SetConstraint( aLayoutee, iConstraint, aOnMajorAxis );
    
    // Now invalidate the element
    aLayoutee->Invalidate();
}

void gxConstraintLayout::SetConstraint( gxViewElement* aLayoutee,
                                        gxConstraint*  aConstraint,
                                        bool           aOnMajorAxis )
{
    mConstraints.Set( aLayoutee, aConstraint, aOnMajorAxis );
}

gxConstrained* gxConstraintLayout::FindConstrained( gxViewElement* aLayoutee )
{
    // Search for the element in our list.
    gxConstrained::Iterator iIter = std::find_if( mConstraineds.begin(),
                                                  mConstraineds.end(),
                                                  ElementFinder( aLayoutee ) );
    
    bool iFound = iIter != mConstraineds.end();
    
    return iFound ? *iIter : NULL;
}

//!
bool IndexCompare( gxConstrained* aL, gxConstrained* aR )
{
    return aL->mLayoutee->GetIndex() < aR->mLayoutee->GetIndex();
}

//!
void gxConstraintLayout::SortConstraineds()
{
    mConstraineds.sort( IndexCompare );
}

gxConstrained* gxConstraintLayout::GetConstrained( gxViewElement* aLayoutee )
{
    
    gxConstrained* iConstrained = FindConstrained( aLayoutee );
    
    // If the constrained was not found
    if ( iConstrained == NULL )
    {
        // Create one a new constrained
        iConstrained = new gxConstrained( aLayoutee );
        
        // Add it to our data list
        mConstraineds.push_back( iConstrained );
        
        // Now sort the constraineds
        SortConstraineds();
    }
    
    return iConstrained;
}

void gxConstraintLayout::Add( gxViewElement* aLayoutee )
{
    // This will do the job - just add the element if it aint already there.
    GetConstrained( aLayoutee );
}