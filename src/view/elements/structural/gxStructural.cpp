#include "View/Elements/Structural/gxStructural.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxStructural::gxStructural()
{
    // Structural view elements are not subject to any zoom or
    // scroll transformations.
    mTransformFlags.Unset( gxTransFlags::Scale | gxTransFlags::Scroll );
}

gxStructural::~gxStructural()
{
}

void gxStructural::Paint(gxPainter &aPainter)
{
    if ( !IsVisible() )
        return;

    PaintChildren(aPainter);
}

void gxStructural::PaintChildren(gxPainter &aPainter)
{
    forEachChild( aChild )
    {
        aChild->Paint( aPainter );
    }
}

gxRect gxStructural::GetBounds() const
{
    gxASSERT( GetParent() == NULL, "GetBounds() called but no parent." );

    // This will return a rect at (0,0) origin with the size of the parent.
    return gxRect( GetParent()->GetBounds().GetSize() );
}