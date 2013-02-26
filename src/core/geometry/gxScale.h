#ifndef gxScale_h
#define gxScale_h

#include "core/geometry/gxGeometry.h"
/**
 * @brief A structures containing the values for scale transformations
 */
struct gxScale
{
    float X, Y;
    
    gxScale() : X( 1.0 ), Y( 1.0 ) { }
    gxScale( float aX,
             float aY )
    : X( aX ), Y( aY ) { }

    bool operator==( const gxScale& aScale ) const
    {
        return X == aScale.X && Y == aScale.Y;
    }
    
    bool operator!=( const gxScale& aScale ) const
    {
        return X != aScale.X || Y != aScale.Y;
    }
    
    gxScale operator*( const gxScale& s ) const
    {
        return gxScale( X * s.X, Y * s.Y );
    }
    
    gxScale& operator*=( const gxScale& s )
    {
        X *= s.X;
        Y *= s.Y;
        return *this;
    }
    
    bool IsntZero()
    {
        return X != 1 || Y != 1;
    }
    
    bool IsZero()
    {
        return X == 1 && Y == 1;
    }
    
    void Reset()
    {
        X = 1;
        Y = 1;
    }
};

#endif // gxScale_h
