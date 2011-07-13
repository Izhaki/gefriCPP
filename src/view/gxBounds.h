#ifndef gxBounds_h
#define gxBounds_h

#include "core/geometry/gxRect.h"

/**
 * @brief A class similar to gxRect, but with an added flag denoting whether
 * the bounds are those of a structural element.
 * 
 * Structural bounds are used with structural view elements and are not subject
 * to some transformations, like scaling or scrolling.
 */
class gxBounds: public gxRect
{
public:
  /**
  * @brief True means that the bounds are structural ones.
  */
  bool Structural;

  gxBounds()
    : gxRect(),
    Structural(false)
    { }
  gxBounds(int xx, int yy, int ww, int hh)
    : gxRect(xx, yy, ww, hh),
    Structural(false)
    { }
  gxBounds(const gxPoint& topLeft, const gxPoint& bottomRight)
    : gxRect (topLeft, bottomRight),
    Structural(false)
    { }
  gxBounds(const gxPoint& pt, const gxSize& size)
    : gxRect (pt, size),
    Structural(false)
    { }
  gxBounds(const gxSize& size)
    : gxRect (size),
    Structural(false)
    { }
    
  gxBounds & operator=(const gxRect &rect)
  {
    x = rect.x;
    y = rect.y;
    width = rect.width;
    height = rect.height;
  }
};

#endif // gxBounds_h