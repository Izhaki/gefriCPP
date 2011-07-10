#include "core/gxObserverList.h"

gxObserverList::~gxObserverList()
{
  RemoveAll();
}

void gxObserverList::Notify(gxObject *aSubject)
{
  ObserverList::iterator observer;
    
  for (observer = mObservers.begin(); observer != mObservers.end(); ++observer)
  {
    (**observer)(aSubject);
  }
}

void gxObserverList::Add(gxCallback *aCallback)
{
  mObservers.push_back(aCallback);
}

void gxObserverList::Remove(gxCallback *aCallback)
{
  ObserverList::iterator observer;
    
  for (observer = mObservers.begin(); observer != mObservers.end(); ++observer)
  {
    if ( (**observer) == (*aCallback))
    {
      // Both the original callback and the one passed as a parameter are
      // stray pointers, so delete them.
      delete *observer;
      delete aCallback;
      mObservers.erase(observer);
      break;
    }
  }
}

void gxObserverList::RemoveAll()
{
  ObserverList::iterator observer;
    
  for (observer = mObservers.begin(); observer != mObservers.end(); ++observer)
  {
    delete *observer;
    // erase() returns a new valid iterator that exludes the object removed.
    observer = mObservers.erase(observer);
  }
}