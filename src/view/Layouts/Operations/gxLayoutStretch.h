#ifndef gxStretch_h
#define gxStretch_h

#include "View/Layouts/Constraints/gxConstraints.h"

struct gxLayoutStretch
{
    enum Type
    {
        None,
        Max,
        Full
    };
    
    gxLayoutStretch( const Type                     aType,
                     const gxRect&                  aRect,
                           gxViewElement::Iterator& aLayoutees,
                     const bool                     onMajorAxis );
    
    gxPix GetMaxSize(       gxViewElement::Iterator& aLayoutees,
                      const bool                     onMajorAxis );
};

#endif //gxStretch_h
