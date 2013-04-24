#ifndef gxConstraint_h
#define gxConstraint_h

typedef bool gxAxis;
#define gxMajorAxis true
#define gxMinorAxis false

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
    
    virtual ~gxConstraint() {}
    
    virtual Type GetType() = 0;
};

#endif //gxConstraint_h
