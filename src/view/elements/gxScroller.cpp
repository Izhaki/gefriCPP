#include "view/elements/gxScroller.h"
#include "core/gxCallback.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxScroller::gxScroller()
  : mScrollX(0), mScrollY(0), mScrollManager(NULL)
{
}

gxScroller::gxScroller(gxScrollManager *aScrollManager)
  : mScrollX(0), mScrollY(0), mScrollManager(NULL)
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
  if (mScrollX != aScrollX || mScrollY != aScrollY)
  {
    Erase();
    mScrollX = aScrollX;
    mScrollY = aScrollY;
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

  aPainter.SetScroll(mScrollX, mScrollY);

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

  if (mScrollX != 0 || mScrollY != 0)
  {
    aRect.Offset(-mScrollX, -mScrollY);
  }
}

void gxScroller::ReadjustScrollbars()
{
  gxRect iBounds;
  GetDescendantsBounds(iBounds);

  gxSize iMySize = GetBounds().GetSize();

  if (mScrollManager)
    mScrollManager->AdjustScrollbars(iMySize.x, iBounds.x + iBounds.width, iMySize.y, iBounds.y + iBounds.height);
}