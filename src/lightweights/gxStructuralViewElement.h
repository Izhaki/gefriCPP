#ifndef gxStructuralViewElement_h
#define gxStructuralViewElement_h

#include "lightweights/gxViewElement.h"

/**
 * @brief A view element that has no visual representation, but is inserted
 * to the view hierarchy in order to perform certain operations. 
 *
 * Structural view elements have no defined bounds and generally take the bounds
 * of their parent. They behave as transparent elements.
 *
 * Examples of structural view elements include layers, scalers, and
 * {@link gxRootViewElement root view element}.
 */
class gxStructuralViewElement: public gxViewElement
{
public:
  gxStructuralViewElement();
  ~gxStructuralViewElement();

  /**
   * @brief Paints the view element by calling 
   * {@link gxViewElement::PaintChildren() PaintChildren()}.
   * 
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  void Paint(gxPainter &aPainter);

  /**
   * @brief Returns the bounds of this view element.
   */
  virtual gxRect GetBounds() const;
protected:
  /**
   * @brief Paints the children of this view element.
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  virtual void PaintChildren(gxPainter &aPainter);
};

#endif // gxStructuralViewElement_h