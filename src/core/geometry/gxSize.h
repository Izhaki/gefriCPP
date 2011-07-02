/////////////////////////////////////////////////////////////////////////////
// Source copied in its majority from the wxWidgets library
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef gxSize_h
#define gxSize_h

#include "core/geometry/gxGeometry.h"

class gxSize
{
public:
  // members are public for compatibility, don't use them directly.
  int x, y;

  // constructors
  gxSize() : x(0), y(0) { }
  gxSize(int xx, int yy) : x(xx), y(yy) { }

  // no copy ctor or assignment operator - the defaults are ok

  bool operator==(const gxSize& sz) const { return x == sz.x && y == sz.y; }
  bool operator!=(const gxSize& sz) const { return x != sz.x || y != sz.y; }

  gxSize operator+(const gxSize& sz) const { return gxSize(x + sz.x, y + sz.y); }
  gxSize operator-(const gxSize& sz) const { return gxSize(x - sz.x, y - sz.y); }
  gxSize operator/(int i) const { return gxSize(x / i, y / i); }
  gxSize operator*(int i) const { return gxSize(x * i, y * i); }

  gxSize& operator+=(const gxSize& sz) { x += sz.x; y += sz.y; return *this; }
  gxSize& operator-=(const gxSize& sz) { x -= sz.x; y -= sz.y; return *this; }
  gxSize& operator/=(const int i) { x /= i; y /= i; return *this; }
  gxSize& operator*=(const int i) { x *= i; y *= i; return *this; }

  void IncTo(const gxSize& sz)
    { if ( sz.x > x ) x = sz.x; if ( sz.y > y ) y = sz.y; }
  void DecTo(const gxSize& sz)
    { if ( sz.x < x ) x = sz.x; if ( sz.y < y ) y = sz.y; }

  void IncBy(int dx, int dy) { x += dx; y += dy; }
  void IncBy(const gxSize& sz) { IncBy(sz.x, sz.y); }
  void IncBy(int d) { IncBy(d, d); }

  void DecBy(int dx, int dy) { IncBy(-dx, -dy); }
  void DecBy(const gxSize& sz) { DecBy(sz.x, sz.y); }
  void DecBy(int d) { DecBy(d, d); }


  gxSize& Scale(float xscale, float yscale)
    { x = (int)(x*xscale); y = (int)(y*yscale); return *this; }

  // accessors
  void Set(int xx, int yy) { x = xx; y = yy; }
  void SetWidth(int w) { x = w; }
  void SetHeight(int h) { y = h; }

  int GetWidth() const { return x; }
  int GetHeight() const { return y; }

  bool IsFullySpecified() const { return x != gxDefaultCoord && y != gxDefaultCoord; }

  // combine this size with the other one replacing the default (i.e. equal
  // to gxDefaultCoord) components of this object with those of the other
  void SetDefaults(const gxSize& size)
  {
    if ( x == gxDefaultCoord )
      x = size.x;
    if ( y == gxDefaultCoord )
      y = size.y;
  }

  // compatibility
  int GetX() const { return x; }
  int GetY() const { return y; }
};

#endif // gxSize_h