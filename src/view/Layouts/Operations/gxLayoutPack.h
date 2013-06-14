#ifndef gxLayoutPack_h
#define gxLayoutPack_h

#include "View/Layouts/Constraints/gxConstraints.h"

struct gxLayoutPack
{
    enum Type
    {
        None,
        Start,
        Middle,
        End
    };
    
    /**
     * @brief The actual Pack operation
     *
     * @param aType The desired Pack type.
     * @param aRect The rect to Pack with reference to.
     * @param aLayoutees A view elements iterator of the elements to lay out.
     * @param aConstraints The constraints map.
     * @param aOnMajorAxis Whether we are layouting on the major or minor axes.
     */
    gxLayoutPack( const Type                     aType,
                  const gxRect&                  aRect,
                        gxViewElement::Iterator& aLayoutees,
                  const gxConstraints&           aConstraints,
                  const bool                     onMajorAxis );
};


#endif
