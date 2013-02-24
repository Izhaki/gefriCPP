#ifndef gxShape_h
#define gxShape_h

#include "view/elements/visual/gxVisual.h"

/**
 * @brief A {@link gxViewElement visual element} that is drawn on screen
 * and represents some shape. Rectangles, circles, lines and the likes.
 *
 * Shapes drawing involves pens and brushes that can be set dynamically to
 * determine the line and fill styles for the shape.
 *
 * Subclasses should not override {@link gxShape::PaintSelf PaintSelf()},
 * but override {@link gxShape::PaintShape PaintShape()} instead.
 */
class gxShape: public gxVisual
{
public:
  gxShape() {}
  gxShape(const gxRect &aBounds)
    : gxVisual(aBounds) { }
protected:
  void PaintSelf(gxPainter &aPainter);
  /**
   * @brief Paints the shape 
   * @param aPainter The painter used for drawing.
   */
  virtual void PaintShape(gxPainter &aPainter) = 0;
};

#endif // gxShape_h