#include "View/Layouts/Operations/gxLayoutPack.h"
#include "View/Layouts/Constraints/gxPackConstraint.h"

// TODO: change aType to aDefault
gxLayoutPack::gxLayoutPack( const Type                     aType,
                            const gxRect&                  aRect,
                            gxViewElement::Iterator& aLayoutees,
                            const gxConstraints&           aConstraints,
                            const bool                     onMajorAxis )
{
    // The overall size of each block
    gxPix iStartBlockSize  = 0,
          iMiddleBlockSize = 0,
          iEndBlockSize    = 0;
    
    gxPix iLayouteeSize;
    
    gxPackConstraint* iPackConstraint;
    Type              iPack;
    
    // Work out the block sizes
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        iLayouteeSize = aLayoutees.Current()->GetSize( onMajorAxis );
        
        // Get the Pack constraint of the layoutees.
        aConstraints.Get( aLayoutees.Current(), iPackConstraint );
        
        if ( iPackConstraint )
        {
            iPack = iPackConstraint->GetValue();
        } else {
            iPack = aType;
        }
        
        switch ( iPack )
        {
            case None:                                      break;
            case Start:  iStartBlockSize  += iLayouteeSize; break;
            case Middle: iMiddleBlockSize += iLayouteeSize; break;
            case End:    iEndBlockSize    += iLayouteeSize; break;
        }
    }
    
    gxPix iPosition;
    gxPix iContainerSize     = aRect.GetSize( onMajorAxis );
    gxPix iContainerPosition = aRect.GetPosition( onMajorAxis );
    
    gxPix iStartBlockPosition  = iContainerPosition,
          iMiddleBlockPosition = iContainerPosition + ( iContainerSize - iStartBlockSize ) / 2,
          iEndBlockPosition    = iContainerPosition + ( iContainerSize - iEndBlockSize );
    
    
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        iLayouteeSize = aLayoutees.Current()->GetSize( onMajorAxis );
        
        // Get the Pack constraint of the layoutees.
        aConstraints.Get( aLayoutees.Current(), iPackConstraint );
        
        if ( iPackConstraint )
        {
            iPack = iPackConstraint->GetValue();
        } else {
            iPack = aType;
        }
        
        switch ( iPack )
        {
            case None:
                break;
                
            case Start:
                iPosition             = iStartBlockPosition;
                iStartBlockPosition  += iLayouteeSize;
                break;
                
            case Middle:
                iPosition             = iMiddleBlockPosition;
                iMiddleBlockPosition += iLayouteeSize;
                break;
                
            case End:
                iPosition             = iEndBlockPosition;
                iEndBlockPosition    += iLayouteeSize;
                break;
        }
        
        aLayoutees.Current()->SetPosition( iPosition, onMajorAxis );
    }
}
