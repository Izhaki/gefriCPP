#include "View/Elements/Visual/shapes/gxLine.h"

void gxLine::PaintShape( gxPainter &aPainter )
{
    aPainter.DrawLine( mBounds );
}