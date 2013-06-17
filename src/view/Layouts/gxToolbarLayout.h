#ifndef gxToolbarLayout_h
#define gxToolbarLayout_h

#include "View/Layouts/gxConstraintLayout.h"
#include "View/Layouts/Operations/gxLayoutOperations.h"
#include "View/Layouts/Constraints/gxPackConstraint.h"

/**
 * @brief A layout that packs the layoutees based on their constraints on the
 * major axis, then stretches and align them on the minor axis.
 */
class gxToolbarLayout : public gxConstraintLayout
{
public:
    gxToolbarLayout();
    
    gxToolbarLayout( gxLayoutStretch::Type aStretch,
                     gxLayoutAlign::Type   aAlign,
                     bool                  aOnMajorAxis );
protected:
    gxLayoutStretch::Type mStretch;
    gxLayoutAlign::Type   mAlign;
    
    virtual bool IsSupportedConstraint( const gxConstraintId aId );
    
    virtual void DoLayout( gxViewElement* aLayouter );
};


#endif //gxToolbarLayout_h
