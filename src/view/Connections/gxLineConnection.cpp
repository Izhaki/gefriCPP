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

void gxLineConnection::DoValidate()
{
    if ( !mSource || !mDestination )
        return;
    
    mFrom = mSource->GetPosition( mDestination->GetReference() );
    mTo =   mDestination->GetPosition( mSource->GetReference() );
    
    Repaint();
}
