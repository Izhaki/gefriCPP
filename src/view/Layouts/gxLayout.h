#ifndef gxLayout_h
#define gxLayout_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"
#include <map>

#include "core/gxLog.h"

// Forward Declaration
class gxViewElement;

// TODO: should this be public as it is at the moment? Shouldn't it be private?
struct gxLayoutData
{
    gxLayoutData( gxViewElement* aElement) : Element( aElement ) { }
    gxViewElement* Element;
    gxRect         Rect;
};


class gxLayout : public gxObject
{
public:
    typedef std::list< gxLayoutData* > Data;
    typedef typename Data::iterator    DataIterator;

    // A helper class to find elements in the data list.
    class ElementFinder
    {
    public:
        ElementFinder( gxViewElement* aElement ) : mElement( aElement ) {}
        bool operator() ( const gxLayoutData* aData ) const
        {
            return aData->Element == mElement;
        }
    private:
        gxViewElement* mElement;
    };
    
    
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
    
    gxLayoutData* GetDataOf( gxViewElement* aElement );
private:
    void Initialize();
    void DoMajorDistribution();
    void DoMinorSize();
    void DoMinorPosition();
};

#endif //gxLayout_h
