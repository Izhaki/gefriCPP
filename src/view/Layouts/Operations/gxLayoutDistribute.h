#ifndef gxDistribute_h
#define gxDistribute_h

#include "View/Layouts/Constraints/gxConstraints.h"

struct gxLayoutDistribute
{
    enum Type
    {
        Element,
        Full,
        Equal,
        Start,
        Middle,
        End
    };
    
    gxLayoutDistribute( const Type                     aType,
                        const gxRect&                  aRect,
                              gxViewElement::Iterator& aLayoutees,
                        const gxConstraints&           aConstraints,
                        const bool                     onMajorAxis );
};

#endif //gxDistribute_h
