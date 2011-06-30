#include "lightweights/shapes/gxRectangle.h"

void gxRectangle::PaintShape(gxPainter &aPainter)
{
  aPainter.DrawRectangle(mBounds.x, mBounds.y, mBounds.width, mBounds.height);
}