#include "View/Layouts/Layouters/gxStretch.h"
#include "View/Elements/gxViewElement.h"

gxStretch::gxStretch( const Type         aType,
                      gxLayoutData::List aData,
                      const gxRect&      aBounds,
                      const bool         onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxLayoutData::Iterator iData;
    gxRect                 iRect;
    gxViewElement*         iChild;
    gxPix                  iSize = 0;
    
    if ( aType == Full )
    {
        
        iSize = aBounds.GetSize( onMajorAxis );
        
    } else if ( aType == Max ) {
        // Work out the biggest Size
        
        gxPix iChildSize;
        
        for ( iData = aData.begin(); iData != aData.end(); ++iData )
        {
            iChild     = (*iData)->Element;            
            iChildSize = iChild->GetBounds().GetSize( onMajorAxis );
            iSize      = gxMax( iSize, iChildSize );
        }
        
    }
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
        // TODO: won't be easier if view element had setSize?
        iRect = iChild->GetBounds();
        iRect.SetSize( iSize, onMajorAxis );
        iChild->SetBounds( iRect );
    }
    
}
