#ifndef gxObservable_h
#define gxObservable_h

#include <vector>
#include "core/observable/gxCallback.h"

class evEvent
{
public:
  // A dummy virtual method to make this class polymorphic
  virtual void dummy() { }
};


class gxObservable
{
public:
    ~gxObservable();
    
    void Fire( evEvent *aEvent, gxCallback *aCallback = NULL);
    
    void Subscribe( gxCallback *aCallback );
    void Unsubscribe( gxCallback *aCallback );
    
private:
    typedef std::vector < gxCallback* > CallbackList;

    void UnsubscribeAll();
    bool AlreadySubscribed( gxCallback *aCallback );
  
    CallbackList mCallbacks;
};

#endif // gxObservable_h