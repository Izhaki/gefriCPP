#include "gxZoomManager.h"

gxZoomManager::gxZoomManager()
{
}

gxZoomManager::~gxZoomManager()
{
}

gxScale gxZoomManager::GetZoom() const
{
    return mZoom;
}

void gxZoomManager::SetZoom( const float aZoomH, const float aZoomV )
{
    mZoom.X = aZoomH;
    mZoom.Y = aZoomV;

    Fire( new evZoom( this ) );
}

void gxZoomManager::SetZoom( const float aZoom )
{
    mZoom.X = aZoom;
    mZoom.Y = aZoom;

    Fire( new evZoom( this ) );
}

void gxZoomManager::MultiplyZoom( const float aMultiplierH, const float aMultiplierV )
{
    mZoom.X *= aMultiplierH;
    mZoom.Y *= aMultiplierV;

    Fire( new evZoom(this) );
}

void gxZoomManager::MultiplyZoom( const float aMultiplier )
{
    mZoom.X *= aMultiplier;
    mZoom.Y *= aMultiplier;

    Fire( new evZoom(this) );
}

void gxZoomManager::AddObserverAndNotify( gxCallback *aCallback )
{
    Subscribe( aCallback );

    Fire( new evZoom(this), aCallback );
}