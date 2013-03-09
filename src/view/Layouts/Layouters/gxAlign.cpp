#include "View/Layouts/Layouters/gxAlign.h"

gxAlign::gxAlign( const Type         aType,
                  gxLayoutData::List aData,
                  const gxRect&      aContainer,
                  const bool         onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxLayoutData::Iterator iData;
    gxPix                  iPosition = 0;
    gxPix                  iContainerSize = aContainer.GetSize( onMajorAxis );
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        gxPix iSize = (*iData)->Bounds.GetSize( onMajorAxis );
        
        switch ( aType )
        {
            case None:                                               break;
            case Start:  iPosition = 0;                              break;
            case Middle: iPosition = ( iContainerSize - iSize ) / 2; break;
            case End:    iPosition = ( iContainerSize - iSize );     break;
        }
        
        (*iData)->Bounds.SetPosition( iPosition, onMajorAxis );
    }
}
