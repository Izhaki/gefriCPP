#ifndef gxScaler_h
#define gxScaler_h

#include "lightweights/gxStructuralViewElement.h"

class gxScaler: public gxStructuralViewElement
{
public:
  gxScaler();
  ~gxScaler();

  /**
   * @brief Sets the scale.
   * @param aScaleX the X axis scale
   * @param aScaleY the Y axis scale
   */
  void SetScale(float aScaleX, float aScaleY);

  /**
   * @brief Multiplies the scale by the given X and Y factor
   * @param aXfactor Yey! The X Factor
   * @param aYfactor The Y Factor
   */
  void MultiplyScale(float aXfactor, float aYfactor);

  /**
   * @brief Paints the view element by scaling the painter then calling
   * {@link gxViewElement::PaintChildren() PaintChildren()}.
   * 
   * @param aPainter The {@link gxPainter painter} to be used for drawing.
   */
  void Paint(gxPainter &aPainter);
  
  virtual void TranslateToParent(gxRect &aRect);
  
private:
  float mScaleX;
  float mScaleY;
};

#endif // gxScaler_h