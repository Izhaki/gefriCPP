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
    
    gxAlign( const Type                 aType,
             const gxRect&              aRect,
             const gxViewElement::List& aLayoutees,
             const gxConstraints&       aConstraints,
             const bool                 onMajorAxis );
};

#endif //gxAlign_h
