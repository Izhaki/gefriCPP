#ifndef gxBounds_h
#define gxBounds_h

#include "core/geometry/gxRect.h"

// char used as 1 byte int
#define gxTransformFlags char

struct gxTransformation
{
  enum
  {
    Translate = 0x01,
    Scroll    = 0x02,
    Scale     = 0x04,
    All       = Translate | Scroll | Scale
  };
};

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
//  bool Structural;


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
    mTransformFlags = gxTransformation::All;
  }
  
  /**
   * @brief Checks if the bounds reject a certain type of transformation.
   * @param aFlags The transformation flags being tested.
   * @return True if the bounds reject the given flag.
   */
  bool Reject(gxTransformFlags aFlags)
  {
    return !(mTransformFlags & aFlags);
  }
  
  /**
   * @brief Exludes the given transformation flag from the bounds.
   * @param aFlags The flag to exclude
   */
  void ExludeFlags(gxTransformFlags aFlags)
  {
    mTransformFlags &= ~aFlags;
  }
  
private:
  gxTransformFlags mTransformFlags;
};

#endif // gxBounds_h