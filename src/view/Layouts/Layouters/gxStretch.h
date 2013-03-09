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
               const gxRect&      aBounds,
               const bool         onMajorAxis );
};

#endif //gxStretch_h
