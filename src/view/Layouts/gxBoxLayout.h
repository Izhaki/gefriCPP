#ifndef gxBoxLayout_h
#define gxBoxLayout_h

#include "View/Layouts/gxLayout.h"
#include "View/Layouts/Layouters/gxAlign.h"
#include "View/Layouts/Layouters/gxStretch.h"
#include "View/Layouts/Layouters/gxDistribute.h"

class gxBoxLayout : public gxLayout
{
public:
    gxBoxLayout();
    
    gxBoxLayout( bool aOnMajorAxis );
    
    gxBoxLayout( gxDistribute::Type aDistribute,
                 gxStretch::Type    aStretch,
                 gxAlign::Type      aAlign,
                 bool               aOnMajorAxis );
protected:
    gxStretch::Type    mStretch;
    gxAlign::Type      mAlign;
    gxDistribute::Type mDistribute;
    
    virtual void DoLayout();    
};

#endif // gxBoxLayout_h
