#ifndef gxBorderLayout_h
#define gxBorderLayout_h

#include "View/Layouts/gxLayout.h"

class gxBorderLayout : public gxLayout
{
public:
    gxBorderLayout();
    
    gxBorderLayout( bool aOnMajorAxis );
protected:
    virtual bool IsSupportedConstraint( gxConstraint::Type  aType );    
    virtual void DoLayout( gxViewElement* aLayouter );
private:
    void AddConstraineds( gxConstrained::List& aFiltered,
                          bool                 aOnMajorAxis );
        
    void AddRegionConstraineds( gxLayoutRegion::Type aRegion,
                                gxConstrained::List& aFiltered );
    
    void LayoutAxis( gxConstrained::List& aFiltered,
                     gxRect&              aBounds,
                     bool                 aOnMajorAxis );
    
    gxConstrained* GetCenterConstrained();
};


#endif // gxBorderLayout_h
