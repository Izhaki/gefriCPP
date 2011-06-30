#ifndef gxLightweightSystem_h
#define gxLightweightSystem_h

#include "core/gxObject.h"
#include "core/gxPaintDC.h"
#include "lightweights/gxRootViewElement.h"

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
protected:
  /**
   * @brief Sets the {@link gxRootViewElement root view element} of the system.
   * @param aRootViewElement The new {@link gxRootViewElement root view 
    * element}.
   */
  void SetRootViewElement(gxRootViewElement *aRootViewElement);

  /// The control this system is linked to.
  gxLightweightControl *mControl;

  /// The root view element of this system.
  gxRootViewElement *mRootViewElement;

  /// the top-level view element.
  gxViewElement *mContents ;
};

#endif // gxLightweightSystem_h