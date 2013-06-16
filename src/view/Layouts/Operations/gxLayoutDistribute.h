#ifndef gxDistribute_h
#define gxDistribute_h

#include "View/Layouts/Constraints/gxConstraints.h"

/**
 * @brief A class to wrap the distribution operation of layutees which has flex
 * or percentage constraints. Thus, the layout first sizes the layoutees, then 
 * distributes them.
 */
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
