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
 * @brief A structure containing the values of various transformations that
 * can be performed in the view layer.
 */
struct gxTransformations
{
    gxScale Scale;
    gxPoint Scroll;
    gxPoint Translate;

    bool ScaleNeeded()     { return Scale.Needed(); }
    bool ScrollNeeded()    { return Scroll.IsntZero(); }
    bool TranslateNeeded() { return Translate.IsntZero(); }
    
};

#endif // gxTransformations_h