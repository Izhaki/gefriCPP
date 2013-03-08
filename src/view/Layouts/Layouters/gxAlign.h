#ifndef gxAlign_h
#define gxAlign_h

#include "View/Layouts/gxLayoutData.h"

struct gxAlign
{
    enum Type
    {
        None,
        Start,
        Middle,
        End
    };
    
    gxAlign( Type               aType,
             gxLayoutData::List aData,
             const gxRect&      aBounds );
};

#endif //gxAlign_h
