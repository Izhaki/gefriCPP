#include "view/managers/gxScrollManager.h"
#include <wx/log.h>
#include <math.h>

gxScrollManager::gxScrollManager()
{
}

gxScrollManager::~gxScrollManager()
{
}

void gxScrollManager::SetPosition( gxPosition const &aPosition )
{
    mScroll.mPosition = aPosition;
    Fire( new evScroll( this ) );
}

void gxScrollManager::SetPosition( const gxPix aPositionX, const gxPix aPositionY )
{
    gxPosition iPosition( aPositionX, aPositionY );
    SetPosition( iPosition );
}

void gxScrollManager::SetPosition( const bool isVertical, const gxPix aPosition )
{
    if ( isVertical )
        SetPositionY( aPosition );
    else
        SetPositionX( aPosition );
}

void gxScrollManager::SetPositionX( const gxPix aPositionX )
{
    mScroll.mPosition.X = aPositionX;
    Fire( new evScroll( this ) );    
}

void gxScrollManager::SetPositionY( const gxPix aPositionY )
{
    mScroll.mPosition.Y = aPositionY;
    Fire( new evScroll( this ) );    
}

void gxScrollManager::AdjustScrollbars( gxSize const &aVisible, gxSize const &aRange )
{
    if ( mScroll.mVisible == aVisible && mScroll.mRange == aRange )
        return;

    gxPosition iPosition;

    // The new scroll position is proportional to the previous one.
    if ( mScroll.mPosition.X != 0 && aRange.X > aVisible.X )
    {
        float oldPosRatio = ( mScroll.mRange.X - mScroll.mVisible.X ) / (float)mScroll.mPosition.X;
        iPosition.X = gxFloor( ( aRange.X - aVisible.X ) / oldPosRatio );
    }

    // The new scroll position is proportional to the previous one.
    if ( mScroll.mPosition.Y != 0 && aRange.Y > aVisible.Y )
    {
        float oldPosRatio = ( mScroll.mRange.Y - mScroll.mVisible.Y ) / (float)mScroll.mPosition.Y;
        iPosition.Y = gxFloor( ( aRange.Y - aVisible.Y ) / oldPosRatio );
    }

    mScroll.mPosition = iPosition;
    mScroll.mVisible  = aVisible;
    mScroll.mRange    = aRange;

    Fire( new evScroll( this ) );
}

void gxScrollManager::AddObserverAndNotify( gxCallback *aCallback )
{
    Subscribe( aCallback );
    Fire( new evScroll( this ), aCallback );
}