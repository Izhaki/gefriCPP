// NOTE - this was not tested because GCC 4.2 lack of support to the sytax of
// callback.hpp and the current complexity in compiling the wxWidgets and
// Gefri with the Apple compiler.

// Nor was callback.cpp modified to support comparison.

#ifndef gxCallbackMai_h
#define gxCallbackMai_h

#include "core/observable/callback.hpp"
#include "core/observable/gxOldCallback.h"

#define mcCallback( aEventClass, aDelegate ) \
    new gxSignedCallback< aEventClass >( util::BIND_MEM_CB( &aDelegate, this ) )

/**
 * @brief A specialised template class that implements a wrapper to an
 * actual callback with a specific event given as a parameter.
 */
template < class TEvent >
class gxSignedCallback : public gxOldCallback
{
public:
    // Typedef our callback signature using FastDelegate
    typedef util::Callback< const TEvent* > gxDelegate;
    
    gxSignedCallback( gxDelegate aDelegate )
    {
        mDelegate = aDelegate;
    }
    
    virtual void operator()(const evEvent* aEvent)
    {
        // Try to convert the event to the type associated with this callback
        // (will return null if fails).
        const TEvent* iEvent = dynamic_cast<const TEvent*> (aEvent);
        
        // If it's the same event class then launch the callback.
        if ( iEvent )
            mDelegate( iEvent );
            }
    
    virtual bool operator==(const gxOldCallback &aOther) const
    {
        // Try to type cast the abstract callback to the concrete one (will return null if not successful).
        const gxSignedCallback< TEvent >* const iOther = dynamic_cast<const gxSignedCallback< TEvent >*>(&aOther);
        
        // If it is the same callback signature
        if ( iOther )
        {
            // It is the same if the delegates are equal
            return ( iOther->mDelegate == mDelegate );
        } else {
            return false;
        }
        
    }
protected:
    gxDelegate mDelegate;
};

#endif // gxCallbackMai_h