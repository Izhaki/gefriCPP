#include "view/elements/gxStructuralViewElement.h"
#include "core/gxAssert.h"

gxStructuralViewElement::gxStructuralViewElement()
{
  // Structural view elements should not be subject to any zoom or
  // scroll transformations.
  mTransformFlags.Unset(gxTransformFlags::Scale | gxTransformFlags::Scroll);
}

gxStructuralViewElement::~gxStructuralViewElement()
{
}

void gxStructuralViewElement::Paint(gxPainter &aPainter)
{
  if (!IsVisible())
    return;

  PaintChildren(aPainter);
}

void gxStructuralViewElement::PaintChildren(gxPainter &aPainter)
{
  // Return if there are no children.
  if (mChildren.empty())
    return;

  for (EACHCHILD)
  {
    CHILD->Paint(aPainter);
  }
}

gxRect gxStructuralViewElement::GetBounds() const
{
  gxASSERT(GetParent() == NULL, "gxStructuralViewElement::GetBounds() called but no parent.");

  // This will return a rect at (0,0) origin with the size of the parent.
  gxRect iBounds(GetParent()->GetBounds().GetSize());

  return iBounds;
}