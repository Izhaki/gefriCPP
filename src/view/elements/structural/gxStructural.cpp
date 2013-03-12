#include "View/Elements/Structural/gxStructural.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxStructural::gxStructural()
{
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
    if ( IsChildless() )
        return;
    
    forEachChild( aChild )
    {
        aChild->Paint( aPainter );
    }
}

void gxStructural::Repaint()
{
    if ( IsInvalid() )
        return;

    gxASSERT( Parentless(), "GetBounds() called but no parent." );
    
    // Simply call repaint on my parent.
    GetParent()->Repaint();

}


gxRect gxStructural::GetBounds() const
{
    gxASSERT( Parentless(), "GetBounds() called but no parent." );

    return GetParent()->GetBounds();
}

void gxStructural::SetBounds( const gxRect &aNewBounds )
{
    gxASSERT( true, "SetBounds Called on Structural Element" );
}