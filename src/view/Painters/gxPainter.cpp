#include "View/Painters/gxPainter.h"
#include <math.h>
#include "core/gxLog.h"

gxPainter::gxPainter()
  : mRelative(true)
{
}

void gxPainter::SetTranslate( gxPoint aDelta )
{
    if ( ScaleNeeded() )
    {
        // Take into account any scaling that is in force.
        // Say the value given is (40,40), with a scale set to 2 the resultant
        // position will be (80,80). Makes sense innit?
        mTrans.Translate += aDelta * mTrans.Scale;
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
        mTrans.Scroll += aScroll * mTrans.Scale;
    } else {
        mTrans.Scroll += aScroll;
    }
}

void gxPainter::SetScale( gxScale const &aScale )
{
    // We multiply the current scale with the new one.
    mTrans.Scale *= aScale;
}

void gxPainter::PushState()
{
    gxPainterState *iState = new gxPainterState();

    iState->transformations = mTrans;
    iState->clipArea        = GetClipRect();
    iState->relative        = mRelative;

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
    mTrans    = aState->transformations;
    mRelative = aState->relative;

    SetAbsoluteClipArea( aState->clipArea );
}

void gxPainter::SetClipArea( gxRect const &aRect )
{
    // Transforms the rect, taking into account trnaslation, scale, etc.
    gxRect iTransformedRect( aRect );
    Transform( iTransformedRect );
  
    IntersectClipArea( iTransformedRect );
}

void gxPainter::Transform( gxRect &aRect )
{
    if ( ScaleNeeded() )
        aRect.Scale( mTrans.Scale );

    if ( TranslateNeeded() )
        aRect += mTrans.Translate;

    if ( ScrollNeeded() )
        aRect -= mTrans.Scroll;
}

void gxPainter::Transform( gxPoint &aPoint )
{
    if ( ScaleNeeded() )
        aPoint *= mTrans.Scale;

    if ( TranslateNeeded() )
        aPoint += mTrans.Translate;

    if ( ScrollNeeded() )
        aPoint -= mTrans.Scroll;
}

bool gxPainter::IsRelative()
{
    return mRelative;
}

void gxPainter::SetRelative( bool aRelative )
{
    // If we're using absolute positiong, reset both the scale and translate
    // transformations.
    if ( !aRelative )
    {
        mTrans.Scale.Reset();
        mTrans.Translate.Reset();
    }

    mRelative = aRelative;
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

// Drawing Methods

void gxPainter::DrawRectangle( gxPix aX,
                               gxPix aY,
                               gxPix aW,
                               gxPix aH )
{
    gxRect iRect( aX, aY, aW, aH );
    DrawRectangle( iRect );
}

void gxPainter::DrawRectangle( gxRect aRect )
{
    Transform( aRect );
    DoDrawRectangle( aRect );
}

void gxPainter::DrawLine( gxRect aRect )
{
    DrawLine( aRect.GetTopLeft(), aRect.GetBottomRight() );
}

void gxPainter::DrawLine( gxPix x1,
                          gxPix y1,
                          gxPix x2,
                          gxPix y2 )
{
    DrawLine( gxPoint( x1, y1 ), gxPoint( x2, y2) );
}

void gxPainter::DrawLine( gxPoint aFrom,
                          gxPoint aTo )
{
    Transform( aFrom );
    Transform( aTo );
    DoDrawLine( aFrom, aTo );
}

void gxPainter::DrawText( gxString &aText,
                          gxPix    aX,
                          gxPix    aY,
                          double   aAngle )
{
    gxPoint iPoint( aX, aY );
    Transform( iPoint );
    DoDrawText( aText, iPoint.X , iPoint.Y, aAngle );
}

void gxPainter::DrawText( gxString &aText,
                          gxPix    aX,
                          gxPix    aY,
                          gxPix    aPadX,
                          gxPix    aPadY,
                          bool     isHorizontal )
{
    gxPoint iPoint = isHorizontal ? gxPoint( aX, aY ) : gxPoint( aY, aX );
    
    Transform( iPoint );
    
    iPoint.X += aPadX;
    iPoint.Y += aPadY;
    
    if ( isHorizontal )
    {
        DoDrawText( aText, iPoint.X , iPoint.Y );
    } else {
        // Text rotation is done with the top left point as origion,
        // so make the old top right the new top left
        iPoint.Y = iPoint.Y + GetTextSize( aText ).X;
        iPoint.X += 3; //TODO: remove hack
        DoDrawText( aText, iPoint.X , iPoint.Y, 90 );
    }
}
