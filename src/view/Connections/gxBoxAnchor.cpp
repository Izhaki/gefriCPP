#include "view/Connections/gxBoxAnchor.h"

gxBoxAnchor::gxBoxAnchor( gxVisual* aOwner )
  : mOwner( aOwner )
{
}

gxPoint gxBoxAnchor::GetPosition()
{
    gxRect iRect = mOwner->GetBounds();
    
    // Will atomatically include all transform flags.
    gxTransFlags iFlags;
    
    mOwner->TransformToAbsolute( iRect, iFlags );
    
    // The anchor position is the X + half the width or Y + half the height.
    return iRect.GetPosition() + iRect.GetSize().Scale( 0.5, 0.5 );
}