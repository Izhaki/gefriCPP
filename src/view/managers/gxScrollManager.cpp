#include "view/managers/gxScrollManager.h"#include <wx/log.h>
gxScrollManager::gxScrollManager()
  : mScrollX(0), mScrollY(0){}
gxScrollManager::~gxScrollManager(){}

void gxScrollManager::SetScroll(const int aScrollX, const int aScrollY)
{
  mScrollX = aScrollX;
  mScrollY = aScrollY;
  mObservers.Notify(this);
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
  mObservers.Notify(this);
}

void gxScrollManager::SetScrollY(const int aScrollY)
{
  mScrollY = aScrollY;
  mObservers.Notify(this);
}

int gxScrollManager::GetScrollX() const
{
  return mScrollX;
}
int gxScrollManager::GetScrollY() const
{
  return mScrollY;
}