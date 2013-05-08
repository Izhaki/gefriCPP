#ifndef gxConstraint_h
#define gxConstraint_h

#define gxMajorAxis true
#define gxMinorAxis false

#include <typeinfo>

typedef const std::type_info* gxConstraintId;

class gxConstraint
{
public:
    enum Type
    {
        Pixels = 1,
        Percent,
        Flex,
        Region,
        Split,
        Collapse,
        Locked,
        Resizable,
        Span,
        Align,
        
        // Internal Constraints
        Size,
    };
    
    typedef int Value;
    
    static gxConstraint* Create ( Type  aType,
                                  Value aValue );
    
    virtual ~gxConstraint() {}
    
//!    gxConstraintId GetId() { return &typeid( *this ); }
    
};

#endif //gxConstraint_h
