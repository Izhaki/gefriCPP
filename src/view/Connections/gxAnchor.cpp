#include "view/Connections/gxAnchor.h"
#include "View/Connections/gxConnection.h"

gxAnchor::gxAnchor( gxVisual* aVisual )
: mVisual( aVisual ),
  mConnection( NULL )
{
    mNotifier = new gxChangeNotifier();
    mNotifier->gxSubscribe( evAnsectorChanged, OnVisualChanged );
    
    aVisual->AddChild( mNotifier );
}

gxAnchor::~gxAnchor()
{
    // TODO: if the visual is deleted, shouldn't the anchor too?
    if ( mVisual )
        mVisual->RemoveChild( mNotifier );
    
    mNotifier->gxUnsubscribe( evAnsectorChanged );
    delete mNotifier;
}

void gxAnchor::SetConnection( gxConnection* aConnection )
{
    mConnection = aConnection;
}

void gxAnchor::OnVisualChanged( bool aDeleted )
{
    if ( aDeleted )
    {
        // Remove the notifier from the visual
        mVisual->RemoveChild( mNotifier );
        mVisual = NULL;
    } else {
        if ( mConnection )
        {
            mConnection->InvalidateConnection();
        }
    }
}