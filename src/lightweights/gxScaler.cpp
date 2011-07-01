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
    int x = aRect.x;
    int y = aRect.y;
    int w = aRect.width;
    int h = aRect.height;
        
    wxLogDebug(_T("TranslateToParent Before: %i, %i, %i, %i"), x, y, w, h);    
        
    aRect.SetX((int)floor(x * mScaleX));
    aRect.SetY((int)floor(y * mScaleY));
    aRect.SetWidth((int)floor( (x + w) * mScaleX) - aRect.x);
    aRect.SetHeight((int)floor( (y + h) * mScaleY) - aRect.y); 

   wxLogDebug(_T("TranslateToParent After Scale: %i, %i, %i, %i"), aRect.GetX(), aRect.GetY(), aRect.GetWidth(), aRect.GetHeight());   
    
  if (GetParent() != NULL)
    aRect.Offset(GetParent()->GetBounds().GetPosition());
}