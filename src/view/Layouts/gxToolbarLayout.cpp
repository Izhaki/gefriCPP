#include "View/Layouts/gxToolbarLayout.h"

gxToolbarLayout::gxToolbarLayout()
{}

gxToolbarLayout::gxToolbarLayout( gxLayoutStretch::Type aStretch,
                                  gxLayoutAlign::Type   aAlign,
                                  bool                  aOnMajorAxis ):
    mStretch           ( aStretch     ),
    mAlign             ( aAlign       ),
    gxConstraintLayout ( aOnMajorAxis )
{}

bool gxToolbarLayout::IsSupportedConstraint( const gxConstraintId aId )
{
    return aId == gxTypeId( gxPackConstraint* );
}

void gxToolbarLayout::DoLayout( gxViewElement* aLayouter )
{
    // We want the bounds to be in relative coordinates.
    // In order to ignore the X,Y position of the layouter we simply call GetSize();
    // this will return a rectangle at coordinates (0,0) with the layouter size.
    gxRect iContainerBounds( aLayouter->GetInnerBounds().GetSize() );
    
    gxViewElement::VisualIterator iLayoutees( aLayouter->GetChildren() );
    
    gxLayoutPack( gxLayoutPack::None,
                  iContainerBounds,
                  iLayoutees,
                  mConstraints,
                  mOnMajorAxis );
    
    gxLayoutStretch( mStretch,
                     iContainerBounds,
                     iLayoutees,
                     !mOnMajorAxis );
    
    gxLayoutAlign( mAlign,
                   iContainerBounds,
                   iLayoutees,
                   !mOnMajorAxis );
}
