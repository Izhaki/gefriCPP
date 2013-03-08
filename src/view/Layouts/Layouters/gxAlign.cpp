#include "View/Layouts/Layouters/gxAlign.h"
#include "View/Elements/gxViewElement.h"

gxAlign::gxAlign( Type               aType,
                  gxLayoutData::List aData,
                  const gxRect&      aBounds )
{
    if ( aType == None )
        return;
    
    gxLayoutData::Iterator   iData;
    gxRect                   iRect;
    gxViewElement*           iChild;
    gxPix                    iPosition = 0;
    gxPix                    iContainerHeight = aBounds.GetHeight();
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
        iRect = iChild->GetBounds();
        
        if ( aType == Start )
            iPosition = 0;
        else if ( aType == Middle )
            iPosition = ( iContainerHeight - iRect.GetHeight() ) / 2;
        else if ( aType == End )
            iPosition = iContainerHeight - iRect.GetHeight();
                    
        iRect.SetY( iPosition );
        iChild->SetBounds( iRect );
    }
}
