#include "View/Elements/Structural/gxStructural.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxStructural::gxStructural()
{
    // structural bounds are virtual, so we don't really regard them as children
    // clippers. Also, A scaler child of a scroller will mark the scroller as
    // Trace rather than Invalid during invalidation if the former would clip
    // children
    mFlags.Unset( gxViewElement::ClipChildren );
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
    
    
    Iterator iChildren( GetChildren() );
    for ( iChildren.First(); iChildren.Current(); iChildren.Next() )
    {
        iChildren.Current()->Paint( aPainter );
    }
}

void gxStructural::Repaint()
{
    gxViewElement* iParent = GetParent();
    
    if ( iParent != NULL )
    {
        // Simply repaint on my parent.
        iParent->Repaint();
    }
}


gxRect gxStructural::GetBounds() const
{
    gxWarnIf( Parentless(), "GetBounds() called but no parent." );

    return GetParent()->GetBounds();
}

void gxStructural::SetBounds( const gxRect &aNewBounds )
{
    gxWarn( "SetBounds Called on Structural Element" );
}