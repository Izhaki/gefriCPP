#include "gxObservable.h"


gxObservable::~gxObservable()
{
    UnsubscribeAll();
}

void gxObservable::Fire( evEvent *aEvent, gxCallback *aCallback )
{
    CallbackList::iterator iCallback;
    
    // For each callback
    for ( iCallback = mCallbacks.begin(); iCallback != mCallbacks.end(); ++iCallback )
    {
        // If no particular callback was requested or we are on that particular one,
        if ( aCallback == NULL ||  *aCallback == **iCallback )
        {
            // call the callback (would only happen if it involves the same event type).
            ( **iCallback )( aEvent );
        }
    }
  
    // Clients will call Fire( new evEvent() ), so
    // once we're done notifying delete the event object. 
    delete aEvent;
}

bool gxObservable::AlreadySubscribed( gxCallback *aCallback )
{
    CallbackList::iterator iCallback;

    // For each callback
    for ( iCallback = mCallbacks.begin(); iCallback != mCallbacks.end(); ++iCallback )
    {
        if ( (**iCallback) == (*aCallback) )
            return true;
    }
    
    return false;
}

void gxObservable::Subscribe( gxCallback *aCallback )
{
    // If the callback already subscribed
    if ( AlreadySubscribed( aCallback ) )
    {
        // No use for the passed callback - delete it
        delete aCallback;
    }
    else
    {
        // Add it to the callback list
        mCallbacks.push_back( aCallback );
    }
}

void gxObservable::Unsubscribe( gxCallback *aCallback )
{
    CallbackList::iterator iCallback;

    // For each callback
    for ( iCallback = mCallbacks.begin(); iCallback != mCallbacks.end(); ++iCallback )
    {
        if ( (**iCallback) == (*aCallback) )
        {
            // The original callback is now stary, so delete it and remove from the list
            delete *iCallback;
            mCallbacks.erase(iCallback);
            break;
        }
    }

    // We need to delete the callback we ere looking for whether or not we've found it
    delete aCallback;
}

void gxObservable::UnsubscribeAll()
{
    CallbackList::iterator iCallback;
    
    for ( iCallback = mCallbacks.begin(); iCallback != mCallbacks.end(); ++iCallback )
    {
        delete *iCallback;
    }
    mCallbacks.clear();
}