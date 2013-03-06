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
    typedef typename tRects::iterator           tRectsIterator;
        
    gxLayout();
    
    void SetViewElement( gxViewElement* aViewElement );
    
    void Layout();
    
    // Layout data setters
    
    void SetRect( gxViewElement* aViewElement,
                  gxRect         aRect );
    
protected:    
    gxViewElement* mViewElement;
    
    tRects mRects;
    
    // TODO: sort out these enums to something else
    enum {
        Original,
        Max,
        Full
    } mMinorSize;
    
    enum {
        NoChange,
        Start,
        Middle,
        End
    } mMinorPosition;

private:
    void ResetRects();
    void DoMinorSize();
    void DoMinorPosition();
};

#endif //gxLayout_h
