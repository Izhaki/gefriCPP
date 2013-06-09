#include "View/Layouts/Operations/gxDistribute.h"

gxDistribute::gxDistribute( const Type                     aType,
                            const gxRect&                  aRect,
                                  gxViewElement::Iterator& aLayoutees,
                            const gxConstraints&           aConstraints,
                            const bool                     onMajorAxis,
                            const bool                     aRelative )
{
    // First Set the size of the elements.
    bool iHasFlex = DoSize( aRect, aLayoutees, aConstraints, onMajorAxis );
    
    // If any of the elements has flex, the elements will take the full size
    // of the container. Thus it makes little sense to distribute items in any
    // other way than Start.
    Type iType = iHasFlex ? Start : aType;
    
    // Now distribute the elements
    DoDistribute( iType, aRect, aLayoutees, aConstraints, onMajorAxis, aRelative );
}

bool gxDistribute::DoSize( const gxRect&                  aRect,
                                 gxViewElement::Iterator& aLayoutees,
                           const gxConstraints&           aConstraints,
                           const bool                     onMajorAxis )
{
    gxPix iTotalPixels  = 0;
    int   iTotalPercent = 0;
    int   iTotalFlex    = 0;
    
    // For readability sake (we used these in the switch statements)
    using gxSizeConstraint::Unit::Pixels;
    using gxSizeConstraint::Unit::Percent;
    using gxSizeConstraint::Unit::Flex;
    
    gxSizeConstraint* iSizeConstraint = NULL;
    
    // Work out how much there is from each type of size:
    // Pixels, Percent, Flex
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        aConstraints.Get( aLayoutees.Current(), iSizeConstraint, onMajorAxis );
        
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
            iTotalPixels += aLayoutees.Current()->GetSize( onMajorAxis );
        }
    }
    
    gxPix iRectSize = aRect.GetSize( onMajorAxis );
    
    // The amount of pixels left is the container size minus the total pixels
    // used by figures which size is pixel-based.
    gxPix iPixelsLeft    = iRectSize - iTotalPixels;
    
    // The amount of pixels left for flex-based element is the amount of pixels
    // left minus the pixels that will be taken by percentage sized elements.
    gxPix iFlexLeft      = iPixelsLeft - iPixelsLeft * iTotalPercent / 100;
    gxPix iSize;
    
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        aConstraints.Get( aLayoutees.Current(), iSizeConstraint, onMajorAxis );
        
        if ( iSizeConstraint ) {
            int iValue = iSizeConstraint->GetValue();
            
            switch ( iSizeConstraint->GetUnit() ) {
                case Pixels:  iSize = iValue;                           break;
                case Percent: iSize = iPixelsLeft * iValue / 100;       break;
                case Flex:    iSize = iFlexLeft * iValue / iTotalFlex ; break;
                default: break;
            }
            aLayoutees.Current()->SetSize( iSize, onMajorAxis );
        }
    }
    
    return iTotalFlex != 0;
}

void gxDistribute::DoDistribute( const Type                     aType,
                                 const gxRect&                  aRect,
                                       gxViewElement::Iterator& aLayoutees,
                                 const gxConstraints&           aConstraints,
                                 const bool                     onMajorAxis,
                                 const bool                     aRelative )
{
    // This position is right for Start.
    // Notice that we first work out the position in relative coordinates,
    // and we'll later change it to absolute if needed.
    gxPix iPosition = 0;
    
    gxPix iSpacing  = 0;
    
    // First work out the initial position of the elements, and the space
    // between them
    if ( aType != Start )
    {
        int   iCount        = aLayoutees.Count();
        int   iElementsSize = 0;
        
        // Calulate the total size of all elements
        for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
        {
            iElementsSize += aLayoutees.Current()->GetSize( onMajorAxis );
        }
        
        if ( aType == Middle || aType == End )
        {
            gxPix iRectSize = aRect.GetSize( onMajorAxis );
            
            // This is right for End
            iPosition = iRectSize - iElementsSize;
            
            if ( aType == Middle )
                // and that's for Middle
                iPosition = iPosition / 2;
        }
        
        if ( aType == Full || aType == Equal )
        {
            gxPix iRectSize = aRect.GetSize( onMajorAxis );
            
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
            
            iSpacing = ( iRectSize - iElementsSize ) / iSpaceCount;
            
            if ( aType == Equal )
                iPosition += iSpacing;
        }
    }
    
    // Turn the position to absolute coordinates if needed.
    if ( !aRelative )
        iPosition += aRect.GetPosition( onMajorAxis );
    
    gxPix iLayouteeSize;
    
    // Now apply position and spacing
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        aLayoutees.Current()->SetPosition( iPosition, onMajorAxis );
        
        iLayouteeSize = aLayoutees.Current()->GetSize( onMajorAxis );
        
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
