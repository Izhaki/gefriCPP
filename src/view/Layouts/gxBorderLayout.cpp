#include "View/Layouts/gxBorderLayout.h"
#include "View/Elements/gxViewElement.h"
#include "View/Layouts/Layouters/gxDistribute.h"
#include "View/Layouts/Layouters/gxStretch.h"
#include "View/Layouts/Layouters/gxAlign.h"
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
    
    // The center is always flex 1, unless the user has set it higher
    if ( iCenterConstraints->GetFlex() == 0 )
        iCenterConstraints->SetFlex( 1 );
    
    
    // We'll be using this box layout to help with the layouting
    gxBoxLayout iBoxLayout( gxDistribute::Start,
                            gxStretch::Full,
                            gxAlign::Start );
    
    
    // A filtered list of constaints.
    gxConstraints::List iFiltered;
    gxRect              iBounds;

    // First do major axis layout
    {
        AddConstraints( iFiltered, mOnMajorAxis );
    
        iBounds = mViewElement->GetInnerBounds();
    
        iBoxLayout.DoLayout( iBounds, iFiltered, mOnMajorAxis );
    }

    // Now clear the filtered list so we can add the minor elements to it
    iFiltered.clear();
    
    // Do the minor axis layout
    {
        AddConstraints( iFiltered, !mOnMajorAxis );
    
        iBounds = iCenterConstraints->Bounds;
    
        iBoxLayout.DoLayout( iBounds, iFiltered, !mOnMajorAxis );
    }
    
    // Now offset the minor elements to the previous position of the center
    // region
    {
        // As iBounds still contains the bounds of the center region before
        // Layout, we can use it to find the correct offset
        gxPix iOldCenterPosition = iBounds.GetPosition( mOnMajorAxis );
    
        forEachConstraint( iConstraints )
        {
            (*iConstraints)->Bounds.Translate( iOldCenterPosition, mOnMajorAxis );
        }
    }
}

gxConstraints* gxBorderLayout::GetCenterConstraints()
{
    gxConstraints*          iResult = NULL;
    short                   iFound  = 0;
    
    forEachConstraint( iConstraints )
    {
        if ( (*iConstraints)->Region == gxRegion::Center )
        {
            iResult = *iConstraints;
            iFound++;
        }
    }
    
    gxASSERT( iFound > 1,  "More than one center region defined in layout" );
    gxASSERT( iFound == 0, "No center region defined in layout" );
    
    return iResult;
}

void gxBorderLayout::AddConstraints( gxConstraints::List &aFiltered,
                                     bool aOnMajorAxis )
{
    // Add the start regions
    gxRegion iStartRegion = aOnMajorAxis ? gxRegion::West : gxRegion::North;
    AddRegionConstraints( iStartRegion, aFiltered );
    
    // Add the center
    AddRegionConstraints( gxRegion::Center, aFiltered );
    
    // Add the end regions
    gxRegion iEndRegion = aOnMajorAxis ? gxRegion::East : gxRegion::South;
    AddRegionConstraints( iEndRegion, aFiltered );    
}


void gxBorderLayout::AddRegionConstraints( gxRegion aRegion,
                                           gxConstraints::List &aFiltered )
{
    forEachConstraint( iConstraints )
    {
        if ( (*iConstraints)->Region == aRegion )
        {
            aFiltered.push_back( *iConstraints );
        }
    }    
}

void gxBorderLayout::SetRegion( gxViewElement* aViewElement,
                                gxRegion       aRegion )
{
    gxConstraints* iConstraints = GetConstraints( aViewElement );
    
    iConstraints->Region = aRegion;
    
    aViewElement->Invalidate();
    
}
