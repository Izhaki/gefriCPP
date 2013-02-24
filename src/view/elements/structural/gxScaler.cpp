#include "View/Elements/Structural/gxScaler.h"
#include "core/gxAssert.h"

gxScaler::gxScaler()
: mZoomManager( NULL )
{
}

gxScaler::gxScaler( gxZoomManager *aZoomManager )
: mZoomManager( NULL )
{
    SetZoomManager( aZoomManager );
}

gxScaler::~gxScaler()
{
    // Remove the callback from the previous zoom manager (if any).
    if ( mZoomManager )
        mZoomManager->gxUnsubscribe( evZoomChanged );
}

void gxScaler::SetZoomManager( gxZoomManager *aZoomManager )
{
    // Remove the callback from the previous zoom manager (if any).
    if ( mZoomManager )
        mZoomManager->gxUnsubscribe( evZoomChanged );

    mZoomManager = aZoomManager;
    aZoomManager->gxSubscribe( evZoomChanged, OnZoomChanged );
}

void gxScaler::SetScale( gxScale const &aScale )
{
    if ( mScale != aScale )
    {
        Erase();
        mScale = aScale;
    
        // As the scale changed we need to revalidate the hierarcy tree (for
        // example so a Scroller parent can readjust the scrollbars).
        Invalidate();
        Repaint();
    }
}

void gxScaler::OnZoomChanged( const gxScale *aZoom )
{
    SetScale( *aZoom );
}

void gxScaler::Paint( gxPainter &aPainter )
{
    // Push current painter state so it can be restored after setting the
    // scale
    aPainter.PushState();
  
    aPainter.SetScale( mScale );
  
    PaintChildren( aPainter );

    // Pop (will also restore) the painter state to before SetScale().
    aPainter.PopState();
}

void gxScaler::Transform( gxRect       &aRect,
                          gxTransFlags &aTransFlags )
{
    // Don't scale if the bounds reject it
    if ( aTransFlags.ScaleOff() )
        return;

    if ( mScale.IsntZero() )
    {
        aRect.Scale( mScale.X, mScale.Y );
    }
}