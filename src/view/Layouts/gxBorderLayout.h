#ifndef gxBorderLayout_h
#define gxBorderLayout_h

#include "View/Layouts/gxLayout.h"

class gxBorderLayout : public gxLayout
{
public:
    gxBorderLayout();
    
    gxBorderLayout( bool aOnMajorAxis );
    
    
    void SetRegion( gxViewElement* aViewElement,
                    gxRegion       aRegion );

protected:
    virtual void DoLayout();
private:
    void AddConstraints( gxConstraints::List &aFiltered,
                         bool aOnMajorAxis );
        
    void AddRegionConstraints( gxRegion aRegion,
                               gxConstraints::List &aFiltered );
    
    gxConstraints* GetCenterConstraints();
};


#endif // gxBorderLayout_h
