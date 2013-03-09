#include "View/Layouts/Layouters/gxStretch.h"

gxStretch::gxStretch( const Type         aType,
                      gxConstraints::List aData,
                      const gxRect&      aContainer,
                      const bool         onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxConstraints::Iterator iData;
    gxRect                 iRect;
    gxPix                  iSize = 0;
    
    switch ( aType )
    {
        case None:                                            break;
        case Full: iSize = aContainer.GetSize( onMajorAxis ); break;
        case Max:  iSize = GetMaxSize( aData, onMajorAxis );  break;
    }    
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        (*iData)->Bounds.SetSize( iSize, onMajorAxis );
    }
    
}

gxPix gxStretch::GetMaxSize( gxConstraints::List aData,
                             const bool         onMajorAxis )
{
    gxConstraints::Iterator iData;
    gxPix                  iChildSize;    
    gxPix                  iSize = 0;    
    
    for ( iData = aData.begin(); iData != aData.end(); ++iData )
    {
        iChildSize = (*iData)->Bounds.GetSize( onMajorAxis );
        iSize      = gxMax( iSize, iChildSize );
    }
    
    return iSize;
}
