#include "view/elements/gxStructuralViewElement.h"
#include "core/gxAssert.h"

gxStructuralViewElement::gxStructuralViewElement()
{
}

gxStructuralViewElement::~gxStructuralViewElement()
{
}

void gxStructuralViewElement::Paint(gxPainter &aPainter)
{
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

gxBounds gxStructuralViewElement::GetBounds() const
{
  gxASSERT(GetParent() == NULL, "gxStructuralViewElement::GetBounds() called but no parent.");

  // This will return a rect at (0,0) origin with the size of the parent.
  gxBounds bounds(GetParent()->GetBounds().GetSize());
  
  // The bounds of a structural element should not be subject to any zoom or
  // scroll transformations.
  bounds.mTransformFlags.Unset(gxBounds::Scalable | gxBounds::Scrollable);
  return bounds;
}