#ifndef gxCallback_h
#define gxCallback_h

// Forward declaration
class evEvent;

/**
 * @brief An abstract wrapper class for callbacks used in 
 * subject-observer communication.
 * 
 * This class helps overcoming the fact that C++ does not allow non-static
 * member methods to be used as callbacks.
 */
 
class gxCallback
{
public:
  /**
   * @brief Overloading the () operator, allowing clients to simply use
   * iCallback( new SomeEvent() ) syntex.
   * @param aEvent The event to pass to the callback
   */
    virtual void operator()(const evEvent *aEvent) = 0;

  /**
   * @brief Overloading the comparison operator is needed as we compare
   * callbacks by comparing the instance of their object.
   */
    virtual bool operator==(const gxCallback &aOther) const = 0; 
};

// The specialised implementation is being injected here.
#include "core/observable/gxCallbackClugston.h"

#endif // gxCallback_h