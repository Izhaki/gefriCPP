#ifndef gxRatio_h
#define gxRatio_h


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
 * Both percent and flex are stored within this class in the mValue member.
 * Percentages are stored as positive values, flex as negative.
 */
class gxRatio
{
public:
    gxRatio() : mValue(0) {}
    
    void SetPercent( short aValue ) { mValue = aValue; }
    void SetFlex   ( short aValue ) { mValue = -aValue; }
    
    short GetPercent()
    {
        return mValue > 0 ? mValue : 0;
    }
    
    short GetFlex()
    {
        return mValue < 0 ? -mValue : 0;
    }
    
    bool IsEmpty()   { return mValue == 0; }
    bool IsntEmpty() { return mValue != 0; }
    
    bool IsPercent() { return mValue > 0; }
    bool IsFlex()    { return mValue < 0; }
private:
    short mValue;
};


#endif // gxRatio_h
