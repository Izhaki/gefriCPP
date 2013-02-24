#include "View/Connections/gxConnection.h"

void gxConnection::SetSourceAnchor( gxAnchor* aAnchor )
{
    mSource = aAnchor;
}

void gxConnection::SetDestinationAnchor( gxAnchor* aAnchor )
{
    mDestination = aAnchor;
}
