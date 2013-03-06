#include "View/Elements/gxViewElement.h"

gxLayout::gxLayout()
  : mViewElement( NULL ),
    mMinorSize( Original ),
    mMinorPosition ( Middle )
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
    
    ResetRects();
    DoMinorSize();
    DoMinorPosition();
}

void gxLayout::ResetRects()
{
    tRectsIterator iPair;
    gxRect         iRect;
    gxViewElement* iChild;
    
    for ( iPair = mRects.begin(); iPair != mRects.end(); ++iPair )
    {
        iChild = iPair->first;
        iRect  = iPair->second;
        
        iChild->SetBounds( iRect );
    }
}

void gxLayout::DoMinorSize()
{
    if ( mMinorSize == Original )
        return;
    
    tRectsIterator iPair;
    gxRect         iRect;
    gxViewElement* iChild;
    gxPix          iHeight = 0;
    
    if ( mMinorSize == Full )
    {
        
        iHeight = mViewElement->GetBounds().GetSize().GetHeight();
        
    } else if ( mMinorSize == Max ) {
        
        gxPix iChildHeight;
        
        // Find the maximum height
        for ( iPair = mRects.begin(); iPair != mRects.end(); ++iPair )
        {
            iChild = iPair->first;
            
            iChildHeight = iChild->GetBounds().GetHeight();
            iHeight = gxMax( iHeight, iChildHeight );
        }
        
    }
        
    for ( iPair = mRects.begin(); iPair != mRects.end(); ++iPair )
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
    if ( mMinorPosition == NoChange )
        return;
    
    tRectsIterator iPair;
    gxRect         iRect;
    gxViewElement* iChild;
    gxPix          iPosition = 0;
    
    // TODO: would be nice to have a GetHeight() from ViewElement
    gxPix          iContainerHeight = mViewElement->GetBounds().GetSize().GetHeight();

    for ( iPair = mRects.begin(); iPair != mRects.end(); ++iPair )
    {
        iChild = iPair->first;
        
        iRect = iChild->GetBounds();
        
        if ( mMinorSize == Full || mMinorPosition == Start )
            iPosition = 0;
        else if ( mMinorPosition == Middle )
            iPosition = ( iContainerHeight - iRect.GetHeight() ) / 2;
        else if ( mMinorPosition == End )
            iPosition = iContainerHeight - iRect.GetHeight();
        
        // TODO: won't be easier if view element had setHeight?
        iRect.SetY( iPosition );
        iChild->SetBounds( iRect );
    }
}

void gxLayout::SetRect( gxViewElement* aViewElement,
                        gxRect         aRect )
{
    mRects[ aViewElement ] = aRect;
}

