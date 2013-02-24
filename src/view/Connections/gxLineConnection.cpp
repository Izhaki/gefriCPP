#include "View/Connections/gxLineConnection.h"

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
    
    // TODO: is this really needed? Can a line have children???
    // Call the base class validate so children are also validated and this object
    // is marked as valid.
    gxLine::Validate();
    
    Repaint();
}
