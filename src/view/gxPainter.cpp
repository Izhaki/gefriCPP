#include "view/gxPainter.h"
#include <wx/log.h>
#include <math.h>
#include "core/gxLog.h"

gxPainter::gxPainter()
  :mTranslateX(0), mTranslateY(0),
   mScrollX(0), mScrollY(0),
   mScaleX(1), mScaleY(1),
   mNeedsTranslating(false), mNeedsScaling(false), mNeedsScrolling(false)
{
  mTransformEnabledFlags.Set(gxPainter::All);
}

void gxPainter::SetTranslate(int dx, int dy)
{
  if (mNeedsScaling)
  {
    // Take into account any scaling that is in force.
    // Say the value given is (40,40), with a scale set to 2 the resultant
    // position will be (80,80). Makes sense innit?
    mTranslateX += (int)floor( dx * mScaleX);
    mTranslateY += (int)floor( dy * mScaleY);
  } else {
    mTranslateX += dx;
    mTranslateY += dy;
  }
  
  mNeedsTranslating = (mTranslateX != 0) || (mTranslateY != 0); 
}

void gxPainter::SetScroll(int sx, int sy)
{
  if (mNeedsScaling)
  {
    // Take into account any scaling that is in force.
    // Say the value given is (40,40), with a scale set to 2 the resultant
    // position will be (80,80). Makes sense innit?
    mScrollX += (int)floor( sx * mScaleX);
    mScrollY += (int)floor( sy * mScaleY);
  } else {
    mScrollX += sx;
    mScrollY += sy;
  }
  
  mNeedsScrolling = (mScrollX != 0) || (mScrollY != 0); 
}

void gxPainter::SetScale(float sx, float sy)
{
  mScaleX *= sx;
  mScaleY *= sy;

  mNeedsScaling = (mScaleX != 1) || (mScaleY != 1);
}

void gxPainter::PushState()
{
  //gxRect clipRect = GetDcClipRect();

  gxPainterState *s = new gxPainterState();

  s->dx = mTranslateX;
  s->dy = mTranslateY;

  s->scrollX = mScrollX;
  s->scrollY = mScrollY;

  s->sx = mScaleX;
  s->sy = mScaleY;
  s->clipArea = GetClipRect();

  s->transformEnabledFlags = mTransformEnabledFlags;

  mStateStack.push(s);
}

void gxPainter::PopState()
{
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
  
  mScrollX = aState->scrollX;
  mScrollY = aState->scrollY;
  
  mNeedsScrolling = (mScrollX != 0) || (mScrollY != 0);
  
  mScaleX = aState->sx;
  mScaleY = aState->sy;

  mNeedsScaling = (mScaleX != 1) || (mScaleY != 1);
  
  SetAbsoluteClipArea(aState->clipArea);
  
  mTransformEnabledFlags = aState->transformEnabledFlags;
}

void gxPainter::SetClipArea(gxRect const &aRect)
{
  // Transforms the rect, taking into account trnaslation, scale, etc.
  gxRect transformedRect(aRect);
  Transform(transformedRect);
  
  IntersectClipArea(transformedRect);
}

void gxPainter::DisableScale()
{
  mTransformEnabledFlags.Unset(gxPainter::Scale);
}

bool gxPainter::ScaleEnabled()
{
  return mTransformEnabledFlags.IsSet(gxPainter::Scale);
}

void gxPainter::DisableScroll()
{
  mTransformEnabledFlags.Unset(gxPainter::Scroll);
}

bool gxPainter::ScrollEnabled()
{
  return mTransformEnabledFlags.IsSet(gxPainter::Scroll);
}

void gxPainter::Transform(gxRect &aRect)
{
  if (ScaleEnabled() && mNeedsScaling)
    aRect.Scale(mScaleX, mScaleY);

  if (mNeedsTranslating)
    aRect.Offset(mTranslateX, mTranslateY); 

  if (ScrollEnabled() && mNeedsScrolling)
    aRect.Offset(-mScrollX, -mScrollY); 
}

void gxPainter::Transform(gxPoint &aPoint)
{
  if (ScaleEnabled() && mNeedsScaling)
  {
    aPoint.x = (int)(aPoint.x * mScaleX);
    aPoint.y = (int)(aPoint.y * mScaleY);
  }

  if (mNeedsTranslating)
  {
    aPoint.x += mTranslateX;
    aPoint.y += mTranslateY;
  }

  if (ScrollEnabled() && mNeedsScrolling)
  {
    aPoint.x -= mScrollX;
    aPoint.y -= mScrollY;
  }
}