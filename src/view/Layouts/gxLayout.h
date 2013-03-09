#ifndef gxLayout_h
#define gxLayout_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"

#include "core/gxLog.h"

// Forward Declarations
class gxViewElement;

#include "View/Layouts/Constraints/gxConstraints.h"
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
    
    void SetPercent( gxViewElement* aViewElement,
                     short          aPercent );
    
    void SetFlex( gxViewElement* aViewElement,
                  short          aFlex );
        
    // A helper class to find elements in the data list.
    class ElementFinder
    {
    public:
        ElementFinder( gxViewElement* aElement ) : mElement( aElement ) {}
        bool operator() ( const gxConstraints* aData ) const
        {
            return aData->Element == mElement;
        }
    private:
        gxViewElement* mElement;
    };
    
protected:    
    gxViewElement* mViewElement;
    
    gxConstraints::List mData;
    
    gxStretch::Type    mStretch;
    gxAlign::Type      mAlign;
    gxDistribute::Type mDistribute;
    
    gxConstraints* GetDataOf( gxViewElement* aElement );

    void Init();
    
    // Sorts the layout data list based on the element index
    void SortElements();
    void Apply();
};

#endif //gxLayout_h
