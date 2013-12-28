#include "View/Layouts/gxBoxLayout.h"
#include "View/Elements/gxViewElement.h"

gxBoxLayout::gxBoxLayout():
    mDistribute ( gxLayoutDistribute::Element ),
    mStretch    ( gxLayoutStretch::None       ),
    mAlign      ( gxLayoutAlign::None         )
{}

gxBoxLayout::gxBoxLayout( bool aOnMajorAxis ):
    gxConstraintLayout ( aOnMajorAxis ),
    mDistribute        ( gxLayoutDistribute::Element ),
    mStretch           ( gxLayoutStretch::None       ),
    mAlign             ( gxLayoutAlign::None         )
{}

gxBoxLayout::gxBoxLayout( gxLayoutDistribute::Type aDistribute,
                          gxLayoutStretch::Type    aStretch,
                          gxLayoutAlign::Type      aAlign ):
    mDistribute ( aDistribute  ),
    mStretch    ( aStretch     ),
    mAlign      ( aAlign       )
{}

gxBoxLayout::gxBoxLayout( gxLayoutDistribute::Type aDistribute,
                          gxLayoutStretch::Type    aStretch,
                          gxLayoutAlign::Type      aAlign,
                          bool                     aOnMajorAxis ):
    mDistribute        ( aDistribute  ),
    mStretch           ( aStretch     ),
    mAlign             ( aAlign       ),
    gxConstraintLayout ( aOnMajorAxis )
{}

bool gxBoxLayout::IsSupportedConstraint( const gxConstraintId aId )
{
    return aId == gxTypeId( gxSizeConstraint* );
}

void gxBoxLayout::DoLayout( gxViewElement* aLayouter )
{
    // We construct the bouns as relative coordinates, thus we use GetSize -
    // this will give a (0,0) position.
    gxRect iContainerBounds( aLayouter->GetInnerBounds().GetSize() );
    
    gxViewElement::VisualIterator iLayoutees( aLayouter->GetChildren() );
    
    DoLayout( iContainerBounds, iLayoutees, mConstraints, mOnMajorAxis );
}

void gxBoxLayout::DoLayout( const gxRect&                  aRect,
                                  gxViewElement::Iterator& aLayoutees,
                            const gxConstraints&           aConstraints,
                            const bool                     aOnMajorAxis )
{   
    gxLayoutDistribute( mDistribute,
                        aRect,
                        aLayoutees,
                        aConstraints,
                        aOnMajorAxis );
    
    gxLayoutStretch( mStretch,
                     aRect,
                     aLayoutees,
                     !aOnMajorAxis );

    gxLayoutAlign( mAlign,
                   aRect,
                   aLayoutees,
                   !aOnMajorAxis );
}