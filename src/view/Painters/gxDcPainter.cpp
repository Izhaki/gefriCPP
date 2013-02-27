#include "View/Painters/gxDcPainter.h"

gxDcPainter::gxDcPainter( gxPaintDC     *aDc,
                          gxRects const &aDamagedRects )
{
    mDc = aDc;
    mDamagedRects = aDamagedRects;
}

gxRect gxDcPainter::GetClipRect() const
{
    return mDc->GetClippingBox();
}

bool gxDcPainter::NeedsPainting( gxRect const &aRect )
{
    // Transform the rect
    gxRect iRect( aRect );
    Transform( iRect );

    // Get the cliping rect
    gxRect iClipRect = GetClipRect();

    // If the rect is not within the clip rect return false
    if ( !iClipRect.Intersects( iRect ) )
        return false;

    // If the rect intersects with any of the damaged rects return true
    for( unsigned int i = 0; i < mDamagedRects.size(); i++ )
    {
        if ( mDamagedRects[i].Intersects( iRect ) )
            return true;
    }

    return false;
}

void gxDcPainter::IntersectClipArea( gxRect const &aRect )
{
    mDc->SetClippingRegion(aRect);
}

void gxDcPainter::SetAbsoluteClipArea( gxRect const &aRect )
{
    mDc->DestroyClippingRegion();
    mDc->SetClippingRegion( aRect );
}

void gxDcPainter::DoDrawRectangle( gxRect const &aRect )
{
    mDc->DrawRectangle( aRect );
}

void gxDcPainter::DoDrawLine( gxPoint &aFrom,
                              gxPoint &aTo )
{
    mDc->DrawLine( aFrom.X, aFrom.Y, aTo.X, aTo.Y );
}

void gxDcPainter::DoDrawText( gxString &aText,
                              gxPix    &aX,
                              gxPix    &aY,
                              double   aAngle )
{
    if ( aAngle == 0 )
        mDc->DrawText( aText, aX , aY );
    else
        mDc->DrawRotatedText( aText, aX, aY, aAngle );
}

gxSize gxDcPainter::GetTextSize( gxString &aText )
{
    wxSize iSize = mDc->GetTextExtent( aText );
    return gxSize( iSize.x, iSize.y );
}