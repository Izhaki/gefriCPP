#ifndef gxRatioConstraint_h
#define gxRatioConstraint_h

#include "core/gxAssert.h"

/**
 * @brief A class representing a rational size that can be either percentages
 * or flex units.
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
 *
 * Both percent and flex are stored within this class in the mRatio member.
 * Percentages are stored as positive values, flex as negative.
 */
class gxAbstractRatioConstraint
{
public:
    virtual short GetPercent() { Assert(); return 0; }
    
    virtual short GetFlex() { Assert(); return 0; }
    
    virtual void SetPercent( short aValue ) { Assert(); }
    virtual void SetFlex   ( short aValue ) { Assert(); }
    
    virtual bool IsPercent() { Assert(); return false; }
    virtual bool IsFlex()    { Assert(); return false; }
    
    
    // Readability methods related to Percent and Flex ratios.
    virtual bool IsPixels()   { Assert(); return true; }
    virtual bool IsntPixels() { Assert(); return false; }
private:
    void Assert()
    {
        gxAssert( true, "No ratio constraints for this layout" );
    }
};

class gxRatioConstraint: virtual public gxAbstractRatioConstraint
{
public:
    gxRatioConstraint() : mRatio(0) {}
    
    virtual short GetPercent()
    {
        return mRatio > 0 ? mRatio : 0;
    }
    
    virtual short GetFlex()
    {
        return mRatio < 0 ? -mRatio : 0;
    }
    
    virtual void SetPercent( short aValue ) { mRatio = aValue; }
    virtual void SetFlex   ( short aValue ) { mRatio = -aValue; }
    
    virtual bool IsPercent() { return mRatio > 0; }
    virtual bool IsFlex()    { return mRatio < 0; }
    
    virtual bool IsPixels()   { return mRatio == 0; }
    virtual bool IsntPixels() { return mRatio != 0; }    
private:
    short mRatio;
};


#endif // gxRatioConstraint_h
