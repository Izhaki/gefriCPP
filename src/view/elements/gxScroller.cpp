#include "view/elements/gxScroller.h"
#include "core/gxCallback.h"
#include "core/gxAssert.h"

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
  aScrollManager->mObservers.Add( gxCALLBACK(gxScroller, OnScrollManagerUpdate) );
}

void gxScroller::SetScroll(float aScrollX, float aScrollY)
{
  Erase();
  mScrollX = aScrollX;
  mScrollY = aScrollY;
  Repaint();
}

void gxScroller::OnScrollManagerUpdate(const gxObject *aSubject)
{
  SetScroll(mScrollManager->GetScrollX(), mScrollManager->GetScrollY());
}

void gxScroller::Paint(gxPainter &aPainter)
{
  // Push current painter state so it can be restored after setting the
  // scroll values
  aPainter.PushState();

  aPainter.SetTranslate(-mScrollX, -mScrollY);

  PaintChildren(aPainter);

  // Pop (will also restore) the painter state to before SetTranslate().
  aPainter.PopState();
}

void gxScroller::TransformChild(gxBounds &aBounds)
{
  // Structural areas don't need scrolling
  if (aBounds.Structural)
    return;  

  if (mScrollX != 1 || mScrollY != 1)
  {
    aBounds.Offset(-mScrollX, -mScrollY);
  }
}