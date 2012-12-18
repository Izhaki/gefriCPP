#ifndef gxObservable_h
#define gxObservable_h

#include <vector>
#include "core/observable/gxOldCallback.h"

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
    void Fire( evEvent *aEvent, gxOldCallback *aCallback = NULL);
    
    void Subscribe( gxOldCallback *aCallback );
    void Unsubscribe( gxOldCallback *aCallback );
    
private:
    typedef std::vector < gxOldCallback* > CallbackList;

    void UnsubscribeAll();
    bool AlreadySubscribed( gxOldCallback *aCallback );
  
    CallbackList mCallbacks;
};

#endif // gxObservable_h