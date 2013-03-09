#include "View/Layouts/Layouters/gxDistribute.h"
#include "View/Elements/gxViewElement.h"

gxDistribute::gxDistribute( const Type         aType,
                            gxLayoutData::List aData,
                            const gxRect&      aContainer,
                            const bool         onMajorAxis )
{
    gxLayoutData::Iterator iData;
    gxRect                 iRect;
    gxPix                  iChildSize;
    
    int   iCount        = aData.size();
    int   iElementsSize = 0;
    gxPix iPosition     = 0;
    gxPix iSpacing      = 0;
    
    // Calulate the total size of all elements
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iElementsSize += (*iData)->Bounds.GetSize( onMajorAxis );
    }
    
    if ( aType == Middle || aType == End )
    {
        gxPix iContainerSize = aContainer.GetSize( onMajorAxis );
        
        // This is right for mdEnd
        iPosition = iContainerSize - iElementsSize;
        
        if ( aType == Middle )
            // and that's for mdMiddle
            iPosition = iPosition / 2;
    }
    
    if ( aType == Full || aType == Equal )
    {
        gxPix iContainerSize = aContainer.GetSize( onMajorAxis );
        
        int iSpaceCount;
        
        if ( aType == Full )
        {
            // If we're on full distribution the space count is one less than
            // the elements count (3 elements get 2 space).
            iSpaceCount = iCount - 1;
            
            // ensure there's at least 1 space.
            if ( iSpaceCount < 1 ) iSpaceCount = 1;
        } else {
            // If we're on equal distribution the space count is one more than
            // the elements count (3 elements get 4 space).
            iSpaceCount = iCount + 1;
        }
        
        iSpacing = ( iContainerSize - iElementsSize ) / iSpaceCount;
        
        if ( aType == Equal )
            iPosition += iSpacing;
    }
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        (*iData)->Bounds.SetPosition( iPosition, onMajorAxis );
        
        iChildSize = (*iData)->Bounds.GetSize( onMajorAxis );
        
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
