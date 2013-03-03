#include "View/Elements/Structural/Anchors/gxBoxAnchor.h"

gxBoxAnchor::gxBoxAnchor()
  : gxAnchor()
{
}

gxPoint gxBoxAnchor::GetPosition()
{
    gxRect iRect = GetParent()->GetBounds();

    // It's the parent's bounds we need to transform, not ours; thus, the call
    // to GetParent()
    GetParent()->TransformToAbsolute( iRect );
    
    return iRect.GetCenter();
}