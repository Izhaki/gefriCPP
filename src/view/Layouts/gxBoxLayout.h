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
    void DoLayout( const gxRect&              aRect,
                   const gxViewElement::List& aLayoutees,
                   const gxConstraints&       aConstraints,
                   const bool                 aOnMajorAxis );
    
protected:
    gxStretch::Type    mStretch;
    gxAlign::Type      mAlign;
    gxDistribute::Type mDistribute;
    
    virtual void DoLayout( gxViewElement* aLayouter );
    virtual bool IsSupportedConstraint( const gxConstraintId aId );
};

#endif // gxBoxLayout_h
