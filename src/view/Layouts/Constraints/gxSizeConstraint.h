#ifndef gxSizeConstraint_h
#define gxSizeConstraint_h

#include "Core/gxAssert.h"
#include "View/Layouts/Constraints/gxConstraint.h"
#include "View/Layouts/Constraints/gxConstrained.h"

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
private:
    typedef gxConstraint::Type gxSizeUnit;
public:
    static const gxConstraint::Type Id = Size;
    virtual gxConstraint::Type GetType() { return Size; }
    
    gxSizeConstraint( gxConstraint::Type aType,
                      int                aValue ) :
        mUnit(  aType ),
        mValue( aValue )
    {
        switch ( aType )
        {
            case gxConstraint::Pixels:
            case gxConstraint::Percent:
            case gxConstraint::Flex:
                break;
            default:
                gxWarn( "Invalid unit" );
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
        return mUnit == gxConstraint::Pixels;
    }
    
    bool IsPercent()
    {
        return mUnit == gxConstraint::Percent;
    }
    
    bool IsFlex()
    {
        return mUnit == gxConstraint::Flex;
    }
    
    
protected:
    int        mValue;
    gxSizeUnit mUnit;
};

#endif // gxSizeConstraint_h
