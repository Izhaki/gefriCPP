#ifndef gxComposite_h
#define gxComposite_h

#include "core/gxAssert.h"
#include "core/gxIterator.h"

#include <list>

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
    typedef tComposite                    ChildrenType;
    typedef std::list< tComposite* >      List;
//    typedef typename List::iterator       Eterator;
    typedef typename List::const_iterator ConstIterator;
    
    gxComposite()
    : mParent(NULL)
    { }
    
    // A virtual destructor is a must or a polymorphic derived class destructor
    // won't be called.
    virtual ~gxComposite()
    {
        RemoveAllChildren( true );
        
        if ( HasParent() )
            GetParent()->Remove( This() );
    }
    
    class Iterator: public gxIterator<List>
    {
    public:
        Iterator( List* aList ): gxIterator<List>( aList ) { }
    };
    
    /**
     * @brief Adds a new child to this object.
     * @param aChild The child to be added
     */
    void DoAdd( tComposite* aChild )
    {
        // Make sure child isn't null
        gxWarnIf( aChild == NULL, "Null paased to Add" );
        
        // Check for cycle in hierarchy
        for ( tComposite* f = This();
              f != NULL;
              f  = f->GetParent() )
        {
            gxWarnIf( aChild == f,
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
     * @brief Allows adding up to 8 different children to this object.
     * @param aChild1-8 The children to be added
     */
    void Add( tComposite* aChild1,
              tComposite* aChild2 = NULL,
              tComposite* aChild3 = NULL,
              tComposite* aChild4 = NULL,
              tComposite* aChild5 = NULL,
              tComposite* aChild6 = NULL,
              tComposite* aChild7 = NULL,
              tComposite* aChild8 = NULL )
    {
        DoAdd( aChild1 );
        if ( aChild2 ) DoAdd( aChild2 );
        if ( aChild3 ) DoAdd( aChild3 );
        if ( aChild4 ) DoAdd( aChild4 );
        if ( aChild5 ) DoAdd( aChild5 );
        if ( aChild6 ) DoAdd( aChild6 );
        if ( aChild7 ) DoAdd( aChild7 );
        if ( aChild8 ) DoAdd( aChild8 );
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
        gxWarnIf( aChild->GetParent() != this,
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
        typename List::iterator it;
        for ( it = mChildren.begin();
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
    
    bool HasParent() const
    {
        return mParent != NULL;
    }
    
    bool Parentless() const
    {
        return !HasParent();
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
        if ( aAndRemoveFromParent && HasParent() )
            GetParent()->Remove( This() );
            
            mParent = aParent;
    }
    
    /**
     * @brief Returns the children of this object.
     * @return A pointer to an std::list representing the children
     */
    List* GetChildren() { return &mChildren; }

    /**
     * @brief Returns index of this view element within its parent list of
     * children.
     * @return The index of this element.
     */
    int GetIndex() const
    {
        gxWarnIf( Parentless(),
                  "GetIndex called with no parent." );
        
        return HasParent() ? GetParent()->GetChildIndex( this ) : -1 ;
    }
    
    /**
     * @brief Returns the index of a child within the list of children.
     * @return The index of the child.
     */
    int GetChildIndex( const gxComposite* aChild ) const
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
    List        mChildren;
    /// the parent of this object
    tComposite* mParent;
private:
    inline tComposite* This()
    {
        return static_cast<tComposite*>(this);
    }
};

template< class T >
struct CompositeIndexCompare
{
    bool operator()( gxComposite<T>* const& aL, gxComposite<T>* const& aR)
    {
        return aL->GetIndex() < aR->GetIndex();
    }
};


#endif // gxComposite_h