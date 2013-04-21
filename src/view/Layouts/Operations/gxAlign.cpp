#include "View/Layouts/Operations/gxAlign.h"

gxAlign::gxAlign( const Type          aType,
                  gxConstrained::List aConstraineds,
                  const gxRect&       aContainer,
                  const bool          onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxPix iPosition = 0;
    gxPix iContainerSize = aContainer.GetSize( onMajorAxis );
    
    forEachConstrainedOf( aConstraineds, iConstrained )
    {
        gxPix iSize = (*iConstrained)->Bounds.GetSize( onMajorAxis );
        
        switch ( aType )
        {
            case None:                                               break;
            case Start:  iPosition = 0;                              break;
            case Middle: iPosition = ( iContainerSize - iSize ) / 2; break;
            case End:    iPosition = ( iContainerSize - iSize );     break;
        }
        
        (*iConstrained)->Bounds.SetPosition( iPosition, onMajorAxis );
    }
}
