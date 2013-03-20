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
    class Constraints: public gxConstraints,
                       public gxRegionConstraint,
                       public gxRatioConstraint
    {
    public:
        Constraints( gxViewElement* aElement) :
            gxConstraints( aElement ) {}
    };
    
    virtual gxConstraints* CreateConstraints( gxViewElement* aElement );
    virtual void DoLayout();
private:
    void AddConstraints( gxConstraints::List& aFiltered,
                         bool                 aOnMajorAxis );
        
    void AddRegionConstraints( gxRegion             aRegion,
                               gxConstraints::List& aFiltered );
    
    void LayoutAxis( gxConstraints::List& aFiltered,
                     gxRect&              aBounds,
                     bool                 aOnMajorAxis );
    
    gxConstraints* GetCenterConstraints();
};


#endif // gxBorderLayout_h
