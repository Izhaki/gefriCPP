#ifndef gxScroller_h
#define gxScroller_h

#include "view/elements/gxStructuralViewElement.h"
#include "view/managers/gxScrollManager.h"
#include "view/gxTransformations.h"

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
   * @param aScrollX The X axis scroll
   * @param aScaleY The Y axis scroll
   */
  void SetScroll(gxScroll const &aScroll);

  /**
   * @brief A handler method for scroll change notifications from the
   * {@link gxScrollManager scroll manager}.
   * @param aNotification The notification object.
   */
  void OnScrollPositionUpdate(const gxScrollPositionChangedNotification *aNotification);
  DECLARE_CALLBACK(gxScroller, OnScrollPositionUpdate, gxScrollPositionChangedNotification)

  /**
   * @brief A  handler method for scroll range change notifications from the
   * {@link gxScrollManager scroll manager}.
   * @param aNotification The notification object.
   */
  void OnScrollRangeUpdate(const gxScrollRangeChangedNotification *aNotification);
  DECLARE_CALLBACK(gxScroller, OnScrollRangeUpdate, gxScrollRangeChangedNotification)

  /**
   * @brief Paints the view element by translating the painter then calling
   * {@link gxViewElement::PaintChildren() PaintChildren()}.
   * 
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  void Paint(gxPainter &aPainter);

protected:
  virtual void Transform(gxRect &aRect, gxTransformFlags &aTransFlags);

  bool ValidateSelf();

  /**
   * @brief This method is called when the scroller needs to readjust the
   * scroll bars associated with it.
   */
  void ReadjustScrollbars();

  gxScrollManager *mScrollManager;
private:
  gxScroll mScroll;
};

#endif // gxScroller_h