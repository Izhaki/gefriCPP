#include "View/Layouts/gxBoxLayout.h"
#include "View/Elements/gxViewElement.h"

gxBoxLayout::gxBoxLayout()
  : mDistribute ( gxDistribute::Element ),
    mStretch    ( gxStretch::None       ),
    mAlign      ( gxAlign::None         )
{
}

gxBoxLayout::gxBoxLayout( bool aOnMajorAxis )
  : gxLayout    ( aOnMajorAxis ),
    mDistribute ( gxDistribute::Element ),
    mStretch    ( gxStretch::None       ),
    mAlign      ( gxAlign::None         )
{
}

gxBoxLayout::gxBoxLayout( gxDistribute::Type aDistribute,
                          gxStretch::Type    aStretch,
                          gxAlign::Type      aAlign,
                          bool               aOnMajorAxis )
  : mDistribute ( aDistribute  ),
    mStretch    ( aStretch     ),
    mAlign      ( aAlign       ),
    gxLayout    ( aOnMajorAxis )
{
    
}



void gxBoxLayout::DoLayout()
{
    bool onMajorAxis = true;
    
    gxDistribute( mDistribute,
                  mData,
                  mViewElement->GetInnerBounds(),
                  onMajorAxis );
    
    gxStretch( mStretch,
               mData,
               mViewElement->GetInnerBounds(),
               !onMajorAxis );
    
    gxAlign( mAlign,
             mData,
             mViewElement->GetInnerBounds(),
             !onMajorAxis );
}
