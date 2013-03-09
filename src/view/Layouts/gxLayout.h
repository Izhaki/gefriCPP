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
#include "View/Layouts/Layouters/gxDistribute.h"

class gxLayout : public gxObject
{
public:
    gxLayout();
    ~gxLayout();
    
    void SetViewElement( gxViewElement* aViewElement );
    
    void Layout();
    
    // Layout data setters
    
    void Add( gxViewElement* aViewElement );
    
    void SetRect( gxViewElement* aViewElement,
                 gxRect         aRect );
    
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
    
protected:    
    gxViewElement* mViewElement;
    
    gxLayoutData::List mData;
    
    gxStretch::Type    mStretch;
    gxAlign::Type      mAlign;
    gxDistribute::Type mDistribute;
    
    gxLayoutData* GetDataOf( gxViewElement* aElement );
private:
    void Init();
};

#endif //gxLayout_h
