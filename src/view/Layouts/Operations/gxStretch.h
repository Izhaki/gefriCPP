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
    
    gxStretch( const Type                 aType,
               const gxRect&              aRect,
               const gxViewElement::List& aLayoutees,
               const bool                 onMajorAxis );
    
    gxPix GetMaxSize( const gxViewElement::List& aLayoutees,
                      const bool                 onMajorAxis );
};

#endif //gxStretch_h
