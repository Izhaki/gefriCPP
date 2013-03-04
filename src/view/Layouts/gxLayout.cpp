#include "View/Elements/gxViewElement.h"

void gxLayout::Layout( gxViewElement* aViewElement )
{
    forEachChildOf( aViewElement, aChild )
    {
        if ( gxFoundInMap( mRects, aChild ) )
        {
            gxLog("Layout Request" );
            aChild->SetBounds( mRects[ aChild ] );
        }
    }
    // aViewElement->GetChildrenItterator();
//    gxLog("Layout Request" );
}

void gxLayout::SetRect( gxViewElement* aViewElement,
                        gxRect         aRect )
{
//    if ( gxFoundInMap( mRects, aViewElement ) )
//        return;
    
    mRects[ aViewElement ] = aRect;
    
    // gxRect iRect = mRects[ aViewElement ];    
}