#include "view/elements/gxScaler.h"
#include "core/gxCallback.h"
#include "core/gxAssert.h"

gxScaler::gxScaler()
: mZoomManager(NULL)
{
}

gxScaler::gxScaler(gxZoomManager *aZoomManager)
: mZoomManager(NULL)
{
  SetZoomManager(aZoomManager);
}

gxScaler::~gxScaler()
{
  // Remove the callback from the previous zoom manager (if any).
  if (mZoomManager)
    mZoomManager->mObservers.Remove( gxCALLBACK( OnZoomManagerUpdate ) );
}

void gxScaler::SetZoomManager(gxZoomManager *aZoomManager)
{
  // Remove the callback from the previous zoom manager (if any).
  if (mZoomManager)
    mZoomManager->mObservers.Remove( gxCALLBACK( OnZoomManagerUpdate ) );

  mZoomManager = aZoomManager;
  aZoomManager->AddObserverAndNotify( gxCALLBACK( OnZoomManagerUpdate ) );
}

void gxScaler::SetScale(gxScale const &aScale)
{
  if (mScale != aScale)
  {
    Erase();
    mScale = aScale;
    
    // As the scale changed we need to revalidate the hierarcy tree (for
    // example so a Scroller parent can readjust the scrollbars).
    Invalidate();
    Repaint();
  }
}

void gxScaler::OnZoomManagerUpdate(const gxZoomChangedNotification *aNotification)
{
  SetScale(aNotification->mZoom);
}

void gxScaler::Paint(gxPainter &aPainter)
{
  // Push current painter state so it can be restored after setting the
  // scale
  aPainter.PushState();
  
  aPainter.SetScale(mScale);
  
  PaintChildren(aPainter);

  // Pop (will also restore) the painter state to before SetScale().
  aPainter.PopState();
}

void gxScaler::Transform(gxRect &aRect, gxTransformFlags &aTransFlags)
{
  // Don't scale if the bounds reject it
  if (aTransFlags.IsntSet(gxTransformFlags::Scale))
    return;

  if (mScale.X != 1 || mScale.Y != 1)
  {
    aRect.Scale(mScale.X, mScale.Y);
  }
}