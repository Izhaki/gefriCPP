#include "View/Elements/gxViewElement.h"
#include "View/Layouts/gxLayout.h"

gxLayout::gxLayout()
  : mViewElement ( NULL      ),
    mDistribute  ( gxDistribute::Equal ),
    mStretch     ( gxStretch::None     ),
    mAlign       ( gxAlign::Middle     )
{
}

void gxLayout::SetViewElement( gxViewElement* aViewElement )
{
    mViewElement = aViewElement;
}

void gxLayout::Layout()
{
    if ( !mViewElement )
        return;

    // TODO: Suspend Validation, or use temp rects
    // Also, shall we cache?
    
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
    
}

bool IndexCompare( gxLayoutData* aL, gxLayoutData* aR )
{
    return aL->Element->GetIndex() < aR->Element->GetIndex();
}

void gxLayout::Init()
{
    gxLayoutData::Iterator iData;
    gxRect                 iRect;
    gxViewElement*         iChild;
    
    // Sort the layout data list based on the element index
    mData.sort( IndexCompare );
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        iRect  = (*iData)->Rect;
        
        // Reset the elements' rects
        iChild->SetBounds( iRect );
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
        // TODO: we need to delete this when destroying the layout.
        iData = new gxLayoutData( aElement );
        mData.push_back( iData );
    }

    return iData;
}

void gxLayout::SetRect( gxViewElement* aViewElement,
                        gxRect         aRect )
{
    gxLayoutData* iData = GetDataOf( aViewElement );
    iData->Rect = aRect;
    
    aViewElement->Invalidate();
}

