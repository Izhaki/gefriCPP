#ifndef gxObserverList_h
#define gxObserverList_h

#include "core/gxCallback.h"
#include "core/gxObject.h"

#include <vector>
typedef std::vector < gxCallback* > ObserverList;

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
   * @brief Notifies all observers (that is, calls all the callbacks in the
   * list.
   * @param aSubject The parameter passed to the callbacks.
   */
  void Notify(gxObject *aSubject);

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