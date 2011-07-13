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

void gxScaler::TranslateToParent(gxRect &aRect)
{
  if (mScaleX != 1 || mScaleY != 1)
  {
    aRect.Scale(mScaleX, mScaleY);
  }
  
  gxASSERT(GetParent() == NULL, "gxScaler::TranslateToParent called, but no parent");

  aRect.Offset(GetParent()->GetBounds().GetPosition());
}

void gxScaler::TransformChild(gxRect &aRect, bool aisStructural)
{
  // Structural areas don't need scaling
  if (aisStructural)
    return;

  if (mScaleX != 1 || mScaleY != 1)
  {
    aRect.Scale(mScaleX, mScaleY);
  }
}