#include "View/Layouts/Layouters/gxStretch.h"

gxStretch::gxStretch( const Type          aType,
                      gxConstraints::List aConstraints,
                      const gxRect&       aContainer,
                      const bool          onMajorAxis )
{
    if ( aType == None )
        return;
    
    gxRect                 iRect;
    gxPix                  iSize = 0;
    
    switch ( aType )
    {
        case None:                                            break;
        case Full: iSize = aContainer.GetSize( onMajorAxis ); break;
        case Max:  iSize = GetMaxSize( aConstraints, onMajorAxis );  break;
    }
    
    forEachConstraintOf( aConstraints, iConstraints )
    {
        (*iConstraints)->Bounds.SetSize( iSize, onMajorAxis );
    }
    
}

gxPix gxStretch::GetMaxSize( gxConstraints::List aConstraints,
                             const bool          onMajorAxis )
{
    gxPix                  iChildSize;    
    gxPix                  iSize = 0;    

    forEachConstraintOf( aConstraints, iConstraints )
    {
        iChildSize = (*iConstraints)->Bounds.GetSize( onMajorAxis );
        iSize      = gxMax( iSize, iChildSize );
    }
    
    return iSize;
}
