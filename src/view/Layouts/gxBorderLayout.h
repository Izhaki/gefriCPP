#ifndef gxBorderLayout_h
#define gxBorderLayout_h

#include "View/Layouts/gxConstraintLayout.h"

class gxBorderLayout : public gxConstraintLayout
{
public:
    gxBorderLayout();
    
    gxBorderLayout( bool aOnMajorAxis );
protected:
    virtual bool IsSupportedConstraint( const gxConstraintId aId );
    
    virtual void DoLayout( gxViewElement* aLayouter );
private:
    void AddAxisElements( gxViewElement::List& aFiltered,
                          bool                 aOnMajorAxis );
        
    void AddRegionElements( gxLayoutRegion::Type aRegion,
                            gxViewElement::List& aFiltered );
    
    void LayoutAxis( gxViewElement::List& aFiltered,
                     gxRect&              aBounds,
                     bool                 aOnMajorAxis );
    
    gxViewElement* GetCenterElement( gxViewElement::Iterator& aLayoutees );
};


#endif // gxBorderLayout_h
