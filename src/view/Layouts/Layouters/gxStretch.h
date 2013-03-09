#ifndef gxStretch_h
#define gxStretch_h

#include "View/Layouts/gxLayoutData.h"

struct gxStretch
{
    enum Type
    {
        None,
        Max,
        Full
    };
    
    gxStretch( const Type         aType,
               gxLayoutData::List aData,
               const gxRect&      aContainer,
               const bool         onMajorAxis );
    
    gxPix GetMaxSize( gxLayoutData::List aData,
                      const bool         onMajorAxis );
};

#endif //gxStretch_h
