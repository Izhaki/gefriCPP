#ifndef gxToolbarLayout_h
#define gxToolbarLayout_h

#include "View/Layouts/gxConstraintLayout.h"
#include "View/Layouts/Constraints/gxPackConstraint.h"

class gxToolbarLayout : public gxConstraintLayout
{
public:
    gxToolbarLayout();
    
    gxToolbarLayout( bool aOnMajorAxis );
protected:
    virtual bool IsSupportedConstraint( const gxConstraintId aId );
    
    virtual void DoLayout( gxViewElement* aLayouter );
};


#endif //gxToolbarLayout_h
