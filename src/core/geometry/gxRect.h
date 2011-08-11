/////////////////////////////////////////////////////////////////////////////
// Source copied in its majority from the wxWidgets library
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef gxRect_h
#define gxRect_h

#include <vector>
#include "core/geometry/gxGeometry.h"

// forward decleration (for gxRects)
class gxRect;

// definition of gxRects - a vector of gxRect
typedef std::vector< gxRect > gxRects;
typedef gxRects::iterator gxRectsIterator;

class gxRect
{
public:
  gxRect()
    : X(0), Y(0), width(0), height(0)
    { }
  gxRect(gxPix aX, gxPix aY, gxPix aW, gxPix aH)
    : X(aX), Y(aY), width(aW), height(aH)
    { }
  gxRect(const gxPoint& aTopLeft, const gxPoint& aBottomRight);
  gxRect(const gxPoint& aPoint, const gxSize& aSize)
    : X(aPoint.X), Y(aPoint.Y), width(aSize.X), height(aSize.Y)
    { }
  gxRect(const gxSize& aSize)
    : X(0), Y(0), width(aSize.X), height(aSize.Y)
    { }

  // default copy ctor and assignment operators ok

  gxPix GetX() const { return X; }
  void SetX(gxPix aX) { X = aX; }

  gxPix GetY() const { return Y; }
  void SetY(gxPix aY) { Y = aY; }

  gxPix GetWidth() const { return width; }
  void SetWidth(gxPix aW) { width = aW; }

  gxPix GetHeight() const { return height; }
  void SetHeight(gxPix aH) { height = aH; }

  gxPoint GetPosition() const { return gxPoint(X, Y); }
  void SetPosition( const gxPoint &aPoint ) { X = aPoint.X; Y = aPoint.Y; }

  gxSize GetSize() const { return gxSize(width, height); }
  void SetSize( const gxSize &aSize )
    { width = aSize.GetWidth();
      height = aSize.GetHeight();
    }

  bool IsEmpty() const { return (width <= 0) || (height <= 0); }

  gxPix GetLeft()   const { return X; }
  gxPix GetTop()    const { return Y; }
  gxPix GetBottom() const { return Y + height - 1; }
  gxPix GetRight()  const { return X + width - 1; }

  void SetLeft(gxPix aLeft) { X = aLeft; }
  void SetRight(gxPix aRight) { width = aRight - X + 1; }
  void SetTop(gxPix aTop) { Y = aTop; }
  void SetBottom(gxPix aBottom) { height = aBottom - Y + 1; }

  gxPoint GetTopLeft() const { return GetPosition(); }
  gxPoint GetLeftTop() const { return GetTopLeft(); }
  void SetTopLeft(const gxPoint &aPoint) { SetPosition(aPoint); }
  void SetLeftTop(const gxPoint &aPoint) { SetTopLeft(aPoint); }

  gxPoint GetBottomRight() const { return gxPoint(GetRight(), GetBottom()); }
  gxPoint GetRightBottom() const { return GetBottomRight(); }
  void SetBottomRight(const gxPoint &aPoint)
    { SetRight(aPoint.X); SetBottom(aPoint.Y); }
  void SetRightBottom(const gxPoint &aPoint) { SetBottomRight(aPoint); }

  gxPoint GetTopRight() const { return gxPoint(GetRight(), GetTop()); }
  gxPoint GetRightTop() const { return GetTopRight(); }
  void SetTopRight(const gxPoint &aPoint)
    { SetRight(aPoint.X); SetTop(aPoint.Y); }
  void SetRightTop(const gxPoint &aPoint) { SetTopLeft(aPoint); }

  gxPoint GetBottomLeft() const { return gxPoint(GetLeft(), GetBottom()); }
  gxPoint GetLeftBottom() const { return GetBottomLeft(); }
  void SetBottomLeft(const gxPoint &aPoint) { SetLeft(aPoint.X); SetBottom(aPoint.Y); }
  void SetLeftBottom(const gxPoint &aPoint) { SetBottomLeft(aPoint); }

  // operations with rect
  gxRect& Inflate(gxPix dx, gxPix dy);
  gxRect& Inflate(const gxSize& d) { return Inflate(d.X, d.Y); }
  gxRect& Inflate(gxPix d) { return Inflate(d, d); }
  gxRect  Inflate(gxPix dx, gxPix dy) const
  {
    gxRect r = *this;
    r.Inflate(dx, dy);
    return r;
  }

  gxRect& Deflate(gxPix dx, gxPix dy) { return Inflate(-dx, -dy); }
  gxRect& Deflate(const gxSize& d) { return Inflate(-d.X, -d.Y); }
  gxRect& Deflate(gxPix d) { return Inflate(-d); }
  gxRect Deflate(gxPix dx, gxPix dy) const
  {
    gxRect r = *this;
    r.Deflate(dx, dy);
    return r;
  }

  void Offset(gxPix dx, gxPix dy) { X += dx; Y += dy; }
  void Offset(const gxPoint& aPoint) { Offset(aPoint.X, aPoint.Y); }

  gxRect& Intersect(const gxRect& aRect);
  gxRect Intersect(const gxRect& aRect) const
  {
    gxRect r = *this;
    r.Intersect(aRect);
    return r;
  }

  gxRect& Union(const gxRect& aRect);
  gxRect Union(const gxRect& aRect) const
  {
    gxRect iRect = *this;
    iRect.Union(aRect);
    return iRect;
  }

  // compare rectangles
  bool operator==(const gxRect& aRect) const;
  bool operator!=(const gxRect& aRect) const { return !(*this == aRect); }

  // return true if the point is (not strcitly) inside the rect
  bool Contains(gxPix X, gxPix Y) const;
  bool Contains(const gxPoint& aPoint) const { return Contains(aPoint.X, aPoint.Y); }
  // return true if the rectangle is (not strcitly) inside the rect
  bool Contains(const gxRect& aRect) const;

  // return true if the rectangles have a non empty intersection
  bool Intersects(const gxRect& aRect) const;

  // these are like Union() but don't ignore empty rectangles
  gxRect operator+(const gxRect& aRect) const;
  gxRect& operator+=(const gxRect& aRect)
  {
    *this = *this + aRect;
    return *this;
  }


  // centre this rectangle in the given (usually, but not necessarily,
  // larger) one
  gxRect CentreIn(const gxRect& aRect, int dir = gxBOTH) const
  {
    return gxRect(dir & gxHORIZONTAL ? aRect.X + (aRect.width - width)/2 : X,
      dir & gxVERTICAL ? aRect.Y + (aRect.height - height)/2 : Y,
      width, height);
  }

  gxRect CenterIn(const gxRect& aRect, int dir = gxBOTH) const
  {
    return CentreIn(aRect, dir);
  }
  
  /**
   * @brief Scales the rect by the given factors.
   * @param aScaleX The X scale factor
   * @param aScaleY The Y scale factor
   */
  void Scale(float aScaleX, float aScaleY);

public:
  gxPix X, Y, width, height;
};

#endif // gxRect_h