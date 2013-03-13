#include "View/Connections/gxLineConnection.h"
#include "core/gxLog.h"

gxLineConnection::gxLineConnection()
{
    // Connections are always positioned in absolute coordinates.
    mFlags.Unset( gxViewElement::Relative );
}

void gxLineConnection::InvalidateConnection()
{
    Erase();
    gxLine::Invalidate();
}

void gxLineConnection::Validate()
{
    // Call the base class validate so children are also validated and this object
    // is marked as valid.
    gxLine::Validate();
    
    if ( !mSource || !mDestination )
        return;
    
    mFrom = mSource->GetPosition( mDestination->GetReference() );
    mTo =   mDestination->GetPosition( mSource->GetReference() );
    
    Repaint();
    
}
