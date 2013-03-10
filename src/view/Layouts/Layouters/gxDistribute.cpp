#include "View/Layouts/Layouters/gxDistribute.h"

gxDistribute::gxDistribute( const Type         aType,
                            gxConstraints::List aData,
                            const gxRect&      aContainer,
                            const bool         onMajorAxis )
{
    // First Set the size of the elements.
    bool iHasFlex = DoSize( aData, aContainer, onMajorAxis );
    
    // If any of the elements has flex, the elements will take the full size
    // of the container. Thus it makes little sense to distribute items in any
    // other way than Start.
    Type iType = iHasFlex ? Start : aType;
    
    // Now distribute the elements
    DoDistribute( iType, aData, aContainer, onMajorAxis );
}

bool gxDistribute::DoSize( gxConstraints::List aData,
                           const gxRect&      aContainer,
                           const bool         onMajorAxis )
{
    gxPix iTotalPixels  = 0;
    int   iTotalPercent = 0;
    int   iTotalFlex    = 0;
    
    gxConstraints::Iterator iConstraints;
    
    // Work out how much there is from each type of size:
    // Pixels, Percent, Flex
    for ( iConstraints = aData.begin();
          iConstraints != aData.end();
          ++iConstraints )
    {
        if ( (*iConstraints)->IsPixels() )
        {
            iTotalPixels += (*iConstraints)->Bounds.GetSize( onMajorAxis );
        } else if ( (*iConstraints)->IsPercent() ) {
            iTotalPercent += (*iConstraints)->GetPercent();
        } else {
            iTotalFlex += (*iConstraints)->GetFlex();
        }
    }
    
    gxPix iContainerSize = aContainer.GetSize( onMajorAxis );
    
    // The amount of pixels left is the container size minus the total pixels
    // used by figures which size is pixel-based.
    gxPix iPixelsLeft    = iContainerSize - iTotalPixels;
    
    // The amount of pixels left for flex-based element is the amount of pixels
    // left minus the pixels that will be taken by percentage sized elements.
    gxPix iFlexLeft      = iPixelsLeft - iPixelsLeft * iTotalPercent / 100;
    gxPix iSize;
    
    for ( iConstraints = aData.begin();
          iConstraints != aData.end();
          ++iConstraints )
    {
        if ( (*iConstraints)->IsntPixels() )
        {
            if ( (*iConstraints)->IsPercent() )
            {
                // Percent
                iSize = iPixelsLeft * (*iConstraints)->GetPercent() / 100;
            } else {
                // Flex
                iSize = iFlexLeft * (*iConstraints)->GetFlex() / iTotalFlex ;
            }
            (*iConstraints)->Bounds.SetSize( iSize, onMajorAxis );
        }
    }
    
    return iTotalFlex != 0;
    
}


void gxDistribute::DoDistribute( const Type          aType,
                                 gxConstraints::List aData,
                                 const gxRect&       aContainer,
                                 const bool          onMajorAxis )
{
    gxConstraints::Iterator iConstraints;
    
    gxPix iPosition = 0;
    gxPix iSpacing  = 0;
    
    // First work out the initial position of the elements, and the space
    // between them
    if ( aType != Start )
    {
        int   iCount        = aData.size();
        int   iElementsSize = 0;
        
        // Calulate the total size of all elements
        for ( iConstraints = aData.begin();
              iConstraints != aData.end();
              ++iConstraints )
        {
            iElementsSize += (*iConstraints)->Bounds.GetSize( onMajorAxis );
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
    }
    
    gxPix iChildSize;
    
    // Now apply position and spacing
    for ( iConstraints = aData.begin();
          iConstraints != aData.end();
          ++iConstraints )
    {
        (*iConstraints)->Bounds.SetPosition( iPosition, onMajorAxis );
        
        iChildSize = (*iConstraints)->Bounds.GetSize( onMajorAxis );
        
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

