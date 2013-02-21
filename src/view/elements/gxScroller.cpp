#include "view/elements/gxScroller.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxScroller::gxScroller()
  : mScrollManager( NULL )
{
}

gxScroller::gxScroller( gxScrollManager *aScrollManager )
  : mScrollManager( NULL )
{
    SetScrollManager( aScrollManager );
}

gxScroller::~gxScroller()
{
    // Remove the callback from the previous scroll manager (if any).
    if ( mScrollManager )
    {
        mScrollManager->gxUnsubscribe( evScrollChanged );
    }
}

void gxScroller::SetScrollManager( gxScrollManager *aScrollManager )
{
    // Remove the callback from the previous scroll manager (if any).
    if ( mScrollManager )
    {
        mScrollManager->gxUnsubscribe( evScrollChanged );
    }

    mScrollManager = aScrollManager;

    aScrollManager->gxSubscribe( evScrollChanged, OnScrollChanged );
}

void gxScroller::OnScrollChanged( const gxScroll *aScroll )
{
    SetScroll( aScroll->mPosition );
}

void gxScroller::SetScroll( gxPoint const &aScrollPosition )
{
    if ( mScrollPosition != aScrollPosition )
    {
        mScrollPosition = aScrollPosition;
        Repaint();
    }
}

void gxScroller::Paint( gxPainter &aPainter )
{
    // Push current painter state so it can be restored after setting the
    // scroll values
    aPainter.PushState();

    aPainter.SetScroll( mScrollPosition );

    PaintChildren( aPainter );

    // Pop (will also restore) the painter state to before SetTranslate().
    aPainter.PopState();
}

void gxScroller::Validate()
{
    ReadjustScrollbars();

    // Call the base class validate so children are also validated and this
    // object is marked as valid.
    gxStructuralViewElement::Validate();

    Repaint();
}

void gxScroller::Transform( gxRect &aRect, gxTransFlags &aTransFlags )
{
    if ( aTransFlags.ScrollOff() )
        return;

    if ( mScrollPosition.IsntZero() )
    {
        aRect.Translate( -mScrollPosition );
    }
}

void gxScroller::ReadjustScrollbars()
{
    if ( !mScrollManager )
        return;

    gxRect iBounds;
    GetDescendantsBounds( iBounds );

    gxSize iMySize = GetBounds().GetSize();
    gxSize iRange( iBounds.X + iBounds.width, iBounds.Y + iBounds.height );

    mScrollManager->AdjustScrollbars( iMySize, iRange );
}