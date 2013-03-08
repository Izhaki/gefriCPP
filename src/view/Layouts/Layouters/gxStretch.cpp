#include "View/Layouts/Layouters/gxStretch.h"
#include "View/Elements/gxViewElement.h"

gxStretch::gxStretch( Type               aType,
                      gxLayoutData::List aData,
                      const gxRect&      aBounds )
{
    if ( aType == None )
        return;
    
    gxLayoutData::Iterator iData;
    gxRect                 iRect;
    gxViewElement*         iChild;
    gxPix                  iHeight = 0;
    
    if ( aType == Full )
    {
        
        iHeight = aBounds.GetHeight();
        
    } else if ( aType == Max ) {
        // Work out the biggest height
        
        gxPix iChildHeight;
        
        for ( iData = aData.begin(); iData != aData.end(); ++iData )
        {
            iChild = (*iData)->Element;
            
            iChildHeight = iChild->GetBounds().GetHeight();
            iHeight = gxMax( iHeight, iChildHeight );
        }
        
    }
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
        // TODO: won't be easier if view element had setHeight?
        iRect = iChild->GetBounds();
        iRect.SetHeight( iHeight );
        iChild->SetBounds( iRect );
    }
    
}
