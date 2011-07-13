#include "view/elements/gxViewElement.h"
#include "view/gxLightweightSystem.h"
#include "core/gxAssert.h"

gxViewElement::gxViewElement()
{
}

gxViewElement::~gxViewElement()
{
}

gxRootViewElement* gxViewElement::GetRootViewElement()
{
  if (GetParent() != NULL)
  {
    return GetParent()->GetRootViewElement();
  } else {
    return NULL;
  }
}

void gxViewElement::TransformToAbsolute(gxBounds &aBounds)
{ 
  gxASSERT(GetParent() == NULL, "gxViewElement::TransformToAbsolute called, but no parent");

  GetParent()->TransformChild(aBounds);
  GetParent()->TransformToAbsolute(aBounds);
}

void gxViewElement::TransformChild(gxBounds &aBounds)
{
  aBounds.Offset(GetBounds().GetPosition());
}

void gxViewElement::Erase()
{
  // Repaint really does what we need - takes the element's bounds and adds
  // dirty region to queue repaint.
  Repaint();
  
}

void gxViewElement::Repaint()
{
  gxBounds bounds = GetBounds();
  Repaint(bounds);
}

void gxViewElement::Repaint(gxBounds &aBounds)
{
  // Get root view element and return if no such found
  gxRootViewElement *root = GetRootViewElement();
  if (!root) return;

  // Get the lightweight system and return if no such found
  gxLightweightSystem *lws = root->GetLightweightSystem();
  if (!lws) return;
  
  // Translate the bounds to absolute coordinates.
  TransformToAbsolute(aBounds);
  
  // instruct the lightweight system to mark the bounds of this view element
  // as ones need repainting
  lws->AddDirtyRegion(aBounds);
}

void gxViewElement::OnAddChild(gxViewElement *aChild)
{
  aChild->Repaint();
}

void gxViewElement::OnRemoveChild(gxViewElement *aChild)
{
  aChild->Erase();
}