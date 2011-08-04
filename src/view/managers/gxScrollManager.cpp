#include "view/managers/gxScrollManager.h"
#include <wx/log.h>
#include <math.h>

gxScrollManager::gxScrollManager()
  : mScrollX(0), mScrollY(0), mVisibleX(0), mRangeX(0), mVisibleY(0), mRangeY(0)
{
}

gxScrollManager::~gxScrollManager()
{
}

void gxScrollManager::SetScroll(const int aScrollX, const int aScrollY)
{
  mScrollX = aScrollX;
  mScrollY = aScrollY;
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
  mScrollX = aScrollX;
  mObservers.Notify(new gxScrollPositionChangedNotification(this));
}

void gxScrollManager::SetScrollY(const int aScrollY)
{
  mScrollY = aScrollY;
  mObservers.Notify(new gxScrollPositionChangedNotification(this));
}

void gxScrollManager::AdjustScrollbars(int aVisibleX, int aRangeX, int aVisibleY, int aRangeY)
{
  int newPosX = 0;
  int newPosY = 0;

  // The new scroll position is proportional to the previous one.
  if (mScrollX != 0 && aRangeX - aVisibleX > 0)
  {
    float oldPosRatio = (mRangeX - mVisibleX) / (float)mScrollX;
    newPosX = (int)floor((aRangeX - aVisibleX) / oldPosRatio);
  }

  // The new scroll position is proportional to the previous one.
  if (mScrollY != 0 && aRangeY - aVisibleY > 0)
  {
    float oldPosRatio = (mRangeY - mVisibleY) / (float)mScrollY;
    newPosY = (int)floor((aRangeY - aVisibleY) / oldPosRatio);
  }

  mVisibleX = aVisibleX;
  mRangeX = aRangeX;
  mVisibleY = aVisibleY;
  mRangeY = aRangeY;

  SetScroll(newPosX, newPosY);

  mObservers.Notify(new gxScrollRangeChangedNotification(this));
}

void gxScrollManager::AddObserverAndNotify(gxCallback *aCallback)
{
  mObservers.Add(aCallback);
  mObservers.Notify(new gxScrollRangeChangedNotification(this), aCallback);
}