#ifndef gxComposite_h
#define gxComposite_h

#include "core/gxObject.h"
#include "core/gxAssert.h"

#include <list>

// A macro for looping all childrens
#define forEachChild( aItem ) \
    ChildrenType* aItem; \
    for ( ChildIterator it = mChildren.begin(); \
          it != mChildren.end() && ( aItem = Child( it ) ); \
          ++it \
        )
/**
 * @brief A generic class that can contain children of its own kind, therefore
 * allowing  data to be arranged in hierarchical structure, with all objects
 * sharing the same protocol.
 * 
 * This class protocol only deals with parent-children operations. Direct
 * descendants will define more specific operations (eg, Paint).
 *
 */
template <class tComposite>
class gxComposite: public gxObject
{
public:
    typedef tComposite                  ChildrenType;
    typedef std::list< gxComposite* >   Children;
    typedef typename Children::iterator ChildIterator;
    
    gxComposite()
    {
        mParent = NULL;
    }
    
    // A virtual destructor is a must or a polymorphic derived class destructor
    // won't be called.
    virtual ~gxComposite()
    {
        RemoveAllChildren( true );
        
        if ( GetParent() != NULL )
            GetParent()->RemoveChild( this );
    }

    /**
     * @brief Adds a new child to this object.
     * @param aChild The child to be added
     */
    void AddChild( gxComposite *aChild )
    {
        // Make sure child isn't null
        gxASSERT( aChild == NULL, "Null paased to AddChild" );
        
        // Check for cycle in hierarchy
        for ( gxComposite* f = this; f!= NULL; f = f->GetParent() )
        {
            gxASSERT( aChild == f,
                     "Cycle in Hierarchy when trying to add a child" );
        }
        
        // Set the child parent to this
        aChild->SetParent( this );
        
        // Add to children list
        mChildren.push_back( aChild );
        
        // Notify
        OnAddChild( (tComposite*)aChild );
    }

    /**
     * @brief Removes a child from this object.
     * @param aChild The child to be deleted
     * @param aAndDelete Whether or not the child object should be deleted and
     * nulled.
     */
    void RemoveChild( gxComposite* aChild,
                      bool         aAndDelete = false )
    {
        // Make sure it is one of my children
        gxASSERT( aChild->GetParent() != this,
                 "RemoveChild is called on a wrong parent." );
        
        // Notify
        OnBeforeChildRemoval( (tComposite*)aChild ) ;
        
        // Remove from children list
        mChildren.remove( aChild );
        
        // Set child parent to NULL (but don't call again RemoveChild on this)
        aChild->SetParent( NULL, false );
        
        // Delete if requested
        if ( aAndDelete )
        {
            delete aChild;
            aChild = NULL;
        }
        
        OnAfterChildRemoval();
    }

    /**
     * @brief Removes all object children.
     * @param aAndDelete Whether or nor removed children are deleted and nulled
     */
    void RemoveAllChildren( bool aAndDelete = false )
    {
        for ( ChildIterator it = mChildren.begin(); !mChildren.empty(); it = mChildren.begin() )
        {
            RemoveChild( *it, aAndDelete );
        }
    }

    /**
     * @brief Returns the parent of this object.
     * @return The parent
     */
    tComposite* GetParent() const
    {
        return (tComposite*)mParent;
    }
    
    /**
     * @brief Sets the parent of this object.
     * @param aParent The parent object
     * @param aAndRemoveFromParent Whether or not to call RemoveChild on the
     * parent. Default to True
     */
    void SetParent( gxComposite* aParent,
                    bool         aAndRemoveFromParent = true )
    {
        // Detach from previous parent
        if ( aAndRemoveFromParent && GetParent() != NULL )
            GetParent()->RemoveChild( this );
            
            mParent = aParent;
    }
    
    /**
     * @brief Returns the children of this object.
     * @return An std::list representing the children
     */
    Children GetChildren() { return mChildren; }

    /**
     * @brief Returns true if this object has no children.
     * @return ture if the object has no children
     */
    bool IsChildless() { return mChildren.empty(); }

    /**
     * @brief Returns true if this object has children.
     * @return ture if the object has children
     */
    bool HasChildren() { return !mChildren.empty(); }
protected:
    /**
     * @brief A virtual method that will be called whenever a child is added.
     * @param aChild The child that was added
     */
    virtual void OnAddChild( tComposite* aChild ) { }
    /**
     * @brief A virtual method that will be called whenever a child is about to
     * be removed.
     * @param aChild The child that was removed
     */
    virtual void OnBeforeChildRemoval( tComposite* aChild ) { }

    /**
     * @brief A virtual method that will be called after a child has been removed.
     *
     * This will give view elements a chance to, for example, revalidate
     * themselves.
     */
    virtual void OnAfterChildRemoval() { }

    /**
     * @brief Convinience method for type casting.
     * @param it The iterator to be casted
     * @return A typecasted child
     */
    tComposite* Child( ChildIterator it ) { return (tComposite*)(*it); }

    /// the children this object contains
    Children     mChildren;
    /// the parent of this object
    gxComposite* mParent;
};

#endif // gxComposite_h