#include "view/managers/gxScrollManager.h"
#include <wx/log.h>
#include <math.h>

gxScrollManager::gxScrollManager()
{
}

gxScrollManager::~gxScrollManager()
{
}

void gxScrollManager::SetScroll(const int aScrollX, const int aScrollY)
{
  mScroll.X = aScrollX;
  mScroll.Y = aScrollY;
  mObservers.Notify(new gxNotification());
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

void gxScrollManager::AdjustScrollbars(int aVisibleX, int aRangeX, int aVisibleY, int aRangeY)
{
  int newPosX = 0;
  int newPosY = 0;

  // The new scroll position is proportional to the previous one.
  if (mScroll.X != 0 && aRangeX - aVisibleX > 0)
  {
    float oldPosRatio = (mRange.X - mVisible.X) / (float)mScroll.X;
    newPosX = (int)floor((aRangeX - aVisibleX) / oldPosRatio);
  }

  // The new scroll position is proportional to the previous one.
  if (mScroll.Y != 0 && aRangeY - aVisibleY > 0)
  {
    float oldPosRatio = (mRange.Y - mVisible.Y) / (float)mScroll.Y;
    newPosY = (int)floor((aRangeY - aVisibleY) / oldPosRatio);
  }

  mVisible.X = aVisibleX;
  mRange.X = aRangeX;
  mVisible.Y = aVisibleY;
  mRange.Y = aRangeY;

  SetScroll(newPosX, newPosY);

  mObservers.Notify(new gxScrollRangeChangedNotification(this));
}

void gxScrollManager::AddObserverAndNotify(gxCallback *aCallback)
{
  mObservers.Add(aCallback);
  mObservers.Notify(new gxScrollRangeChangedNotification(this), aCallback);
}