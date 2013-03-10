#include "View/Layouts/Layouters/gxAlign.h"

gxAlign::gxAlign( const Type          aType,
                  gxConstraints::List aConstraints,
                  const gxRect&       aContainer,
                  const bool          onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxPix                   iPosition = 0;
    gxPix                   iContainerSize = aContainer.GetSize( onMajorAxis );
    
    forEachConstraintOf( aConstraints, iConstraints )
    {
        gxPix iSize = (*iConstraints)->Bounds.GetSize( onMajorAxis );
        
        switch ( aType )
        {
            case None:                                               break;
            case Start:  iPosition = 0;                              break;
            case Middle: iPosition = ( iContainerSize - iSize ) / 2; break;
            case End:    iPosition = ( iContainerSize - iSize );     break;
        }
        
        (*iConstraints)->Bounds.SetPosition( iPosition, onMajorAxis );
    }
}
