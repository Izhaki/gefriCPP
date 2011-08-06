#ifndef gxVisualViewElement_h
#define gxVisualViewElement_h

#include "view/elements/gxViewElement.h"

/**
 * @brief A view element that has visual representation and defined bounds,
 * like shapes.
 */
class gxVisualViewElement: public gxViewElement
{
public:
  gxVisualViewElement();
  gxVisualViewElement(const gxRect &aBounds);
  ~gxVisualViewElement();

  /**
   * @brief Paints the view element, by calling {@link
   * gxViewElement::PaintSelf() PaintSelf()}, {@link
   * gxViewElement::PaintChildren() PaintChildren()} and then
   * {@link gxViewElement::PaintBorder() PaintBorder()}
   *
   * As part of the default painting mechanism, visual view elements clip the
   * painting of their children to their bounds.
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  void Paint(gxPainter &aPainter);

  /**
   * @brief Returns the bounds of this view element.
   */
  gxRect GetBounds() const;

  /**
   * @brief Sets new bounds to this view element.
   * @param aNewBounds The new bounds
   */
  virtual void SetBounds(const gxRect &aNewBounds);
  
  virtual void GetChildrenBounds(gxRect &aBounds);
protected:
  /**
   * @brief Paints graphics related to this view element.
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  virtual void PaintSelf(gxPainter &aPainter) {}
  /**
   * @brief Paints the children of this view element.
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  virtual void PaintChildren(gxPainter &aPainter);

  /**
   * @brief Paints the border of this view element.
   * 
   * As children might overpaint any borders painted by {@link
   * gxViewElement::PaintSelf() PaintSelf()}, this method
   * is called after {@link gxViewElement::PaintChildren() PaintChildren()}
   * to paint any borders of the view element.
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  virtual void PaintBorder(gxPainter &aPainter) {};

  /**
   * @brief Translates (moves) the element.
   * @param dx The amount of pixels to move on the X axis.
   * @param dy The amount of pixels to move on the Y axis.
   */
  void Translate(int dx, int dy);

  /// The bounds of this view element
  gxRect mBounds;
};

#endif // gxVisualViewElement_h