#include "view/Connections/gxBoxAnchor.h"

gxBoxAnchor::gxBoxAnchor( gxVisual* aOwner )
  : mOwner( aOwner )
{
}

gxPoint gxBoxAnchor::GetPosition()
{
    gxRect iRect = mOwner->GetBounds();
        
    mOwner->TransformToAbsolute( iRect );
    
    return iRect.GetCenter();
}