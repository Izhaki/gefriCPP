#include "View/Elements/Visual/shapes/gxLine.h"

void gxLine::PaintShape( gxPainter &aPainter )
{
    aPainter.DrawLine( mFrom, mTo );
//        aPainter.DrawLine( mBounds );
}

gxRect gxLine::GetBounds() const
{
    gxPoint iTopLeft, iBotRight;
    
    // Ensure we don't get negative width or height
    iTopLeft.X  = gxMin( mFrom.X, mTo.X );
    iBotRight.X = gxMax( mFrom.X, mTo.X );
    iTopLeft.Y  = gxMin( mFrom.Y, mTo.Y );
    iBotRight.Y = gxMax( mFrom.Y, mTo.Y );

    return gxRect( iTopLeft, iBotRight );
}