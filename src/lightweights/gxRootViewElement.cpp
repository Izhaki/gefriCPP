#include "lightweights/gxRootViewElement.h"
#include "gxLightweightSystem.h"

gxRootViewElement* gxRootViewElement::GetRootViewElement()
{
  return this;
}

gxLightweightSystem* gxRootViewElement::GetLightweightSystem() const
{
  return mLightweightSystem;
}

void gxRootViewElement::SetLightweightSystem(gxLightweightSystem *aLightweightSystem)
{
  mLightweightSystem = aLightweightSystem;
}

gxRect gxRootViewElement::GetBounds() const
{
  if (GetLightweightSystem() != NULL)
  {
    // Get the lightweight system control bounds.
    gxRect bounds =  GetLightweightSystem()->GetControlBounds();
    // Set origin to 0
    bounds.SetX(0);
    bounds.SetY(0);

    return bounds;
  }
  return gxRect(0, 0, 0, 0);
}