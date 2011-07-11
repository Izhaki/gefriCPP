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

gxRect gxStructuralViewElement::GetBounds() const
{
  if (GetParent() != NULL)
  {
    // This will return a rect at (0,0) origin with the size of the parent.
    return gxRect(GetParent()->GetBounds().GetSize());
  } else {
    gxASSERT(true, "gxStructuralViewElement::GetBounds() called but no parent.");
  }
  return gxRect(0, 0, 0, 0);
}