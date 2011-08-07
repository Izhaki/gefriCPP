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
  int X, Y;

  // constructors
  gxSize() : X(0), Y(0) { }
  gxSize(int aX, int aY) : X(aX), Y(aY) { }

  // no copy ctor or assignment operator - the defaults are ok

  bool operator==(const gxSize& aSize) const { return X == aSize.X && Y == aSize.Y; }
  bool operator!=(const gxSize& aSize) const { return X != aSize.X || Y != aSize.Y; }

  gxSize operator+(const gxSize& aSize) const { return gxSize(X + aSize.X, Y + aSize.Y); }
  gxSize operator-(const gxSize& aSize) const { return gxSize(X - aSize.X, Y - aSize.Y); }
  gxSize operator/(int i) const { return gxSize(X / i, Y / i); }
  gxSize operator*(int i) const { return gxSize(X * i, Y * i); }

  gxSize& operator+=(const gxSize& aSize) { X += aSize.X; Y += aSize.Y; return *this; }
  gxSize& operator-=(const gxSize& aSize) { X -= aSize.X; Y -= aSize.Y; return *this; }
  gxSize& operator/=(const int i) { X /= i; Y /= i; return *this; }
  gxSize& operator*=(const int i) { X *= i; Y *= i; return *this; }

  void IncTo(const gxSize& aSize)
    { if ( aSize.X > X ) X = aSize.X; if ( aSize.Y > Y ) Y = aSize.Y; }
  void DecTo(const gxSize& aSize)
    { if ( aSize.X < X ) X = aSize.X; if ( aSize.Y < Y ) Y = aSize.Y; }

  void IncBy(int dx, int dy) { X += dx; Y += dy; }
  void IncBy(const gxSize& aSize) { IncBy(aSize.X, aSize.Y); }
  void IncBy(int d) { IncBy(d, d); }

  void DecBy(int dx, int dy) { IncBy(-dx, -dy); }
  void DecBy(const gxSize& aSize) { DecBy(aSize.X, aSize.Y); }
  void DecBy(int d) { DecBy(d, d); }


  gxSize& Scale(float aScaleX, float aScaleY)
    { X = (int)(X * aScaleX); Y = (int)(Y * aScaleY); return *this; }

  // accessors
  void Set(int aX, int aY) { X = aX; Y = aY; }
  void SetWidth(int aW) { X = aW; }
  void SetHeight(int aH) { Y = aH; }

  int GetWidth() const { return X; }
  int GetHeight() const { return Y; }

  bool IsFullySpecified() const { return X != gxDefaultCoord && Y != gxDefaultCoord; }

  // combine this size with the other one replacing the default (i.e. equal
  // to gxDefaultCoord) components of this object with those of the other
  void SetDefaults(const gxSize& size)
  {
    if ( X == gxDefaultCoord )
      X = size.X;
    if ( Y == gxDefaultCoord )
      Y = size.Y;
  }

  // compatibility
  int GetX() const { return X; }
  int GetY() const { return Y; }
};

#endif // gxSize_h