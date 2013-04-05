#include "View/Layouts/gxBorderLayout.h"
#include "View/Elements/gxViewElement.h"
#include "View/Layouts/Operations/gxLayoutOperations.h"
#include "View/Layouts/gxBoxLayout.h"

gxBorderLayout::gxBorderLayout()
{}

gxBorderLayout::gxBorderLayout( bool aOnMajorAxis )
  : gxLayout ( aOnMajorAxis )
{}

void gxBorderLayout::DoLayout()
{
    // Get the center constrainst. This will also raise assertion if there
    // isn't one, or if there's more than 1.
    gxConstraints* iCenterConstraints = GetCenterConstraints();
    
    if ( !iCenterConstraints )
        return;
    
    gxSizeConstraint* iSizeConstraint = NULL;
    iCenterConstraints->Get( iSizeConstraint, true );
    
    // The center is always flex 1, unless the user has set it higher
    if ( !( iSizeConstraint &&
            iSizeConstraint->IsFlex() &&
            iSizeConstraint->GetValue() > 0 ) )
    {
        iCenterConstraints->Set( gcFlex, 1 );
    }
    
    // A filtered list of constaints.
    gxConstraints::List iFiltered;
    gxRect              iBounds;

    // First do major axis layout
    iBounds = mViewElement->GetInnerBounds();
    LayoutAxis( iFiltered, iBounds, mOnMajorAxis );
    
    // Now clear the filtered list so we can add the minor elements to it
    iFiltered.clear();

    // Do the minor axis layout - it is done with reference to the current
    // bounds of the center region.
    iBounds = iCenterConstraints->Bounds;
    LayoutAxis( iFiltered, iBounds, !mOnMajorAxis );
    
    // Now offset the minor elements to the previous position of the center
    // region /As iBounds still contains the bounds of the center region before
    // Layout, we can use it to find the correct offset
    gxPix iOldCenterPosition = iBounds.GetPosition( mOnMajorAxis );
    
    forEachConstraintOf( iFiltered, iConstraints )
    {
        (*iConstraints)->Bounds.Translate( iOldCenterPosition, mOnMajorAxis );
    }
}

gxConstraints* gxBorderLayout::GetCenterConstraints()
{
    gxConstraints*      iResult           = NULL;
    gxRegionConstraint* iRegionConstraint = NULL;
    short               iFound            = 0;
    
    forEachConstraint( iConstraints )
    {
        (*iConstraints)->Get( iRegionConstraint );
        if ( iRegionConstraint && iRegionConstraint->GetValue() == grCenter )
        {
            iResult = *iConstraints;
            iFound++;
        }
    }
    
    gxAssert( iFound > 1,  "More than one center region defined in layout" );
    gxAssert( iFound == 0, "No center region defined in layout" );
    
    return iResult;
}

void gxBorderLayout::LayoutAxis( gxConstraints::List& aFiltered,
                                 gxRect&              aBounds,
                                 bool                 aOnMajorAxis )
{
    // We'll be using this box layout to help with the layouting
    gxBoxLayout iBoxLayout( gxDistribute::Start,
                            gxStretch::Full,
                            gxAlign::Start );
    
    AddConstraints( aFiltered, aOnMajorAxis );
    iBoxLayout.DoLayout( aBounds, aFiltered, aOnMajorAxis );    
}


void gxBorderLayout::AddConstraints( gxConstraints::List& aFiltered,
                                     bool                 aOnMajorAxis )
{
    // Add the start regions
    gxLayoutRegion iStartRegion = aOnMajorAxis ? grWest : grNorth;
    AddRegionConstraints( iStartRegion, aFiltered );
    
    // Add the center
    AddRegionConstraints( grCenter, aFiltered );
    
    // Add the end regions
    gxLayoutRegion iEndRegion = aOnMajorAxis ? grEast : grSouth;
    AddRegionConstraints( iEndRegion, aFiltered );    
}


void gxBorderLayout::AddRegionConstraints( gxLayoutRegion       aRegion,
                                           gxConstraints::List& aFiltered )
{
    gxRegionConstraint* iRegionConstraint = NULL;
    //TODO: is it iConstraints or iConstraint?
    forEachConstraint( iConstraint )
    {
        (*iConstraint)->Get( iRegionConstraint );

        if ( iRegionConstraint && iRegionConstraint->GetValue() == aRegion )
        {
            aFiltered.push_back( *iConstraint );
        }
    }    
}
