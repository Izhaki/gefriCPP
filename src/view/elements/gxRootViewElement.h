#ifndef gxRootViewElement_h
#define gxRootViewElement_h

#include "view/elements/gxStructuralViewElement.h"

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
  gxRootViewElement()
    : mLightweightSystem(NULL) { }

  /**
   * @brief Returns the {@link gxLightweightSystem lightweight system}
   * associated with this view element (and all its children).
   */
  virtual gxLightweightSystem* GetLightweightSystem() const;

  /**
   * @brief Overrides the base class implementation to return itself. 
   */
  virtual const gxRootViewElement* GetRootViewElement() const;

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
  virtual gxBounds GetBounds() const;
  
  virtual void Revalidate();

protected:
  virtual void TransformToAbsolute(gxBounds &aBounds);
private:
  /// The {@link gxLightweightSystem lightweight system} associated with this
  /// root view element.
  gxLightweightSystem *mLightweightSystem;
};

#endif // gxRootViewElement_h