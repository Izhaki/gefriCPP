#include "view/Connections/gxBoxAnchor.h"

gxBoxAnchor::gxBoxAnchor( gxVisual* aOwner )
  : gxAnchor( aOwner )
{
}

gxPoint gxBoxAnchor::GetPosition()
{
    gxRect iRect = mVisual->GetBounds();
        
    mVisual->TransformToAbsolute( iRect );
    
    return iRect.GetCenter();
}