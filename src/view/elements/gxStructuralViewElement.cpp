#include "view/elements/gxStructuralViewElement.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxStructuralViewElement::gxStructuralViewElement()
{
    // Structural view elements are not subject to any zoom or
    // scroll transformations.
    mTransformFlags.Unset( gxTransFlags::Scale | gxTransFlags::Scroll );
}

gxStructuralViewElement::~gxStructuralViewElement()
{
}

void gxStructuralViewElement::Paint(gxPainter &aPainter)
{
    if ( !IsVisible() )
        return;

    PaintChildren(aPainter);
}

void gxStructuralViewElement::PaintChildren(gxPainter &aPainter)
{
    for ( EACHCHILD )
    {
        CHILD->Paint( aPainter );
    }
}

gxRect gxStructuralViewElement::GetBounds() const
{
    gxASSERT( GetParent() == NULL, "GetBounds() called but no parent." );

    // This will return a rect at (0,0) origin with the size of the parent.
    return gxRect( GetParent()->GetBounds().GetSize() );
}