#ifndef gxBounds_h
#define gxBounds_h

#include "core/geometry/gxRect.h"
#include "core/gxFlags.h"

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
  enum TransformFlags
  {
    Translatable       = 0x01,
    Scrollable         = 0x02,
    Scalable           = 0x04,
    FullyTransformable = Translatable | Scrollable | Scalable
  };

  gxBounds()
    : gxRect()
    { Init(); }
  gxBounds(int xx, int yy, int ww, int hh)
    : gxRect(xx, yy, ww, hh)
    { Init(); }
  gxBounds(const gxPoint& topLeft, const gxPoint& bottomRight)
    : gxRect (topLeft, bottomRight)
    { Init(); }
  gxBounds(const gxPoint& pt, const gxSize& size)
    : gxRect (pt, size)
    { Init(); }
  gxBounds(const gxSize& size)
    : gxRect (size)
    { Init(); }
    
  gxBounds & operator=(const gxRect &rect)
  {
    x = rect.x;
    y = rect.y;
    width = rect.width;
    height = rect.height;
  }

  /**
   * @brief Common initializer for all constructors
   */
  virtual void Init()
  {
    mTransformFlags.Set(gxBounds::FullyTransformable);
  }

  gxFlags<gx8Flags> mTransformFlags;
};

#endif // gxBounds_h