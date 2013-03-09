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
    
    gxAlign( const Type         aType,
             gxLayoutData::List aData,
             const gxRect&      aContainer,
             const bool         onMajorAxis );
};

#endif //gxAlign_h
