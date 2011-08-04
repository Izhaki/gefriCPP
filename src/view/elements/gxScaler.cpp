#include "view/elements/gxScaler.h"
#include "core/gxCallback.h"
#include "core/gxAssert.h"

gxScaler::gxScaler()
  : mScaleX(1), mScaleY(1), mZoomManager(NULL)
{
}

gxScaler::gxScaler(gxZoomManager *aZoomManager)
  : mScaleX(1), mScaleY(1), mZoomManager(NULL)
{
  SetZoomManager(aZoomManager);
}

gxScaler::~gxScaler()
{
    // Remove the callback from the previous zoom manager (if any).
  if (mZoomManager)
    mZoomManager->mObservers.Remove( gxCALLBACK(gxScaler, OnZoomManagerUpdate) );
}

void gxScaler::SetZoomManager(gxZoomManager *aZoomManager)
{
  // Remove the callback from the previous zoom manager (if any).
  if (mZoomManager)
    mZoomManager->mObservers.Remove( gxCALLBACK(gxScaler, OnZoomManagerUpdate) );

  mZoomManager = aZoomManager;
  aZoomManager->AddObserverAndNotify( gxCALLBACK(gxScaler, OnZoomManagerUpdate) );
}

void gxScaler::SetScale(float aScaleX, float aScaleY)
{
  if (mScaleX != aScaleX || mScaleY != aScaleY)
  {
    Erase();
    mScaleX = aScaleX;
    mScaleY = aScaleY;
    
    // As the scale changed we need to revalidate the hierarcy tree (for
    // example so a Scroller parent can readjust the scrollbars).
    Revalidate();
    Repaint();
  }
}

void gxScaler::OnZoomManagerUpdate(const gxNotification *aNotification)
{
  const gxZoomChangedNotification* Notification = dynamic_cast<const gxZoomChangedNotification*> (aNotification);
  if ( Notification )
  {
    SetScale(Notification->zoomH, Notification->zoomV);
  }
}

void gxScaler::Paint(gxPainter &aPainter)
{
  // Push current painter state so it can be restored after setting the
  // scale
  aPainter.PushState();
  
  aPainter.SetScale(mScaleX, mScaleY);
  
  PaintChildren(aPainter);

  // Pop (will also restore) the painter state to before SetScale().
  aPainter.PopState();
}

void gxScaler::TransformChild(gxBounds &aBounds)
{
  // Don't scale if the bounds reject it
  if (aBounds.mTransformFlags.IsntSet(gxBounds::Scalable))
    return;

  if (mScaleX != 1 || mScaleY != 1)
  {
    aBounds.Scale(mScaleX, mScaleY);
  }
}