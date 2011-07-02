/////////////////////////////////////////////////////////////////////////////
// Source copied in its majority from the wxWidgets library
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef gxPoint_h
#define gxPoint_h

#include "core/geometry/gxGeometry.h"

class gxPoint
{
public:
  int x, y;

  gxPoint() : x(0), y(0) { }
  gxPoint(int xx, int yy) : x(xx), y(yy) { }

  // no copy ctor or assignment operator - the defaults are ok

  // comparison
  bool operator==(const gxPoint& p) const { return x == p.x && y == p.y; }
  bool operator!=(const gxPoint& p) const { return !(*this == p); }

  // arithmetic operations (component wise)
  gxPoint operator+(const gxPoint& p) const { return gxPoint(x + p.x, y + p.y); }
  gxPoint operator-(const gxPoint& p) const { return gxPoint(x - p.x, y - p.y); }

  gxPoint& operator+=(const gxPoint& p) { x += p.x; y += p.y; return *this; }
  gxPoint& operator-=(const gxPoint& p) { x -= p.x; y -= p.y; return *this; }

  gxPoint& operator+=(const gxSize& s) { x += s.GetWidth(); y += s.GetHeight(); return *this; }
  gxPoint& operator-=(const gxSize& s) { x -= s.GetWidth(); y -= s.GetHeight(); return *this; }

  gxPoint operator+(const gxSize& s) const { return gxPoint(x + s.GetWidth(), y + s.GetHeight()); }
  gxPoint operator-(const gxSize& s) const { return gxPoint(x - s.GetWidth(), y - s.GetHeight()); }

  gxPoint operator-() const { return gxPoint(-x, -y); }
};

#endif // gxPoint_h