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
    while( !mConstraints.empty() )
    {
        delete mConstraints.front(), mConstraints.pop_front();
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
    
    bool iElementPartOfLayout = FindConstraints( aLayoutee );
    
    // If the view element is part of my layout, mark me as invalid
    if ( iElementPartOfLayout )
        mLayoutStatus = Invalid;
}

bool IndexCompare( gxConstraints* aL, gxConstraints* aR )
{
    return aL->mLayoutee->GetIndex() < aR->mLayoutee->GetIndex();
}

void gxLayout::SortConstraints()
{
    mConstraints.sort( IndexCompare );
}

void gxLayout::Init()
{
    SortConstraints();
    
    forEachConstraint( iConstraints )
    {
        (*iConstraints)->Reset();
    }
}

void gxLayout::Apply()
{
    forEachConstraint( iConstraints )
    {
        (*iConstraints)->Apply();
    }
}

void gxLayout::SetConstraint( gxViewElement*      aLayoutee,
                              gxConstraint::Type  aType,
                              gxConstraint::Value aValue)
{
    // Warn if the layout does not accepts the provided constraint type
    gxAssert( IsSupportedConstraint( aType ) , "Constraint type is not accepted by this layout" );
    
    // Get the constrainst of the view element and set the new constraint
    GetConstraints( aLayoutee )->Set( aType, aValue );
    
    // Now invalidate the element
    aLayoutee->Invalidate();
}


gxConstraints* gxLayout::FindConstraints( gxViewElement* aLayoutee )
{
    // Search for the element in our list.
    gxConstraints::Iterator iIter = std::find_if( mConstraints.begin(),
                                                  mConstraints.end(),
                                                  ElementFinder( aLayoutee ) );
    
    bool iFound = iIter != mConstraints.end();
    
    return iFound ? *iIter : NULL;
}

gxConstraints* gxLayout::GetConstraints( gxViewElement* aLayoutee )
{

    gxConstraints* iConstraints = FindConstraints( aLayoutee );
    
    if ( iConstraints == NULL )
    {
        // If layout data was not found, create one
        iConstraints = new gxConstraints( aLayoutee );
                
        // Add it to our data list
        mConstraints.push_back( iConstraints );
    }

    return iConstraints;
}

void gxLayout::Add( gxViewElement* aLayoutee )
{
    // This will do the job - just add the element if it aint already there.
    GetConstraints( aLayoutee );
}