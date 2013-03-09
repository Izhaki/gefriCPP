#ifndef gxLayoutData_h
#define gxLayoutData_h

// Forward Dec
class gxViewElement;

#include <list>
#include "core/geometry/gxGeometry.h"
#include "View/Layouts/Constraints/gxRatio.h"

struct gxConstraints
{
    typedef std::list< gxConstraints* > List;
    typedef typename List::iterator    Iterator;
    
    gxConstraints( gxViewElement* aElement) : Element( aElement ) { }
    gxViewElement* Element;
    gxRect         Rect;
    gxRatio        Ratio;
    
    
    // A helper variable for when the layout is calculated/
    gxRect         Bounds;
    
    // Sets the CalcRect to the original rect
    void Reset();
    void Apply();
    
    bool  IsPixels()   { return Ratio.IsEmpty(); }
    bool  IsntPixels() { return Ratio.IsntEmpty(); }
    bool  IsPercent()  { return Ratio.IsntEmpty() && Ratio.IsPercent(); }
    bool  IsFlex()     { return Ratio.IsntEmpty() && Ratio.IsFlex(); }
    gxPix GetFlex()    { return Ratio.GetFlex(); }
    gxPix GetPercent() { return Ratio.GetPercent(); }
    
};

#endif // gxLayoutData_h
