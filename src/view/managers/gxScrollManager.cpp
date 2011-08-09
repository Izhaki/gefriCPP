#include "view/managers/gxScrollManager.h"
#include <wx/log.h>
#include <math.h>

gxScrollManager::gxScrollManager()
{
}

gxScrollManager::~gxScrollManager()
{
}

void gxScrollManager::SetScroll(gxScroll const &aScroll)
{
  mScroll = aScroll;
  mObservers.Notify(new gxNotification());
}

void gxScrollManager::SetScroll(const int aScrollX, const int aScrollY)
{
  gxScroll newScroll(aScrollX, aScrollY);
  SetScroll(newScroll);
}

void gxScrollManager::SetScroll(const bool isVertical, const int aScroll)
{
  if (isVertical)
    SetScrollY(aScroll);
  else
    SetScrollX(aScroll);
}

void gxScrollManager::SetScrollX(const int aScrollX)
{
  mScroll.X = aScrollX;
  mObservers.Notify(new gxScrollPositionChangedNotification(this));
}

void gxScrollManager::SetScrollY(const int aScrollY)
{
  mScroll.Y = aScrollY;
  mObservers.Notify(new gxScrollPositionChangedNotification(this));
}

void gxScrollManager::AdjustScrollbars(gxSize const &aVisible, gxSize const &aRange)
{
  if (mVisible == aVisible && mRange == aRange)
    return;

  gxScroll newScroll;

  // The new scroll position is proportional to the previous one.
  if (mScroll.X != 0 && aRange.X > aVisible.X )
  {
    float oldPosRatio = (mRange.X - mVisible.X) / (float)mScroll.X;
    newScroll.X = (int)floor((aRange.X - aVisible.X) / oldPosRatio);
  }

  // The new scroll position is proportional to the previous one.
  if (mScroll.Y != 0 && aRange.Y > aVisible.Y )
  {
    float oldPosRatio = (mRange.Y - mVisible.Y) / (float)mScroll.Y;
    newScroll.Y = (int)floor((aRange.Y - aVisible.Y) / oldPosRatio);
  }

  mVisible = aVisible;
  mRange = aRange;

  SetScroll(newScroll);

  mObservers.Notify(new gxScrollRangeChangedNotification(this));
}

void gxScrollManager::AddObserverAndNotify(gxCallback *aCallback)
{
  mObservers.Add(aCallback);
  mObservers.Notify(new gxScrollRangeChangedNotification(this), aCallback);
}