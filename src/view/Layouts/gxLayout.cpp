#include "View/Elements/gxViewElement.h"
#include "View/Layouts/gxLayout.h"

gxLayout::gxLayout()
  : mViewElement ( NULL      ),
    mDistribute  ( gxDistribute::Equal ),
    mStretch     ( gxStretch::Max     ),
    mAlign       ( gxAlign::Middle     )
{
}

gxLayout::~gxLayout()
{
    // Empty the layout data list
    while( !mData.empty() ) delete mData.front(), mData.pop_front();
}

//while(!foo.empty()) delete foo.front(), foo.pop_front();

void gxLayout::SetViewElement( gxViewElement* aViewElement )
{
    mViewElement = aViewElement;
}

void gxLayout::Layout()
{
    if ( !mViewElement )
        return;
    
    Init();
    
    bool onMajorAxis = true;
    
    gxDistribute( mDistribute,
                  mData,
                  mViewElement->GetInnerBounds(),
                  onMajorAxis );
    
    gxStretch( mStretch,
               mData,
               mViewElement->GetInnerBounds(),
               !onMajorAxis );
    
    gxAlign( mAlign,
             mData,
             mViewElement->GetInnerBounds(),
             !onMajorAxis );
    
    Apply();
    
}

bool IndexCompare( gxLayoutData* aL, gxLayoutData* aR )
{
    return aL->Element->GetIndex() < aR->Element->GetIndex();
}

void gxLayout::SortElements()
{
    mData.sort( IndexCompare );
}

void gxLayout::Init()
{
    gxLayoutData::Iterator iData;
    
    SortElements();
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        (*iData)->Reset();
    }
}

void gxLayout::Apply()
{
    gxLayoutData::Iterator iData;
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        (*iData)->Apply();
    }
}

gxLayoutData* gxLayout::GetDataOf( gxViewElement* aElement )
{
    // Search for the element in our list.
    gxLayoutData::Iterator iIter = std::find_if( mData.begin(),
                                                 mData.end(),
                                                 ElementFinder( aElement ) );
    
    bool          iFound = iIter != mData.end();
    gxLayoutData* iData;
    
    if ( iFound )
    {
        iData = *iIter;
    } else {
        // If layout data was not found, create one
        iData = new gxLayoutData( aElement );
        
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
    gxLayoutData* iData = GetDataOf( aViewElement );
    iData->Rect = aRect;
    
    aViewElement->Invalidate();
}

