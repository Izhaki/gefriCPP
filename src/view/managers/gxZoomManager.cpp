#include "gxZoomManager.h"

gxZoomManager::gxZoomManager()
{
}

gxZoomManager::~gxZoomManager()
{
}

gxScale gxZoomManager::GetZoom() const
{
  return mZoom;
}

void gxZoomManager::SetZoom(const float aZoomH, const float aZoomV)
{
  mZoom.X = aZoomH;
  mZoom.Y = aZoomV;
  mObservers.Notify(new gxZoomChangedNotification(this));
}

void gxZoomManager::SetZoom(const float aZoom)
{
  mZoom.X = aZoom;
  mZoom.Y = aZoom;
  mObservers.Notify(new gxZoomChangedNotification(this));
}

void gxZoomManager::MultiplyZoom(const float aMultiplierH, const float aMultiplierV)
{
  mZoom.X *= aMultiplierH;
  mZoom.Y *= aMultiplierV;
  mObservers.Notify(new gxZoomChangedNotification(this));
}

void gxZoomManager::MultiplyZoom(const float aMultiplier)
{
  mZoom.X *= aMultiplier;
  mZoom.Y *= aMultiplier;
  mObservers.Notify(new gxZoomChangedNotification(this));
}

void gxZoomManager::AddObserverAndNotify(gxCallback *aCallback)
{
  mObservers.Add(aCallback);
  mObservers.Notify(new gxZoomChangedNotification(this), aCallback);
}