#include "View/Layouts/Layouters/gxDistribute.h"
#include "View/Elements/gxViewElement.h"

gxDistribute::gxDistribute( Type               aType,
                            gxLayoutData::List aData,
                            const gxRect&      aBounds )
{
    gxLayoutData::Iterator iData;
    gxRect                 iRect;
    gxViewElement*         iChild;
    gxPix                  iChildWidth;
    
    int   iCount         = aData.size();
    int   iElementsWidth = 0;
    gxPix iPosition      = 0;
    gxPix iSpacing       = 0;
    
    // Calulate the total width of all elements
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        iElementsWidth += iChild->GetBounds().GetWidth();
    }
    
    if ( aType == Middle || aType == End )
    {
        gxPix iContainerWidth = aBounds.GetWidth();
        
        // This is right for mdEnd
        iPosition = iContainerWidth - iElementsWidth;
        
        if ( aType == Middle )
            // and that's for mdMiddle
            iPosition = iPosition / 2;
    }
    
    if ( aType == Full || aType == Equal )
    {
        gxPix iContainerWidth = aBounds.GetWidth();
        int iSpaceCount;
        
        if ( aType == Full )
        {
            // If we're on full distribution the space count is one less than
            // the elements count ( 3 elements get 2 space).
            iSpaceCount = iCount - 1;
            
            // ensure there's at least 1 space.
            if ( iSpaceCount < 1 ) iSpaceCount = 1;
        } else {
            // If we're on equal distribution the space count is one more than
            // the elements count ( 3 elements get 4 space).
            iSpaceCount = iCount + 1;
        }
        
        iSpacing = ( iContainerWidth - iElementsWidth ) / iSpaceCount;
        
        if ( aType == Equal )
            iPosition += iSpacing;
    }
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
        iRect       = iChild->GetBounds();
        iChildWidth = iRect.GetWidth();
        
        iRect.SetX( iPosition );
        iChild->SetBounds( iRect );
        
        switch ( aType )
        {
            case Start:
            case Middle:
            case End:
                iPosition += iChildWidth;
                break;
            case Full:
            case Equal:
                iPosition += iChildWidth + iSpacing;
                break;
            default:
                break;
        }
    }
    
}
