#ifndef gxBorderLayout_h
#define gxBorderLayout_h

#include "View/Layouts/gxConstraintLayout.h"

class gxBorderLayout : public gxConstraintLayout
{
public:
    gxBorderLayout();
    
    gxBorderLayout( bool aOnMajorAxis );
protected:
    virtual bool IsSupportedConstraint( gxConstraint::Type  aType );
    
    virtual void DoLayout( gxViewElement* aLayouter );
private:
    void AddAxisElements( gxViewElement::List& aFiltered,
                          bool                 aOnMajorAxis );
        
    void AddRegionElements( gxLayoutRegion::Type aRegion,
                            gxViewElement::List& aFiltered );
    
    void LayoutAxis( gxViewElement::List& aFiltered,
                     gxRect&              aBounds,
                     bool                 aOnMajorAxis );
    
    gxViewElement* GetCenterElement( gxViewElement::List aLayoutees );
};


#endif // gxBorderLayout_h
