#ifndef gxPrimitiveConstraint_h
#define gxPrimitiveConstraint_h

#include "View/Layouts/Constraints/gxConstraint.h"

template< class PrimitiveType >
class gxPrimitiveConstraint : public gxConstraint
{
public:
    virtual ~gxPrimitiveConstraint() {}
    
    gxPrimitiveConstraint( PrimitiveType aValue ) :
    mValue( aValue )
    {}
    
    PrimitiveType GetValue()
    {
        return mValue;
    }
protected:
    PrimitiveType mValue;
};

#endif //gxPrimitiveConstraint_h
