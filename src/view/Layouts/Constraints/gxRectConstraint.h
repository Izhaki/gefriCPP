#ifndef gxRectConstraint_h
#define gxRectConstraint_h

#include "core/gxAssert.h"

// Currently not in use as the assumption is that all layouts will need the
// rect constraint - it is used in Reset()

class gxAbstractRectConstraint
{
public:
    virtual gxRect& GetRect()
    {
        Assert();
        return gxDummyRect;
    }
    
    virtual void SetRect( gxRect aRect ) { Assert(); }
private:
    void Assert()
    {
        gxASSERT( true, "No rect constraints for this layout" );
    }
};

class gxRectConstraint: virtual public gxAbstractRectConstraint
{
public:
    virtual gxRect& GetRect()
    {
        return mRect;
    }
    
    virtual void SetRect( gxRect aRect )
    {
        mRect = aRect;
    }
private:
    gxRect mRect;
};

#endif //gxRectConstraint_h
