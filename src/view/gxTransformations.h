#ifndef gxTransformations_h
#define gxTransformations_h

#include "core/gxFlags.h"
#include "core/geometry/gxGeometry.h"

/**
 * @brief A class representing which transformations are enabled.
 * 
 * Used by {@link gxPainter painters} and {@ling gxViewElement view elements}
 */
class gxTransformFlags : public gxFlags<gx8Flags>
{
public:
    gxTransformFlags() { Set( gxTransformFlags::All ); }
    gxTransformFlags( gx8Flags aFlags ) { Set( aFlags ); }
  
    enum
    {
        Translate = 0x01,
        Scroll    = 0x02,
        Scale     = 0x04,
        All       = Translate | Scroll | Scale
    };
};

/**
 * @brief A structures containing the values for scale transformations
 */
struct gxScale
{
    float X, Y;

    gxScale() : X( 1.0 ), Y( 1.0 ) { }

    bool operator==( const gxScale& aScale ) const { return X == aScale.X && Y == aScale.Y; }
    bool operator!=( const gxScale& aScale ) const { return X != aScale.X || Y != aScale.Y; }
    
    bool Needed() { return X != 1 || Y != 1; }
};

/**
 * @brief A structures containing the values for scroll transformations
 */
struct gxPosition
{
    gxPix X, Y;

    gxPosition() : X( 0 ), Y( 0 ) { }
    gxPosition( gxPix aX, gxPix aY ) : X( aX ), Y( aY ) { }

    bool operator==( const gxPosition& aPosition ) const { return X == aPosition.X && Y == aPosition.Y; }
    bool operator!=( const gxPosition& aPosition ) const { return X != aPosition.X || Y != aPosition.Y; }
    
    bool Needed() { return X != 0 || Y != 0; }
};

/**
 * @brief A structures containing the values for translate transformations
 */
struct gxTranslate
{
    gxTranslate() : X( 0 ), Y( 0 ) { }
    gxPix X, Y;
    
    bool Needed() { return X != 0 || Y != 0; }
};

/**
 * @brief A structure containing the values of various transformations that
 * can be performed in the view layer.
 */
struct gxTransformations
{
    gxScale     Scale;
    gxPosition  Scroll;
    gxTranslate Translate;

    bool ScaleNeeded()     { return Scale.Needed(); }
    bool ScrollNeeded()    { return Scroll.Needed(); }    
    bool TranslateNeeded() { return Translate.Needed(); }
    
};

#endif // gxTransformations_h