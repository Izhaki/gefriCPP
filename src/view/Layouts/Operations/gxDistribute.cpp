#include "View/Layouts/Operations/gxDistribute.h"
#include "View/Layouts/Operations/gxLayoutSize.h"

gxDistribute::gxDistribute( const Type                     aType,
                            const gxRect&                  aRect,
                                  gxViewElement::Iterator& aLayoutees,
                            const gxConstraints&           aConstraints,
                            const bool                     onMajorAxis )
{
    bool iHasFlex;

    // First Set the size of the elements.
    gxLayoutSize( aRect, aLayoutees, aConstraints, onMajorAxis, iHasFlex );
    
    // If any of the elements has flex, the elements will take the full size
    // of the container. Thus it makes little sense to distribute items in any
    // other way than Start.
    Type iType = iHasFlex ? Start : aType;
    
    // Now distribute the elements
    
    // This position is right for Start.
    // Notice that we first work out the position in relative coordinates,
    // and we'll later change it to absolute.
    gxPix iPosition = 0;
    
    gxPix iSpacing  = 0;
    
    // First work out the initial position of the elements, and the space
    // between them
    if ( iType != Start )
    {
        int   iCount        = aLayoutees.Count();
        int   iElementsSize = 0;
        
        // Calulate the total size of all elements
        for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
        {
            iElementsSize += aLayoutees.Current()->GetSize( onMajorAxis );
        }
        
        if ( iType == Middle || iType == End )
        {
            gxPix iRectSize = aRect.GetSize( onMajorAxis );
            
            // This is right for End
            iPosition = iRectSize - iElementsSize;
            
            if ( iType == Middle )
                // and that's for Middle
                iPosition = iPosition / 2;
        }
        
        if ( iType == Full || iType == Equal )
        {
            gxPix iRectSize = aRect.GetSize( onMajorAxis );
            
            int iSpaceCount;
            
            if ( iType == Full )
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
            
            iSpacing = ( iRectSize - iElementsSize ) / iSpaceCount;
            
            if ( iType == Equal )
                iPosition += iSpacing;
        }
    }
    
    // Turn the position into an absolute one.
    iPosition += aRect.GetPosition( onMajorAxis );
    
    gxPix iLayouteeSize;
    
    // Now apply position and spacing
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        aLayoutees.Current()->SetPosition( iPosition, onMajorAxis );
        
        iLayouteeSize = aLayoutees.Current()->GetSize( onMajorAxis );
        
        switch ( iType )
        {
            case Start:
            case Middle:
            case End:
                iPosition += iLayouteeSize;
                break;
            case Full:
            case Equal:
                iPosition += iLayouteeSize + iSpacing;
                break;
            default:
                break;
        }
    }
}

