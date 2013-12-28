#include "View/Layouts/Operations/gxLayoutAlign.h"

gxLayoutAlign::gxLayoutAlign( const Type                     aType,
                              const gxRect&                  aRect,
                                    gxViewElement::Iterator& aLayoutees,
                              const bool                     onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxPix iPosition = 0;
    gxPix iContainerSize = aRect.GetSize( onMajorAxis );
    gxPix iContainerPosition = aRect.GetPosition( onMajorAxis );
    
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        gxPix iSize = aLayoutees.Current()->GetSize( onMajorAxis );
        
        switch ( aType )
        {
            case None:                                               break;
            case Start:  iPosition = 0;                              break;
            case Middle: iPosition = ( iContainerSize - iSize ) / 2; break;
            case End:    iPosition = ( iContainerSize - iSize );     break;
        }
        
        // Now translate the position into an absolute one
        iPosition += iContainerPosition;
        
        aLayoutees.Current()->SetPosition( iPosition, onMajorAxis );
    }
}
