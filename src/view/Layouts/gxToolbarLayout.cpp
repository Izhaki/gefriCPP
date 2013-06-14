#include "View/Layouts/gxToolbarLayout.h"

gxToolbarLayout::gxToolbarLayout()
{}

gxToolbarLayout::gxToolbarLayout( bool aOnMajorAxis ):
    gxConstraintLayout ( aOnMajorAxis )
{}

bool gxToolbarLayout::IsSupportedConstraint( const gxConstraintId aId )
{
    return aId == gxTypeId( gxPackConstraint* );
}

void gxToolbarLayout::DoLayout( gxViewElement* aLayouter )
{
    // We construct the bouns as relative coordinates, thus we use GetSize -
    // this will give a (0,0) position.
    gxRect iContainerBounds( aLayouter->GetInnerBounds().GetSize() );
    
    gxViewElement::VisualIterator iLayoutees( aLayouter->GetChildren() );
    
    gxLayoutPack( gxLayoutPack::None,
                  iContainerBounds,
                  iLayoutees,
                  mConstraints,
                  !mOnMajorAxis );
}
