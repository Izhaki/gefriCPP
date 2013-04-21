#include "View/Layouts/gxBorderLayout.h"
#include "View/Elements/gxViewElement.h"
#include "View/Layouts/Operations/gxLayoutOperations.h"
#include "View/Layouts/gxBoxLayout.h"

gxBorderLayout::gxBorderLayout()
{}

gxBorderLayout::gxBorderLayout( bool aOnMajorAxis )
  : gxLayout ( aOnMajorAxis )
{}

bool gxBorderLayout::IsSupportedConstraint( gxConstraint::Type  aType )
{
    switch ( aType )
    {
        case gxConstraint::Percent:
        case gxConstraint::Flex:
        case gxConstraint::Pixels:
        case gxConstraint::Region:
        case gxConstraint::Split:
        case gxConstraint::Resizable:
            return true;
            
        default:
            return false;
    }
}

void gxBorderLayout::DoLayout( gxViewElement* aLayouter )
{
    // Get the center constrainst. This will also raise assertion if there
    // isn't one, or if there's more than 1.
    gxConstrained* iCenterConstrained = GetCenterConstrained();
    
    if ( !iCenterConstrained )
        return;
    
    // Major axis flex check; The center is always flex 1, unless the user has
    // set it higher.
    if ( iCenterConstrained->GetFlex( gxMajorAxis ) == 0 )
    {
        iCenterConstrained->Set( gxConstraint::Flex, 1, gxMajorAxis );
    }
    
    // Minor axis flex check; The center is always flex 1, unless the user has
    // set it higher.
    if ( iCenterConstrained->GetFlex( gxMinorAxis ) == 0 )
    {
        iCenterConstrained->Set( gxConstraint::Flex, 1, gxMinorAxis );
    }
        
    // A filtered list of constaints.
    gxConstrained::List iFiltered;
    gxRect              iBounds;

    // First do major axis layout
    iBounds = aLayouter->GetInnerBounds();
    LayoutAxis( iFiltered, iBounds, mOnMajorAxis );
    
    // Now clear the filtered list so we can add the minor elements to it
    iFiltered.clear();

    // Do the minor axis layout - it is done with reference to the current
    // bounds of the center region.
    iBounds = iCenterConstrained->Bounds;
    LayoutAxis( iFiltered, iBounds, !mOnMajorAxis );
    
    // Now offset the minor elements to the previous position of the center
    // region /As iBounds still contains the bounds of the center region before
    // Layout, we can use it to find the correct offset
    gxPix iOldCenterPosition = iBounds.GetPosition( mOnMajorAxis );
    
    forEachConstrainedOf( iFiltered, iConstrained )
    {
        (*iConstrained)->Bounds.Translate( iOldCenterPosition, mOnMajorAxis );
    }
}

gxConstrained* gxBorderLayout::GetCenterConstrained()
{
    gxConstrained*      iResult           = NULL;
    short               iFound            = 0;
    
    forEachConstrained( iConstrained )
    {
        if ( (*iConstrained)->GetRegion() == gxLayoutRegion::Center )
        {
            iResult = *iConstrained;
            iFound++;
        }
    }
    
    gxWarnIf( iFound > 1,  "More than one center region defined in layout" );
    gxWarnIf( iFound == 0, "No center region defined in layout" );
    
    return iResult;
}

void gxBorderLayout::LayoutAxis( gxConstrained::List& aFiltered,
                                 gxRect&              aBounds,
                                 bool                 aOnMajorAxis )
{
    // We'll be using this box layout to help with the layouting
    gxBoxLayout iBoxLayout( gxDistribute::Start,
                            gxStretch::Full,
                            gxAlign::Start );
    
    AddConstraineds( aFiltered, aOnMajorAxis );
    iBoxLayout.DoLayout( aBounds, aFiltered, aOnMajorAxis );    
}


void gxBorderLayout::AddConstraineds( gxConstrained::List& aFiltered,
                                      bool                 aOnMajorAxis )
{
    using namespace gxLayoutRegion;
    // Add the start regions
    Type iStartRegion = aOnMajorAxis ? West : North;
    AddRegionConstraineds( iStartRegion, aFiltered );
    
    // Add the center
    AddRegionConstraineds( Center, aFiltered );
    
    // Add the end regions
    Type iEndRegion = aOnMajorAxis ? East : South;
    AddRegionConstraineds( iEndRegion, aFiltered );
}


void gxBorderLayout::AddRegionConstraineds( gxLayoutRegion::Type aRegion,
                                            gxConstrained::List& aFiltered )
{
    forEachConstrained( iConstrained )
    {
        if ( (*iConstrained)->GetRegion() == aRegion )
        {
            aFiltered.push_back( *iConstrained );
        }
    }    
}
