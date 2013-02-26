#ifndef gxTransformations_h
#define gxTransformations_h

#include "core/gxFlags.h"
#include "core/geometry/gxGeometry.h"
 
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
        return Scale.IsntZero();
    }
    
    bool ScrollNeeded()
    {
        return Scroll.IsntZero();
    }
    
    bool TranslateNeeded()
    {
        return Translate.IsntZero();
    }
};

#endif // gxTransformations_h