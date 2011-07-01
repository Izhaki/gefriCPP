#include "lightweights/gxPainter.h"
#include <wx/log.h>
#include <math.h>

gxPainter::gxPainter()
  :mTranslateX(0), mTranslateY(0),
   mScaleX(1), mScaleY(1),
   mNeedsTranslating(false), mNeedsScaling(false)
{
}

void gxPainter::SetTranslate(int dx, int dy)
{
  if (mNeedsScaling)
  {
    // Take into account any scaling that is in force.
    // Say the value given is (40,40), with a scale set to 2 the resultant
    // resultant will be (80,80). Makes sense innit?
    mTranslateX += (int)floor( dx * mScaleX);
    mTranslateY += (int)floor( dy * mScaleY);
  } else {
    mTranslateX += dx;    
    mTranslateY += dy;
  }
  
  mNeedsTranslating = (mTranslateX != 0) || (mTranslateY != 0); 
}

void gxPainter::SetScale(float sx, float sy)
{
  mScaleX *= sx;
  mScaleY *= sy;
  
  mNeedsScaling = (mScaleX != 1) || (mScaleY != 1);
}

void gxPainter::PushState()
{
  //wxLogDebug(_T("PushState: %i, %i, %i, %i"), mClipArea.GetX(), mClipArea.GetY(), mClipArea.GetWidth(), mClipArea.GetHeight());
  //gxRect clipRect = GetDcClipRect();
  //wxLogDebug(_T("PushState (absolute clip rect): %i, %i, %i, %i"), clipRect.GetX(), clipRect.GetY(), clipRect.GetWidth(), clipRect.GetHeight());

  gxPainterState *s = new gxPainterState();

  s->dx = mTranslateX;
  s->dy = mTranslateY;

  s->sx = mScaleX;
  s->sy = mScaleY;
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

  mNeedsTranslating = (mTranslateX != 0) || (mTranslateY != 0); 
  
  mScaleX = aState->sx;
  mScaleY = aState->sy;

  mNeedsScaling = (mScaleX != 1) || (mScaleY != 1);
  
  SetAbsoluteClipArea(aState->clipArea);
}

void gxPainter::SetClipArea(gxRect const &aRect)
{
  // Transforms the rect, taking into account trnaslation, scale, etc.
  gxRect transformedRect(aRect);
  Transform(transformedRect);

  IntersectClipArea(transformedRect);
}

void gxPainter::Transform(gxRect &aRect)
{
  if (mNeedsScaling)
  {
    int x = aRect.x;
    int y = aRect.y;
    int w = aRect.width;
    int h = aRect.height;
    
    aRect.SetX((int)floor(x * mScaleX));
    aRect.SetY((int)floor(y * mScaleY));
    aRect.SetWidth((int)floor( (x + w) * mScaleX) - aRect.x);
    aRect.SetHeight((int)floor( (y + h) * mScaleY) - aRect.y);
  }

  if (mNeedsTranslating) {
      aRect.Offset(mTranslateX, mTranslateY); 
  }

  //wxLogDebug(_T("Transform After Translate: %i, %i, %i, %i"), aRect.GetX(), aRect.GetY(), aRect.GetWidth(), aRect.GetHeight());

}