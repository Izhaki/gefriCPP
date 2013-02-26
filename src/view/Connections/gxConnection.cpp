#include "View/Connections/gxConnection.h"

void gxConnection::SetSourceAnchor( gxAnchor* aAnchor )
{
    // TODO: this should invalidate the figure
    mSource = aAnchor;
}

void gxConnection::SetDestinationAnchor( gxAnchor* aAnchor )
{
    // TODO: this should invalidate the figure    
    mDestination = aAnchor;
}
