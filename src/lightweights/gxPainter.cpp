#include "lightweights/gxPainter.h"
#include <wx/log.h>

gxPainter::gxPainter()
  :mTranslateX(0), mTranslateY(0)
{
}

void gxPainter::SetTranslate(int dx, int dy)
{
  mTranslateX += dx;
  mTranslateY += dy;
}

void gxPainter::PushState()
{
  //wxLogDebug(_T("PushState: %i, %i, %i, %i"), mClipArea.GetX(), mClipArea.GetY(), mClipArea.GetWidth(), mClipArea.GetHeight());
  //gxRect clipRect = GetDcClipRect();
  //wxLogDebug(_T("PushState (absolute clip rect): %i, %i, %i, %i"), clipRect.GetX(), clipRect.GetY(), clipRect.GetWidth(), clipRect.GetHeight());

  gxPainterState *s = new gxPainterState();

  s->dx = mTranslateX;
  s->dy = mTranslateY;
  //s->clipArea = mClipArea;
  s->clipArea = GetClipRect();

  mStateStack.push(s);
}

void gxPainter::PopState()
{
  //wxLogDebug(_T("PopState"));
  // Get the top state from the stack
  gxPainterState *s = mStateStack.top();
  // Restore it
  RestoreState(s);

  // Remove it from stack;
  mStateStack.pop();

  delete s;
  s = NULL;
}

void gxPainter::RestoreState()
{
  // Get the top state from the stack
  gxPainterState *s = mStateStack.top();
  // Restore it
  RestoreState(s);
}

void gxPainter::RestoreState(gxPainterState *aState)
{
  mTranslateX = aState->dx;
  mTranslateY = aState->dy;

  //mClipArea = aState->clipArea;
  //Transform(mClipArea);
  SetAbsoluteClipArea(aState->clipArea);
}

void gxPainter::SetClipArea(gxRect const &aRect)
{
  //wxLogDebug(_T("SetClipArea Before Transform: %i, %i, %i, %i"), aRect.GetX(), aRect.GetY(), aRect.GetWidth(), aRect.GetHeight());
  //mClipArea = aRect;

  // Transforms the rect, taking into account trnaslation, scale, etc.
  gxRect transformedRect(aRect);
  Transform(transformedRect);


  //wxLogDebug(_T("SetClipArea After Transform: %i, %i, %i, %i"), transformedRect.GetX(), transformedRect.GetY(), transformedRect.GetWidth(), transformedRect.GetHeight());

  IntersectClipArea(transformedRect);
}

void gxPainter::Transform(gxRect &aRect)
{
  // only translate if needed
  if (mTranslateX != 0 && mTranslateY != 0)
  {
    aRect.Offset(mTranslateX, mTranslateY);
  }
    
}