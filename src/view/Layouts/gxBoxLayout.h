#ifndef gxBoxLayout_h
#define gxBoxLayout_h

#include "View/Layouts/gxConstraintLayout.h"
#include "View/Layouts/Operations/gxLayoutOperations.h"

class gxBoxLayout : public gxConstraintLayout
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
    virtual void DoLayout( gxRect&             aRect,
                           gxConstrained::List aConstraineds,
                           bool                aOnMajorAxis  );
    
protected:
    gxStretch::Type    mStretch;
    gxAlign::Type      mAlign;
    gxDistribute::Type mDistribute;
    
    virtual void DoLayout( gxViewElement* aLayouter );
    virtual bool IsSupportedConstraint( gxConstraint::Type  aType );    
};

#endif // gxBoxLayout_h
