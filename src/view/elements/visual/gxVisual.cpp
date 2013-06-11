#include "View/Elements/Visual/gxVisual.h"
#include "View/gxLightweightSystem.h"
#include "core/gxLog.h"
#include "core/gxAssert.h"

gxVisual::gxVisual() :
    mBounds( 0, 0, 0, 0 ),
    mLayout( NULL )
{
}

gxVisual::gxVisual( const gxRect& aBounds ) :
    mLayout( NULL )
{
    mBounds = aBounds;
}

gxVisual::~gxVisual()
{
}

void gxVisual::Paint( gxPainter& aPainter )
{
    if ( !IsVisible() )
        return;

    gxRect iBounds = GetBounds();
    
    // Check if the painter has a different positioning mode than the one we
    // need.
    bool iPositioningModeDifferent = aPainter.IsRelative() != IsRelative();
    
    // If it does, change its positioning mode
    if ( iPositioningModeDifferent )
    {
        aPainter.PushState();
        aPainter.SetRelative( IsRelative() );
    }
    
    // Only paint if need to (intersect with the bounds of painting area and
    // damaged areas).
    if ( aPainter.NeedsPainting( iBounds ) )
    {
        // Push current painter state so it can be restored later on.
        aPainter.PushState();

        // Sets the clip area of the painter to the bounds
        if ( IsClippingChildren() )
            aPainter.SetClipArea( iBounds );

        PaintSelf( aPainter );
        PaintChildren( aPainter );
        PaintBorder( aPainter );

        // Pop (will also restore) the painter state to before any painting was
        // done.
        aPainter.PopState();
    }

    if ( iPositioningModeDifferent )
    {
        aPainter.PopState();
    }
    
}

void gxVisual::Repaint()
{
    gxRect iBounds = GetOuterBounds();
    gxViewElement::Repaint( iBounds, IsRelative() );
}

void gxVisual::PaintChildren( gxPainter& aPainter )
{
    // Return if there are no children.
    if ( IsChildless() )
        return;

    // Push current painter state so it can be poped after translate
    aPainter.PushState();

    // Offset all paint operation by the top-left point of this element
    aPainter.SetTranslate( GetBounds().GetPosition() );

    Iterator iChildren( GetChildren() );
    for ( iChildren.First(); iChildren.Current(); iChildren.Next() )
    {
        // Paint the child
        iChildren.Current()->Paint( aPainter );
    }

    // Pop (will also restore) the painter state to before translate.
    aPainter.PopState();
}

void gxVisual::GetDescendantsBounds( gxRect& aBounds )
{
    // Union with my bounds.
    aBounds.Union( GetBounds() );
  
    // And then with those of all children (in case these are not clipped).
    if ( !IsClippingChildren() )
        gxViewElement::GetDescendantsBounds( aBounds );
}

gxRect gxVisual::GetBounds() const
{
    return mBounds;
}

void gxVisual::SetBounds( const gxRect& aNewBounds )
{
    // Check if either translate or resize happened
    bool iTranslate = aNewBounds.GetPosition() != mBounds.GetPosition();
    bool iResize    = aNewBounds.GetSize()     != mBounds.GetSize();
    bool iChanged   = iTranslate || iResize;

    // Erase the view element if either happened
    if ( iChanged && IsVisible() )
        Erase();

    // Preform translation
    if ( iTranslate )
    {
        gxPoint iDelta = aNewBounds.GetPosition() - mBounds.GetPosition();
        Translate( iDelta );
    }

    // Preform resize
    if ( iResize )
    {
        mBounds.SetSize( aNewBounds.GetSize() );
    }

    // Repaint
    if ( iChanged && IsVisible() )
    {
        Invalidate();
        Repaint();
    }
}

void gxVisual::SetLayout( gxLayout* aLayout )
{
    mLayout = aLayout;
}

gxLayout* gxVisual::GetLayout()
{
    return mLayout;
}

void gxVisual::InvalidateLayout( gxViewElement* aChild )
{
    if ( mLayout )
        mLayout->Invalidate( aChild );
}

void gxVisual::Layout()
{
    if ( mLayout )
        mLayout->Layout( this );
}

void gxVisual::Translate( gxPoint aDelta )
{
    mBounds += aDelta;
    
    // There will be additional handling here for absolute positioned figures,
    // which will also need to translate all of its children.
}