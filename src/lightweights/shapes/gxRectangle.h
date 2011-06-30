#ifndef gxRectangle_h
#define gxRectangle_h

#include "lightweights/shapes/gxShape.h"

/**
 * @brief A rectanglular shape.
 */
class gxRectangle: public gxShape
{
public:
  gxRectangle() {}
  gxRectangle(const gxRect &aBounds)
    : gxShape(aBounds) {}

protected:
  virtual void PaintShape(gxPainter &aPainter);
};

#endif // gxRectangle_h