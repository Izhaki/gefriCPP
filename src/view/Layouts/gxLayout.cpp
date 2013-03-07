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
    
    Init();
    
    DoMajorDistribution();
    DoMinorSize();
    DoMinorPosition();
}

bool IndexCompare( gxLayoutData* aL, gxLayoutData* aR )
{
    return aL->Element->GetIndex() < aR->Element->GetIndex();
}

void gxLayout::Init()
{
    DataIterator   iData;
    gxRect         iRect;
    gxViewElement* iChild;
    
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
    DataIterator   iData;
    gxRect         iRect;    
    gxViewElement* iChild;
    gxPix          iChildWidth;

//    int   iElementCount = mData.size();
    int   iTotalWidth   = 0;
    gxPix iPosition     = 0;
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
        iTotalWidth += iChild->GetBounds().GetWidth();
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
            default:
                break;
        }
    }
}

void gxLayout::DoMinorSize()
{
    if ( mMinorSize == msElement )
        return;
    
    DataIterator   iData;
    gxRect         iRect;
    gxViewElement* iChild;
    gxPix          iHeight = 0;
    
    if ( mMinorSize == msFull )
    {
        
        iHeight = mViewElement->GetBounds().GetSize().GetHeight();
        
    } else if ( mMinorSize == msMax ) {
        
        gxPix iChildHeight;
        
        // Find the maximum height
        for ( iData = mData.begin(); iData != mData.end(); ++iData )
        {
            iChild = (*iData)->Element;
            
            iChildHeight = iChild->GetBounds().GetHeight();
            iHeight = gxMax( iHeight, iChildHeight );
        }
        
    }
        
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
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
    
    DataIterator   iData;
    gxRect         iRect;
    gxViewElement* iChild;
    gxPix          iPosition = 0;
    
    // TODO: would be nice to have a GetHeight() from ViewElement
    gxPix          iContainerHeight = mViewElement->GetBounds().GetSize().GetHeight();

    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
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


gxLayoutData* gxLayout::GetDataOf( gxViewElement* aElement )
{
    // Search for the element in our list.
    DataIterator  iIter = std::find_if( mData.begin(),
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
    iData->Rect    = aRect;
}

