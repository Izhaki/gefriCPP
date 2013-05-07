#include "View/Layouts/gxConstraintLayout.h"
#include "View/Elements/gxViewElement.h"

gxConstraintLayout::gxConstraintLayout()
{
}

gxConstraintLayout::gxConstraintLayout( bool aOnMajorAxis ):
    gxLayout( aOnMajorAxis )
{
}

gxConstraintLayout::~gxConstraintLayout()
{
}

void gxConstraintLayout::Init()
{
}

void gxConstraintLayout::Apply()
{
}

void gxConstraintLayout::SetConstraint( gxViewElement*      aLayoutee,
                                        gxConstraint::Type  aType,
                                        gxConstraint::Value aValue,
                                        bool                aOnMajorAxis )
{
    // Warn if the layout does not accepts the provided constraint type
    gxAssert( IsSupportedConstraint( aType ) , "Constraint type is not accepted by this layout" );
    
    mConstraints.Set( aLayoutee, aType, aValue, aOnMajorAxis );
    
    // Now invalidate the element
    aLayoutee->Invalidate();
}
