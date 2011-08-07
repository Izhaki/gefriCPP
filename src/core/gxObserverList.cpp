#include "core/gxObserverList.h"

gxObserverList::~gxObserverList()
{
  RemoveAll();
}

void gxObserverList::Notify(gxNotification *aNotification, gxCallback *aCallback)
{
  ObserverList::iterator iObserver;
    
  for (iObserver = mObservers.begin(); iObserver != mObservers.end(); ++iObserver)
  {
    // If no particular callback was requested or we are on that particular one,
    // Call the callback
    if (aCallback == NULL || aCallback == *iObserver)
      (**iObserver)(aNotification);
  }
  
  // Clients will call observers.Notify(new gxNotification()), so
  // once we're done notifying delete the notification object. 
  delete aNotification;
}

void gxObserverList::Add(gxCallback *aCallback)
{
  mObservers.push_back(aCallback);
}

void gxObserverList::Remove(gxCallback *aCallback)
{
  ObserverList::iterator iObserver;
    
  for (iObserver = mObservers.begin(); iObserver != mObservers.end(); ++iObserver)
  {
    if ( (**iObserver) == (*aCallback))
    {
      // Both the original callback and the one passed as a parameter are
      // stray pointers, so delete them.
      delete *iObserver;
      delete aCallback;
      mObservers.erase(iObserver);
      break;
    }
  }
}

void gxObserverList::RemoveAll()
{
  ObserverList::iterator iObserver;
    
  for (iObserver = mObservers.begin(); iObserver != mObservers.end(); ++iObserver)
  {
    delete *iObserver;
    // erase() returns a new valid iterator that exludes the object removed.
    iObserver = mObservers.erase(iObserver);
  }
}