#include "view/elements/gxViewElement.h"
#include "view/gxLightweightSystem.h"
#include "core/gxAssert.h"

gxViewElement::gxViewElement()
  : mFlags(0)
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
  // No point repainting the figure if it is invalid.
  if (!IsValid())
    return;
    
  gxBounds bounds = GetBounds();
  Repaint(bounds);
}

void gxViewElement::Repaint(gxBounds &aBounds)
{
  // No point repainting the figure if it is invalid.
  if (!IsValid())
    return;

  // Get root view element and return if no such found.
  gxRootViewElement *root = GetRootViewElement();
  gxASSERT(root == NULL, "gxViewElement::Repaint could not find root element");

  // Get the lightweight system and return if no such found.
  gxLightweightSystem *lws = root->GetLightweightSystem();
  gxASSERT(root == NULL, "gxViewElement::Repaint could not find the lightweight system");
  
  // Translate the bounds to absolute coordinates.
  TransformToAbsolute(aBounds);
  
  // instruct the lightweight system to mark the bounds of this view element
  // as ones need repainting
  lws->AddDirtyRegion(aBounds);
}

void gxViewElement::GetChildrenBounds(gxBounds &aBounds)
{
  for (EACHCHILD)
  {
    gxBounds childBounds;
    CHILD->GetChildrenBounds(childBounds);
    
    // Exclude scroll transformations for these bounds.
    childBounds.mTransformFlags.Unset(gxBounds::Scrollable);

    TransformChild(childBounds);
    aBounds.Union(childBounds);
  }
}

void gxViewElement::Invalidate()
{
  mFlags.Unset(gxViewElement::Valid);
}

void gxViewElement::Revalidate()
{
  Invalidate();

  // View elements parent might be null before all elements are inserted to the
  // hierarchy tree (when they are still created and added to their parents).
  if (GetParent() != NULL)
  {
    // Revalidate further up the hierarchy tree. When the revalidation hits a
    // RootViewElement validation will start downwards.
    GetParent()->Revalidate();
  }
}

void gxViewElement::Validate()
{
  if (IsValid())
    return;

  // Validate myself
  ValidateSelf();
  
  // Set myself as Valid
  mFlags.Set(gxViewElement::Valid);

  // Ask all children to validate themselves.
  for (EACHCHILD)
  {
    CHILD->Validate();
  }
}

bool gxViewElement::IsValid()
{
  return mFlags.IsSet(gxViewElement::Valid);
}

void gxViewElement::OnAddChild(gxViewElement *aChild)
{
  // Newly created children are invalid. So once a child is added try to
  // revalidate it. If the child is not inserted into a composition which
  // has root view element at the very top of the hierarchy tree, the view
  // element will remain invalid and therefore will not be repainted as
  // Repaint will return.
  aChild->Revalidate();
  aChild->Repaint();
}

void gxViewElement::OnRemoveChild(gxViewElement *aChild)
{
  aChild->Erase();
}