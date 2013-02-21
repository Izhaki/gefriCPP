#include "view/gxPainter.h"
#include <math.h>
#include "core/gxLog.h"

gxPainter::gxPainter()
{
}

void gxPainter::SetTranslate( gxPoint aDelta )
{
    if ( ScaleNeeded() )
    {
        // Take into account any scaling that is in force.
        // Say the value given is (40,40), with a scale set to 2 the resultant
        // position will be (80,80). Makes sense innit?
        mTrans.Translate.X += gxFloor( aDelta.X * mTrans.Scale.X );
        mTrans.Translate.Y += gxFloor( aDelta.Y * mTrans.Scale.Y );
    } else {
        mTrans.Translate += aDelta;
    }
}

void gxPainter::SetScroll( gxPoint aScroll )
{
    if ( ScaleNeeded() )
    {
        // Take into account any scaling that is in force.
        // Say the value given is (40,40), with a scale set to 2 the resultant
        // position will be (80,80). Makes sense innit?
        mTrans.Scroll.X += gxFloor( aScroll.X * mTrans.Scale.X );
        mTrans.Scroll.Y += gxFloor( aScroll.Y * mTrans.Scale.Y );
    } else {
        mTrans.Scroll += aScroll;
    }
}

void gxPainter::SetScale( gxScale const &aScale )
{
    // TODO: Unify to 1 line
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

void gxPainter::SetTransformFlags( gxTransFlags aFlags )
{
    mTrans.Enabled = aFlags;
}

void gxPainter::Transform( gxRect &aRect )
{
    // TODO: Have a Scale method that simply takes scale (or coefficient)
    if ( ScaleNeeded() )
        aRect.Scale( mTrans.Scale.X, mTrans.Scale.Y );

    if ( TranslateNeeded() )
        aRect.Translate( mTrans.Translate );

    if ( ScrollNeeded() )
        aRect.Translate( -mTrans.Scroll );
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
        aPoint += mTrans.Translate;
    }

    if ( ScrollNeeded() )
    {
        aPoint -= mTrans.Scroll;
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
