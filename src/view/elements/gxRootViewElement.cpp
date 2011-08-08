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

gxRect gxRootViewElement::GetBounds() const
{
  gxASSERT(GetLightweightSystem() == NULL, "gxRootViewElement::GetBounds called but no Lightweight System");
  
  if (GetLightweightSystem() != NULL)
  {
    // This will return a rectangle at origin (0,0) with the size of the
    // of the control bounds.
    return gxRect(GetLightweightSystem()->GetControlBounds().GetSize());
  }
  return gxRect(0, 0, 0, 0);
}

void gxRootViewElement::Revalidate()
{
  Invalidate();

  // Since a single user action might lead to a multitude of objects becoming
  // invalid (like the removal of 3 children), we don't want to validate the
  // whole tree per object that changed. Instead, we queue some validation
  // requests (in some event loop).
  //
  // What this means is that after all modified objects have been doing their
  // marking of invalid objects, the queue validation request will be processed
  // and will lead to Validate() on this class being called.
  if (GetLightweightSystem() != NULL)
    GetLightweightSystem()->QueueValidation();
}

void gxRootViewElement::TransformToAbsolute(gxRect &aRect, gxTransformFlags &aTransFlags)
{
  // RootViewElement has no parent. So translation stops here.
}