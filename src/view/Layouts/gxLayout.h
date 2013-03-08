#ifndef gxLayout_h
#define gxLayout_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"

#include "core/gxLog.h"

// Forward Declarations
class gxViewElement;

#include "View/Layouts/gxLayoutData.h"
#include "View/Layouts/Layouters/gxAlign.h"
#include "View/Layouts/Layouters/gxStretch.h"

class gxLayout : public gxObject
{
public:
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
        
    gxLayout();
    
    void SetViewElement( gxViewElement* aViewElement );
    
    void Layout();
    
    // Layout data setters
    
    void SetRect( gxViewElement* aViewElement,
                  gxRect         aRect );
    
protected:    
    gxViewElement* mViewElement;
    
    gxLayoutData::List mData;
    
    gxStretch::Type    mStretch;
    gxAlign::Type      mAlign;
    MajorDistribution  mMajorDistribution;
    
    gxLayoutData* GetDataOf( gxViewElement* aElement );
private:
    void Init();
    void DoMajorDistribution();
//    void DoMinorSize();
};

#endif //gxLayout_h
