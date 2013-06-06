#include "View/Layouts/gxBorderLayout.h"
#include "View/Elements/gxViewElement.h"
#include "View/Layouts/Operations/gxLayoutOperations.h"
#include "View/Layouts/gxBoxLayout.h"
#include "gxLog.h"

gxBorderLayout::gxBorderLayout()
{}

gxBorderLayout::gxBorderLayout( bool aOnMajorAxis ):
    gxConstraintLayout ( aOnMajorAxis )
{}

bool gxBorderLayout::IsSupportedConstraint( const gxConstraintId aId )
{
    return aId == gxTypeId( gxSizeConstraint* ) ||
           aId == gxTypeId( gxRegionConstraint* );
}

void gxBorderLayout::DoLayout( gxViewElement* aLayouter )
{
    gxViewElement::VisualIterator iLayoutees( aLayouter->GetChildren() );
 
    // Cache the center, major and minor elements.
    CacheElements( iLayoutees );
    
    // Get the center element ( will also assert there's only one and will flex
    // it.
    gxViewElement* iCenterElement = GetCenterElement();
    
    if ( iCenterElement == NULL )
        return;
    
        
    // We'll be using this box layout to help with the layouting
    gxBoxLayout             iBoxLayout( gxDistribute::Start,
                                        gxStretch::Full,
                                        gxAlign::Start );    
    
    // An iterator of the first axis elements to be laid out.
    gxViewElement::Iterator iMains( mOnMajorAxis ? &mMajorElements : &mMinorElements);
    
    // Do the main axis layout using the layouter bounds
    iBoxLayout.DoLayout( aLayouter->GetInnerBounds(), iMains, mConstraints, mOnMajorAxis );

    
    // An iterator of the second axis elements to be laid out.
    gxViewElement::Iterator iSubs ( mOnMajorAxis ? &mMinorElements : &mMajorElements );
    
    // Do the sub axis layout - it is done with reference to the current
    // bounds of the center region.
    iBoxLayout.DoLayout( iCenterElement->GetBounds(), iSubs, mConstraints, !mOnMajorAxis, false );
}

void gxBorderLayout::CacheElements( gxViewElement::Iterator& aLayoutees )
{
    // Clear the chached center elements
    mCenterElements.clear();
    
    // Temp lists for all regions but center
    gxViewElement::List iNorthElements, iEastElements, iSouthElements, iWestElements;
    
    using namespace gxLayoutRegion;
    gxRegionConstraint* iRegion   = NULL;
    gxViewElement*      iLayoutee = NULL;
    
    // For each layoutee
    for ( aLayoutees.First(); aLayoutees.Current(); aLayoutees.Next() )
    {
        iLayoutee = aLayoutees.Current();
        // Get the region constraint for the layoutee
        mConstraints.Get( iLayoutee, iRegion );
        
        if ( iRegion )
        {
            // Add the layoutee to the corresponding list
            switch ( iRegion->GetValue() )
            {                    
                case Center: mCenterElements.push_back( iLayoutee ); break;
                case North:  iNorthElements.push_back(  iLayoutee ); break;
                case East:   iEastElements.push_back(   iLayoutee ); break;
                case South:  iSouthElements.push_back(  iLayoutee ); break;
                case West:   iWestElements.push_back(   iLayoutee ); break;
            }
        }
    }
    
    // Construct the major elements list
    mMajorElements.clear();
    ConcatList( mMajorElements, iWestElements );
    ConcatList( mMajorElements, mCenterElements );
    ConcatList( mMajorElements, iEastElements );
    
    // Construct the minor elements list
    mMinorElements.clear();
    ConcatList( mMinorElements, iNorthElements );
    ConcatList( mMinorElements, mCenterElements );
    ConcatList( mMinorElements, iSouthElements );    
}

gxViewElement* gxBorderLayout::GetCenterElement()
{
    int iCenterElementsCount = mCenterElements.size();
    
    gxWarnIf( iCenterElementsCount > 1,  "More than one center region defined in layout" );
    gxWarnIf( iCenterElementsCount == 0, "No center region defined in layout" );

    if ( iCenterElementsCount != 1 )
        return NULL;
    
    // Get the center element
    gxViewElement* iCenterElement = mCenterElements.front();
 
    // Center elemens always has flex 1 or higher, so on both major and minor
    // axes set the flex to 1 (unless the user has set it to a higher value)
    if ( mConstraints.GetFlex( iCenterElement, gxMajorAxis ) == 0 )
        mConstraints.Set( iCenterElement, new gxSizeConstraint( gxSizeConstraint::Flex, 1), gxMajorAxis );

    if ( mConstraints.GetFlex( iCenterElement, gxMinorAxis ) == 0 )
        mConstraints.Set( iCenterElement, new gxSizeConstraint( gxSizeConstraint::Flex, 1), gxMinorAxis );

    return iCenterElement;
}

void gxBorderLayout::ConcatList( gxViewElement::List& aTo,
                                 gxViewElement::List& aFrom )
{
    aTo.insert( aTo.end(), aFrom.begin(), aFrom.end() );
}

