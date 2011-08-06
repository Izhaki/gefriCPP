#ifndef gxViewElement_h
#define gxViewElement_h

#include "core/geometry/gxGeometry.h"
#include "core/gxComposite.h"
#include "core/gxFlags.h"
#include "view/gxPainter.h"
#include "view/gxBounds.h"


// char used as 1 byte int
#define gxViewElementFlags char

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
 * - {@link gxVisualViewElement Visual view element} - a view element that has
 *    a visual representation (ie, it can be seen) and has defined bounds. For
 *    example, shapes like circles and rectangles. 
 * - {@link gxStructuralViewElement Structural view element} - a view
 *   element that is added to the hierarchy to preform a specific task. These
 *   by default behave as transparent objects that has the bounds of
 *   their parent. Examples are layers, scaler, or a {@link gxRootViewElement 
 *   root view element}.
 */
class gxViewElement: public gxComposite
{
public:
  gxViewElement();
  ~gxViewElement();

  /**
   * @brief Paints the view element and its children.
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  virtual void Paint(gxPainter &aPainter) = 0;

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
  virtual gxBounds GetBounds() const = 0;
  
  /**
   * @brief Returns the union of all desendents bounds.
   * 
   * This is a recursive method.
   * @param aBounds The bounds to union all children with.
   */
  virtual void GetChildrenBounds(gxBounds &aBounds);

protected:
  /**
   * @brief Transforms the bounds to absolute coordinates.
   *
   * This is a recursive method that goes all the way up the parent tree.
   * @param aBounds The bounds to transform
   */
  virtual void TransformToAbsolute(gxBounds &aBounds);

  /**
   * @brief Transforms the bounds of the child to the coordinates of this 
   * parent.
   * 
   * Used by TransformToAbsolute.
   * @param aBounds The bounds to transform.
   */
  virtual void TransformChild(gxBounds &aBounds);
  
  /**
   * @brief Paints the children of this view element.
   *
   * This is an abstract methods that subclasses will override. 
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  virtual void PaintChildren(gxPainter &aPainter) = 0;

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

  /**
   * @brief Repaints the view element making its bounds dirty.
   */
  virtual void Repaint();
  
  /**
   * @brief Repaints part or the whole of the view element.
   * @param aBounds The bounds of the area to be repainted.
   */
  virtual void Repaint(gxBounds &aBounds);

  // Validation related methods
  
  /**
   * @brief Marks the view element is invalid.
   */
  virtual void Invalidate();

  /**
   * @brief Marks the view element as invalid and calls Revalidate on all
   * parents.
   * 
   * This method is called whenever the size or position of the element change,
   * so to let parent objects a change to respond to the change.
   * 
   * For example, a layout will need to update all children if one changes
   * position; a Scroller might need to readjust the scrollbar range when a
   * child grows in size.
   */
  virtual void Revalidate();


  /**
   * @brief Calls ValidateSelf(), and then Validate() on all children.
   */
  virtual void Validate();

  /**
   * @brief Asks the view element to perform any operations that are needed
   * to make it valid
   */
  virtual void ValidateSelf() { }
  
  /**
   * @brief Returns whether or not the view element is valid.
   * @return True if the view element is valid.
   */
  bool IsValid();

  enum Flags
  {
    Valid = 0x01
  };
  
  gxFlags<gx8Flags> mFlags;


  IMPLEMENT_COMPOSITE(gxViewElement)
};

#endif // gxViewElement_h