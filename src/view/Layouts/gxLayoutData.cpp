#include "View/Layouts/gxLayoutData.h"
#include "View/Elements/gxViewElement.h"

void gxLayoutData::Reset()
{
    Bounds = Rect;
}

void gxLayoutData::Apply()
{
    Element->SetBounds( Bounds );
}
