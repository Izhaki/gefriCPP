#include "View/Elements/gxViewElement.h"
#include "View/Layouts/gxLayout.h"

gxLayout::gxLayout()
  : mViewElement       ( NULL      ),
    mMajorDistribution ( mdEqual   ),
    mStretch           ( gxStretch::Full ),
    mAlign             ( gxAlign::Middle  )
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
    
    DoMajorDistribution();
    
    gxStretch( mStretch,
               mData,
               mViewElement->GetInnerBounds() );
    
    gxAlign( mAlign,
             mData,
             mViewElement->GetInnerBounds() );
    
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

void gxLayout::DoMajorDistribution()
{
    gxLayoutData::Iterator iData;
    gxRect                 iRect;
    gxViewElement*         iChild;
    gxPix                  iChildWidth;

    int   iCount         = mData.size();
    int   iElementsWidth = 0;
    gxPix iPosition      = 0;
    gxPix iSpacing       = 0;
    
    // Calulate the total width of all elements
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        iElementsWidth += iChild->GetBounds().GetWidth();
    }
    
    if ( mMajorDistribution == mdMiddle || mMajorDistribution == mdEnd )
    {
        gxPix iContainerWidth = mViewElement->GetInnerBounds().GetWidth();

        // This is right for mdEnd
        iPosition = iContainerWidth - iElementsWidth;
        
        if ( mMajorDistribution == mdMiddle )
            // and that's for mdMiddle
            iPosition = iPosition / 2;
    }
    
    if ( mMajorDistribution == mdFull || mMajorDistribution == mdEqual )
    {
        gxPix iContainerWidth = mViewElement->GetInnerBounds().GetWidth();
        int iSpaceCount;
        
        if ( mMajorDistribution == mdFull )
        {
            // If we're on full distribution the space count is one less than
            // the elements count ( 3 elements get 2 space).
            iSpaceCount = iCount - 1;
            
            // ensure there's at least 1 space.
            if ( iSpaceCount < 1 ) iSpaceCount = 1;
        } else {
            // If we're on equal distribution the space count is one more than
            // the elements count ( 3 elements get 4 space).
            iSpaceCount = iCount + 1;
        }

        iSpacing = ( iContainerWidth - iElementsWidth ) / iSpaceCount;
        
        if ( mMajorDistribution == mdEqual )
            iPosition += iSpacing;
    }
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
        iRect       = iChild->GetBounds();
        iChildWidth = iRect.GetWidth();
        
        iRect.SetX( iPosition );
        iChild->SetBounds( iRect );
        
        switch ( mMajorDistribution )
        {
            case mdStart:
            case mdMiddle:
            case mdEnd:
                iPosition += iChildWidth;
                break;
            case mdFull:
            case mdEqual:
                iPosition += iChildWidth + iSpacing;
                break;
            default:
                break;
        }
    }
}

//void gxLayout::DoMinorSize()
//{
//    if ( mMinorSize == msElement )
//        return;
//    
//    gxLayoutData::Iterator iData;
//    gxRect                 iRect;
//    gxViewElement*         iChild;
//    gxPix                  iHeight = 0;
//    
//    if ( mMinorSize == msFull )
//    {
//        
//        iHeight = mViewElement->GetInnerBounds().GetHeight();
//        
//    } else if ( mMinorSize == msMax ) {
//        // Work out the biggest height
//        
//        gxPix iChildHeight;
//        
//        for ( iData = mData.begin(); iData != mData.end(); ++iData )
//        {
//            iChild = (*iData)->Element;
//            
//            iChildHeight = iChild->GetBounds().GetHeight();
//            iHeight = gxMax( iHeight, iChildHeight );
//        }
//        
//    }
//        
//    for ( iData = mData.begin(); iData != mData.end(); ++iData )
//    {
//        iChild = (*iData)->Element;
//        
//        // TODO: won't be easier if view element had setHeight?
//        iRect = iChild->GetBounds();
//        iRect.SetHeight( iHeight );
//        iChild->SetBounds( iRect );
//    }
//}

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

