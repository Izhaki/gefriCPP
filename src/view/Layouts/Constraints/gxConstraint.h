#ifndef gxConstraint_h
#define gxConstraint_h

#define gxMajorAxis true
#define gxMinorAxis false

#include <typeinfo>

typedef const std::type_info* gxConstraintId;

#define gxTypeId( aType ) &typeid( aType )

class gxConstraint
{
public:
    virtual ~gxConstraint() {}
};

#endif //gxConstraint_h
