#include "View/Connections/gxConnection.h"

void gxConnection::SetSourceAnchor( gxAnchor* aAnchor )
{
    mSource = aAnchor;
    mSource->SetConnection( this );
    InvalidateConnection();
}

void gxConnection::SetDestinationAnchor( gxAnchor* aAnchor )
{
    mDestination = aAnchor;
    mDestination->SetConnection( this );
    InvalidateConnection();
}
