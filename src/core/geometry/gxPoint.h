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
    gxPix X, Y;

    gxPoint() : X(0), Y(0) { }
    gxPoint( gxPix aX,
             gxPix aY )
      : X( aX ), Y( aY ) { }

    // no copy ctor or assignment operator - the defaults are ok

    // comparison
    bool operator==( const gxPoint& p ) const
    {
        return X == p.X && Y == p.Y;
    }
    
    bool operator!=( const gxPoint& p ) const
    {
        return !( *this == p );
    }

    // arithmetic operations (component wise)
    gxPoint operator+( const gxPoint& p ) const
    {
        return gxPoint( X + p.X, Y + p.Y );
    }

    gxPoint& operator+=( const gxPoint& p )
    {
        X += p.X;
        Y += p.Y;
        return *this;
    }

    gxPoint operator+( const gxSize& s ) const
    {
        return gxPoint( X + s.GetWidth(), Y + s.GetHeight() );
    }
    
    gxPoint& operator+=( const gxSize& s )
    {
        X += s.GetWidth();
        Y += s.GetHeight();
        return *this;
    }
    
    gxPoint operator-( const gxPoint& p ) const
    {
        return gxPoint( X - p.X, Y - p.Y );
    }

    gxPoint& operator-=( const gxPoint& p )
    {
        X -= p.X;
        Y -= p.Y;
        return *this;
    }

    gxPoint operator-( const gxSize& s ) const
    {
        return gxPoint( X - s.GetWidth(), Y - s.GetHeight() );
    }
        
    gxPoint& operator-=( const gxSize& s )
    {
        X -= s.GetWidth();
        Y -= s.GetHeight();
        return *this;
    }
    
    gxPoint operator-() const
    {
        return gxPoint( -X, -Y );
    }
    
    gxPoint operator*( const gxScale& s ) const
    {
        return gxPoint( gxFloor( X * s.X ), gxFloor( Y * s.Y ) );
    }
    
    gxPoint& operator*=( const gxScale& s )
    {
        X = gxFloor( X * s.X);
        Y = gxFloor( Y * s.Y);
        return *this;
    }
    
    bool IsZero() const
    {
        return X == 0 && Y == 0;
    }
    
    bool IsntZero() const
    {
        return X != 0 || Y != 0;
    }
    
    void Reset()
    {
        X = 0;
        Y = 0;
    }
};

#endif // gxPoint_h