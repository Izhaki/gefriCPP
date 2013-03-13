#ifndef gxViewElement_h
#define gxViewElement_h

#include "core/geometry/gxGeometry.h"
#include "core/gxComposite.h"
#include "View/Painters/gxPainter.h"
#include "View/gxTransformations.h"
#include "View/Layouts/gxLayout.h"

// Forward declarations
class gxRootViewElement;
class gxLightweightSystem;

/**
 * @brief A class representing a lightweight object that is part of the view
 * layer.
 *
 * View elements are of two principle kinds (each represented by a
 * corresponding subclass):
 *
 * - {@link gxVisual Visual view element} - a view element that has
 *    a visual representation (ie, it can be seen) and has defined bounds. For
 *    example, shapes like circles and rectangles. 
 * - {@link gxStructural Structural view element} - a view
 *   element that is added to the hierarchy to preform a specific task. These
 *   by default behave as transparent objects that has the bounds of
 *   their parent. Examples are layers, scaler, or a {@link gxRootViewElement 
 *   root view element}.
 */
class gxViewElement: public gxComposite<gxViewElement>
{
public:
    gxViewElement();
    ~gxViewElement();

    /**
     * @brief Paints the view element and its children.
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    virtual void Paint( gxPainter& aPainter ) = 0;
    
    /**
     * @brief Called when the figure needs to be repainted
     */
    virtual void Repaint() = 0;

    /**
     * @brief Repaints part or the whole of the view element.
     * @param aBounds The bounds of the area to be repainted.
     */
    virtual void Repaint( gxRect& aBounds,
                          bool    areRelative );
    
    /**
     * @brief Erases the view element from the view.
     *
     * Erase() achieves its task by requesting a repaint of the view element
     * bounds.
     *
     * Note that this method does not call erase on the children, so it assumes
     * that all children are drawn within the bounds of their parent.
     */
    void Erase();

    /**
     * @brief Returns the bounds of this view element.
     *
     * This abstract method is implemented by subclasses.
     */
    virtual gxRect GetBounds() const = 0;

    /**
     * @brief Returns the inner bounds of this view element, accounting for
     * border and insets if any.
     */
    virtual gxRect GetInnerBounds() const { return GetBounds(); }
    
    /**
     * @brief Returns the outer bounds of this view element, accounting for
     * shadows.
     */
    virtual gxRect GetOuterBounds() const { return GetBounds(); }

    /**
     * @brief Sets new bounds to this view element.
     * @param aNewBounds The new bounds
     */
    virtual void SetBounds( const gxRect& aNewBounds ) = 0;
    
    /**
     * @brief Returns the union of all descendant bounds.
     *
     * This is a recursive method that travels down the composition tree to
     * all children and their childrean and so on, but only if needed. So for
     * instance, a visual that clips its children wouldn't traverse them.
     *
     * @param aBounds The bounds to union all children with.
     */
    virtual void GetDescendantsBounds( gxRect& aBounds );

    /**
     * @brief Returns whether or not the view element is visible.
     * @return Ture if the view element is visible.
     */
    bool IsVisible();
    
    /**
     * @brief Sets whether or not the view element is visible.
     * @param aVisible whether or not the view element should be visible.
     */
    virtual void SetVisible( bool const aVisible );

    /**
     * @brief Marks the view element as visible.
     */
    void Show();

    /**
     * @brief Hides the view element (marking it as invisible).
     */
    void Hide();

    /**
     * @brief Transforms a rect (typically bounds) to the coordinates of this
     * element. Normally called by children.
     *
     * Subclasses will override this method to perform their own translations.
     *
     * Used by TransformToAbsolute.
     * @param aRect The rect to transform.
     */
    virtual void Transform( gxRect &aRect );
    
    /**
     * @brief Transforms a rect (typically bounds) to absolute coordinates.
     *
     * This is a recursive method that goes all the way up the parent tree.
     * @param aRect The rect to transform.
     */
    virtual void TransformToAbsolute( gxRect &aRect );
    
    
    virtual void TransformToLocal( gxRect &aRect );
    
    /**
     * @brief Marks the view element and all of its parents as invalid, and
     * notifies all descendents that their ancestor is now invalid. But calling
     * InvalidateUp() and InvalidateDown().
     *
     * This method is called whenever the size or position of the element
     * changes, so to let ancestors and descendents a chance to respond to the
     * change.
     *
     * For example, a layout will need to update all children if one changes
     * position; a Scroller might need to readjust the scrollbar range when a
     * child grows in size.
     *
     * Once invalidation reaches the root view element, it will queue a
     * validation request in the event loop, which once processed will validate
     * all invalid figures.
     */
    void Invalidate();
    
    // Layout related methods
    
    void SetLayout( gxLayout* aLayout );
    
    /**
     * @brief Layouts the children of this view element.
     */
    void Layout();
protected:
    /**
     * @brief Paints the children of this view element.
     *
     * This is an abstract methods that subclasses will override.
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    virtual void PaintChildren( gxPainter &aPainter ) = 0;

    /**
     * @brief Returns the {@link gxLightweightSystem lightweight system}
     * associated with this view element (and all its children).
     */
    
    virtual gxLightweightSystem* GetLightweightSystem() const;

    /**
     * @brief Returns the {@link gxRootViewElement root element} of the hierarchy
     * by traversing up the hierarchy until hitting the root.
     */
    virtual const gxRootViewElement* GetRootViewElement() const;

    // Validation related methods

    /**
     * @brief Marks the view element and all of its parents as invalid.
     *
     * Once invalidation reaches the root view element, it will queue a
     * validation request in the event loop, which once processed will validate
     * all invalid figures.
     */
    virtual void InvalidateUp();    

    /**
     * @brief This method notifies all descendents that one of their ancestors
     * is invalid.
     *
     * Often view elements need to know if their ancestor change. For instance,
     * when its parent has moved, a source figure for a connection will need
     * to update the connection anchor position.
     */
    void InvalidateDown();
    
    /**
     * @brief A virtual method to handle changes in ancestors.
     *
     * Called by AncestorChanged().
     */
    virtual void OnAncestorInvalid() {}
    
    
    /**
     * @brief Asks the view element to perform any operations that are needed
     * to make it valid. Also validates all children.
     *
     * Note that subclasses are likely to need to call the base class
     * validate, so chilren are also validated and the view element is marked as
     * valid.
     */
    virtual void Validate();

    /**
     * @brief Marks this view element as invalid (sets th valid flag to false);
     */
    void MarkInvalid();

    /**
     * @brief Marks this view element as valid (sets th valid flag to true);
     */
    void MarkValid();

    /**
     * @brief Returns whether or not the view element is valid.
     * @return True if the view element is valid.
     */
    bool IsValid();

    /**
     * @brief Returns whether or not the view element is invalid.
     * @return True if the view element is invalid.
     */
    bool IsInvalid();
        
    /**
     * @brief Returns whether or not the view element clips its children.
     * @return Ture if it clips.
     */
    bool IsClippingChildren();
    
    /**
     * @brief Returns whether or not the view element is positioned relative
     * to its parent.
     * @return Ture if it is relative.
     */
    bool IsRelative();

    
    virtual void OnAddChild( gxViewElement *aChild );
    virtual void OnBeforeChildRemoval( gxViewElement *aChild );
    virtual void OnAfterChildRemoval();

    enum Flags
    {
        Valid        = 0x01,
        Visible      = 0x02,
        ClipChildren = 0x04,
        Relative     = 0x08
    };
  
    gxFlags<gx8Flags> mFlags;
    
    gxLayout*         mLayout;
};

#endif // gxViewElement_h