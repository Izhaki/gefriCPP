#include "View/Layouts/Layouters/gxDistribute.h"
#include "View/Elements/gxViewElement.h"

gxDistribute::gxDistribute( const Type         aType,
                            gxLayoutData::List aData,
                            const gxRect&      aBounds,
                            const bool         onMajorAxis )
{
    gxLayoutData::Iterator iData;
    gxRect                 iRect;
    gxViewElement*         iChild;
    gxPix                  iChildSize;
    
    int   iCount        = aData.size();
    int   iElementsSize = 0;
    gxPix iPosition     = 0;
    gxPix iSpacing      = 0;
    
    // Calulate the total size of all elements
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        iElementsSize += iChild->GetBounds().GetSize( onMajorAxis );
    }
    
    if ( aType == Middle || aType == End )
    {
        gxPix iContainerSize = aBounds.GetSize( onMajorAxis );
        
        // This is right for mdEnd
        iPosition = iContainerSize - iElementsSize;
        
        if ( aType == Middle )
            // and that's for mdMiddle
            iPosition = iPosition / 2;
    }
    
    if ( aType == Full || aType == Equal )
    {
        gxPix iContainerSize = aBounds.GetSize( onMajorAxis );
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
        
        iSpacing = ( iContainerSize - iElementsSize ) / iSpaceCount;
        
        if ( aType == Equal )
            iPosition += iSpacing;
    }
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChild = (*iData)->Element;
        
        iRect      = iChild->GetBounds();
        iChildSize = iRect.GetSize( onMajorAxis );
        
        iRect.SetPosition( iPosition, onMajorAxis );
        iChild->SetBounds( iRect );
        
        switch ( aType )
        {
            case Start:
            case Middle:
            case End:
                iPosition += iChildSize;
                break;
            case Full:
            case Equal:
                iPosition += iChildSize + iSpacing;
                break;
            default:
                break;
        }
    }
    
}
