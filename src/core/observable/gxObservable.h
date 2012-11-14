#ifndef gxObservable_h
#define gxObservable_h

#include <vector>
#include "core/observable/gxCallback.h"

class evEvent
{
public:
    // A virtual destructor to make this class polymorphic. This is needed
    // so dynamic_cast can work. Also this will lead to the destructors
    // of derived classes to be called when the generic evEvent is destroyed.
    virtual ~evEvent() { }
};


class gxObservable
{
public:
    virtual ~gxObservable();
    
    // TODo: docs
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