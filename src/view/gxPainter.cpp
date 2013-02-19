#include "view/gxPainter.h"
#include <math.h>
#include "core/gxLog.h"

gxPainter::gxPainter()
  : mNeedsTranslating( false ),
    mNeedsScaling( false ),
    mNeedsScrolling( false )
{
}

void gxPainter::UpdateTransformationsNeeded()
{
    mNeedsTranslating = mTrans.TranslateNeeded();

    mNeedsScrolling = mTrans.ScrollNeeded();

    mNeedsScaling = mTrans.ScaleNeeded();
}

void gxPainter::SetTranslate( gxPix dx,
                              gxPix dy )
{
    if ( mNeedsScaling )
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

    UpdateTransformationsNeeded();
}

void gxPainter::SetScroll( gxPix sx,
                           gxPix sy )
{
    if ( mNeedsScaling )
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

    UpdateTransformationsNeeded();
}

void gxPainter::SetScale( gxScale const &aScale )
{
    mTrans.Scale.X *= aScale.X;
    mTrans.Scale.Y *= aScale.Y;

    UpdateTransformationsNeeded();
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
    UpdateTransformationsNeeded();

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
    UpdateTransformationsNeeded();
}

void gxPainter::Transform( gxRect &aRect )
{
    if ( mNeedsScaling )
        aRect.Scale( mTrans.Scale.X, mTrans.Scale.Y );

    // TODO - change to aRect += mTrans.Translate (ditto for scrolling)
    if ( mNeedsTranslating )
        aRect.Offset( mTrans.Translate.X, mTrans.Translate.Y );

    if ( mNeedsScrolling )
        aRect.Offset( -mTrans.Scroll.X, -mTrans.Scroll.Y );
}

void gxPainter::Transform( gxPoint &aPoint )
{
    if ( mNeedsScaling )
    {
        aPoint.X = gxFloor( aPoint.X * mTrans.Scale.X );
        aPoint.Y = gxFloor( aPoint.Y * mTrans.Scale.Y );
    }

    if ( mNeedsTranslating )
    {
        aPoint.X += mTrans.Translate.X;
        aPoint.Y += mTrans.Translate.Y;
    }

    if ( mNeedsScrolling )
    {
        aPoint.X -= mTrans.Scroll.X;
        aPoint.Y -= mTrans.Scroll.Y;
    }
}