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
    
    gxStretch( const Type         aType,
               gxConstraints::List aData,
               const gxRect&      aContainer,
               const bool         onMajorAxis );
    
    gxPix GetMaxSize( gxConstraints::List aData,
                      const bool         onMajorAxis );
};

#endif //gxStretch_h
