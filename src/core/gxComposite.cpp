#include "gxComposite.h"

gxComposite::gxComposite()
{
  mParent = NULL;
}

gxComposite::~gxComposite()
{
  RemoveAllChildren(true);

  if (GetParent() != NULL)
    GetParent()->RemoveChild(this);
}

void gxComposite::SetParent(gxComposite* aParent, bool aAndRemoveFromParent)
{
  // Detach from previous parent
  if (aAndRemoveFromParent && GetParent() != NULL)
    GetParent()->RemoveChild(this);

  mParent = aParent;
}

void gxComposite::AddChild(gxComposite *aChild)
{
  // Make sure child isn't null
  wxASSERT_MSG(aChild != NULL, _T("Null paased to AddChild"));

  // Check for cycle in hierarchy
  for (gxComposite* f = this; f!= NULL; f = f->GetParent())
  {
    wxASSERT_MSG(aChild != f, _T("Cycle in Hierarchy when trying to add a child"));
  }

  // Set the child parent to this
  aChild->SetParent(this);

  // Add to children list
  mChildren.push_back(aChild);

  // Notify
  OnAddChild(aChild);
}

void gxComposite::RemoveChild(gxComposite* aChild, bool aAndDelete)
{
  // Make sure it is one of my children
  wxASSERT(aChild->GetParent() == this);

  // Notify
  OnRemoveChild(aChild);

  // Remove from children list
  mChildren.remove(aChild);

  // Set child parent to NULL (but don't call again RemoveChild on this)
  aChild->SetParent(NULL, false);

  // Delete if requested
  if (aAndDelete)
  {
    delete aChild;
    aChild = NULL;
  }
}

void gxComposite::RemoveAllChildren(bool aAndDelete)
{
  for (ChildIterator it = mChildren.begin(); !mChildren.empty(); it = mChildren.begin() ) {
    RemoveChild(*it, aAndDelete);
  }
}