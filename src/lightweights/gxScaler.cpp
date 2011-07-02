#include "lightweights/gxScaler.h"

gxScaler::gxScaler()
  : mScaleX(1), mScaleY(1)
{
}

gxScaler::~gxScaler()
{
}

void gxScaler::SetScale(float aScaleX, float aScaleY)
{
  Erase();
  mScaleX = aScaleX;
  mScaleY = aScaleY;
  Repaint();
}

void gxScaler::MultiplyScale(float aXfactor, float aYfactor)
{
  SetScale(mScaleX * aXfactor, mScaleY * aYfactor);
}

void gxScaler::Paint(gxPainter &aPainter)
{
  // Push current painter state so it can be restored after setting the
  // scale
  aPainter.PushState();
  
  aPainter.SetScale(mScaleX, mScaleY);
  
  PaintChildren(aPainter);

  // Pop (will also restore) the painter state to before SetScale().
  aPainter.PopState();
}

void gxScaler::TranslateToParent(gxRect &aRect)
{
  if (mScaleX != 1 || mScaleY != 1)
  {
    aRect.Scale(mScaleX, mScaleY);
  }
    
  if (GetParent() != NULL)
    aRect.Offset(GetParent()->GetBounds().GetPosition());
}