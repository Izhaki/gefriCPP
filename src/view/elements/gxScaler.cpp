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
  aZoomManager->mObservers.Add( gxCALLBACK(gxScaler, OnZoomManagerUpdate) );
}

void gxScaler::SetScale(float aScaleX, float aScaleY)
{
  Erase();
  mScaleX = aScaleX;
  mScaleY = aScaleY;
  Repaint();
}

void gxScaler::OnZoomManagerUpdate(const gxObject *aSubject)
{
  gxZoom newZoom = mZoomManager->GetZoom();
  SetScale(newZoom.v, newZoom.h);
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
  // Structural bounds don't need scaling
  if (aBounds.Structural)
    return;

  if (mScaleX != 1 || mScaleY != 1)
  {
    aBounds.Scale(mScaleX, mScaleY);
  }
}