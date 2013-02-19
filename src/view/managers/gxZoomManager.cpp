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

void gxZoomManager::SetZoom( const float aZoomH,
                             const float aZoomV )
{
    mZoom.X = aZoomH;
    mZoom.Y = aZoomV;

    Fire( evZoomChanged );
}

void gxZoomManager::SetZoom( const float aZoom )
{
    mZoom.X = aZoom;
    mZoom.Y = aZoom;

    Fire( evZoomChanged );
}

void gxZoomManager::MultiplyZoom( const float aMultiplierH,
                                  const float aMultiplierV )
{
    mZoom.X *= aMultiplierH;
    mZoom.Y *= aMultiplierV;

    Fire( evZoomChanged );
}

void gxZoomManager::MultiplyZoom( const float aMultiplier )
{
    mZoom.X *= aMultiplier;
    mZoom.Y *= aMultiplier;

    Fire( evZoomChanged );
}