#ifndef gxLayoutPack_h
#define gxLayoutPack_h

#include "View/Layouts/Constraints/gxConstraints.h"

/**
 * @brief A class to wrap the packing operation of layoutees, so based on their
 * constraints, these are grouped in the start (top or left), middle, or end
 * (bottom or right) areas.
 *
 * This operation is used by the toolbar layout.
 */
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
     * @param aDefault The default pack type for layoutees with no pack 
     * constraint.
     * @param aRect The rect to Pack with reference to.
     * @param aLayoutees A view elements iterator of the elements to layout.
     * @param aConstraints The constraints map.
     * @param aOnMajorAxis Whether we are layouting on the major or minor axis.
     */
    gxLayoutPack( const Type                     aDefault,
                  const gxRect&                  aRect,
                        gxViewElement::Iterator& aLayoutees,
                  const gxConstraints&           aConstraints,
                  const bool                     onMajorAxis );
};


#endif
