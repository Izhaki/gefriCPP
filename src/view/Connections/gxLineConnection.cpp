#include "View/Connections/gxLineConnection.h"
#include "core/gxLog.h"

void gxLineConnection::Validate()
{
    if ( !mSource || !mDestination )
        return;
    
    mFrom = mSource->GetPosition( mDestination->GetReference() );
    mTo =   mDestination->GetPosition( mSource->GetReference() );
    
    // Call the base class validate so children are also validated and this object
    // is marked as valid.
    gxLine::Validate();
    
    Repaint();
    
}
