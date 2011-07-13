#include "view/elements/gxRootViewElement.h"
#include "view/gxLightweightSystem.h"
#include "core/gxAssert.h"

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

gxBounds gxRootViewElement::GetBounds() const
{
  gxASSERT(GetLightweightSystem() == NULL, "gxRootViewElement::GetBounds called but no Lightweight System");
  
  if (GetLightweightSystem() != NULL)
  {
    // This will return a rectangle at origin (0,0) with the size of the
    // of the control bounds.
    return gxBounds(GetLightweightSystem()->GetControlBounds().GetSize());
  }
  return gxBounds(0, 0, 0, 0);
}

void gxRootViewElement::TransformToAbsolute(gxBounds &aBounds)
{
  // RootViewElement has no parent. So translation stops here.
}