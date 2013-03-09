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
    
    gxRect( gxPix aX, gxPix aY, gxPix aW, gxPix aH )
        : X( aX ), Y( aY ), width( aW ), height( aH )
        { }
    
    gxRect( const gxPoint& aTopLeft,
            const gxPoint& aBottomRight );
    
    gxRect( const gxPoint& aPoint,
            const gxSize& aSize )
        : X( aPoint.X ), Y( aPoint.Y ), width( aSize.X ), height( aSize.Y )
        { }
    
    gxRect( const gxSize& aSize )
        : X( 0 ), Y( 0 ), width( aSize.X ), height( aSize.Y )
        { }

    // default copy ctor and assignment operators ok

    gxPix GetX() const
    {
        return X;
    }
    
    void SetX( gxPix aX )
    {
        X = aX;
    }

    gxPix GetY() const
    {
        return Y;
    }
    
    void SetY( gxPix aY )
    {
        Y = aY;
    }

    gxPix GetWidth() const
    {
        return width;
    }
    
    void SetWidth( gxPix aW )
    {
        width = aW;
    }

    gxPix GetHeight() const
    {
        return height;
    }
    
    void SetHeight( gxPix aH )
    {
        height = aH;
    }

    gxPoint GetPosition() const
    {
        return gxPoint(X, Y);
    }
    
    gxPix GetPosition( bool onMajorAxis )
    {
        return onMajorAxis ? GetX() : GetY();
    }
    
    void SetPosition( const gxPoint &aPoint )
    {
        X = aPoint.X;
        Y = aPoint.Y;
    }
    
    void SetPosition( const gxPix aPosition, bool onMajorAxis )
    {
        if ( onMajorAxis )
            X = aPosition;
        else
            Y = aPosition;
    }
    
    gxSize GetSize() const
    {
        return gxSize( width, height );
    }
    
    gxPix GetSize( bool onMajorAxis ) const
    {
        return onMajorAxis ? GetWidth() : GetHeight();
    }
    
    void SetSize( const gxSize &aSize )
    {
        width  = aSize.GetWidth();
        height = aSize.GetHeight();
    }

    void SetSize( const gxPix aSize, bool onMajorAxis )
    {
        if ( onMajorAxis )
            width  = aSize;
        else
            height = aSize;
    }
    
    gxPoint GetCenter() const
    {
        return GetPosition() + GetSize().Scale( 0.5, 0.5 );
    }

    bool IsEmpty() const
    {
        return (width <= 0) || (height <= 0);
    }

    gxPix GetLeft()   const { return X; }
    gxPix GetTop()    const { return Y; }
    gxPix GetBottom() const { return Y + height; }
    gxPix GetRight()  const { return X + width; }

    void SetLeft( gxPix aLeft ) { X = aLeft; }
    void SetRight( gxPix aRight ) { width = aRight - X; }
    void SetTop( gxPix aTop ) { Y = aTop; }
    void SetBottom( gxPix aBottom ) { height = aBottom - Y; }

    gxPoint GetTopLeft() const { return GetPosition(); }
    void SetTopLeft( const gxPoint &aPoint ) { SetPosition( aPoint ); }

    gxPoint GetBottomRight() const
    {
        return gxPoint( GetRight(), GetBottom() );
    }
    
    void SetBottomRight( const gxPoint &aPoint )
    {
        SetRight(  aPoint.X );
        SetBottom( aPoint.Y );
    }
    
    gxPoint GetTopRight() const
    {
        return gxPoint( GetRight(), GetTop() );
    }
    
    void SetTopRight( const gxPoint &aPoint )
    {
        SetRight( aPoint.X );
        SetTop( aPoint.Y );
    }

    gxPoint GetBottomLeft() const
    {
        return gxPoint( GetLeft(), GetBottom() );
    }
    
    void SetBottomLeft( const gxPoint &aPoint )
    {
        SetLeft( aPoint.X );
        SetBottom( aPoint.Y );
    }
    
    // operations with rect
    gxRect& Inflate( gxPix dx,
                     gxPix dy );
    
    gxRect& Inflate( const gxSize& d )
    {
        return Inflate(d.X, d.Y);
    }
    
    gxRect& Inflate( gxPix d )
    {
        return Inflate(d, d);
    }
    
    gxRect  Inflate( gxPix dx,
                     gxPix dy ) const
    {
        gxRect r = *this;
        r.Inflate( dx, dy );
        return r;
    }

    gxRect& Deflate( gxPix dx,
                     gxPix dy )
    {
        return Inflate( -dx, -dy );
    }
    
    gxRect& Deflate( const gxSize& d )
    {
        return Inflate( -d.X, -d.Y );
    }
    
    gxRect& Deflate( gxPix d )
    {
        return Inflate( -d );
    }
    
    gxRect Deflate( gxPix dx, gxPix dy ) const
    {
        gxRect r = *this;
        r.Deflate(dx, dy);
        return r;
    }

    void Translate( gxPix dx,
                    gxPix dy )
    {
        X += dx;
        Y += dy;
    }
    
    // Offsets the rect position
    void Translate( const gxPoint& aPoint )
    {
        Translate( aPoint.X, aPoint.Y );
    }

    gxRect& Intersect( const gxRect& aRect );
    
    gxRect Intersect( const gxRect& aRect ) const
    {
        gxRect r = *this;
        r.Intersect( aRect );
        return r;
    }

    gxRect& Union( const gxRect& aRect );
    gxRect Union( const gxRect& aRect ) const
    {
        gxRect iRect = *this;
        iRect.Union( aRect );
        return iRect;
    }

    // compare rectangles
    bool operator==( const gxRect& aRect ) const;
    bool operator!=( const gxRect& aRect ) const
    {
        return !( *this == aRect );
    }

    // returns true if the point is (not strcitly) inside the rect
    bool Contains( gxPix X,
                   gxPix Y ) const;
    
    bool Contains( const gxPoint& aPoint ) const
    {
        return Contains( aPoint.X, aPoint.Y );
    }
    
    // returns true if the rectangle is (not strcitly) inside the rect
    bool Contains( const gxRect& aRect ) const;

    // returns true if the rectangles have a non empty intersection
    bool Intersects( const gxRect& aRect ) const;

    // these are like Union() but don't ignore empty rectangles
    gxRect operator+( const gxRect& aRect ) const;
    gxRect& operator+=( const gxRect& aRect )
    {
        *this = *this + aRect;
        return *this;
    }

    // centre this rectangle in the given (usually, but not necessarily,
    // larger) one
    gxRect CentreIn( const gxRect& aRect,
                     int   dir = gxBOTH ) const
    {
        return gxRect(
            dir & gxHORIZONTAL ? aRect.X + ( aRect.width  - width  ) / 2 : X,
            dir & gxVERTICAL   ? aRect.Y + ( aRect.height - height ) / 2 : Y,
            width,
            height
        );
    }

    gxRect CenterIn( const gxRect& aRect, int dir = gxBOTH ) const
    {
        return CentreIn( aRect, dir );
    }
  
    /**
     * @brief Scales the rect by the given factors.
     * @param aScaleX The X scale factor
     * @param aScaleY The Y scale factor
     */
    void Scale( float aScaleX,
                float aScaleY );
    
    void Scale( const gxScale aScale );

public:
    gxPix X, Y, width, height;
};

#endif // gxRect_h