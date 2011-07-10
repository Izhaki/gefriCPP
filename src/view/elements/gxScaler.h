#ifndef gxScaler_h
#define gxScaler_h

#include "view/elements/gxStructuralViewElement.h"
#include "view/managers/gxZoomManager.h"

/**
 * @brief A view element that scales (zoom) all its children.
 * 
 * Scalers are inserted into the hierarchy of of view elements to facilitate
 * zooming.
 * 
 * This class provides a very simply protocol for setting the scale 
 * (@link gxScaler::SetScale SetScale), but is intendent to be used with
 * @link gxZoomManager gxZoomManager} which provide additional methods for zoom
 * manipulation.
 */
class gxScaler: public gxStructuralViewElement
{
public:
  gxScaler();
  gxScaler(gxZoomManager *aZoomManager);
  ~gxScaler();

  /**
   * @brief Sets the {@link gxZoomManager zoom manager} for this scaler.
   * @param aZoomManager The new {@link gxZoomManager zoom manager}.
   */
  void SetZoomManager(gxZoomManager *aZoomManager);
  
  /**
   * @brief Sets the scale.
   * @param aScaleX the X axis scale
   * @param aScaleY the Y axis scale
   */
  void SetScale(float aScaleX, float aScaleY);

  /**
   * @brief A handler method for zoom change notifications from the
   * {@link gxZoomManager zoom manager}.
   * @param aSubject The object that triggered the notification.
   */
  void OnZoomManagerUpdate(const gxObject *aSubject); 

  /**
   * @brief Paints the view element by scaling the painter then calling
   * {@link gxViewElement::PaintChildren() PaintChildren()}.
   * 
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  void Paint(gxPainter &aPainter);
  
  virtual void TranslateToParent(gxRect &aRect);
protected:
  gxZoomManager *mZoomManager;
private:
  float mScaleX;
  float mScaleY;
};

#endif // gxScaler_h