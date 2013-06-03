#include "View/Layouts/Operations/gxStretch.h"

gxStretch::gxStretch( const Type                     aType,
                      const gxRect&                  aRect,
                            gxViewElement::Iterator& aLayoutees,
                      const bool                     onMajorAxis )
{
    gxPix  iSize = 0;
    
    switch ( aType )
    {
        case None: return;                                           break;
        case Full: iSize = aRect.GetSize( onMajorAxis );             break;
        case Max:  iSize = GetMaxSize( aLayoutees, onMajorAxis );    break;
    }
    
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        aLayoutees.Current()->SetSize( iSize, onMajorAxis );
    }
    
}

gxPix gxStretch::GetMaxSize(       gxViewElement::Iterator& aLayoutees,
                             const bool                     onMajorAxis )
{
    gxPix iLayouteeSize;
    gxPix iSize = 0;

    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        iLayouteeSize = aLayoutees.Current()->GetSize( onMajorAxis );
        iSize          = gxMax( iSize, iLayouteeSize );
    }
    
    return iSize;
}
