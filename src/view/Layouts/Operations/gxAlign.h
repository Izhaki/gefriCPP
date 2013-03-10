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
    
    gxAlign( const Type          aType,
             gxConstraints::List aConstraints,
             const gxRect&       aContainer,
             const bool          onMajorAxis );
};

#endif //gxAlign_h
