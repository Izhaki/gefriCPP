#ifndef gxPackConstraint_h
#define gxPackConstraint_h
#include "View/Layouts/Operations/gxLayoutPack.h"

class gxPackConstraint : public gxPrimitiveConstraint< gxLayoutPack::Type >
{
public:
    gxPackConstraint( gxLayoutPack::Type aPack ) :
        gxPrimitiveConstraint< gxLayoutPack::Type >( aPack )
    {}
};

#endif //gxPackConstraint_h
