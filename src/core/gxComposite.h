#ifndef gxComposite_h
#define gxComposite_h

#include "core/gxObject.h"

#include <list>

// forward decleration (for the list)
class gxComposite;

typedef std::list< gxComposite* > Children;
typedef Children::iterator ChildIterator;

// A macro with common implementation for direct descendants
// Largly implementing typecasting.
#define IMPLEMENT_COMPOSITE(compositeclass)                             \
public:                                                                 \
  compositeclass* GetParent() const { return (compositeclass*)mParent; } \
protected:                                                              \
  compositeclass* Child(ChildIterator it)                               \
    { return ((compositeclass*)(*it)); }                                \
  virtual void OnAddChild(gxComposite* aChild)                          \
    { OnAddChild((compositeclass*)aChild); }                            \
  virtual void OnAddChild(compositeclass* aChild);                      \
  virtual void OnBeforeChildRemoval(gxComposite* aChild)                \
    { OnBeforeChildRemoval( (compositeclass*)aChild ); }                \
  virtual void OnBeforeChildRemoval(compositeclass* aChild);

// A macro for looping all childrens
#define EACHCHILD ChildIterator it = mChildren.begin(); it != mChildren.end(); ++it
#define CHILD Child(it)

/**
 * @brief A generic class that can contain children of its own kind, therefore allowing 
 * data to be arranged in hierarchical structure, with all objects sharing the
 * same protocol.
 * 
 * This class protocol only deals with parent-children operations. Direct
 * descendants will define more specific operations (eg, Paint).
 *
 */
class gxComposite: public gxObject
{
public:
    gxComposite();
    
    // A virtual destructor is a must or a polymorphic derived class destructor
    // won't be called.
    virtual ~gxComposite();

  /**
   * @brief Adds a new child to this object.
   * @param aChild The child to be added
   */
  void AddChild(gxComposite *aChild);

  /**
   * @brief Removes a child from this object.
   * @param aChild The child to be deleted
   * @param aAndDelete Whether or not the child object should be deleted and nulled
   */
  void RemoveChild(gxComposite *aChild, bool aAndDelete = false);

  /**
   * @brief Removes all object children.
   * @param aAndDelete Whether or nor removed children are deleted and nulled
   */
  void RemoveAllChildren(bool aAndDelete = false);

  /**
   * @brief Sets the parent of this object.
   * @param aParent The parent object
   * @param aAndRemoveFromParent Whether or not to call RemoveChild on the
   *              parent. Default to True
   */
  void SetParent(gxComposite* aParent, bool aAndRemoveFromParent = true);
  /**
   * @brief Returns the parent of this object.
   * @return The parent
   */
  gxComposite* GetParent() { return mParent; }

  /**
   * @brief Returns the children of this object.
   * @return An std::list representing the children
   */
  Children GetChildren() { return mChildren; }
protected:
  /**
   * @brief A virtual method that will be called whenever a child is added.
   *
   * This method will be overriden by the IMPLEMENT_COMPOSITE macro, so
   * when used, subclasses should not override this method, but implement
   * the typecasted version instead; eg, OnAddChild(gxFigure* aChild).
   * @param aChild The child that was added
   */
  virtual void OnAddChild(gxComposite* aChild) { }
   /**
   * @brief A virtual method that will be called whenever a child is about to
   * be removed.
   *
   * This method will be overriden by the IMPLEMENT_COMPOSITE macro, so
   * when used, subclasses should not override this method, but implement
   * the typecasted version instead; eg, OnRemoveChild(gxFigure* aChild).
   * @param aChild The child that was removed
   */ 
  virtual void OnBeforeChildRemoval(gxComposite* aChild) { }

  /**
   * @brief A virtual method that will be called after a child has been removed.
   * 
   * This will give view elements a chance to, for example, revalidate
   * themselves.
   */
  virtual void OnAfterChildRemoval() { }

  /**
   * @brief Convinience method for type casting. Subclasses will override this by using
   * IMPLEMENT_COMPOSITE.
   * @param it The iterator to be casted
   * @return A typecasted child
   */
  gxComposite* Child(ChildIterator it) { return (*it); }

  /// the children this object contains
  Children          mChildren;
  /// the parent of this object
  gxComposite* mParent;
};

#endif // gxComposite_h