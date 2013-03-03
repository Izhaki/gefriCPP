#include "View/Connections/gxConnection.h"

void gxConnection::SetSourceAnchor( gxAnchor* aAnchor )
{
    if ( mSource )
    {
        mSource->UnsetConnection();
    }
    
    mSource = aAnchor;
    mSource->SetConnection( this );
    InvalidateConnection();
}

void gxConnection::SetDestinationAnchor( gxAnchor* aAnchor )
{
    if ( mDestination )
    {
        mDestination->UnsetConnection();
    }
    
    mDestination = aAnchor;
    mDestination->SetConnection( this );
    InvalidateConnection();
}
