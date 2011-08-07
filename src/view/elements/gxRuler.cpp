#include "view/elements/gxRuler.h"
#include "view/gxLightweightSystem.h"

gxRuler::gxRuler(const gxRect  &aBounds,
                 gxDivProvider *aDivProvider)
: gxVisualViewElement(aBounds),
  mZoomManager(NULL),
  mScrollManager(NULL),
  mIsHorizontal(aBounds.width > aBounds.height),
  mBlockTextRatio(0.5),
  mStartPixel(0),
  mDivProvider(aDivProvider)
{
  
}

gxRuler::~gxRuler()
{
  // If a zoom manager is linked, remove the callbacks.
  if (mZoomManager)
    mZoomManager->mObservers.Remove( gxCALLBACK(gxRuler, OnZoomManagerUpdate) );

  // If a scroll manager is linked, remove the callbacks.
  if (mScrollManager)
    mScrollManager->mObservers.Remove( gxCALLBACK(gxRuler, OnScrollManagerUpdate) );
}

void gxRuler::SetZoomManager(gxZoomManager *aZoomManager)
{
  // Remove the callback from the previous zoom manager (if any).
  if (mZoomManager)
    mZoomManager->mObservers.Remove( gxCALLBACK(gxRuler, OnZoomManagerUpdate) );

  mZoomManager = aZoomManager;
  aZoomManager->AddObserverAndNotify( gxCALLBACK(gxRuler, OnZoomManagerUpdate) );
}

void gxRuler::OnZoomManagerUpdate(const gxNotification *aNotification)
{
  // Convert the notification to the correct class.
  const gxZoomChangedNotification* iNotification = dynamic_cast<const gxZoomChangedNotification*> (aNotification);
  if ( iNotification )
  {
    SetScale ( mIsHorizontal ? iNotification->mZoom.X : iNotification->mZoom.Y );
  }
}

void gxRuler::SetScrollManager(gxScrollManager *aScrollManager)
{
  // Remove the callback from the previous scroll manager (if any).
  if (mScrollManager)
    mScrollManager->mObservers.Remove( gxCALLBACK(gxRuler, OnScrollManagerUpdate) );

  mScrollManager = aScrollManager;
  aScrollManager->AddObserverAndNotify( gxCALLBACK(gxRuler, OnScrollManagerUpdate) );
}

void gxRuler::OnScrollManagerUpdate(const gxNotification *aNotification)
{
  mStartPixel = mIsHorizontal ? mScrollManager->GetScrollX() : mScrollManager->GetScrollY();
}

void gxRuler::ValidateSelf()
{
  // To calculate the minimum block size we need the lightweight
  // system, which will only be available when ValidateSelf is called.
  CalcMinBlockSize();
}

void gxRuler::CalcMinBlockSize()
{
  // Find the maximum text size.
  std::string iBiggestLabel = mDivProvider->GetLabelOfPixel( mIsHorizontal ? mBounds.width : mBounds.height );
  gxSize iMaxTextSize = GetLightweightSystem()->GetTextSize(iBiggestLabel);

  // Take into account the ratio of the text for the block.
  mDivProvider->SetMinBlockSize( (int)ceil(iMaxTextSize.X / mBlockTextRatio) );
}

void gxRuler::SetScale(const float aScale)
{
  mScale = aScale;
  mDivProvider->SetScale(aScale);
}

void gxRuler::SetBounds(const gxRect &aNewBounds)
{
  gxVisualViewElement::SetBounds(aNewBounds);
  mIsHorizontal = aNewBounds.width > aNewBounds.height;
}

void gxRuler::PaintSelf(gxPainter &aPainter)
{
  // Draw border
  aPainter.DrawRectangle(mBounds);

  // The div position, in pixels, and not subject to any scale calculations
  int iPos;
  
  // The length of the line of the div
  int iLineLength;
  
  // The last pixel to be drawn, we need to take into account the scale 
  int iEndPixel =  mStartPixel + GetMyVisibleSize();

  // Start with the block at the start pixel
  gxViewDiv *iDiv = mDivProvider->BlockAtPixel(mStartPixel / mScale);
  do
  {
    iPos = iDiv->Pixel;

    // Based on the type of the div draw different lines / text
    switch (iDiv->Type)
    {
      case gxViewDiv::Block:
        iLineLength = mBounds.height;
        aPainter.DrawText(mDivProvider->GetLabelOfPixel(iPos), iPos, 0, 3, 3, mIsHorizontal);
        break;
      case gxViewDiv::Key:
        iLineLength = int(mBounds.height / 3);
        break;
      case gxViewDiv::Normal:
        iLineLength = 2;
        break;
    }
    aPainter.DrawLine(iPos, 0, iPos, iLineLength, mIsHorizontal);

    iDiv = mDivProvider->Next();

    // Stop when the actual position (taking into account the scale) of the
    // next div is smaller than the last pixel to be drawn. 
  } while ( (int)(iDiv->Pixel * mScale) < iEndPixel );
}

int gxRuler::GetMyVisibleSize()
{
  // Returns whichever is smaller: my scaled size or my parent size
  if (mIsHorizontal)
    return gxMin((int)( mBounds.width * mScale ), GetParent()->GetBounds().width);
  else
    return gxMin((int)( mBounds.height * mScale ), GetParent()->GetBounds().height);
}