#ifndef gxZoomManager_h
#define gxZoomManager_h#include "core/gxObject.h"
#include "core/gxObserverList.h"
class gxZoom{public:  float v, h;  gxZoom() : v(1), h(1) {}  gxZoom(float aV, float aH): v(aV), h(aH) {}};class gxZoomManager: public gxObject
{
public:
  gxZoomManager();
  ~gxZoomManager(); 


  gxZoom GetZoom() const;
  /**
   * @brief Sets the Zoom to the given values.
   * @param aZoomV The vertical zoom factor.
   * @param aZoomH The horizontal zoom factor.
   */
  void SetZoom(const float aZoomV, const float aZoomH);
  
  /**
   * @brief A convinience method for setting both the vertical and horizontal
   * zoom to the same value.
   * @param aZoom Both the vertical and horizontal zoom factor.
   */
  void SetZoom(const float aZoom);
  
  /**
   * @brief Multiply the current zoom by the given multiplier.
   * @param aMultiplierV The vertical zoom multiplier.
   * @param aMultiplierH The horizontal zoom multiplier.
   */
  void MultiplyZoom(const float aMultiplierV, const float aMultiplierH);
  
  /**
   * @brief A convinience method for multiplying both the horizontal and
   * vertical  zoom by the same multiplier.
   * @param aMultiplier Both the vertical and horizontal multiplier.
   */
  void MultiplyZoom(const float aMultiplier);
  
  gxObserverList mObservers;
private:  gxZoom mZoom;};#endif // gxZoomManager_h