#ifndef gxAlign_h
#define gxAlign_h

#include "View/Layouts/Constraints/gxConstraints.h"

struct gxAlign
{
    enum Type
    {
        None,
        Start,
        Middle,
        End
    };
    
    gxAlign( const Type                     aType,
             const gxRect&                  aRect,
                   gxViewElement::Iterator& aLayoutees,
             const gxConstraints&           aConstraints,
             const bool                     onMajorAxis,
             const bool                     aRelative = true );
};

#endif //gxAlign_h
