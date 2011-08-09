#include "view/elements/gxScroller.h"
#include "core/gxCallback.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxScroller::gxScroller()
  : mScrollManager(NULL)
{
}

gxScroller::gxScroller(gxScrollManager *aScrollManager)
  : mScrollManager(NULL)
{
  SetScrollManager(aScrollManager);
}

gxScroller::~gxScroller()
{
    // Remove the callback from the previous scroll manager (if any).
  if (mScrollManager)
  {
    mScrollManager->mObservers.Remove( gxCALLBACK( OnScrollPositionUpdate ) );
    mScrollManager->mObservers.Remove( gxCALLBACK( OnScrollRangeUpdate ) );
  }
}

void gxScroller::SetScrollManager(gxScrollManager *aScrollManager)
{
  // Remove the callback from the previous scroll manager (if any).
  if (mScrollManager)
  {
    //mScrollManager->mObservers.Remove( gxCALLBACK(gxScroller, OnScrollPositionUpdate, gxScrollPositionChangedNotification) );
    mScrollManager->mObservers.Remove( gxCALLBACK( OnScrollPositionUpdate ) );
    mScrollManager->mObservers.Remove( gxCALLBACK( OnScrollRangeUpdate ) );
  }

  mScrollManager = aScrollManager;
  aScrollManager->AddObserverAndNotify( gxCALLBACK( OnScrollPositionUpdate ) );
  aScrollManager->AddObserverAndNotify( gxCALLBACK( OnScrollRangeUpdate ) );
}

void gxScroller::OnScrollPositionUpdate(const gxScrollPositionChangedNotification *aNotification)
{
  SetScroll( mScrollManager->GetScroll() );
}

void gxScroller::OnScrollRangeUpdate(const gxScrollRangeChangedNotification *aNotification)
{
  SetScroll( mScrollManager->GetScroll() );
}

void gxScroller::SetScroll(gxScroll const &aScroll)
{
  if (mScroll != aScroll)
  {
    mScroll = aScroll;
    Repaint();
  }
}

void gxScroller::Paint(gxPainter &aPainter)
{
  // Push current painter state so it can be restored after setting the
  // scroll values
  aPainter.PushState();

  aPainter.SetScroll(mScroll.X, mScroll.Y);

  PaintChildren(aPainter);

  // Pop (will also restore) the painter state to before SetTranslate().
  aPainter.PopState();
}

bool gxScroller::ValidateSelf()
{
  ReadjustScrollbars();
  return true;
}

void gxScroller::Transform(gxRect &aRect, gxTransformFlags &aTransFlags)
{
  // Don't scroll if the bounds reject it
  if (aTransFlags.IsntSet(gxTransformFlags::Scroll))
    return;

  if (mScroll.X != 0 || mScroll.Y != 0)
  {
    aRect.Offset(-mScroll.X, -mScroll.Y);
  }
}

void gxScroller::ReadjustScrollbars()
{
  if (!mScrollManager)
    return;

  gxRect iBounds;
  GetDescendantsBounds(iBounds);

  gxSize iMySize = GetBounds().GetSize();
  gxSize iRange(iBounds.x + iBounds.width, iBounds.y + iBounds.height);
 
  mScrollManager->AdjustScrollbars(iMySize, iRange);

}