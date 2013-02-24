/////////////////////////////////////////////////////////////////////////////
// Source copied in its majority from the wxWidgets library
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#include "core/geometry/gxRect.h"

gxRect::gxRect( const gxPoint& aTopLeft,
                const gxPoint& aBottomRight )
{
    X = aTopLeft.X;
    Y = aTopLeft.Y;
    width  = aBottomRight.X - aTopLeft.X;
    height = aBottomRight.Y - aTopLeft.Y;

    if ( width < 0 )
    {
        width = -width;
        X = aBottomRight.X;
    }
    width++;

    if ( height < 0 )
    {
        height = -height;
        Y = aBottomRight.Y;
    }
    height++;
}

bool gxRect::operator==( const gxRect& aRect ) const
{
    return (
        ( X      == aRect.X      ) &&
        ( Y      == aRect.Y      ) &&
        ( width  == aRect.width  ) &&
        ( height == aRect.height )
    );
}

gxRect gxRect::operator+( const gxRect& aRect ) const
{
    gxPix x1 = gxMin( this->X, aRect.X );
    gxPix y1 = gxMin( this->Y, aRect.Y );
    gxPix y2 = gxMax( Y + height, aRect.height + aRect.Y );
    gxPix x2 = gxMax( X + width, aRect.width + aRect.X );
    return gxRect( x1, y1, x2-x1, y2-y1 );
}

gxRect& gxRect::Union( const gxRect& aRect )
{
    // ignore empty rectangles: union with an empty rectangle shouldn't extend
    // this one to (0, 0)
    if ( !width || !height )
    {
        *this = aRect;
    }
    else if ( aRect.width && aRect.height )
    {
        gxPix x1 = gxMin( X, aRect.X );
        gxPix y1 = gxMin( Y, aRect.Y );
        gxPix y2 = gxMax( Y + height, aRect.height + aRect.Y );
        gxPix x2 = gxMax( X + width, aRect.width + aRect.X );

        X = x1;
        Y = y1;
        width = x2 - x1;
        height = y2 - y1;
    }
    //else: we're not empty and rect is empty

    return *this;
}

gxRect& gxRect::Inflate( gxPix dx,
                         gxPix dy )
{
    if ( -2 * dx > width )
    {
        // Don't allow deflate to eat more width than we have,
        // a well-defined rectangle cannot have negative width.
        X += width/2;
        width = 0;
    } else {
        // The inflate is valid.
        X -= dx;
        width += 2*dx;
    }

    if ( -2 * dy > height )
    {
        // Don't allow deflate to eat more height than we have,
        // a well-defined rectangle cannot have negative height.
        Y += height/2;
        height = 0;
    } else {
        // The inflate is valid.
        Y -= dy;
        height += 2 * dy;
    }

    return *this;
}

bool gxRect::Contains( gxPix cx,
                       gxPix cy ) const
{
    return (
        ( cx >= X ) &&
        ( cy >= Y ) &&
        ( ( cy - Y ) < height ) &&
        ( ( cx - X ) < width )
    );
}

bool gxRect::Contains( const gxRect& aRect ) const
{
    return Contains( aRect.GetTopLeft() ) && Contains( aRect.GetBottomRight() );
}

gxRect& gxRect::Intersect( const gxRect& aRect )
{
    gxPix x2 = GetRight(),
          y2 = GetBottom();

    if ( X < aRect.X )
        X = aRect.X;
    
    if ( Y < aRect.Y )
        Y = aRect.Y;
    
    if ( x2 > aRect.GetRight() )
        x2 = aRect.GetRight();
    
    if ( y2 > aRect.GetBottom() )
        y2 = aRect.GetBottom();

    width  = x2 - X + 1;
    height = y2 - Y + 1;

    if ( width <= 0 || height <= 0 )
    {
        width =
        height = 0;
    }

    return *this;
}

bool gxRect::Intersects( const gxRect& aRect ) const
{
    gxRect iRect = Intersect( aRect );

    // if there is no intersection, both width and height are 0
    return iRect.width != 0;
}

void gxRect::Scale( float aScaleX,
                    float aScaleY )
{
    gxPix originalX = X;
    gxPix originalY = Y;
    
    X = gxFloor( originalX * aScaleX );
    Y = gxFloor( originalY * aScaleY );
    width =  gxFloor( ( originalX + width  ) * aScaleX ) - X;
    height = gxFloor( ( originalY + height ) * aScaleY ) - Y;
}

void gxRect::Scale( const gxScale aScale )
{
    Scale( aScale.X, aScale.Y );
}
