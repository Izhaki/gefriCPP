#include "view/elements/gxScroller.h"
#include "core/observable/gxCallback.h"
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
        mScrollManager->Unsubscribe( mcCallback( evScrollPosition, gxScroller::OnScrollPositionChanged ) );
        mScrollManager->Unsubscribe( mcCallback( evScrollRange, gxScroller::OnScrollRangeChanged ) );
    }
}

void gxScroller::SetScrollManager( gxScrollManager *aScrollManager )
{
    // Remove the callback from the previous scroll manager (if any).
    if ( mScrollManager )
    {
        mScrollManager->Unsubscribe( mcCallback( evScrollPosition, gxScroller::OnScrollPositionChanged ) );
        mScrollManager->Unsubscribe( mcCallback( evScrollRange, gxScroller::OnScrollRangeChanged ) );
    }

    mScrollManager = aScrollManager;

    mScrollManager->Subscribe( mcCallback( evScrollPosition, gxScroller::OnScrollPositionChanged ) );
    aScrollManager->AddObserverAndNotify( mcCallback( evScrollRange, gxScroller::OnScrollRangeChanged ) );
}

void gxScroller::OnScrollPositionChanged( const evScrollPosition *aEvent )
{
    SetScroll( mScrollManager->GetScroll() );
}

void gxScroller::OnScrollRangeChanged( const evScrollRange *aEvent )
{
    SetScroll( mScrollManager->GetScroll() );
}

void gxScroller::SetScroll( gxScroll const &aScroll )
{
    if ( mScroll != aScroll )
    {
        mScroll = aScroll;
        Repaint();
    }
}

void gxScroller::Paint( gxPainter &aPainter )
{
    // Push current painter state so it can be restored after setting the
    // scroll values
    aPainter.PushState();

    aPainter.SetScroll( mScroll.X, mScroll.Y );

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

void gxScroller::Transform( gxRect &aRect, gxTransformFlags &aTransFlags )
{
    if ( aTransFlags.IsntSet( gxTransformFlags::Scroll ) )
        return;

    if ( mScroll.X != 0 || mScroll.Y != 0 )
    {
        aRect.Offset( -mScroll.X, -mScroll.Y );
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