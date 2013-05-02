#include "View/Layouts/Operations/gxStretch.h"

gxStretch::gxStretch( const Type          aType,
                      gxConstrained::List aConstraineds,
                      const gxRect&       aRect,
                      const bool          onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxRect                 iRect;
    gxPix                  iSize = 0;
    
    switch ( aType )
    {
        case None:                                                   break;
        case Full: iSize = aRect.GetSize( onMajorAxis );             break;
        case Max:  iSize = GetMaxSize( aConstraineds, onMajorAxis ); break;
    }
    
    forEachConstrainedOf( aConstraineds, iConstrained )
    {
        (*iConstrained)->Bounds.SetSize( iSize, onMajorAxis );
    }
    
}

gxPix gxStretch::GetMaxSize( gxConstrained::List aConstraineds,
                             const bool          onMajorAxis )
{
    gxPix                  iLayouteedSize;    
    gxPix                  iSize = 0;    

    forEachConstrainedOf( aConstraineds, iConstrained )
    {
        iLayouteedSize = (*iConstrained)->Bounds.GetSize( onMajorAxis );
        iSize      = gxMax( iSize, iLayouteedSize );
    }
    
    return iSize;
}
