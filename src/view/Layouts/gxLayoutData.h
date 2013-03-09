#ifndef gxLayoutData_h
#define gxLayoutData_h

// Forward Dec
class gxViewElement;

#include <list>
#include "core/geometry/gxGeometry.h"

struct gxRationalSize
{
    int  Size;
    
    enum Unit {
        Percentage,
        Flex
    } mUnit;
};

struct gxLayoutData
{
    typedef std::list< gxLayoutData* > List;
    typedef typename List::iterator    Iterator;
    
    gxLayoutData( gxViewElement* aElement) : Element( aElement ) { }
    gxViewElement* Element;
    gxRect         Rect;
    
    // A helper variable for when the layout is calculated/
    gxRect         Bounds;
    
    // Sets the CalcRect to the original rect
    void Reset();
    void Apply();
};

#endif // gxLayoutData_h
