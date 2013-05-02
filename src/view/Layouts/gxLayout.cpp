#include "View/Layouts/gxLayout.h"
#include "View/Elements/gxViewElement.h"

gxLayout::gxLayout()
  : mOnMajorAxis ( true ),
    mLayoutStatus( Invalid )
{
}

gxLayout::gxLayout( bool aOnMajorAxis )
: mOnMajorAxis ( aOnMajorAxis ),
  mLayoutStatus( Invalid )
{
}

gxLayout::~gxLayout()
{
}

void gxLayout::Layout( gxViewElement* aLayouter )
{
    gxWarnIf( aLayouter == NULL, "No layouter provided" );
    
    // No point doing a layout if the layout is already valid.
    if ( mLayoutStatus == Valid )
        return;
    
    // Mark the layout as in progress
    mLayoutStatus = InProgress;
    
    Init();
    
    DoLayout( aLayouter );
    
    Apply();
    
    // Mark the layout as valid
    mLayoutStatus = Valid;
    
}

void gxLayout::Invalidate( gxViewElement* aLayoutee )
{
    // If the layout is in progress or already marked as invalid, do nothing.
    if ( mLayoutStatus != Valid )
        return;
    
//!    bool iElementPartOfLayout = FindConstrained( aLayoutee );
    
    // If the view element is part of my layout, mark me as invalid
//!    if ( iElementPartOfLayout )
    mLayoutStatus = Invalid;
}

void gxLayout::Init()
{
}

void gxLayout::Apply()
{
}

