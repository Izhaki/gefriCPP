#include "view/elements/gxVisualViewElement.h"
#include "view/gxLightweightSystem.h"
#include "core/gxLog.h"

gxVisualViewElement::gxVisualViewElement()
  : mBounds(0, 0, 0, 0)
{
}

gxVisualViewElement::gxVisualViewElement(const gxRect &aBounds)
{
  mBounds = aBounds; 
}

gxVisualViewElement::~gxVisualViewElement()
{
}

void gxVisualViewElement::Paint(gxPainter &aPainter)
{
  // Push the painter state as the next line might change it.
  aPainter.PushState();

  // Sets the painter transform flags to my own transform flags.
  aPainter.SetTransformFlags(mTransformFlags);

  // Get the bounds
  gxRect bounds(GetBounds());

  // wxLogDebug(_T("Paint: %i, %i, %i, %i"), bounds.GetX(), bounds.GetY(), bounds.GetWidth(), bounds.GetHeight());

  // Only paint if need to (intersect with the bounds of painting area and
  // damaged areas).
  if (aPainter.NeedsPainting(bounds))
  {
    // Push current painter state so it can be restored after setting the
    // clip area
    aPainter.PushState();

    // Sets the clip area of the painter to the bounds
    aPainter.SetClipArea(bounds);

    PaintSelf(aPainter);
    PaintChildren(aPainter);
    PaintBorder(aPainter);

    // Pop (will also restore) the painter state to before SetClipArea.
    aPainter.PopState();
  }
  
  aPainter.PopState();
}

void gxVisualViewElement::PaintChildren(gxPainter &aPainter)
{
  // Return if there are no children.
  if (mChildren.empty())
    return;

  // Push current painter state so it can be poped after translate
  aPainter.PushState();

  // Offset all paint operation by the top-left point of this elemet
  aPainter.SetTranslate(mBounds.x, mBounds.y);

  for (EACHCHILD)
  {
    // Paint the child
    CHILD->Paint(aPainter);
  }

  // Pop (will also restore) the painter state to before translate.
  aPainter.PopState();
}

void gxVisualViewElement::GetDescendantsBounds(gxRect &aBounds)
{
  // Union with my bounds.
  aBounds.Union(GetBounds());
  
  // And then with those of all children (this isn't needed if we clip children).
  gxViewElement::GetDescendantsBounds(aBounds);
}

gxRect gxVisualViewElement::GetBounds() const
{
  return mBounds;
}

void gxVisualViewElement::SetBounds(const gxRect &aNewBounds)
{
  // Check if either translate or resize happened
  bool iTranslate = (aNewBounds.x != mBounds.x) || (aNewBounds.y != mBounds.y); 
  bool iResize = (aNewBounds.width != mBounds.width) || (aNewBounds.height != mBounds.height);

  // Erase the view element if either happened
  if (iTranslate || iResize)
    Erase();

  // Preform translation
  if (iTranslate)
  {
    int dx = aNewBounds.x - mBounds.x;
    int dy = aNewBounds.y - mBounds.y;
    Translate(dx,dy);
  }

  // Preform resize
  if (iResize)
  {
    mBounds.width = aNewBounds.width;
    mBounds.height = aNewBounds.height;
  }

  // Repaint
  if (iTranslate || iResize)
  {
    Revalidate();
    Repaint();
  }
}

void gxVisualViewElement::Translate(int dx, int dy)
{
  mBounds.x += dx;
  mBounds.y += dy;
}