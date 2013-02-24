#include "view/gxDcPainter.h"

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

void gxDcPainter::DrawRectangle( gxPix aX,
                                 gxPix aY,
                                 gxPix aW,
                                 gxPix aH )
{
    gxRect iRect( aX, aY, aW, aH );
    Transform( iRect );
    mDc->DrawRectangle( iRect );
}

void gxDcPainter::DrawRectangle( gxRect const &aRect )
{
    gxRect iRect(aRect);
    Transform(iRect);
    mDc->DrawRectangle( iRect );
}

void gxDcPainter::DrawLine( gxPix x1,
                            gxPix y1,
                            gxPix x2,
                            gxPix y2,
                            bool  isHorizontal )
{
    gxPoint iFrom = isHorizontal ? gxPoint( x1, y1 ) : gxPoint( y1, x1 );
    gxPoint iTo = isHorizontal ? gxPoint( x2, y2 ) : gxPoint( y2, x2 );
    Transform( iFrom );
    Transform( iTo );
    mDc->DrawLine( iFrom.X, iFrom.Y, iTo.X, iTo.Y );
}

void gxDcPainter::DrawText( gxString &aText,
                            gxPix    aX,
                            gxPix    aY )
{
    gxPoint iPoint( aX, aY );
    Transform( iPoint );
    mDc->DrawText( aText, iPoint.X , iPoint.Y );
}

void gxDcPainter::DrawText( gxString &aText,
                            gxPix    aX,
                            gxPix    aY,
                            gxPix    aPadX,
                            gxPix    aPadY,
                            bool     isHorizontal )
{
    gxPoint iPoint = isHorizontal ? gxPoint( aX, aY ) : gxPoint( aY, aX );

    Transform(iPoint);
  
    iPoint.X += aPadX;
    iPoint.Y += aPadY;

    if ( isHorizontal )
    {
        mDc->DrawText( aText, iPoint.X , iPoint.Y );
    } else {
        // Text rotation is done with the top left point as origion,
        // so make the old top right the new top left
        iPoint.Y = iPoint.Y + GetTextSize( aText ).X;
        mDc->DrawRotatedText( aText, iPoint.X, iPoint.Y, 90 );
  }
}

void gxDcPainter::DrawRotatedText( gxString &aText,
                                   gxPix    aX,
                                   gxPix    aY,
                                   double   aAngle )
{
    gxPoint iPoint( aX, aY );
    Transform( iPoint );
    mDc->DrawRotatedText( aText, iPoint.X + 3, iPoint.Y, aAngle );
}

gxSize gxDcPainter::GetTextSize( gxString &aText )
{
    wxSize iSize = mDc->GetTextExtent( aText );
    return gxSize( iSize.x, iSize.y );
}