#ifndef gxPrimitiveConstraint_h
#define gxPrimitiveConstraint_h

#include "View/Layouts/Constraints/gxConstraint.h"

template< class Type >
class gxPrimitiveConstraint : public gxConstraint
{
public:
    virtual ~gxPrimitiveConstraint() {}
    
    gxPrimitiveConstraint( Type aValue ) :
    mValue( aValue )
    {}
    
    Type GetValue()
    {
        return mValue;
    }
protected:
    Type mValue;
};

#endif //gxPrimitiveConstraint_h
