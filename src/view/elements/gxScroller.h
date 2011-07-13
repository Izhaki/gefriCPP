#ifndef gxScroller_h
#define gxScroller_h

#include "view/elements/gxStructuralViewElement.h"
#include "view/managers/gxScrollManager.h"

/**
 * @brief A view element that scrolls all its children.
 * 
 * Scrollers are inserted into the hierarchy of of view elements to facilitate
 * scrolling.
 */
class gxScroller: public gxStructuralViewElement
{
public:
  gxScroller();
  gxScroller(gxScrollManager *aScrollManager);
  ~gxScroller();

  /**
   * @brief Sets the {@link gxScrollManager scroll manager} for this scroller.
   * @param aScrollManager The new {@link gxScrollManager scroll manager}.
   */
  void SetScrollManager(gxScrollManager *aScrollManager);
  
  /**
   * @brief Sets the scale.
   * @param aScaleX the X axis scale
   * @param aScaleY the Y axis scale
   */
  void SetScroll(float aScrollX, float aScrollY);

  /**
   * @brief A handler method for scroll change notifications from the
   * {@link gxScrollManager scroll manager}.
   * @param aSubject The object that triggered the notification.
   */
  void OnScrollManagerUpdate(const gxObject *aSubject); 

  /**
   * @brief Paints the view element by scaling the painter then calling
   * {@link gxViewElement::PaintChildren() PaintChildren()}.
   * 
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  void Paint(gxPainter &aPainter);

protected:
  virtual void TransformChild(gxBounds &aBounds);

  gxScrollManager *mScrollManager;
private:
  float mScrollX;
  float mScrollY;
};

#endif // gxScroller_h