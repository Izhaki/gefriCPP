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
    
    gxDistribute( const Type         aType,
                  gxLayoutData::List aData,
                  const gxRect&      aBounds,
                  const bool         onMajorAxis );
};

#endif //gxDistribute_h
