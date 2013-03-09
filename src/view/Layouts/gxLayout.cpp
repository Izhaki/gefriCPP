#include "View/Elements/gxViewElement.h"
#include "View/Layouts/gxLayout.h"

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
    while( !mData.empty() ) delete mData.front(), mData.pop_front();
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

void gxLayout::SortElements()
{
    mData.sort( IndexCompare );
}

void gxLayout::Init()
{
    gxConstraints::Iterator iData;
    
    SortElements();
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        (*iData)->Reset();
    }
}

void gxLayout::Apply()
{
    gxConstraints::Iterator iData;
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        (*iData)->Apply();
    }
}

gxConstraints* gxLayout::GetDataOf( gxViewElement* aElement )
{
    // Search for the element in our list.
    gxConstraints::Iterator iIter = std::find_if( mData.begin(),
                                                 mData.end(),
                                                 ElementFinder( aElement ) );
    
    bool          iFound = iIter != mData.end();
    gxConstraints* iData;
    
    if ( iFound )
    {
        iData = *iIter;
    } else {
        // If layout data was not found, create one
        iData = new gxConstraints( aElement );
        
        // An initiate the rect using the element's bounds
        iData->Rect = aElement->GetBounds();
        
        // Add it to our data list
        mData.push_back( iData );
    }

    return iData;
}

void gxLayout::Add( gxViewElement* aViewElement )
{
    // This will do the job - just add the element if it aint already there.
    GetDataOf( aViewElement );
}

void gxLayout::SetRect( gxViewElement* aViewElement,
                        gxRect         aRect )
{
    gxConstraints* iData = GetDataOf( aViewElement );
    iData->Rect = aRect;
    
    aViewElement->Invalidate();
}

void gxLayout::SetPercent( gxViewElement* aViewElement,
                           short          aPercent )
{
    gxConstraints* iData = GetDataOf( aViewElement );
    
    iData->Ratio.SetPercent( aPercent );
    
    aViewElement->Invalidate();
}

void gxLayout::SetFlex( gxViewElement* aViewElement,
                        short          aFlex )
{
    gxConstraints* iData = GetDataOf( aViewElement );
    
    iData->Ratio.SetFlex( aFlex );
    
    aViewElement->Invalidate();
}