#include "View/Elements/Structural/Anchors/gxAnchor.h"
#include "View/Connections/gxConnection.h"

gxAnchor::gxAnchor()
: mConnection( NULL )
{
}

gxAnchor::~gxAnchor()
{
}

void gxAnchor::SetConnection( gxConnection* aConnection )
{
    mConnection = aConnection;
}

void gxAnchor::OnAncestorChanged(  bool aDeleted  )
{
    if ( mConnection )
    {
        mConnection->InvalidateConnection();
    }
}
