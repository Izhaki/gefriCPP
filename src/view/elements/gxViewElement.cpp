#include "View/Elements/gxViewElement.h"
#include "View/gxLightweightSystem.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxViewElement::gxViewElement()
: mFlags( gxViewElement::Visible |
          gxViewElement::ClipChildren ),
  mLayout( NULL ),
  mValid( Invalid )
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

    // TODO: we shouldn't really carry on doing this if the current element
    // is using absolute positioning.
    
    iParent->Transform( aRect );
    iParent->TransformToAbsolute( aRect );
}

void gxViewElement::TransformToLocal( gxRect &aRect )
{
    // A hackish way of doing transform to local:
    //     Start with a rect at (0, 0).
    //     Transform to absolute.
    //     Then substruct for the rect in question.
    gxRect iOffset(0, 0, 0, 0);
    
    TransformToAbsolute( iOffset );
    
    aRect -= iOffset.GetPosition();
}

void gxViewElement::Transform( gxRect &aRect )
{
    aRect += GetBounds().GetPosition();
}

void gxViewElement::Erase()
{
    // Repaint really does what we need - takes the element's bounds and adds
    // dirty region to queue repaint.
    Repaint();
}


void gxViewElement::Repaint( gxRect& aBounds,
                             bool    areRelative )
{
    gxViewElement* iParent = GetParent();
    
    if ( iParent != NULL )
    {
        if ( areRelative )
            iParent->Transform( aBounds );
        
        iParent->Repaint( aBounds, areRelative );
    }
}

void gxViewElement::GetDescendantsBounds( gxRect &aBounds )
{
    if ( IsChildless() )
        return;
    
    forEachChild( aChild )
    {
        gxRect iChildBounds;
        aChild->GetDescendantsBounds( iChildBounds );
        
        // Consider the caller is at (0, 0); this view element is
        // located at (20, 20); The child bounds return (30, 30); But relative
        // to the caller these are really (50, 50) - not (30, 30). So we have
        // to transform the children bounds.
        if ( aChild->IsRelative() )
        {
            Transform( iChildBounds );
            aBounds.Union( iChildBounds );
        } else {
            // TODO: currently we don't account for absolute elements with
            // GetDescendantBounds. Reason is that there isn't really a reason
            // to. Anyhow, if we would, we'd have to translate these to local
            // coordinates, but more importantly, prevent scalers from scaling
            // these, which currently there's no way to do - most likely the
            // solution for this would involve splitting The parameters given
            // To GetDescendantsBounds into relative bounds and absolute bounds.
            //TransformToLocal( iChildBounds );
        }
        
        
//        gxLogRect( _T("Desc Bounds: "), iChildBounds );

        
    }
}

void gxViewElement::Invalidate()
{
    // No point invalidating if I'm already invalid.
    if ( IsInvalid() )
        return;
    
    MarkInvalid();
    
    if ( GetParent() != NULL )
    {
        // Invalidate further up the hierarchy tree.
        GetParent()->InvalidateUp( this );
    }

    InvalidateDown();
}

void gxViewElement::InvalidateUp( gxViewElement* aTrigger,
                                  ValidState     aValid )
{
    // If the new valid state and mine are the same - not point doing anything.
    if ( mValid == aValid )
        return;
    
    // If this element is Invalid, don't change it (to Trace).
    if ( IsntInvalid() )
        mValid = aValid;
    
    
    if ( GetParent() != NULL )
    {
        // If this view element is clipping its children, its size and position
        // wouldn't change as far as ancestors are concerned, if such is the
        // case, invalidate the parent with Trace. This means ancestors won't be
        // in invalid state (thus they won't require validation), but validation
        // starting from the root element can still travel down the hierarchy.
        if ( IsClippingChildren() )
        {
            GetParent()->InvalidateUp( this, Trace );
        } else {
            GetParent()->InvalidateUp( this, Invalid );
        }
        
        
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
    // Ask all children to validate themselves in case they are invalid.
    forEachChild( aChild )
    {
        if ( aChild->IsntValid() )
            aChild->Validate();
    }

    // Only validate if the valid state is Invalid (but not if it's Trace).
    if ( IsInvalid() )
        DoValidate();
    
    // TODO: does layout must come before MarkValid? - Layout will invalidate
    // The children.
    Layout();
    
    MarkValid();
}

void gxViewElement::MarkInvalid()
{
    mValid = Invalid;
}

void gxViewElement::MarkValid()
{
    mValid = Valid;
}

bool gxViewElement::IsValid()
{
    return mValid == Valid;
}

bool gxViewElement::IsntValid()
{
    return mValid != Valid;
}

bool gxViewElement::IsInvalid()
{
    return mValid == Invalid;
}

bool gxViewElement::IsntInvalid()
{
    return mValid != Invalid;
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
    // Newly created children are invalid. So once a child is added, invalidate
    // the parent. If the child is not inserted into a composition which
    // has root view element at the very top of the hierarchy tree, the view
    // element will remain invalid and therefore will not be repainted as
    // Repaint will return.
    aChild->Invalidate();
    aChild->Repaint();
}

void gxViewElement::OnBeforeChildRemoval( gxViewElement *aChild )
{

    // We need revalidation as an addition of a child might affect layouts etc.
    aChild->Invalidate();
    
    // TODO: We need to move the child from the layout.
    aChild->Erase();
}

void gxViewElement::OnAfterChildRemoval()
{
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