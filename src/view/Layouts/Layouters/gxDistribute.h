#ifndef gxDistribute_h
#define gxDistribute_h

#include "View/Layouts/Constraints/gxConstraints.h"

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
                  gxConstraints::List aConstraints,
                  const gxRect&       aContainer,
                  const bool          onMajorAxis );
    
    bool DoSize( gxConstraints::List aConstraints,
                 const gxRect&       aContainer,
                 const bool          onMajorAxis );

    void DoDistribute( const Type          aType,
                       gxConstraints::List aConstraints,
                       const gxRect&       aContainer,
                       const bool          onMajorAxis );
    
};

#endif //gxDistribute_h
