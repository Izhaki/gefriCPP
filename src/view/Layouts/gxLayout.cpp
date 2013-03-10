#include "View/Layouts/gxLayout.h"
#include "View/Elements/gxViewElement.h"

gxLayout::gxLayout()
  : mViewElement ( NULL ),
    mOnMajorAxis ( true )
{
}

gxLayout::gxLayout( bool aOnMajorAxis )
: mViewElement ( NULL         ),
  mOnMajorAxis ( aOnMajorAxis )
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
    if ( !mViewElement )
        return;
    
    Init();
    
    DoLayout();
    
    Apply();
    
}

bool IndexCompare( gxConstraints* aL, gxConstraints* aR )
{
    return aL->Element->GetIndex() < aR->Element->GetIndex();
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

gxConstraints* gxLayout::GetConstraints( gxViewElement* aElement )
{
    // Search for the element in our list.
    gxConstraints::Iterator iIter = std::find_if( mConstraints.begin(),
                                                  mConstraints.end(),
                                                  ElementFinder( aElement ) );
    
    bool           iFound = iIter != mConstraints.end();
    gxConstraints* iConstraints;
    
    if ( iFound )
    {
        iConstraints = *iIter;
    } else {
        // If layout data was not found, create one
        iConstraints = new gxConstraints( aElement );
        
        // An initiate the rect using the element's bounds
        iConstraints->Rect = aElement->GetBounds();
        
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

void gxLayout::SetRect( gxViewElement* aViewElement,
                        gxRect         aRect )
{
    gxConstraints* iConstraints = GetConstraints( aViewElement );
    iConstraints->Rect = aRect;
    
    aViewElement->Invalidate();
}

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