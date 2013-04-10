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
        // TODO, can't we just store X/Y ? Can the map key be a pair?
        // Or alternatively have one map for major, one for minor?
        Size,
    };
    
    virtual ~gxConstraint() {}
};

#endif //gxConstraint_h
