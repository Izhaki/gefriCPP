#include "View/Layouts/gxLayout.h"
#include "View/Elements/gxViewElement.h"

gxLayout::gxLayout()
  : mViewElement ( NULL ),
    mOnMajorAxis ( true ),
    mLayoutStatus( Invalid )
{
}

gxLayout::gxLayout( bool aOnMajorAxis )
: mViewElement ( NULL         ),
  mOnMajorAxis ( aOnMajorAxis ),
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

void gxLayout::SetViewElement( gxViewElement* aViewElement )
{
    mViewElement = aViewElement;
}

void gxLayout::Layout()
{
    // No point doing a layout if the element was not set or if the layout
    // is already valid.
    if ( !mViewElement || mLayoutStatus == Valid )
        return;
    
    // Mark the layout as in progress
    mLayoutStatus = InProgress;
    
    Init();
    
    DoLayout();
    
    Apply();
    
    // Mark the layout as valid
    mLayoutStatus = Valid;
    
}

void gxLayout::Invalidate( gxViewElement* aViewElement )
{
    // If the layout is in progress or already marked as invalid, do nothing.
    if ( mLayoutStatus != Valid )
        return;
    
    bool iElementPartOfLayout = FindConstraints( aViewElement );
    
    // If the view element is part of my layout, mark me as invalid
    if ( iElementPartOfLayout )
        mLayoutStatus = Invalid;
}

bool IndexCompare( gxConstraints* aL, gxConstraints* aR )
{
    return aL->mElement->GetIndex() < aR->mElement->GetIndex();
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


gxConstraints* gxLayout::FindConstraints( gxViewElement* aElement )
{
    // Search for the element in our list.
    gxConstraints::Iterator iIter = std::find_if( mConstraints.begin(),
                                                  mConstraints.end(),
                                                  ElementFinder( aElement ) );

    if ( iIter == mConstraints.end() )
    {
        return NULL;
    } else {
        return *iIter;
    }
}

gxConstraints* gxLayout::GetConstraints( gxViewElement* aElement )
{

    gxConstraints* iConstraints = FindConstraints( aElement );
    
    if ( iConstraints == NULL )
    {
        // If layout data was not found, create one
        iConstraints = CreateConstraints( aElement );
        
        // An initiate the rect using the element's bounds
//        iConstraints->Rect = aElement->GetBounds();
        
        // Add it to our data list
        mConstraints.push_back( iConstraints );
    }

    return iConstraints;
}

void gxLayout::Add( gxViewElement* aViewElement )
{
    // This will do the job - just add the element if it aint already there.
    GetConstraints( aViewElement );
}

/*
//!
void gxLayout::SetRect( gxViewElement* aViewElement,
                        gxRect         aRect )
{
    gxConstraints* iConstraints = GetConstraints( aViewElement );
    iConstraints->Rect = aRect;
    
    aViewElement->Invalidate();
}
*/

void gxLayout::SetPercent( gxViewElement* aViewElement,
                           short          aPercent )
{
    gxConstraints* iConstraints = GetConstraints( aViewElement );
    
    iConstraints->SetPercent( aPercent );
    
    aViewElement->Invalidate();
}

void gxLayout::SetFlex( gxViewElement* aViewElement,
                        short          aFlex )
{
    gxConstraints* iConstraints = GetConstraints( aViewElement );
    
    iConstraints->SetFlex( aFlex );
    
    aViewElement->Invalidate();
}

void gxLayout::InvalidateElement( gxViewElement* aViewElement )
{
    aViewElement->Invalidate();
}