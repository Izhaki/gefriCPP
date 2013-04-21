#include "View/Layouts/Operations/gxDistribute.h"

gxDistribute::gxDistribute( const Type          aType,
                            gxConstrained::List aConstraineds,
                            const gxRect&       aContainer,
                            const bool          onMajorAxis )
{
    // First Set the size of the elements.
    bool iHasFlex = DoSize( aConstraineds, aContainer, onMajorAxis );
    
    // If any of the elements has flex, the elements will take the full size
    // of the container. Thus it makes little sense to distribute items in any
    // other way than Start.
    Type iType = iHasFlex ? Start : aType;
    
    // Now distribute the elements
    DoDistribute( iType, aConstraineds, aContainer, onMajorAxis );
}

bool gxDistribute::DoSize( gxConstrained::List aConstraineds,
                           const gxRect&       aContainer,
                           const bool          onMajorAxis )
{
    gxPix iTotalPixels  = 0;
    int   iTotalPercent = 0;
    int   iTotalFlex    = 0;
    
    // for readability sake (we used these in the switch statements)
    using gxConstraint::Type::Pixels;
    using gxConstraint::Type::Percent;
    using gxConstraint::Type::Flex;
    
    gxSizeConstraint* iSizeConstraint = NULL;
    
    // Work out how much there is from each type of size:
    // Pixels, Percent, Flex
    forEachConstrainedOf( aConstraineds, iConstrained )
    {
        (*iConstrained)->Get( iSizeConstraint, onMajorAxis );
        
        if ( iSizeConstraint )
        {
            int iValue = iSizeConstraint->GetValue();
            
            switch ( iSizeConstraint->GetUnit() )
            {
                case Pixels:  iTotalPixels  += iValue;      break;
                case Percent: iTotalPercent += iValue;      break;
                case Flex:    iTotalFlex    += iValue;      break;
                default: break;
            }
        } else {
            iTotalPixels += (*iConstrained)->Bounds.GetSize( onMajorAxis );
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

    forEachConstrainedOf( aConstraineds, iConstrained ) {
        (*iConstrained)->Get( iSizeConstraint, onMajorAxis );
        
        if ( iSizeConstraint ) {
            int iValue = iSizeConstraint->GetValue();
                        
            switch ( iSizeConstraint->GetUnit() ) {
                case Pixels:  iSize = iValue;                           break;
                case Percent: iSize = iPixelsLeft * iValue / 100;       break;
                case Flex:    iSize = iFlexLeft * iValue / iTotalFlex ; break;
                default: break;
            }
            (*iConstrained)->Bounds.SetSize( iSize, onMajorAxis );            
        }
    }
    
    return iTotalFlex != 0;
}


void gxDistribute::DoDistribute( const Type          aType,
                                 gxConstrained::List aConstraineds,
                                 const gxRect&       aContainer,
                                 const bool          onMajorAxis )
{
    gxPix iPosition = 0;
    gxPix iSpacing  = 0;
    
    // First work out the initial position of the elements, and the space
    // between them
    if ( aType != Start )
    {
        int   iCount        = aConstraineds.size();
        int   iElementsSize = 0;
        
        // Calulate the total size of all elements
        forEachConstrainedOf( aConstraineds, iConstrained )
        {
            iElementsSize += (*iConstrained)->Bounds.GetSize( onMajorAxis );
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
    
    gxPix iLayouteeSize;
    
    // Now apply position and spacing
    forEachConstrainedOf( aConstraineds, iConstrained )
    {
        (*iConstrained)->Bounds.SetPosition( iPosition, onMajorAxis );
        
        iLayouteeSize = (*iConstrained)->Bounds.GetSize( onMajorAxis );
        
        switch ( aType )
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

