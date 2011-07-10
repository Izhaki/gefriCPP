#ifndef gxCallback_h
#define gxCallback_h

#include "core/gxObject.h"

// A helper macro for the creation of callbacks. Example usage:
// ZoomManager.Observers.Attach( CALLBACK(gxScaler, OnZoomChaged) );
// Needs to be called from within the object that has the method
// (because of 'this').
#define CALLBACK(aClass, aMethod) \
  new gxTemplateCallback<aClass>(this, &aClass::aMethod)

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
   * @param aSubject
   */
  virtual void operator()(const gxObject* aSubject) = 0;

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
template <class TClass> class gxTemplateCallback : public gxCallback
{
private:
  // A pointer to the member method.
  void (TClass::*mMethod)(const gxObject*); 
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
  gxTemplateCallback(TClass* aObj, void(TClass::*aMethod)(const gxObject*))
     { mObj = aObj;  mMethod =aMethod; };

  virtual void operator()(const gxObject* aSubject)
   {  (*mObj.*mMethod)(aSubject); }
    
  virtual bool operator==(const gxCallback &aOther) const
  {
    // Try to type cast the abstract callback to the concrete one (will return null if not successful).
    const gxTemplateCallback<TClass>* const other = dynamic_cast<const gxTemplateCallback<TClass>*>(&aOther);
    if (other)
    {
      return (other->mObj == mObj && other->mMethod == mMethod);
    } else {
      return false;
    }
  }
};

#endif // gxCallback_h