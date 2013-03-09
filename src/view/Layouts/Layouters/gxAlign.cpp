#include "View/Layouts/Layouters/gxAlign.h"
#include "View/Elements/gxViewElement.h"

gxAlign::gxAlign( const Type         aType,
                  gxLayoutData::List aData,
                  const gxRect&      aBounds,
                  const bool         onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxLayoutData::Iterator   iData;
    gxRect                   iRect;
    gxViewElement*           iChild;
    gxPix                    iPosition = 0;
    gxPix                    iContainerSize = aBounds.GetSize( onMajorAxis );
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
        iRect = iChild->GetBounds();
        
        if ( aType == Start )
            iPosition = 0;
        else if ( aType == Middle )
            iPosition = ( iContainerSize - iRect.GetSize( onMajorAxis ) ) / 2;
        else if ( aType == End )
            iPosition = iContainerSize - iRect.GetSize( onMajorAxis );
                    
        iRect.SetPosition( iPosition, onMajorAxis );
        iChild->SetBounds( iRect );
    }
}
