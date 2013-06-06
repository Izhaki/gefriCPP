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
     * @brief The actual layout operation.
     *
     * This method is promoted to public as BoxLayout kindly offers this method
     * to BorderLayout.
     *
     * @param aRect The rect to align with reference to.
     * @param aLayoutees A view elements iterator of the elements to lay out.
     * @param aConstraints The constraints map.     
     * @param aOnMajorAxis Whether we are layouting on the major or minor axes.
     * @param aRelative Whether the layoutees are relative to the rect
     *        provided, or wheter the position of the rect should serve as an
     *        anchor.
     */
    void DoLayout( const gxRect&                  aRect,
                         gxViewElement::Iterator& aLayoutees,
                   const gxConstraints&           aConstraints,
                   const bool                     aOnMajorAxis,
                   const bool                     aRelative = true );
    
protected:
    gxStretch::Type    mStretch;
    gxAlign::Type      mAlign;
    gxDistribute::Type mDistribute;
    
    virtual void DoLayout( gxViewElement* aLayouter );
    virtual bool IsSupportedConstraint( const gxConstraintId aId );
};

#endif // gxBoxLayout_h
