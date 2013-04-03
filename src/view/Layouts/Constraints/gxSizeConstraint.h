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

//TODO: Docs

typedef char gxSizeUnit;

gxSizeUnit const GxPixels  = 1;
gxSizeUnit const GxPercent = 2;
gxSizeUnit const GxFlex    = 3;

class gxSizeConstraint : public gxConstraint
{
public:
    
    gxSizeConstraint( gxString aConstraintName,
                      int      aValue ) :
        mValue( aValue )
    {
        if      ( aConstraintName == "Pixels" )  { mUnit = GxPixels;  }
        else if ( aConstraintName == "Flex" )    { mUnit = GxFlex;    }
        else if ( aConstraintName == "Percent" ) { mUnit = GxPercent; }
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
        return mUnit = GxPixels;
    }
    
    bool IsPercent()
    {
        return mUnit = GxPercent;
    }
    
    bool IsFlex()
    {
        return mUnit = GxFlex;
    }
    
    
protected:
    int        mValue;
    gxSizeUnit mUnit;
};

#endif // gxSizeConstraint_h
