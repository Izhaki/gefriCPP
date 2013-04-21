#include "View/Layouts/gxLayout.h"
#include "View/Elements/gxViewElement.h"

gxLayout::gxLayout()
  : mOnMajorAxis ( true ),
    mLayoutStatus( Invalid )
{
}

gxLayout::gxLayout( bool aOnMajorAxis )
: mOnMajorAxis ( aOnMajorAxis ),
  mLayoutStatus( Invalid )
{
}

gxLayout::~gxLayout()
{
    // Empty the layout data list
    while( !mConstraineds.empty() )
    {
        delete mConstraineds.front(), mConstraineds.pop_front();
    }
}

void gxLayout::Layout( gxViewElement* aLayouter )
{
    gxWarnIf( aLayouter == NULL, "No layouter provided" );
    
    // No point doing a layout if the layout is already valid.
    if ( mLayoutStatus == Valid )
        return;
    
    // Mark the layout as in progress
    mLayoutStatus = InProgress;
    
    Init();
    
    DoLayout( aLayouter );
    
    Apply();
    
    // Mark the layout as valid
    mLayoutStatus = Valid;
    
}

void gxLayout::Invalidate( gxViewElement* aLayoutee )
{
    // If the layout is in progress or already marked as invalid, do nothing.
    if ( mLayoutStatus != Valid )
        return;
    
    bool iElementPartOfLayout = FindConstrained( aLayoutee );
    
    // If the view element is part of my layout, mark me as invalid
    if ( iElementPartOfLayout )
        mLayoutStatus = Invalid;
}

bool IndexCompare( gxConstrained* aL, gxConstrained* aR )
{
    return aL->mLayoutee->GetIndex() < aR->mLayoutee->GetIndex();
}

void gxLayout::SortConstraineds()
{
    mConstraineds.sort( IndexCompare );
}

void gxLayout::Init()
{
    forEachConstrained( iConstrained )
    {
        (*iConstrained)->ResetBounds();
    }
}

void gxLayout::Apply()
{
    forEachConstrained( iConstrained )
    {
        (*iConstrained)->ApplyBounds();
    }
}

void gxLayout::SetConstraint( gxViewElement*      aLayoutee,
                              gxConstraint::Type  aType,
                              gxConstraint::Value aValue)
{
    // Warn if the layout does not accepts the provided constraint type
    gxAssert( IsSupportedConstraint( aType ) , "Constraint type is not accepted by this layout" );
    
    // Get the constrainst of the view element and set the new constraint
    GetConstrained( aLayoutee )->Set( aType, aValue );
    
    // Now invalidate the element
    aLayoutee->Invalidate();
}


gxConstrained* gxLayout::FindConstrained( gxViewElement* aLayoutee )
{
    // Search for the element in our list.
    gxConstrained::Iterator iIter = std::find_if( mConstraineds.begin(),
                                                  mConstraineds.end(),
                                                  ElementFinder( aLayoutee ) );
    
    bool iFound = iIter != mConstraineds.end();
    
    return iFound ? *iIter : NULL;
}

gxConstrained* gxLayout::GetConstrained( gxViewElement* aLayoutee )
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

void gxLayout::Add( gxViewElement* aLayoutee )
{
    // This will do the job - just add the element if it aint already there.
    GetConstrained( aLayoutee );
}