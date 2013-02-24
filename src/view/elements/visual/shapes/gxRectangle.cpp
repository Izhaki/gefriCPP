#include "View/Elements/Visual/shapes/gxRectangle.h"

void gxRectangle::PaintShape( gxPainter &aPainter )
{
    aPainter.DrawRectangle( mBounds );
}