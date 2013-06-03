#include "View/Elements/gxViewElement.h"
#include "View/gxLightweightSystem.h"
#include "core/gxAssert.h"
#include "core/gxLog.h"

gxViewElement::gxViewElement():
    mFlags( Visible | ClipChildren ),
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
    gxWarnIf( iRoot == NULL, "Could not find root element" );

    // Get the lightweight system and return if no such found.
    gxLightweightSystem *iLws = iRoot->GetLightweightSystem();
    gxWarnIf( iLws == NULL, "Could not find the lightweight system" );

    return iLws;
}

void gxViewElement::TransformToAbsolute( gxRect &aRect )
{
    gxViewElement* iParent = GetParent();
    
    gxWarnIf( iParent == NULL, "TransformToAbsolute called, but no parent" );

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

void gxViewElement::SetSize( const gxSize& aNewSize )
{
    gxRect iBounds = GetBounds();
    iBounds.SetSize( aNewSize );
    SetBounds( iBounds );
}

void gxViewElement::SetSize( const gxPix aNewSize, bool aOnMajorAxis )
{
    gxRect iBounds = GetBounds();
    iBounds.SetSize( aNewSize, aOnMajorAxis );
    SetBounds( iBounds );
}

void gxViewElement::SetPosition( const gxPoint& aNewPosition )
{
    gxRect iBounds = GetBounds();
    iBounds.SetPosition( aNewPosition );
    SetBounds( iBounds );
}

void gxViewElement::SetPosition( const gxPix aNewPosition, bool aOnMajorAxis )
{
    gxRect iBounds = GetBounds();
    iBounds.SetPosition( aNewPosition, aOnMajorAxis );
    SetBounds( iBounds );
}

void gxViewElement::GetDescendantsBounds( gxRect &aBounds )
{
    if ( IsChildless() )
        return;
    
    Iterator iChildren( GetChildren() );
    for ( iChildren.First(); iChildren.Current(); iChildren.Next() )
    {
        gxRect iChildBounds;
        iChildren.Current()->GetDescendantsBounds( iChildBounds );
        
        // Consider the caller is at (0, 0); this view element is
        // located at (20, 20); The child bounds return (30, 30); But relative
        // to the caller these are really (50, 50) - not (30, 30). So we have
        // to transform the children bounds.
        if ( iChildren.Current()->IsRelative() )
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

void gxViewElement::InvalidateUp( gxViewElement* aChild,
                                  ValidState     aValid )
{
    // If the new valid state and mine are the same - not point doing anything.
    if ( mValid == aValid )
        return;
    
    // Only in the valid state is invalid (not trace)
    if ( aValid == Invalid )
    {
        // Invalidate the layout.
        InvalidateLayout( aChild );
    }
    
    // If this element is already Invalid, don't change it (particularly
    // not to trace - it is possible to one descendant to bubble up invalid,
    // while a later one will bubble up trace).
    if ( IsntInvalid() )
        mValid = aValid;
    
    
    if ( GetParent() != NULL )
    {
        // If this view element is clipping its children, its size and position
        // wouldn't change as far as ancestors are concerned, if such is the
        // case, then from this element upward we mark all ancestors as Trace.
        // This means ancestors won't be in invalid state (thus they won't
        // require validation), but validation starting from the root element
        // can still travel down the hierarchy.
        if ( IsClippingChildren() )
        {
            aValid = Trace;
        }	
        
        GetParent()->InvalidateUp( this, aValid );
        
    }
}

void gxViewElement::InvalidateDown()
{
    OnAncestorInvalid();
    
    if ( IsChildless() )
        return;
    
    Iterator iChildren( GetChildren() );
    
    // Notify all children that their ancestor has changed.
    for ( iChildren.First(); iChildren.Current(); iChildren.Next() )
    {
        iChildren.Current()->InvalidateDown();
    }
}

void gxViewElement::Validate()
{
    // Keep whether I was invalid before validating the children.
    bool iWasInvalid = IsInvalid();
    
    // Mark me as valid - notice the comment below. If MarkValid() would come
    // after the validation of the descendants, it would override them possibly
    // setting this view element to invalid.
    MarkValid();
    
    
    Iterator iChildren( GetChildren() );
    
    // Ask all children to validate themselves in case they are invalid.
    // Notice that validate on descendants may trigger invalidation and will
    // mark this view element as invalid again.
    for ( iChildren.First(); iChildren.Current(); iChildren.Next() )
    {
        if ( iChildren.Current()->IsntValid() )
            iChildren.Current()->Validate();
    }

    // If I was invalid before validating the descendants, and if I'm not
    // invalid now (because my descendants have marked me as such) - validate
    // me and perform the layout. (If I am invalid now, then the next validation
    // event will lead to my validation.
    if ( iWasInvalid && IsntInvalid() )
    {
        DoValidate();
        Layout();
    }
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
    return mFlags.IsSet( Visible );
}

void gxViewElement::SetVisible( bool const aVisible )
{
    if ( aVisible == IsVisible() )
        return;

    if ( aVisible )
        mFlags.Set( Visible );
    else
        mFlags.Unset( Visible );

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
    return mFlags.IsSet( ClipChildren );
}

void gxViewElement::OnAddChild( gxViewElement *aChild )
{
    aChild->Invalidate();
    aChild->Repaint();
}

void gxViewElement::OnBeforeChildRemoval( gxViewElement *aChild )
{
    // We need revalidation as the deletion of a child might affect layouts etc.
    aChild->Invalidate();
    
    // TODO: We need to move the child from the layout.
    aChild->Erase();
}

void gxViewElement::OnAfterChildRemoval()
{
}

gxLayout* gxViewElement::GetLayout()
{
    // As only gxVisual has layouts, this returns NULL by default.
    // gxVisual will override this.    
    return NULL;
}

void gxViewElement::InvalidateLayout( gxViewElement* aChild )
{
    // As only gxVisual has layouts, this does nothing by default.
    // gxVisual will override this.
}

void gxViewElement::Layout()
{
    // As only gxVisual has layouts, this does nothing by default.
    // gxVisual will override this.
}