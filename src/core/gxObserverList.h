#ifndef gxObserverList_h
#define gxObserverList_h

#include "core/gxObject.h"
#include "core/gxCallback.h"

#include <vector>
typedef std::vector < gxCallback* > ObserverList;

class gxNotification
{
public:
  // A dummy virtual method to make this class polymorphic
  virtual void dummy() { }
};

/**
 * @brief A class that maintains a list of observers (callbacks), and allows
 * notification to all these observers.
 * 
 * This is gefri's implementation of the subject-observer design pattern.
 * Instead of having the subject protocol hardwired into the inheritance tree,
 * an object wishing to be a subject will have a member of this class.
 */
class gxObserverList
{
public:
  ~gxObserverList();
  
  /**
   * @brief Notifies a single or all observers (that is, all the callbacks in
   * the list).
   * @param aNotification A notification object passed to the callbacks.
   * @param aCallback If provided a notification will only be sent to the
   * give callback. NULL will call all callbacks.
   */
  void Notify(gxNotification *aNotification, gxCallback *aCallback = NULL);

  /**
   * @brief Adds a new callback to the list of observers.
   * @param aCallback The callback to add.
   */
  void Add(gxCallback *aCallback);

  /**
   * @brief Removes a callback from the list of oververs.
   * 
   * Note that this method also deletes the callback from the free stack.
   * @param aCallback The callback to remove
   */
  void Remove(gxCallback *aCallback);
private: 
  /**
   * @brief Removes all callbacks from the list
   * 
   * Note that this method also deletes the callback from the free stack.
   */
  void RemoveAll();
  
  ObserverList mObservers;
};

#endif // gxObserverList_h