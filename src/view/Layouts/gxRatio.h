#ifndef gxRatio_h
#define gxRatio_h

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
