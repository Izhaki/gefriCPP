#ifndef gxSizeConstraint_h
#define gxSizeConstraint_h

#include "View/Layouts/Constraints/gxConstraint.h"
#include "Core/gxString.h"

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

#include "View/Layouts/Constraints/gxConstraints.h"

//TODO: Docs

enum gxSizeUnit
{
    gsPixels,
    gsPercent,
    gsFlex
};

class gxSizeConstraint : public gxConstraint
{
public:
    static const gxConstraint::Type Id = Size;
    
    gxSizeConstraint( gxConstraint::Type aType,
                      int                aValue ) :
        mValue( aValue )
    {
        switch ( aType )
        {
            case gxConstraint::Pixels:  mUnit = gsPixels;  break;
            case gxConstraint::Percent: mUnit = gsPercent; break;
            case gxConstraint::Flex:    mUnit = gsFlex;    break;
            default:
                break;
        }        
    }
    
    gxSizeUnit GetUnit()
    {
        return mUnit;
    }
    
    int GetValue()
    {
        return mValue;
    }
    
    bool IsPixels()
    {
        return mUnit == gsPixels;
    }
    
    bool IsPercent()
    {
        return mUnit == gsPercent;
    }
    
    bool IsFlex()
    {
        return mUnit == gsFlex;
    }
    
    
protected:
    int        mValue;
    gxSizeUnit mUnit;
};

#endif // gxSizeConstraint_h
