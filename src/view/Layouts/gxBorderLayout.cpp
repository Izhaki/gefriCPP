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
    // TODO: ensure there's a center region and only 1.
    gxConstraints* iCenterConstraints = GetCenterConstraints();
    
    if ( !iCenterConstraints )
        return;
    
    gxBoxLayout iBoxLayout( gxDistribute::Start,
                            gxStretch::Full,
                            gxAlign::Start );
    
    
    // A filtered list of constaints.
    gxConstraints::List iFiltered;
    gxRect              iBounds;

    // First do major axis layout
    {
        AddMajorElements( iFiltered );
    
        iBounds = mViewElement->GetInnerBounds();
    
        iBoxLayout.DoLayout( iBounds, iFiltered, mOnMajorAxis );
    }

    // Now clear the filtered list so we can add the minor elements to it
    iFiltered.clear();
    
    // Do the minor axis layout
    {
        AddMinorElements( iFiltered );
    
        iBounds = iCenterConstraints->Bounds;
    
        iBoxLayout.DoLayout( iBounds, iFiltered, !mOnMajorAxis );
    }
    
    // Now offset the minor elements to the previous position of the center
    // region
    {
        // As iBounds still contains the bounds of the center region before
        // Layout, we can use it to find the correct offset
        gxPix iOldCenterPosition = iBounds.GetPosition( mOnMajorAxis );
    
        gxConstraints::Iterator iData;
    
        for ( iData = iFiltered.begin(); iData != iFiltered.end(); ++iData )
        {
            (*iData)->Bounds.Translate( iOldCenterPosition, mOnMajorAxis );
        }
    }
 
}

gxConstraints* gxBorderLayout::GetCenterConstraints()
{
    gxConstraints::Iterator iData;
    gxConstraints*          iResult = NULL;
    short                   iFound  = 0;
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        if ( (*iData)->Region == gxRegion::Center )
        {
            iResult = *iData;
            iFound++;
        }
    }
    
    gxASSERT( iFound > 1,  "More than one center region defined in layout" );
    gxASSERT( iFound == 0, "No center region defined in layout" );
    
    return iResult;
}

void gxBorderLayout::AddMajorElements( gxConstraints::List &aFiltered )
{
    // Add the start regions
    gxRegion iStartRegion = mOnMajorAxis ? gxRegion::West : gxRegion::North;
    AddRegionElements( iStartRegion, aFiltered );
    
    // Now add the center region
    {
        AddRegionElements( gxRegion::Center, aFiltered );
    
        // TODO: move this to Center dealing
        // Get the center constraints
        gxConstraints* iCenter = aFiltered.back();
        
        // The center is always flex 1, unless the user has set it to higher
        if ( iCenter->GetFlex() == 0 )
            iCenter->SetFlex( 1 );
    }
    
    // Add the end regions
    gxRegion iEndRegion = mOnMajorAxis ? gxRegion::East : gxRegion::South;
    AddRegionElements( iEndRegion, aFiltered );
}

void gxBorderLayout::AddMinorElements( gxConstraints::List &aFiltered )
{
    // Add the start regions
    gxRegion iStartRegion = !mOnMajorAxis ? gxRegion::West : gxRegion::North;
    AddRegionElements( iStartRegion, aFiltered );
    
    // Now add the center region
    AddRegionElements( gxRegion::Center, aFiltered );
            
    // Add the end regions
    gxRegion iEndRegion = !mOnMajorAxis ? gxRegion::East : gxRegion::South;
    AddRegionElements( iEndRegion, aFiltered );    
}


void gxBorderLayout::AddRegionElements( gxRegion aRegion,
                                        gxConstraints::List &aFiltered )
{
    gxConstraints::Iterator iData;
    
    for ( iData = mData.begin(); iData != mData.end(); ++iData )
    {
        if ( (*iData)->Region == aRegion )
        {
            aFiltered.push_back( *iData );
        }
    }    
}

void gxBorderLayout::SetRegion( gxViewElement* aViewElement,
                                gxRegion       aRegion )
{
    gxConstraints* iData = GetDataOf( aViewElement );
    
    iData->Region = aRegion;
    
    aViewElement->Invalidate();
    
}
