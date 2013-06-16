#ifndef gxStretch_h
#define gxStretch_h

#include "View/Layouts/Constraints/gxConstraints.h"

/**
 * @brief A class to wrap the stretching operation of layutees. Stretching
 * changes the size of each layoutee to either the full size of the container,
 * or that biggest size of all layoutees.
 *
 * Note that stretching is typically done on the minor axis.
 */
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
