#include "view/managers/gxScrollManager.h"
#include <wx/log.h>
#include <math.h>

gxScrollManager::gxScrollManager()
{
}

gxScrollManager::~gxScrollManager()
{
}

void gxScrollManager::SetScroll( gxScroll const &aScroll )
{
    mScroll = aScroll;
    Fire( new evEvent() );
}

void gxScrollManager::SetScroll( const gxPix aScrollX, const gxPix aScrollY )
{
    gxScroll newScroll( aScrollX, aScrollY );
    SetScroll( newScroll );
}

void gxScrollManager::SetScroll( const bool isVertical, const gxPix aScroll )
{
    if ( isVertical )
        SetScrollY( aScroll );
    else
        SetScrollX( aScroll );
}

void gxScrollManager::SetScrollX( const gxPix aScrollX )
{
    mScroll.X = aScrollX;
    Fire( new evScrollPosition( this ) );
}

void gxScrollManager::SetScrollY( const gxPix aScrollY )
{
    mScroll.Y = aScrollY;
    Fire( new evScrollPosition( this ) );
}

void gxScrollManager::AdjustScrollbars( gxSize const &aVisible, gxSize const &aRange )
{
    if ( mVisible == aVisible && mRange == aRange )
        return;

    gxScroll newScroll;

    // The new scroll position is proportional to the previous one.
    if ( mScroll.X != 0 && aRange.X > aVisible.X )
    {
        float oldPosRatio = ( mRange.X - mVisible.X ) / (float)mScroll.X;
        newScroll.X = gxFloor( ( aRange.X - aVisible.X ) / oldPosRatio );
    }

    // The new scroll position is proportional to the previous one.
    if ( mScroll.Y != 0 && aRange.Y > aVisible.Y )
    {
        float oldPosRatio = ( mRange.Y - mVisible.Y ) / (float)mScroll.Y;
        newScroll.Y = gxFloor( ( aRange.Y - aVisible.Y ) / oldPosRatio );
    }

    mVisible = aVisible;
    mRange   = aRange;

    // TODO: this will scroll event which is not really needed.
    SetScroll( newScroll );

    Fire( new evScrollRange( this ) );
}

void gxScrollManager::AddObserverAndNotify( gxCallback *aCallback )
{
    Subscribe( aCallback );
    Fire( new evScrollRange( this ), aCallback );
}