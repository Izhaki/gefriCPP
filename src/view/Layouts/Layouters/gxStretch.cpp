#include "View/Layouts/Layouters/gxStretch.h"

gxStretch::gxStretch( const Type         aType,
                      gxConstraints::List aData,
                      const gxRect&      aContainer,
                      const bool         onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxConstraints::Iterator iConstraints;
    gxRect                 iRect;
    gxPix                  iSize = 0;
    
    switch ( aType )
    {
        case None:                                            break;
        case Full: iSize = aContainer.GetSize( onMajorAxis ); break;
        case Max:  iSize = GetMaxSize( aData, onMajorAxis );  break;
    }    
    
    for ( iConstraints = aData.begin();
          iConstraints != aData.end();
          ++iConstraints )
    {
        (*iConstraints)->Bounds.SetSize( iSize, onMajorAxis );
    }
    
}

gxPix gxStretch::GetMaxSize( gxConstraints::List aData,
                             const bool         onMajorAxis )
{
    gxConstraints::Iterator iConstraints;
    gxPix                  iChildSize;    
    gxPix                  iSize = 0;    
    
    for ( iConstraints = aData.begin();
          iConstraints != aData.end();
          ++iConstraints )
    {
        iChildSize = (*iConstraints)->Bounds.GetSize( onMajorAxis );
        iSize      = gxMax( iSize, iChildSize );
    }
    
    return iSize;
}
