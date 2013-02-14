#include "view/elements/gxVisualViewElement.h"
#include "view/gxLightweightSystem.h"
#include "core/gxLog.h"

gxVisualViewElement::gxVisualViewElement()
  : mBounds( 0, 0, 0, 0 )
{
}

gxVisualViewElement::gxVisualViewElement( const gxRect &aBounds )
{
  mBounds = aBounds; 
}

gxVisualViewElement::~gxVisualViewElement()
{
}

void gxVisualViewElement::Paint( gxPainter &aPainter )
{
  if ( !IsVisible() )
    return;

  // Push the painter state as the next line might change it.
  aPainter.PushState();

  // Sets the painter transform flags to my own transform flags.
  aPainter.SetTransformFlags( mTransformFlags );

  // Get the bounds
  gxRect iBounds( GetBounds() );

  // wxLogDebug(_T("Paint: %i, %i, %i, %i"), bounds.GetX(), bounds.GetY(), bounds.GetWidth(), bounds.GetHeight());

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
  
  aPainter.PopState();
}

void gxVisualViewElement::PaintChildren( gxPainter &aPainter )
{
  // Return if there are no children.
  if ( mChildren.empty() )
    return;

  // Push current painter state so it can be poped after translate
  aPainter.PushState();

  // Offset all paint operation by the top-left point of this elemet
  aPainter.SetTranslate( mBounds.X, mBounds.Y );

  for ( EACHCHILD )
  {
    // Paint the child
    CHILD->Paint( aPainter );
  }

  // Pop (will also restore) the painter state to before translate.
  aPainter.PopState();
}

void gxVisualViewElement::GetDescendantsBounds( gxRect &aBounds )
{
  // Union with my bounds.
  aBounds.Union( GetBounds() );
  
  // And then with those of all children (in case these are not clipped).
  if ( !IsClippingChildren() )
   gxViewElement::GetDescendantsBounds( aBounds );
}

gxRect gxVisualViewElement::GetBounds() const
{
  return mBounds;
}

void gxVisualViewElement::SetBounds( const gxRect &aNewBounds )
{
  // Check if either translate or resize happened
  bool iTranslate = ( aNewBounds.X != mBounds.X ) || ( aNewBounds.Y != mBounds.Y ); 
  bool iResize    = ( aNewBounds.width != mBounds.width ) || ( aNewBounds.height != mBounds.height );

  // Erase the view element if either happened
  if ( iTranslate || iResize )
    Erase();

  // Preform translation
  if ( iTranslate )
  {
    gxPix dx = aNewBounds.X - mBounds.X;
    gxPix dy = aNewBounds.Y - mBounds.Y;
    Translate( dx,dy );
  }

  // Preform resize
  if ( iResize )
  {
    mBounds.width  = aNewBounds.width;
    mBounds.height = aNewBounds.height;
  }

  // Repaint
  if ( iTranslate || iResize )
  {
    Invalidate();
    Repaint();
  }
}

void gxVisualViewElement::Translate( gxPix dx, gxPix dy )
{
  mBounds.X += dx;
  mBounds.Y += dy;
}