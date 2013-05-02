#ifndef gxDistribute_h
#define gxDistribute_h

#include "View/Layouts/Constraints/gxConstrained.h"

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
    
    gxDistribute( const Type          aType,
                  gxConstrained::List aConstraineds,
                  const gxRect&       aRect,
                  const bool          onMajorAxis );
    
    bool DoSize( gxConstrained::List aConstraineds,
                 const gxRect&       aRect,
                 const bool          onMajorAxis );

    void DoDistribute( const Type          aType,
                       gxConstrained::List aConstraineds,
                       const gxRect&       aRect,
                       const bool          onMajorAxis );
    
};

#endif //gxDistribute_h
