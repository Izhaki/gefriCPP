#ifndef gxAlign_h
#define gxAlign_h

#include "View/Layouts/Constraints/gxConstraints.h"

struct gxLayoutAlign
{
    enum Type
    {
        None,
        Start,
        Middle,
        End
    };
    
    /**
     * @brief The actual align operation
     *
     * @param aType The desired align type.
     * @param aRect The rect to align with reference to.
     * @param aLayoutees A view elements iterator of the elements to lay out.
     * @param aConstraints The constraints map.
     * @param aOnMajorAxis Whether we are layouting on the major or minor axes.
     */
    gxLayoutAlign( const Type                     aType,
                   const gxRect&                  aRect,
                         gxViewElement::Iterator& aLayoutees,
                   const gxConstraints&           aConstraints,
                   const bool                     onMajorAxis );
};

#endif //gxAlign_h
