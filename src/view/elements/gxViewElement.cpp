#include "view/elements/gxViewElement.h"
#include "view/gxLightweightSystem.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxViewElement::gxViewElement()
: mFlags( gxViewElement::Visible | gxViewElement::ClipChildren )
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

void gxViewElement::TransformToAbsolute( gxRect           &aRect,
                                         gxTransFlags &aTransFlags )
{
    gxViewElement* iParent = GetParent();
    
    gxASSERT( iParent == NULL, "TransformToAbsolute called, but no parent" );

    iParent->Transform( aRect, aTransFlags );
    iParent->TransformToAbsolute( aRect, aTransFlags );
}

void gxViewElement::Transform( gxRect           &aRect,
                               gxTransFlags &aTransFlags )
{
    if ( aTransFlags.IsSet( gxTransFlags::Translate ) )
        aRect.Translate( GetBounds().GetPosition() );
}

void gxViewElement::Erase()
{
    // Repaint really does what we need - takes the element's bounds and adds
    // dirty region to queue repaint.
    Repaint();
}

void gxViewElement::Repaint()
{
    // No point repainting the figure if it is invalid.
    if ( !IsValid() )
        return;
    
    gxRect iBounds = GetBounds();
    Repaint( iBounds );
}

void gxViewElement::Repaint( gxRect &aBounds )
{
    // No point repainting the figure if it is invalid.
    if ( !IsValid() )
        return;

    // Translate the bounds to absolute coordinates.
    TransformToAbsolute( aBounds, mTransformFlags );

    // instruct the lightweight system to mark the bounds of this view element
    // as ones need repainting
    GetLightweightSystem()->AddDirtyRegion( aBounds );
}

void gxViewElement::GetDescendantsBounds( gxRect &aBounds )
{
    for ( EACHCHILD )
    {
        gxRect iChildBounds;
        CHILD->GetDescendantsBounds( iChildBounds );

        // When getting the children bounds we want all transformations to be
        // done but scroll.
        gxTransFlags iFlags( gxTransFlags::All &
                                ~gxTransFlags::Scroll );

        Transform( iChildBounds, iFlags );

        aBounds.Union( iChildBounds );
    }
}

void gxViewElement::Invalidate()
{
    mFlags.Unset( gxViewElement::Valid );

    // View elements parent might be null before all elements are inserted to
    // the hierarchy tree (when they are still created and added to their
    // parents).
    if ( GetParent() != NULL )
    {
        // Invalidate further up the hierarchy tree.
        GetParent()->Invalidate();
    }
}

void gxViewElement::Validate()
{
    if ( IsValid() )
        return;
  
    // Set myself as Valid
    mFlags.Set( gxViewElement::Valid );

    // Ask all children to validate themselves.
    for ( EACHCHILD )
    {
        CHILD->Validate();
    }    
}

bool gxViewElement::IsValid()
{
    return mFlags.IsSet( gxViewElement::Valid );
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

void gxViewElement::OnAddChild( gxViewElement *aChild )
{
    // Newly created children are invalid. So once a child is added try to
    // revalidate it. If the child is not inserted into a composition which
    // has root view element at the very top of the hierarchy tree, the view
    // element will remain invalid and therefore will not be repainted as
    // Repaint will return.
    aChild->Invalidate();
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