#include "view/elements/visual/shapes/gxRectangle.h"

void gxRectangle::PaintShape(gxPainter &aPainter)
{
  aPainter.DrawRectangle(mBounds);
}