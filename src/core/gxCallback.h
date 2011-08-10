#ifndef gxCallback_h
#define gxCallback_h

// Forward Declaration.
class gxNotification;

// Two helper macros to simplify the dealing with callbacks.

// DECLARE_CALLBACK should be placed within the declaration (.h) of the class.
// It stores the method class and the notification class for the gxCALLBACK
// macro. Example usage:
//
// void OnUpdate(const gxUpdateNotification *aNotification);
// DECLARE_CALLBACK(gxScroller, OnUpdate, gxUpdateNotification)
//
// Note: If the callback uses a subclass of gxNotification, it will only receive
// that type of notification. If the callback uses gxNotification, it will
// receive all the notifications from the subject, and can do the cast itself,
// if needed.
#define DECLARE_CALLBACK(aClass, aMethod, aNotificationClass) \
  typedef aClass             C##aMethod; \
  typedef aNotificationClass N##aMethod;

// gxCALLBACK creates a callback object by taking only the method name.
// Example usage:
// mScrollManager->mObservers.Remove( gxCALLBACK( OnUpdate ) );
#define gxCALLBACK(aMethod) \
  new gxTemplateCallback<C##aMethod, N##aMethod>(this, &C##aMethod::aMethod)
 
/**
 * @brief A callback class used in subject-observer communication.
 * 
 * This class overcomes C++ not allowing non-static member methods to
 * be used as callbacks.
 * 
 * This class facilitate notification to arbitrary object
 * methods instead of methods defined on a base class. This generalizes the
 * observer protocol by decoupling it from the inheritance tree, allowing any
 * class to become an observer.
 * 
 * This class is effectively a Functor that keeps a reference to an object and
 * a member method.
 * 
 * For any languages that support a non-static member method calls, this class
 * is not needed.
 */
class gxCallback
{
public:
  /**
   * @brief Overloading the () operator, allowing clients to simply use
   * callback() syntex.
   * @param aNotification A notification object
   */
  virtual void operator()(const gxNotification *aNotification) = 0;

  /**
   * @brief Overloading the comparison operator is needed as we compare
   * callbacks by comparing the instance of their object.
   * 
   * Note that comparison might not work on virtual method.
   */
  virtual bool operator==(const gxCallback &other) const = 0; 
};

/**
 * @brief A template class that implement the actuall callback.
 */
template <class TClass, class TNotification>
class gxTemplateCallback : public gxCallback
{
private:
  // A pointer to the member method.
  void (TClass::*mMethod)(const TNotification*); 
  // A pointer to the object.
  TClass* mObj;
public:
  // constructor - takes pointer to an object and pointer to a member and stores
  // them in two private variables
  /**
   * @brief The callback constuctor. Take two parameters and store them in
   * private members.
   * @param aObj The instance of the observer object.
   * @param aMethod The method to be called.
   */
  gxTemplateCallback(TClass* aObj, void(TClass::*aMethod)(const TNotification*))
     { mObj = aObj;  mMethod =aMethod; };

  virtual void operator()(const gxNotification* aNotification)
  {
    // Try to convert the notification to the type associated with this callback
    // (will return null if fails).
    const TNotification* iNotification = dynamic_cast<const TNotification*> (aNotification);
    // If it's the same notification class then call the method.
    if ( iNotification )
      (*mObj.*mMethod)(iNotification);
  }
    
  virtual bool operator==(const gxCallback &aOther) const
  {
    // Try to type cast the abstract callback to the concrete one (will return null if not successful).
    const gxTemplateCallback<TClass, TNotification>* const iOther = dynamic_cast<const gxTemplateCallback<TClass, TNotification>*>(&aOther);
    if (iOther)
    {
      return (iOther->mObj == mObj && iOther->mMethod == mMethod);
    } else {
      return false;
    }
  }
};

#endif // gxCallback_h