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
    
    gxStretch( Type               aType,
               gxLayoutData::List aData,
               const gxRect&      aBounds );
};

#endif //gxStretch_h
