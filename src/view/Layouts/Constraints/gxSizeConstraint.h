#ifndef gxSizeConstraint_h
#define gxSizeConstraint_h

#include "View/Layouts/Constraints/gxConstraint.h"

/**
 * @brief A class representing a layout size that can be:
 * - Pixels
 * - Percent
 * - Flex
 *
 * Some layouts involve sizing of elements based on the remaining available
 * space.
 *
 * Percentages are straight forward - if there are 240 available pixels, and the
 * size is set to 50, the element will consume 120 pixels.
 *
 * Flex provides a ratio based on the total flex unit. So if there are two
 * elements, one with 1 Flex the other with 3, the total flex is 4; thus the
 * first element will get 25% (1/4) and the second 75% (3/4).
 */

class gxSizeConstraint : public gxConstraint
{
public:
    enum Type {
        Pixels,
        Percent,
        Flex
    };
    
    gxSizeConstraint( Type aType, int aValue ) :
        mType( aType ),
        mValue( aValue )
    {}
    
    Type GetType()
    {
        return mType;
    }
    
    int GetValue()
    {
        return mValue;
    }
protected:
    int mValue;
    Type mType;
};

#endif // gxSizeConstraint_h
