#include "View/Connections/gxLineConnection.h"
#include "core/gxLog.h"

void gxLineConnection::Validate()
{
    if ( mSource )
    {
        mFrom = mSource->GetPosition();
    }
    
    if ( mDestination )
    {
        mTo = mDestination->GetPosition();
    }
    
    // Call the base class validate so children are also validated and this object
    // is marked as valid.
    gxLine::Validate();
    
    Repaint();
}
