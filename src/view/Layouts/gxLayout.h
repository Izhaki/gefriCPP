#ifndef gxLayout_h
#define gxLayout_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"
#include <map>

#include "core/gxLog.h"

#define gxFoundInMap( aMap, aItem ) \
    !( aMap.find( aItem ) == aMap.end() )

// Forward Declaration
class gxViewElement;

class gxLayout : public gxObject
{
public:
    typedef std::pair< gxViewElement*, gxRect > tRectsPair;
    typedef std::map< gxViewElement*, gxRect >  tRects;
        
    gxLayout() {}
    
    void Layout( gxViewElement* aViewElement );
    
    void SetRect( gxViewElement* aViewElement,
                  gxRect         aRect );
    
protected:
    tRects mRects;
};

#endif //gxLayout_h
