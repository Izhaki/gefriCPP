#ifndef gxBoxLayout_h
#define gxBoxLayout_h

#include "View/Layouts/gxLayout.h"
#include "View/Layouts/Operations/gxLayoutOperations.h"

class gxBoxLayout : public gxLayout
{
public:
    gxBoxLayout();
    
    gxBoxLayout( bool aOnMajorAxis );

    gxBoxLayout( gxDistribute::Type aDistribute,
                 gxStretch::Type    aStretch,
                 gxAlign::Type      aAlign );
    
    gxBoxLayout( gxDistribute::Type aDistribute,
                 gxStretch::Type    aStretch,
                 gxAlign::Type      aAlign,
                 bool               aOnMajorAxis );
    
    /**
     * @brief BoxLayout kindly offers this method to BorderLayout.
     */
    virtual void DoLayout( gxRect&             aContainer,
                           gxConstraints::List aConstraints,
                           bool                aOnMajorAxis  );
    
protected:
    gxStretch::Type    mStretch;
    gxAlign::Type      mAlign;
    gxDistribute::Type mDistribute;
    
    virtual void DoLayout();
    virtual bool IsSupportedConstraint( gxConstraint::Type  aType );    
};

#endif // gxBoxLayout_h
