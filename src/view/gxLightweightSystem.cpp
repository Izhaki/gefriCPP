#include "view/gxLightweightSystem.h"
#include "gxLightweightControl.h"
#include "view/gxDcPainter.h"

gxLightweightSystem::gxLightweightSystem(gxLightweightControl *aControl)
: mContents(NULL),
  mScrollManager(NULL),
  mValidationQueued(false)
{
  // Sets this a the lightweight system of the control so delegation can start.
  aControl->SetLightweightSystem(this);

  // Keep a reference to the control so we can call methods like Refresh.
  mControl = aControl;

  // Create the root view element
  mRootViewElement = new gxRootViewElement(this);
}

gxLightweightSystem::~gxLightweightSystem()
{
  // Remove notification from previous scroll manager, (if such exist).
  if (mScrollManager)
    mScrollManager->mObservers.Remove( gxCALLBACK( OnScrollRangeChanged ) );

  // Unset the lightweight system on the control, so event like paint won't be
  // delegated to an object that has been destroyed
  mControl->UnsetLightweightSystem();
  mControl = NULL;

  delete mRootViewElement;
  mRootViewElement = NULL;
}

void gxLightweightSystem::SetContents(gxViewElement *aViewElement)
{
  // Remove any view element already set.
  if (mContents != NULL)
    mRootViewElement->RemoveChild(mContents);

  // Add the new view element as a child to the root view element.
  mContents = aViewElement;
  mRootViewElement->AddChild(mContents);
}

void gxLightweightSystem::SetScrollManager(gxScrollManager *aScrollManager)
{
  // Remove notification from previous scroll manager, (if such exist).
  if (mScrollManager)
    mScrollManager->mObservers.Remove( gxCALLBACK( OnScrollRangeChanged ) );
    
  mScrollManager = aScrollManager;
  mScrollManager->mObservers.Add( gxCALLBACK( OnScrollRangeChanged ) );
}

void gxLightweightSystem::OnScrollRangeChanged(const gxScrollRangeChangedNotification *aNotification)
{
  mControl->SetScrollbar(wxHORIZONTAL, aNotification->mScroll.X, aNotification->mVisible.X, aNotification->mRange.X);
  mControl->SetScrollbar(wxVERTICAL, aNotification->mScroll.Y, aNotification->mVisible.Y, aNotification->mRange.Y);
}

void gxLightweightSystem::Paint(gxPaintDC *aDc, gxRects const &aDamagedRects)
{
  // Create a painter
  gxDcPainter iPainter(aDc, aDamagedRects);

  // Ask the root view element to paint itself using the painter.
  mRootViewElement->Paint(iPainter);
}

void gxLightweightSystem::AddDirtyRegion(gxRect &aRect)
{
  // This will invalidate the rect and fire a paint event (the current event
  // execution will continue).
  mControl->RefreshRect(aRect);
}

gxRect gxLightweightSystem::GetControlBounds() const
{
  return mControl->GetBounds();
}

gxSize gxLightweightSystem::GetTextSize(gxString &aText)
{
  gxSize iSize = mControl->GetTextSize(aText);
  return gxSize(iSize.X, iSize.Y);
}

void gxLightweightSystem::OnScroll (const bool isVertical, const int aPosition)
{
  if (mScrollManager)
    mScrollManager->SetScroll(isVertical, aPosition);
}

void gxLightweightSystem::QueueValidation()
{
  // To prevent duplicate events, only queue a validation request if none is
  // currently queued.
  if (!mValidationQueued)
  {
    mControl->QueueValidation();
    mValidationQueued = true;
  }
}

void gxLightweightSystem::OnValidationRequest()
{
  // As this is the handler of the event, once this is called validation is
  // no longer queued.
  mValidationQueued = false;

  mRootViewElement->Validate();
}