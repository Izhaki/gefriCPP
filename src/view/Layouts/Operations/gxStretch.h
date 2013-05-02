#ifndef gxStretch_h
#define gxStretch_h

#include "View/Layouts/Constraints/gxConstrained.h"

struct gxStretch
{
    enum Type
    {
        None,
        Max,
        Full
    };
    
    gxStretch( const Type          aType,
               gxConstrained::List aConstraineds,
               const gxRect&       aRect,
               const bool          onMajorAxis );
    
    gxPix GetMaxSize( gxConstrained::List aConstraineds,
                      const bool          onMajorAxis );
};

#endif //gxStretch_h
