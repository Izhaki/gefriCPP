#include "gxZoomManager.h"

gxZoomManager::gxZoomManager()
{
  mZoom = gxZoom(1, 1);
}

gxZoomManager::~gxZoomManager()
{
}

gxZoom gxZoomManager::GetZoom() const
{
  return mZoom;
}

void gxZoomManager::SetZoom(const float aZoomH, const float aZoomV)
{
  mZoom.h = aZoomH;
  mZoom.v = aZoomV;
  mObservers.Notify(new gxZoomChangedNotification(this));
}

void gxZoomManager::SetZoom(const float aZoom)
{
  mZoom.h = aZoom;
  mZoom.v = aZoom;
  mObservers.Notify(new gxZoomChangedNotification(this));
}

void gxZoomManager::MultiplyZoom(const float aMultiplierH, const float aMultiplierV)
{
  mZoom.h *= aMultiplierH;
  mZoom.v *= aMultiplierV;
  mObservers.Notify(new gxZoomChangedNotification(this));
}

void gxZoomManager::MultiplyZoom(const float aMultiplier)
{
  mZoom.h *= aMultiplier;
  mZoom.v *= aMultiplier;
  mObservers.Notify(new gxZoomChangedNotification(this));
}

void gxZoomManager::AddObserverAndNotify(gxCallback *aCallback)
{
  mObservers.Add(aCallback);
  mObservers.Notify(new gxZoomChangedNotification(this), aCallback);
}