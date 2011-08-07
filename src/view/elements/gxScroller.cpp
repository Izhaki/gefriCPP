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
    mScrollManager->mObservers.Remove( gxCALLBACK(gxScroller, OnScrollManagerUpdate) );
}

void gxScroller::SetScrollManager(gxScrollManager *aScrollManager)
{
  // Remove the callback from the previous scroll manager (if any).
  if (mScrollManager)
    mScrollManager->mObservers.Remove( gxCALLBACK(gxScroller, OnScrollManagerUpdate) );

  mScrollManager = aScrollManager;
  aScrollManager->AddObserverAndNotify( gxCALLBACK(gxScroller, OnScrollManagerUpdate) );
}

void gxScroller::SetScroll(int aScrollX, int aScrollY)
{
  if (mScroll.X != aScrollX || mScroll.Y != aScrollY)
  {
    Erase();
    mScroll.X = aScrollX;
    mScroll.Y = aScrollY;
    Repaint();
  }
}

void gxScroller::OnScrollManagerUpdate(const gxNotification *aNotification)
{
  SetScroll(mScrollManager->GetScrollX(), mScrollManager->GetScrollY());
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

void gxScroller::ValidateSelf()
{
  ReadjustScrollbars();
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
  gxRect iBounds;
  GetDescendantsBounds(iBounds);

  gxSize iMySize = GetBounds().GetSize();

  if (mScrollManager)
    mScrollManager->AdjustScrollbars(iMySize.X, iBounds.x + iBounds.width, iMySize.Y, iBounds.y + iBounds.height);
}