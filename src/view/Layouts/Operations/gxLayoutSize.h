#ifndef gxLayoutSize_h
#define gxLayoutSize_h

#include "View/Layouts/Constraints/gxConstraints.h"

/**
 * @brief A class to wrap sizing operation on layutees. The operation takes a
 * rect and claculates the size of each layoutee based on its constraints,
 * accounting for flex and percentage based sizes.
 */
struct gxLayoutSize
{
    /**
     * @brief A layout operation that works out the size of the layoutees
     * based on their size constraints.
     *
     * @param aRect The rect to align with reference to.
     * @param aLayoutees A view elements iterator of the elements to lay out.
     * @param aConstraints The constraints map.
     * @param aOnMajorAxis Whether we are layouting on the major or minor axes.
     * @param hasFlex Returns whether or not any of the layoutess has flex, thus
     * the layoutees will take the full size of the rect.
     */
    gxLayoutSize( const gxRect&                  aRect,
                        gxViewElement::Iterator& aLayoutees,
                  const gxConstraints&           aConstraints,
                  const bool                     onMajorAxis,
                        bool&                    hasFlex );
};

#endif //gxLayoutSize_h
