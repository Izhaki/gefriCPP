#include "View/Layouts/Constraints/gxConstraints.h"
#include "View/Elements/gxViewElement.h"

void gxConstraints::Reset()
{
    Bounds = Rect;
}

void gxConstraints::Apply()
{
    Element->SetBounds( Bounds );
}
