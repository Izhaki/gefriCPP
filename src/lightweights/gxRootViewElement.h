#ifndef gxRootViewElement_h
#define gxRootViewElement_h

#include "lightweights/gxStructuralViewElement.h"

// Forward declaration
class gxLightweightSystem;

/**
 * @brief The root view element in any {@link gxViewElement view element}
 * hierarchy, which links all children to the lightweight system. 
 * 
 * The root view element is not really something that is visiable, but it
 * provides a way for all view elements to communicate with the lightweight
 * system, for example, by keeping a reference to it.
 * Created by the {@link gxLightweightSystem lightweight system}
 */
class gxRootViewElement: public gxStructuralViewElement
{
public:
  /**
   * @brief Overrides the base class implementation to return itself. 
   */
  virtual gxRootViewElement* GetRootViewElement();

  /**
   * @brief Returns the {@link gxLightweightSystem lightweight system}
   * associated with this view element (and all its children).
   */
  gxLightweightSystem* GetLightweightSystem() const;

  /**
   * @brief Sets this view element's {@link gxLightweightSystem lightweight
   * system}.
   * Normally called by the {@link gxLightweightSystem lightweight system}
   *  itself.
   * @param aLightweightSystem The {@link gxLightweightSystem lightweight
   * system} associated with the root view element.
   */
  void SetLightweightSystem(gxLightweightSystem *aLightweightSystem);

  /**
   * @brief Returns the bounds of this view element by getting the bounds of the
   * lightweight control, but with the origin set to (0,0).
   */
  virtual gxRect GetBounds() const;
private:
  /// The {@link gxLightweightSystem lightweight system} associated with this
  /// root view element.
  gxLightweightSystem *mLightweightSystem;
};

#endif // gxRootViewElement_h