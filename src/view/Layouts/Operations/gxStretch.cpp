#include "View/Layouts/Operations/gxStretch.h"

gxStretch::gxStretch( const Type                 aType,
                      const gxRect&              aRect,
                      const gxViewElement::List& aLayoutees,
                      const bool                 onMajorAxis )
{
    gxPix  iSize = 0;
    
    switch ( aType )
    {
        case None: return;                                           break;
        case Full: iSize = aRect.GetSize( onMajorAxis );             break;
        case Max:  iSize = GetMaxSize( aLayoutees, onMajorAxis );    break;
    }
    
    forEachElement( aLayoutees, iLayoutee )
    {
        (*iLayoutee)->SetSize( iSize, onMajorAxis );
    }
    
}

gxPix gxStretch::GetMaxSize( const gxViewElement::List& aLayoutees,
                             const bool                 onMajorAxis )
{
    gxPix iLayouteeSize;
    gxPix iSize = 0;

    forEachElement( aLayoutees, iLayoutee )
    {
        iLayouteeSize = (*iLayoutee)->GetSize( onMajorAxis );
        iSize          = gxMax( iSize, iLayouteeSize );
    }
    
    return iSize;
}
