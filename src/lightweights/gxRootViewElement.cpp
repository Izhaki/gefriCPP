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
  wxASSERT_MSG(GetLightweightSystem() != NULL, _T("gxRootViewElement::GetBounds called but no Lightweight System"));
  
  if (GetLightweightSystem() != NULL)
  {
    // This will return a rectangle at origin (0,0) with the size of the
    // of the control bounds.
    return gxRect(GetLightweightSystem()->GetControlBounds().GetSize());
  }
  return gxRect(0, 0, 0, 0);
}