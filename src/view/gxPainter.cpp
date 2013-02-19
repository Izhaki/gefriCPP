#include "view/gxPainter.h"
#include <math.h>
#include "core/gxLog.h"

gxPainter::gxPainter()
{
}

void gxPainter::SetTranslate( gxPix dx,
                              gxPix dy )
{
    if ( ScaleNeeded() )
    {
        // Take into account any scaling that is in force.
        // Say the value given is (40,40), with a scale set to 2 the resultant
        // position will be (80,80). Makes sense innit?
        mTrans.Translate.X += gxFloor( dx * mTrans.Scale.X );
        mTrans.Translate.Y += gxFloor( dy * mTrans.Scale.Y );
    } else {
        mTrans.Translate.X += dx;
        mTrans.Translate.Y += dy;
    }
}

void gxPainter::SetScroll( gxPix sx,
                           gxPix sy )
{
    if ( ScaleNeeded() )
    {
        // Take into account any scaling that is in force.
        // Say the value given is (40,40), with a scale set to 2 the resultant
        // position will be (80,80). Makes sense innit?
        mTrans.Scroll.X += gxFloor( sx * mTrans.Scale.X );
        mTrans.Scroll.Y += gxFloor( sy * mTrans.Scale.Y );
    } else {
        mTrans.Scroll.X += sx;
        mTrans.Scroll.Y += sy;
    }
}

void gxPainter::SetScale( gxScale const &aScale )
{
    mTrans.Scale.X *= aScale.X;
    mTrans.Scale.Y *= aScale.Y;
}

void gxPainter::PushState()
{
    gxPainterState *iState = new gxPainterState();

    iState->transformations = mTrans;
    iState->clipArea = GetClipRect();

    mStateStack.push( iState );
}

void gxPainter::PopState()
{
    // Get the top state from the stack
    gxPainterState *iState = mStateStack.top();
  
    // Restore it
    RestoreState( iState );

    // Remove it from stack;
    mStateStack.pop();

    delete iState;
    iState = NULL;
}

void gxPainter::RestoreState()
{
    // Get the top state from the stack
    gxPainterState *iState = mStateStack.top();
    
    // Restore it
    RestoreState( iState );
}

void gxPainter::RestoreState( gxPainterState *aState )
{
    mTrans = aState->transformations;

    SetAbsoluteClipArea( aState->clipArea );
}

void gxPainter::SetClipArea( gxRect const &aRect )
{
    // Transforms the rect, taking into account trnaslation, scale, etc.
    gxRect iTransformedRect( aRect );
    Transform( iTransformedRect );
  
    IntersectClipArea( iTransformedRect );
}

void gxPainter::SetTransformFlags( gxTransformFlags aFlags )
{
    mTrans.Enabled = aFlags;
}

void gxPainter::Transform( gxRect &aRect )
{
    if ( ScaleNeeded() )
        aRect.Scale( mTrans.Scale.X, mTrans.Scale.Y );

    // TODO - change to aRect += mTrans.Translate (ditto for scrolling)
    if ( TranslateNeeded() )
        aRect.Offset( mTrans.Translate.X, mTrans.Translate.Y );

    if ( ScrollNeeded() )
        aRect.Offset( -mTrans.Scroll.X, -mTrans.Scroll.Y );
}

void gxPainter::Transform( gxPoint &aPoint )
{
    if ( ScaleNeeded() )
    {
        aPoint.X = gxFloor( aPoint.X * mTrans.Scale.X );
        aPoint.Y = gxFloor( aPoint.Y * mTrans.Scale.Y );
    }

    if ( TranslateNeeded() )
    {
        aPoint.X += mTrans.Translate.X;
        aPoint.Y += mTrans.Translate.Y;
    }

    if ( ScrollNeeded() )
    {
        aPoint.X -= mTrans.Scroll.X;
        aPoint.Y -= mTrans.Scroll.Y;
    }
}

bool gxPainter::TranslateNeeded()
{
    return mTrans.TranslateNeeded();
}

bool gxPainter::ScaleNeeded()
{
    return mTrans.ScaleNeeded();
}

bool gxPainter::ScrollNeeded()
{
    return mTrans.ScrollNeeded();    
}
