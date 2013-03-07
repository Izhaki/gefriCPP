#include "View/Elements/gxViewElement.h"

gxLayout::gxLayout()
  : mViewElement       ( NULL      ),
    mMajorDistribution ( mdStart   ),
    mMinorSize         ( msElement ),
    mMinorPosition     ( mpMiddle  )
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
    
    ResetRects();
    
    DoMajorDistribution();
    DoMinorSize();
    DoMinorPosition();
}

bool IndexCompare( gxViewElement* aL, gxViewElement* aR )
{
    return aL->GetIndex() < aR->GetIndex();
}

void gxLayout::ResetRects()
{
    DataIterator   iPair;
    gxRect         iRect;
    gxViewElement* iChild;
    
    std::sort( mData.begin(), mData.end(), IndexCompare );
    
    for ( iPair = mData.begin(); iPair != mData.end(); ++iPair )
    {
        gxLayoutData& iData = iPair->second;
        
        iChild = iPair->first;
        
        iRect  = iData.Rect;
        iChild->SetBounds( iRect );
    }
    
//    std::sort( mData.begin(), mData.end() );
}

void gxLayout::DoMajorDistribution()
{
    DataIterator   iPair;
    gxRect         iRect;    
    gxViewElement* iChild;
    gxPix          iChildWidth;

//    int   iElementCount = mData.size();
    int   iTotalWidth   = 0;
    gxPix iPosition     = 0;
    
    for ( iPair = mData.begin(); iPair != mData.end(); ++iPair )
    {
        iChild = iPair->first;
        
        iTotalWidth += iChild->GetBounds().GetWidth();
    }
    
    for ( iPair = mData.begin(); iPair != mData.end(); ++iPair )
    {
        iChild = iPair->first;
        
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
            default:
                break;
        }
    }
}

void gxLayout::DoMinorSize()
{
    if ( mMinorSize == msElement )
        return;
    
    DataIterator   iPair;
    gxRect         iRect;
    gxViewElement* iChild;
    gxPix          iHeight = 0;
    
    if ( mMinorSize == msFull )
    {
        
        iHeight = mViewElement->GetBounds().GetSize().GetHeight();
        
    } else if ( mMinorSize == msMax ) {
        
        gxPix iChildHeight;
        
        // Find the maximum height
        for ( iPair = mData.begin(); iPair != mData.end(); ++iPair )
        {
            iChild = iPair->first;
            
            iChildHeight = iChild->GetBounds().GetHeight();
            iHeight = gxMax( iHeight, iChildHeight );
        }
        
    }
        
    for ( iPair = mData.begin(); iPair != mData.end(); ++iPair )
    {
        iChild = iPair->first;
        
        // TODO: won't be easier if view element had setHeight?
        iRect = iChild->GetBounds();
        iRect.SetHeight( iHeight );
        iChild->SetBounds( iRect );
    }
}

void gxLayout::DoMinorPosition()
{
    if ( mMinorPosition == mpElement )
        return;
    
    DataIterator   iPair;
    gxRect         iRect;
    gxViewElement* iChild;
    gxPix          iPosition = 0;
    
    // TODO: would be nice to have a GetHeight() from ViewElement
    gxPix          iContainerHeight = mViewElement->GetBounds().GetSize().GetHeight();

    for ( iPair = mData.begin(); iPair != mData.end(); ++iPair )
    {
        iChild = iPair->first;
        
        iRect = iChild->GetBounds();
        
        if ( mMinorSize == msFull || mMinorPosition == mpStart )
            iPosition = 0;
        else if ( mMinorPosition == mpMiddle )
            iPosition = ( iContainerHeight - iRect.GetHeight() ) / 2;
        else if ( mMinorPosition == mpEnd )
            iPosition = iContainerHeight - iRect.GetHeight();
        
        // TODO: won't be easier if view element had setHeight?
        iRect.SetY( iPosition );
        iChild->SetBounds( iRect );
    }
}

void gxLayout::SetRect( gxViewElement* aViewElement,
                        gxRect         aRect )
{
    mData[ aViewElement ].Rect = aRect;
    
}

