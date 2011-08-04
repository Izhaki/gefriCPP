#include "view/elements/gxRootViewElement.h"
#include "view/gxLightweightSystem.h"
#include "core/gxAssert.h"

const gxRootViewElement* gxRootViewElement::GetRootViewElement() const
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

void gxRootViewElement::Revalidate()
{
  Invalidate();
  
  // Once revalidation hit the root view element, we start validating down the 
  // hierarchy tree.
  Validate();
}

void gxRootViewElement::TransformToAbsolute(gxBounds &aBounds)
{
  // RootViewElement has no parent. So translation stops here.
}