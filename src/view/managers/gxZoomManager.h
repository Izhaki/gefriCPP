#ifndef gxZoomManager_h
#define gxZoomManager_h

#include "core/gxObject.h"
#include "core/gxObserverList.h"

/**
 * @brief A class representing zoom levels.
 */
class gxZoom
{
public:
  float h, v;

  gxZoom() : h(1), v(1) {}
  gxZoom(float aH, float aV): h(aH), v(aV) {}
};

/**
 * @brief Manages zoom by providing clients advance zoom modification protocol
 * and the ability to notify observers on changes.
 */
class gxZoomManager: public gxObject
{
public:
  gxZoomManager();
  ~gxZoomManager(); 


  /**
   * @brief Returns the current zoom.
   * @return The current zoom.
   */
  gxZoom GetZoom() const;
  
  /**
   * @brief Sets the Zoom to the given values.
   * @param aZoomV The vertical zoom factor.
   * @param aZoomH The horizontal zoom factor.
   */
  void SetZoom(const float aZoomH, const float aZoomV);

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
  void MultiplyZoom(const float aMultiplierH, const float aMultiplierV);

  /**
   * @brief A convinience method for multiplying both the horizontal and
   * vertical  zoom by the same multiplier.
   * @param aMultiplier Both the vertical and horizontal multiplier.
   */
  void MultiplyZoom(const float aMultiplier);

  /**
   * @brief Adds an observer to the observers list and notify to the added
   * observer only.
   * @param aCallback The callback to add to the observers list.
   */
  void AddObserverAndNotify(gxCallback *aCallback);
  
  gxObserverList mObservers;
private:
  gxZoom mZoom;
};

/**
 * @brief A notification object to inform observers of zoom changes.
 */
class gxZoomChangedNotification: public gxNotification
{
public:
  gxZoomChangedNotification(const gxZoomManager *aZoomManager)
    : zoomH(aZoomManager->GetZoom().h), zoomV(aZoomManager->GetZoom().v) { }
  float zoomH;
  float zoomV;
};

#endif // gxZoomManager_h