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

struct gxLayoutData
{
    int    Index;
    gxRect Rect;    
};
        
class gxLayout : public gxObject
{
public:
    typedef std::pair< gxViewElement*, gxLayoutData > DataPair;
    typedef std::map < gxViewElement*, gxLayoutData > Data;
    typedef typename Data::iterator                   DataIterator;

    enum MajorDistribution
    {
        mdElement,
        mdFull,
        mdEqual,
        mdStart,
        mdMiddle,
        mdEnd
    };
    
    enum MinorSize
    {
        msElement,
        msMax,
        msFull
    };
    
    enum MinorPosition
    {
        mpElement,
        mpStart,
        mpMiddle,
        mpEnd
    };
        
    gxLayout();
    
    void SetViewElement( gxViewElement* aViewElement );
    
    void Layout();
    
    // Layout data setters
    
    void SetRect( gxViewElement* aViewElement,
                  gxRect         aRect );
    
protected:    
    gxViewElement* mViewElement;
    
    Data mData;
    
    MinorSize         mMinorSize;
    MinorPosition     mMinorPosition;
    MajorDistribution mMajorDistribution;    
private:
    void ResetRects();
    void DoMajorDistribution();
    void DoMinorSize();
    void DoMinorPosition();
};

#endif //gxLayout_h
