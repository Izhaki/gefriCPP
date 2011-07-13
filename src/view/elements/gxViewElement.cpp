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

void gxViewElement::TranslateToAbsolute(gxRect &aRect, bool isStructural)
{ 
  gxASSERT(GetParent() == NULL, "gxViewElement::TranslateToAbsolute called, but no parent");

  //TranslateToParent(aRect);
  GetParent()->TransformChild(aRect, isStructural);
  GetParent()->TranslateToAbsolute(aRect, isStructural);
}

void gxViewElement::TranslateToParent(gxRect &aRect)
{
  gxASSERT(GetParent() == NULL, "gxViewElement::TranslateToParent called, but no parent");

  aRect.Offset(GetParent()->GetBounds().GetPosition());
}

void gxViewElement::TransformChild(gxRect &aRect, bool isStructural)
{
  aRect.Offset(GetBounds().GetPosition());
}

void gxViewElement::Erase()
{
  // Repaint really does what we need - takes the element's bounds and adds
  // dirty region to queue repaint.
  Repaint();
  
}

void gxViewElement::Repaint()
{
  gxRect bounds = GetBounds();
  Repaint(bounds);
}

void gxViewElement::Repaint(gxRect &aRect)
{
  // Get root view element and return if no such found
  gxRootViewElement *root = GetRootViewElement();
  if (!root) return;

  // Get the lightweight system and return if no such found
  gxLightweightSystem *lws = root->GetLightweightSystem();
  if (!lws) return;
  
  // Translate the bounds to absolute coordinates.
  TranslateToAbsolute(aRect, IsStructural());
  
  // instruct the lightweight system to mark the bounds of this view element
  // as ones need repainting
  lws->AddDirtyRegion(aRect);
}

void gxViewElement::OnAddChild(gxViewElement *aChild)
{
  aChild->Repaint();
}

void gxViewElement::OnRemoveChild(gxViewElement *aChild)
{
  aChild->Erase();
}