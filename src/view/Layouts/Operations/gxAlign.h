#ifndef gxAlign_h
#define gxAlign_h

#include "View/Layouts/Constraints/gxConstrained.h"

struct gxAlign
{
    enum Type
    {
        None,
        Start,
        Middle,
        End
    };
    
    gxAlign( const Type          aType,
             gxConstrained::List aConstraineds,
             const gxRect&       aContainer,
             const bool          onMajorAxis );
};

#endif //gxAlign_h
