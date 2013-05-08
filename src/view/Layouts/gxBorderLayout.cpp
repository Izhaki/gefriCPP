#include "View/Layouts/gxBorderLayout.h"
#include "View/Elements/gxViewElement.h"
#include "View/Layouts/Operations/gxLayoutOperations.h"
#include "View/Layouts/gxBoxLayout.h"

gxBorderLayout::gxBorderLayout()
{}

gxBorderLayout::gxBorderLayout( bool aOnMajorAxis ):
    gxConstraintLayout ( aOnMajorAxis )
{}

bool gxBorderLayout::IsSupportedConstraint( gxConstraint::Type aType )
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
    gxViewElement::List iLayoutees = aLayouter->GetChildren();
    // Get the center constrainst. This will also raise assertion if there
    // isn't one, or if there's more than one.
    gxViewElement* iCenterElement = GetCenterElement( iLayoutees );
    
    if ( !iCenterElement )
        return;
    
    // Major axis flex check; The center is always flex 1, unless the user has
    // set it higher.
    if ( mConstraints.GetFlex( iCenterElement, gxMajorAxis ) == 0 )
    {
        mConstraints.Set( iCenterElement, gxConstraint::Flex, 1, gxMajorAxis );
    }
    
    // Minor axis flex check; The center is always flex 1, unless the user has
    // set it higher.
    if ( mConstraints.GetFlex( iCenterElement, gxMinorAxis ) == 0 )
    {
        mConstraints.Set( iCenterElement, gxConstraint::Flex, 1, gxMinorAxis );
    }
        
    // A filtered list of constaints.
    gxViewElement::List iFiltered;
    gxRect              iBounds;

    // First do major axis layout
    iBounds = aLayouter->GetInnerBounds();
    LayoutAxis( iFiltered, iBounds, mOnMajorAxis );
    
    // Now clear the filtered list so we can add the minor elements to it
    iFiltered.clear();

    // Do the minor axis layout - it is done with reference to the current
    // bounds of the center region.
    iBounds = iCenterElement->GetBounds();
    LayoutAxis( iFiltered, iBounds, !mOnMajorAxis );
    
    // Now offset the minor elements to the previous position of the center
    // region /As iBounds still contains the bounds of the center region before
    // Layout, we can use it to find the correct offset
    gxPix iOldCenterPosition = iBounds.GetPosition( mOnMajorAxis );

    forEachElement( iFiltered, iLayoutee )
    {
        // Get the previous bounds
        iBounds = (*iLayoutee)->GetBounds();
        
        // Translate them
        iBounds.Translate( iOldCenterPosition, mOnMajorAxis );
        
        // And set
        (*iLayoutee)->SetBounds( iBounds );
    }
}

gxViewElement* gxBorderLayout::GetCenterElement( gxViewElement::List aLayoutees )
{
    gxViewElement* iResult = NULL;
    short          iFound  = 0;
    
    forEachElement( aLayoutees, iLayoutee )
    {
        if ( mConstraints.GetRegion( *iLayoutee ) == gxLayoutRegion::Center )
        {
            iResult = *iLayoutee;
            iFound++;
        }
    }
    
    gxWarnIf( iFound > 1,  "More than one center region defined in layout" );
    gxWarnIf( iFound == 0, "No center region defined in layout" );
    
    return iResult;
}

void gxBorderLayout::LayoutAxis( gxViewElement::List& aFiltered,
                                 gxRect&              aBounds,
                                 bool                 aOnMajorAxis )
{
    // We'll be using this box layout to help with the layouting
    gxBoxLayout iBoxLayout( gxDistribute::Start,
                            gxStretch::Full,
                            gxAlign::Start );
    
    AddAxisElements( aFiltered, aOnMajorAxis );
    
    iBoxLayout.DoLayout( aBounds, aFiltered, mConstraints, aOnMajorAxis );
}


void gxBorderLayout::AddAxisElements( gxViewElement::List& aFiltered,
                                      bool                 aOnMajorAxis )
{
    using namespace gxLayoutRegion;
    
    // Add the start regions
    Type iStartRegion = aOnMajorAxis ? West : North;
    AddRegionElements( iStartRegion, aFiltered );
    
    // Add the center
    AddRegionElements( Center, aFiltered );
    
    // Add the end regions
    Type iEndRegion = aOnMajorAxis ? East : South;
    AddRegionElements( iEndRegion, aFiltered );
}

void gxBorderLayout::AddRegionElements( gxLayoutRegion::Type aRegion,
                                        gxViewElement::List& aFiltered )
{
    gxConstraints::Map iRegionConstraints =  mConstraints.Get( &typeid( gxRegionConstraint ) );
    
    gxViewElement* iLayoutee = NULL;
    
    forEachConstraint( iRegionConstraints, iConstraint )
    {
        iLayoutee = iConstraint->first.mLayoutee;
        if ( mConstraints.GetRegion( iLayoutee ) == aRegion )
        {
            aFiltered.push_back( iLayoutee );
        }
    }
}
