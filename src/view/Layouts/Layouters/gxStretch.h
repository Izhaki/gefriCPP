#ifndef gxStretch_h
#define gxStretch_h

#include "View/Layouts/Constraints/gxConstraints.h"

struct gxStretch
{
    enum Type
    {
        None,
        Max,
        Full
    };
    
    gxStretch( const Type          aType,
               gxConstraints::List aConstraints,
               const gxRect&       aContainer,
               const bool          onMajorAxis );
    
    gxPix GetMaxSize( gxConstraints::List aConstraints,
                      const bool          onMajorAxis );
};

#endif //gxStretch_h
