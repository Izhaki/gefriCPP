#include "View/Elements/Visual/gxRuler.h"
#include "View/gxLightweightSystem.h"

gxRuler::gxRuler( const gxRect  &aBounds,
                  gxDivProvider *aDivProvider )
: gxVisual( aBounds ),
  mZoomManager( NULL ),
  mScrollManager( NULL ),
  mIsHorizontal( aBounds.width > aBounds.height ),
  mBlockTextRatio( 0.5 ),
  mStartPixel( 0 ),
  mDivProvider( aDivProvider )
{
  
}

gxRuler::~gxRuler()
{
    // If a zoom manager is linked, remove the callbacks.
    if ( mZoomManager )
        mZoomManager->gxUnsubscribe( evZoomChanged );

    // If a scroll manager is linked, remove the callbacks.
    if ( mScrollManager )
    {
        mScrollManager->gxUnsubscribe( evScrollChanged );
    }
}

void gxRuler::SetZoomManager( gxZoomManager *aZoomManager )
{
    // Remove the callback from the previous zoom manager (if any).
    if ( mZoomManager )
        mZoomManager->gxUnsubscribe( evZoomChanged );

    mZoomManager = aZoomManager;
    aZoomManager->gxSubscribe( evZoomChanged, OnZoomChanged );
}

void gxRuler::OnZoomChanged( const gxScale *aZoom )
{
    SetScale ( mIsHorizontal ? aZoom->X : aZoom->Y );
}

void gxRuler::SetScrollManager( gxScrollManager *aScrollManager )
{
    // Remove the callback from the previous scroll manager (if any).
    if ( mScrollManager )
    {
        mScrollManager->gxUnsubscribe( evScrollChanged );
    }

    mScrollManager = aScrollManager;
    aScrollManager->gxSubscribe( evScrollChanged, OnScrollChanged );
}

void gxRuler::OnScrollChanged( const gxScroll *aScroll )
{
    mStartPixel = mIsHorizontal ? aScroll->mPosition.X : aScroll->mPosition.Y;
}


// TODO: Is this right? It is only being called once.
void gxRuler::Validate()
{
    // Call the base class validate so children are also validated and this object
    // is marked as valid.
    gxVisual::Validate();
    
    // To calculate the minimum block size we need the lightweight
    // system, which will only be available when Validate is called.
    CalcMinBlockSize();

    Repaint();
}

void gxRuler::CalcMinBlockSize()
{
    // Find the maximum text size.
    gxString iBiggestLabel = mDivProvider->GetLabelOfPixel( mBounds.GetSize( mIsHorizontal ) );
    gxSize iMaxTextSize = GetLightweightSystem()->GetTextSize( iBiggestLabel );

    // Take into account the ratio of the text for the block.
    mDivProvider->SetMinBlockSize( gxCeil( iMaxTextSize.X / mBlockTextRatio ) );
}

void gxRuler::SetScale( const float aScale )
{
    mScale = aScale;
    mDivProvider->SetScale( aScale );
}

void gxRuler::SetBounds( const gxRect &aNewBounds )
{
    gxVisual::SetBounds( aNewBounds );
    mIsHorizontal = aNewBounds.width > aNewBounds.height;
}

void gxRuler::PaintSelf( gxPainter &aPainter )
{
    // Draw border
    aPainter.DrawRectangle( mBounds );

    // The div position, in pixels, and not subject to any scale calculations
    gxPix iPos;
  
    // The length of the line of the div
    gxPix iLineLength;
  
    // The last pixel to be drawn, we need to take into account the scale 
    gxPix iEndPixel =  mStartPixel + GetMyVisibleSize();

    gxString iLabel;
    
    gxPoint iFrom, iTo;

    // Start with the block at the start pixel
    gxViewDiv *iDiv = mDivProvider->BlockAtPixel( mStartPixel / mScale );
    do
    {
        iPos = iDiv->Pixel;

        // Based on the type of the div draw different lines / text
        switch ( iDiv->Type )
        {
        case gxViewDiv::Block:
            iLineLength = mBounds.height;
            iLabel = mDivProvider->GetLabelOfPixel( iPos );
            aPainter.DrawText( iLabel, iPos, 0, 3, 3, mIsHorizontal );
            break;
        case gxViewDiv::Key:
            iLineLength = gxFloor( mBounds.height / 3 );
            break;
        case gxViewDiv::Normal:
            iLineLength = 2;
            break;
        }
        
        iFrom = mIsHorizontal ? gxPoint( iPos, 0 ) : gxPoint( 0, iPos );
        iTo   = mIsHorizontal ?
                gxPoint( iPos, iLineLength ) :
                gxPoint( iLineLength, iPos );
        
        
        aPainter.DrawLine( iFrom, iTo );

        iDiv = mDivProvider->Next();

        // Stop when the actual position (taking into account the scale) of the
        // next div is smaller than the last pixel to be drawn. 
    } while ( gxFloor( iDiv->Pixel * mScale ) < iEndPixel );
}

gxPix gxRuler::GetMyVisibleSize()
{
    // Returns whichever is smaller: my scaled size or my parent size
    if ( mIsHorizontal )
        return gxMin( gxFloor( mBounds.width * mScale ), GetParent()->GetBounds().width );
    else
        return gxMin( gxFloor( mBounds.height * mScale ), GetParent()->GetBounds().height );
    
}