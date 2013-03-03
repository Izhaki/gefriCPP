#include "View/Elements/Structural/Anchors/gxRectAnchor.h"

gxRectAnchor::gxRectAnchor()
  : gxAnchor()
{
}

gxPoint gxRectAnchor::GetReference()
{
    gxRect iRect = GetParent()->GetBounds();
    
    // It's the parent's bounds we need to transform, not ours; thus, the call
    // to GetParent()
    GetParent()->TransformToAbsolute( iRect );
    
    return iRect.GetCenter();
}

gxPoint gxRectAnchor::GetPosition( const gxPoint& aReference )
{
    gxRect iRect = GetParent()->GetBounds();
    
    // We transform the parent rect, which will give us both the correct
    // absolute center, but also the scaled width and height
    GetParent()->TransformToAbsolute( iRect );    
    
    // We start with the center of the region
    gxPoint iPosition = iRect.GetCenter();
    
    // The deltas between the center point and the reference.
    gxPix dX = aReference.X - iPosition.X;
    gxPix dY = aReference.Y - iPosition.Y;
    
    float lX = abs(dX) / (float)iRect.width;
    float lY = abs(dY) / (float)iRect.height;

    float iScale = 0.5 / gxMax( lX, lY );
    
    dX *= iScale;
    dY *= iScale;
    
    iPosition.X += dX;
    iPosition.Y += dY;
    
    return iPosition;
}