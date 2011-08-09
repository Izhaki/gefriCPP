#ifndef gxLightweightSystem_h
#define gxLightweightSystem_h

#include "core/gxObject.h"
#include "core/gxPaintDC.h"
#include "view/elements/gxRootViewElement.h"
#include "view/managers/gxScrollManager.h"
// forward declaration
class gxLightweightControl;

/**
 * @brief A class linking a system-dependent control with the lightweight 
 * system, faciliating the painting of lightweight {@link gxViewElement view
 * elements}.
 *
 * The linked system-dependent control will delegate various system events,
 *  like paint, to this class.
 * This class will send repaint requests to the control.
 */
class gxLightweightSystem: public gxObject
{
public:
  /**
   * The constructor of the lightweight system.
   *
   * Note that during the lifecycle of this object it assumes the linked control
   * was not destoyed.
   * @param aControl - The control linked to this system. Must not be null.
   */
  gxLightweightSystem(gxLightweightControl *aControl);
  ~gxLightweightSystem();

  /**
   * @brief Sets the top-level {@link gxViewElement view element} to be displayed
   * by the lightweight system.
   *
   * It will be added as the only child of the {@link gxRootViewElement root view
   * element}.
   * @param aViewElement The new top-level {@link gxViewElement view element}
   */
  void SetContents(gxViewElement *aViewElement);

  /**
   * @brief Sets the scroll manager.
   * 
   * In case the {@link gxLightweightControl lightweight control was
   * created with scrollbars, it will send scroll events to this class, which the
   * class then delegates to the scroll manager.
   * @param aScrollManager The scroll manager.
   */
  void SetScrollManager(gxScrollManager *aScrollManager);
  // gxLightweightControl delegate methods
  
  /**
    * @brief A Paint event hander.
    *
    * gxLightweightControl Paint Event will be delegated to this method.
   * @param aDc The DC to paint on
   * @param aDamagedRects A vector of damaged rects
   */
  void Paint(gxPaintDC *aDc, gxRects const &aDamagedRects);

  /**
   * @brief Marks a rectangle that needs repainting (and will queue a
   * repaint on the control).
   *
   * {@link gxViewElement View elements} call this method when repaint is
   *  required (like, for example, when they are erased).
   * @param aRect The rect needs repainting.
   */
  void AddDirtyRegion(gxRect &aRect);

  /**
   * @brief Returns the bounds of the control associated with the system.
   */
  gxRect GetControlBounds() const;

  /**
   * @brief Returns the text size for a given string.
   * @param aText The text whose size we equire.
   * @return The given text size.
   */
  gxSize GetTextSize(std::string aText);

  /**
   * @brief Queues an asynchronous validation request.
   * 
   * This will send and event loop an validation request event that will be
   * processed after the currently processed event is handled.
   */
  void QueueValidation();

  /**
   * @brief Handles a validation request that originated from
   * {@link gxLightweightSystem::QueueValidation QueueValidation()}
   */
  void OnValidationRequest();

  /**
   * @brief Called upon scrol events on the control.
   * @param isVertical Whether the scroll was a vertical one (otherwise it's
   * horizontal).
   * @param aPosition The scroll position.
   */
  void OnScroll (const bool isVertical, const int aPosition);

  /**
   * @brief Called when the scroll range of the scroll bars has changed.
   * @param aNotification The notification object carrying information
   * regarding the change.
   */
  void OnScrollRangeChanged(const gxScrollRangeChangedNotification *aNotification);
  DECLARE_CALLBACK(gxLightweightSystem, OnScrollRangeChanged, gxScrollRangeChangedNotification)
protected:
  /**
   * @brief Sets the {@link gxRootViewElement root view element} of the system.
   * @param aRootViewElement The new {@link gxRootViewElement root view 
    * element}.
   */
  void SetRootViewElement(gxRootViewElement *aRootViewElement);

  /// The control this system is linked to.
  gxLightweightControl *mControl;
  
  /// The scroll manager linked to the system.
  gxScrollManager* mScrollManager;

  /// The root view element of this system.
  gxRootViewElement *mRootViewElement;

  /// the top-level view element.
  gxViewElement *mContents;
  
  /// Denotes whether or not a validation request is already queued.
  bool mValidationQueued;
};

#endif // gxLightweightSystem_h