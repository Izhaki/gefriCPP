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
    : x(0), y(0), width(0), height(0)
    { }
  gxRect(int xx, int yy, int ww, int hh)
    : x(xx), y(yy), width(ww), height(hh)
    { }
  gxRect(const gxPoint& topLeft, const gxPoint& bottomRight);
  gxRect(const gxPoint& pt, const gxSize& size)
    : x(pt.x), y(pt.y), width(size.x), height(size.y)
    { }
  gxRect(const gxSize& size)
    : x(0), y(0), width(size.x), height(size.y)
    { }

  // default copy ctor and assignment operators ok

  int GetX() const { return x; }
  void SetX(int xx) { x = xx; }

  int GetY() const { return y; }
  void SetY(int yy) { y = yy; }

  int GetWidth() const { return width; }
  void SetWidth(int w) { width = w; }

  int GetHeight() const { return height; }
  void SetHeight(int h) { height = h; }

  gxPoint GetPosition() const { return gxPoint(x, y); }
  void SetPosition( const gxPoint &p ) { x = p.x; y = p.y; }

  gxSize GetSize() const { return gxSize(width, height); }
  void SetSize( const gxSize &s ) { width = s.GetWidth(); height = s.GetHeight(); }

  bool IsEmpty() const { return (width <= 0) || (height <= 0); }

  int GetLeft()   const { return x; }
  int GetTop()    const { return y; }
  int GetBottom() const { return y + height - 1; }
  int GetRight()  const { return x + width - 1; }

  void SetLeft(int left) { x = left; }
  void SetRight(int right) { width = right - x + 1; }
  void SetTop(int top) { y = top; }
  void SetBottom(int bottom) { height = bottom - y + 1; }

  gxPoint GetTopLeft() const { return GetPosition(); }
  gxPoint GetLeftTop() const { return GetTopLeft(); }
  void SetTopLeft(const gxPoint &p) { SetPosition(p); }
  void SetLeftTop(const gxPoint &p) { SetTopLeft(p); }

  gxPoint GetBottomRight() const { return gxPoint(GetRight(), GetBottom()); }
  gxPoint GetRightBottom() const { return GetBottomRight(); }
  void SetBottomRight(const gxPoint &p) { SetRight(p.x); SetBottom(p.y); }
  void SetRightBottom(const gxPoint &p) { SetBottomRight(p); }

  gxPoint GetTopRight() const { return gxPoint(GetRight(), GetTop()); }
  gxPoint GetRightTop() const { return GetTopRight(); }
  void SetTopRight(const gxPoint &p) { SetRight(p.x); SetTop(p.y); }
  void SetRightTop(const gxPoint &p) { SetTopLeft(p); }

  gxPoint GetBottomLeft() const { return gxPoint(GetLeft(), GetBottom()); }
  gxPoint GetLeftBottom() const { return GetBottomLeft(); }
  void SetBottomLeft(const gxPoint &p) { SetLeft(p.x); SetBottom(p.y); }
  void SetLeftBottom(const gxPoint &p) { SetBottomLeft(p); }

  // operations with rect
  gxRect& Inflate(gxCoord dx, gxCoord dy);
  gxRect& Inflate(const gxSize& d) { return Inflate(d.x, d.y); }
  gxRect& Inflate(gxCoord d) { return Inflate(d, d); }
  gxRect Inflate(gxCoord dx, gxCoord dy) const
  {
    gxRect r = *this;
    r.Inflate(dx, dy);
    return r;
  }

  gxRect& Deflate(gxCoord dx, gxCoord dy) { return Inflate(-dx, -dy); }
  gxRect& Deflate(const gxSize& d) { return Inflate(-d.x, -d.y); }
  gxRect& Deflate(gxCoord d) { return Inflate(-d); }
  gxRect Deflate(gxCoord dx, gxCoord dy) const
  {
    gxRect r = *this;
    r.Deflate(dx, dy);
    return r;
  }

  void Offset(gxCoord dx, gxCoord dy) { x += dx; y += dy; }
  void Offset(const gxPoint& pt) { Offset(pt.x, pt.y); }

  gxRect& Intersect(const gxRect& rect);
  gxRect Intersect(const gxRect& rect) const
  {
    gxRect r = *this;
    r.Intersect(rect);
    return r;
  }

  gxRect& Union(const gxRect& rect);
  gxRect Union(const gxRect& rect) const
  {
    gxRect r = *this;
    r.Union(rect);
    return r;
  }

  // compare rectangles
  bool operator==(const gxRect& rect) const;
  bool operator!=(const gxRect& rect) const { return !(*this == rect); }

  // return true if the point is (not strcitly) inside the rect
  bool Contains(int x, int y) const;
  bool Contains(const gxPoint& pt) const { return Contains(pt.x, pt.y); }
  // return true if the rectangle is (not strcitly) inside the rect
  bool Contains(const gxRect& rect) const;

  // return true if the rectangles have a non empty intersection
  bool Intersects(const gxRect& rect) const;

  // these are like Union() but don't ignore empty rectangles
  gxRect operator+(const gxRect& rect) const;
  gxRect& operator+=(const gxRect& rect)
  {
    *this = *this + rect;
    return *this;
  }


  // centre this rectangle in the given (usually, but not necessarily,
  // larger) one
  gxRect CentreIn(const gxRect& r, int dir = gxBOTH) const
  {
    return gxRect(dir & gxHORIZONTAL ? r.x + (r.width - width)/2 : x,
      dir & gxVERTICAL ? r.y + (r.height - height)/2 : y,
      width, height);
  }

  gxRect CenterIn(const gxRect& r, int dir = gxBOTH) const
  {
    return CentreIn(r, dir);
  }

public:
  int x, y, width, height;
};

#endif // gxRect_h