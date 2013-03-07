#ifndef gxComposite_h
#define gxComposite_h

#include "core/gxAssert.h"

#include <list>

// A macro for looping all childrens (used from within the composite itself)
#define forEachChild( aItem ) \
    ChildrenType* aItem; \
    for ( ChildIterator it = mChildren.begin(); \
          it != mChildren.end() && ( aItem = *it ); \
          ++it \
        )
// A macro allowing looping all children of a particular composite
#define forEachChildOf( aComposite, aItem ) \
    gxViewElement* aItem; \
    gxViewElement::Children iChildren = aComposite->GetChildren(); \
    for ( gxViewElement::ChildIterator it = iChildren.begin(); \
         it != iChildren.end() && ( aItem = *it ); \
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
class gxComposite
{
public:
    typedef tComposite                  ChildrenType;
    typedef std::list< tComposite* >    Children;
    typedef typename Children::iterator ChildIterator;
    
    gxComposite()
    : mParent(NULL)
    { }
    
    // A virtual destructor is a must or a polymorphic derived class destructor
    // won't be called.
    virtual ~gxComposite()
    {
        RemoveAllChildren( true );
        
        if ( GetParent() != NULL )
            GetParent()->Remove( This() );
    }
    
    

    /**
     * @brief Adds a new child to this object.
     * @param aChild The child to be added
     */
    void Add( tComposite* aChild )
    {
        // Make sure child isn't null
        gxASSERT( aChild == NULL, "Null paased to Add" );
        
        // Check for cycle in hierarchy
        for ( tComposite* f = This();
              f != NULL;
              f  = f->GetParent() )
        {
            gxASSERT( aChild == f,
                     "Cycle in Hierarchy when trying to add a child" );
        }
        
        // Set the child parent to this
        aChild->SetParent( This() );
        
        // Add to children list
        mChildren.push_back( aChild );
        
        // Notify
        OnAddChild( ( tComposite* )aChild );
    }

    /**
     * @brief Removes a child from this object.
     * @param aChild The child to be deleted
     * @param aAndDelete Whether or not the child object should be deleted and
     * nulled.
     */
    void Remove( tComposite* aChild,
                      bool        aAndDelete = false )
    {
        // Make sure it is one of my children
        gxASSERT( aChild->GetParent() != this,
                 "Remove is called on a wrong parent." );
        
        // Notify
        OnBeforeChildRemoval( ( tComposite* )aChild ) ;
        
        // Remove from children list
        mChildren.remove( aChild );
        
        // Set child parent to NULL (but don't call again Remove on this)
        aChild->SetParent( NULL, false );
        
        // Delete if requested
        if ( aAndDelete )
        {
            //TODO: shouldn't the child also delete all its children?
            // Or is it the application that should do so?
            
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
        for ( ChildIterator it = mChildren.begin();
              !mChildren.empty();
              it = mChildren.begin() )
        {
            Remove( *it, aAndDelete );
        }
    }

    /**
     * @brief Returns the parent of this object.
     * @return The parent
     */
    tComposite* GetParent() const
    {
        return mParent;
    }
    
    /**
     * @brief Sets the parent of this object.
     * @param aParent The parent object
     * @param aAndRemoveFromParent Whether or not to call Remove on the
     * parent. Default to True
     */
    void SetParent( tComposite* aParent,
                    bool        aAndRemoveFromParent = true )
    {
        // Detach from previous parent
        if ( aAndRemoveFromParent && GetParent() != NULL )
            GetParent()->Remove( This() );
            
            mParent = aParent;
    }
    
    /**
     * @brief Returns the children of this object.
     * @return An std::list representing the children
     */
    Children GetChildren() { return mChildren; }

    /**
     * @brief Returns index of this view element within its parent list of
     * children.
     * @return The index of this element.
     */
    int GetIndex()
    {
        gxASSERT( GetParent() == NULL,
                 "GetIndex called with no parent." );
        
        return GetParent()->GetChildIndex( this );
    }
    
    /**
     * @brief Returns the index of a child within the list of children.
     * @return The index of the child.
     */
    int GetChildIndex( gxComposite* aChild )
    {
        return distance( mChildren.begin(),
                         find( mChildren.begin(), mChildren.end(), aChild ) );
    }

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

    /// the children this object contains
    Children    mChildren;
    /// the parent of this object
    tComposite* mParent;
private:
    inline tComposite* This()
    {
        return static_cast<tComposite*>(this);
    }
};

#endif // gxComposite_h