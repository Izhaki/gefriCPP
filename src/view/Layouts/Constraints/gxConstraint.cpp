#include "View/Layouts/Constraints/gxConstraint.h"
#include "View/Layouts/Constraints/gxSizeConstraint.h"
#include "View/Layouts/Constraints/gxRegionConstraint.h"
#include "core/gxAssert.h"

gxConstraint* gxConstraint::Create( gxConstraint::Type  aType,
                                    gxConstraint::Value aValue )
{
    switch ( aType )
    {
        case gxConstraint::Pixels:
        case gxConstraint::Percent:
        case gxConstraint::Flex:
            return new gxSizeConstraint( aType, aValue );
        case gxConstraint::Region:
            return new gxRegionConstraint( aValue );
            
        default:
            gxWarn( "No constraint of this type found" );
            return NULL;
    }
}