#include "View/Elements/Structural/gxStructural.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxStructural::gxStructural()
{
    // Structural view elements are not subject to any zoom or
    // scroll transformations.
//    mTransformFlags.Unset( gxTransFlags::Scale | gxTransFlags::Scroll );
        mTransformFlags.Unset( gxTransFlags::Scale | gxTransFlags::Scroll | gxTransFlags::Translate );
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

void gxStructural::Repaint()
{
    if ( !IsValid() )
        return;

    gxASSERT( GetParent() == NULL, "GetBounds() called but no parent." );
    
    // Simply call repaint on my parent.
    return GetParent()->Repaint();

}


gxRect gxStructural::GetBounds() const
{
    gxASSERT( GetParent() == NULL, "GetBounds() called but no parent." );

    return GetParent()->GetBounds();
}