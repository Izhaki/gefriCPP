#include "gxLayoutSize.h"

gxLayoutSize::gxLayoutSize( const gxRect&                  aRect,
                                  gxViewElement::Iterator& aLayoutees,
                            const gxConstraints&           aConstraints,
                            const bool                     onMajorAxis,
                                  bool&                    hasFlex )
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
                case Pixels:  iTotalPixels  += iValue; break;
                case Percent: iTotalPercent += iValue; break;
                case Flex:    iTotalFlex    += iValue; break;
                default:                               break;
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
                default:                                                break;
            }
            aLayoutees.Current()->SetSize( iSize, onMajorAxis );
        }
    }
    
    hasFlex = iTotalFlex != 0;
}