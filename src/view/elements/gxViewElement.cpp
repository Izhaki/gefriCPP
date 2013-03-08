#include "View/Elements/gxViewElement.h"
#include "View/gxLightweightSystem.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxViewElement::gxViewElement()
: mFlags( gxViewElement::Visible |
          gxViewElement::ClipChildren |
          gxViewElement::Relative ),
  mLayout( NULL )
{
}

gxViewElement::~gxViewElement()
{
}

const gxRootViewElement* gxViewElement::GetRootViewElement() const
{
    if ( GetParent() != NULL )
    {
        return GetParent()->GetRootViewElement();
    } else {
        return NULL;
    }
}

gxLightweightSystem* gxViewElement::GetLightweightSystem() const
{
    // Get root view element and return if no such found.
    const gxRootViewElement *iRoot = GetRootViewElement();
    gxASSERT( iRoot == NULL, "Could not find root element" );

    // Get the lightweight system and return if no such found.
    gxLightweightSystem *iLws = iRoot->GetLightweightSystem();
    gxASSERT( iLws == NULL, "Could not find the lightweight system" );

    return iLws;
}

void gxViewElement::TransformToAbsolute( gxRect &aRect )
{
    gxViewElement* iParent = GetParent();
    
    gxASSERT( iParent == NULL, "TransformToAbsolute called, but no parent" );

    iParent->Transform( aRect );
    iParent->TransformToAbsolute( aRect );
}

void gxViewElement::Transform( gxRect &aRect )
{
    aRect.Translate( GetBounds().GetPosition() );
}

void gxViewElement::Erase()
{
    // Repaint really does what we need - takes the element's bounds and adds
    // dirty region to queue repaint.
    Repaint();
}

void gxViewElement::GetDescendantsBounds( gxRect &aBounds )
{
    if ( IsChildless() )
        return;
    
    forEachChild( aChild )
    {
        gxRect iChildBounds;
        aChild->GetDescendantsBounds( iChildBounds );
        
        Transform( iChildBounds );
        
//        gxLogRect( _T("Desc Bounds: "), iChildBounds );

        aBounds.Union( iChildBounds );
    }
}

void gxViewElement::Invalidate()
{
    // No point invalidating if I'm already invalid.
    if ( IsInvalid() )
        return;
    
    InvalidateUp();
    InvalidateDown();
}

void gxViewElement::InvalidateUp()
{
    // No point invalidating if I'm already invalid (this can happed when
    // layouting children - their setbound with invalidate their parents.
    if ( IsInvalid() )
        return;
    
    MarkInvalid();
    
    // View elements parent might be null before all elements are inserted to
    // the hierarchy tree (when they are still created and added to their
    // parents).
    if ( GetParent() != NULL )
    {
        // Invalidate further up the hierarchy tree.
        GetParent()->InvalidateUp();
    }
}

void gxViewElement::InvalidateDown()
{
    OnAncestorInvalid();
    
    if ( IsChildless() )
        return;
    
    // Notify all children that their ancestor has changed.
    forEachChild( aChild )
    {
        aChild->InvalidateDown();
    }
}

void gxViewElement::Validate()
{
    // TODO: does layout must come before BarkValid? - Layout will invalidate
    // The children.
    Layout();
    
    MarkValid();

    if ( IsChildless() )
        return;
    
    // Ask all children to validate themselves in case they are invalid.
    forEachChild( aChild )
    {
        if ( aChild->IsInvalid() )
            aChild->Validate();
    }
}

void gxViewElement::MarkInvalid()
{
    mFlags.Unset( gxViewElement::Valid );    
}

void gxViewElement::MarkValid()
{
    mFlags.Set( gxViewElement::Valid );
}

bool gxViewElement::IsValid()
{
    return mFlags.IsSet( gxViewElement::Valid );
}

bool gxViewElement::IsInvalid()
{
    return mFlags.IsntSet( gxViewElement::Valid );
}

bool gxViewElement::IsVisible()
{
    return mFlags.IsSet( gxViewElement::Visible );
}

void gxViewElement::SetVisible( bool const aVisible )
{
    if ( aVisible == IsVisible() )
        return;

    if ( aVisible )
        mFlags.Set( gxViewElement::Visible );
    else
        mFlags.Unset( gxViewElement::Visible );

    Invalidate();
    Repaint();
}

void gxViewElement::Show()
{
    SetVisible( true );
}

void gxViewElement::Hide()
{
    SetVisible( false );
}

bool gxViewElement::IsClippingChildren()
{
    return mFlags.IsSet( gxViewElement::ClipChildren );
}

bool gxViewElement::IsRelative()
{
    return mFlags.IsSet( gxViewElement::Relative );
}

void gxViewElement::OnAddChild( gxViewElement *aChild )
{
    // Newly created children are invalid. So once a child is added, invalidate
    // the parent. If the child is not inserted into a composition which
    // has root view element at the very top of the hierarchy tree, the view
    // element will remain invalid and therefore will not be repainted as
    // Repaint will return.
    Invalidate();
    aChild->Repaint();
}

void gxViewElement::OnBeforeChildRemoval( gxViewElement *aChild )
{
    aChild->Erase();
}

void gxViewElement::OnAfterChildRemoval()
{
    // We need revalidation as an addition of a child might affect layouts etc.
    Invalidate();
}

void gxViewElement::SetLayout( gxLayout* aLayout )
{
    mLayout = aLayout;
    mLayout->SetViewElement( this );
}

void gxViewElement::Layout()
{
    if ( mLayout )
        mLayout->Layout();
}