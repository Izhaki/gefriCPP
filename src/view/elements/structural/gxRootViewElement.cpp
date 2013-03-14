#include "View/Elements/Structural/gxRootViewElement.h"
#include "View/gxLightweightSystem.h"
#include "core/gxAssert.h"

gxRootViewElement::gxRootViewElement( gxLightweightSystem *aLightweightSystem )
    : mLightweightSystem( aLightweightSystem )
{
}

const gxRootViewElement* gxRootViewElement::GetRootViewElement() const
{
    return this;
}

gxLightweightSystem* gxRootViewElement::GetLightweightSystem() const
{
    return mLightweightSystem;
}

gxRect gxRootViewElement::GetBounds() const
{
    // This will return a rectangle at origin (0,0) with the size of the
    // of the control bounds.
    return gxRect( mLightweightSystem->GetControlBounds().GetSize() );

}

void gxRootViewElement::Repaint( gxRect& aBounds,
                                 bool    areRelative )
{
    if ( mLightweightSystem )
        mLightweightSystem->AddDirtyRegion( aBounds );
}

void gxRootViewElement::InvalidateUp( ValidState aValid )
{
    mValid = aValid;

    // Since a single user action might lead to a multitude of objects becoming
    // invalid (like the removal of 3 children), we don't want to validate the
    // whole tree per object that changed. Instead, we queue some validation
    // requests (in some event loop).
    //
    // What this means is that after all modified objects have been doing their
    // marking of invalid objects, the queue validation request will be processed
    // and will lead to Validate() on this class being called.
    mLightweightSystem->QueueValidation();
}

void gxRootViewElement::TransformToAbsolute( gxRect &aRect )
{
    // RootViewElement has no parent. So translation stops here.
}