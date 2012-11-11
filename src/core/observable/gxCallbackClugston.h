#ifndef gxCallbackClugston_h
#define gxCallbackClugston_h

#include "core/observable/FastDelegate.h"
#include "core/observable/gxCallback.h"

#include "core/gxLog.h"

#define mcCallback( aEventClass, aDelegate ) \
    new gxSignedCallback< aEventClass >( fastdelegate::MakeDelegate( this, &aDelegate ) )

/**
 * @brief A specialised template class that implements a wrapper to an 
 * actual callback with a specific event given as a parameter.
 */
template < class TEvent >
class gxSignedCallback : public gxCallback
{
public:
    // Typedef our callback signature using FastDelegate
    typedef fastdelegate::FastDelegate1< const TEvent* > gxDelegate;

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
  
    virtual bool operator==(const gxCallback &aOther) const
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

#endif // gxCallbackClugston_h