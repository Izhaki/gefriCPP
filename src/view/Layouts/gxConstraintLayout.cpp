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

void gxConstraintLayout::Remove( gxViewElement* aLayoutee )
{
    mConstraints.Remove( aLayoutee );
    
    aLayoutee->Invalidate();
}

