#ifndef gxConstraint_h
#define gxConstraint_h

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
};

#endif //gxConstraint_h
