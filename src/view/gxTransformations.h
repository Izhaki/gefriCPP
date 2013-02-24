#ifndef gxTransformations_h
#define gxTransformations_h

#include "core/gxFlags.h"
#include "core/geometry/gxGeometry.h"

/**
 * @brief A class representing which transformations are enabled.
 * 
 * Used by {@link gxPainter painters} and {@ling gxViewElement view elements}
 */
class gxTransFlags : public gxFlags<gx8Flags>
{
public:
    gxTransFlags() { Set( gxTransFlags::All ); }
    gxTransFlags( gx8Flags aFlags ) { Set( aFlags ); }
  
    enum
    {
        Translate = 0x01,
        Scroll    = 0x02,
        Scale     = 0x04,
        All       = Translate | Scroll | Scale
    };
    
    bool ScaleOn()     { return IsSet( Scale ); }
    bool ScrollOn()    { return IsSet( Scroll ); }
    bool TranslateOn() { return IsSet( Translate ); }
    
    bool ScaleOff()     { return IsntSet( Scale ); }
    bool ScrollOff()    { return IsntSet( Scroll ); }
    bool TranslateOff() { return IsntSet( Translate ); }
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

    bool ScaleNeeded()
    {
        return Scale.IsntZero() && Enabled.IsSet( gxTransFlags::Scale );
    }
    
    bool ScrollNeeded()
    {
        return Scroll.IsntZero() && Enabled.IsSet( gxTransFlags::Scroll );
    }
    
    bool TranslateNeeded()
    {
        return Translate.IsntZero() && Enabled.IsSet( gxTransFlags::Translate );
    }
    
    // What trasformations are enabled
    gxTransFlags Enabled;
};

#endif // gxTransformations_h