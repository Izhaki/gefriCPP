#ifndef gxDistribute_h
#define gxDistribute_h

#include "View/Layouts/gxLayoutData.h"

struct gxDistribute
{
    enum Type
    {
        Element,
        Full,
        Equal,
        Start,
        Middle,
        End
    };
    
    gxDistribute( Type               aType,
                  gxLayoutData::List aData,
                  const gxRect&      aBounds );
};

#endif //gxDistribute_h
