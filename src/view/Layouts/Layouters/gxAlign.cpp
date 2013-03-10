#include "View/Layouts/Layouters/gxAlign.h"

gxAlign::gxAlign( const Type         aType,
                  gxConstraints::List aData,
                  const gxRect&      aContainer,
                  const bool         onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxConstraints::Iterator iConstraints;
    gxPix                   iPosition = 0;
    gxPix                   iContainerSize = aContainer.GetSize( onMajorAxis );
    
    for ( iConstraints = aData.begin();
          iConstraints != aData.end();
          ++iConstraints )
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
