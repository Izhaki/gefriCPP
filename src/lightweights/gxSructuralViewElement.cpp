#include "lightweights/gxStructuralViewElement.h"

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
    return GetParent()->GetBounds();
  } else {
    wxASSERT_MSG(false, _T("gxStructuralViewElement::GetBounds() called but no parent."));
  }
  return gxRect(0, 0, 0, 0);
}