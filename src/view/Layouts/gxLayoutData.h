#ifndef gxLayoutData_h
#define gxLayoutData_h

// Forward Dec
class gxViewElement;

#include <list>
#include "core/geometry/gxGeometry.h"

struct gxLayoutData
{
    typedef std::list< gxLayoutData* > List;
    typedef typename List::iterator    Iterator;
    
    gxLayoutData( gxViewElement* aElement) : Element( aElement ) { }
    gxViewElement* Element;
    gxRect         Rect;
};

#endif // gxLayoutData_h
