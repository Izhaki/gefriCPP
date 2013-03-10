#include "View/Layouts/gxBoxLayout.h"
#include "View/Elements/gxViewElement.h"

gxBoxLayout::gxBoxLayout()
  : mDistribute ( gxDistribute::Element ),
    mStretch    ( gxStretch::None       ),
    mAlign      ( gxAlign::None         )
{}

gxBoxLayout::gxBoxLayout( bool aOnMajorAxis )
  : gxLayout    ( aOnMajorAxis ),
    mDistribute ( gxDistribute::Element ),
    mStretch    ( gxStretch::None       ),
    mAlign      ( gxAlign::None         )
{}

gxBoxLayout::gxBoxLayout( gxDistribute::Type aDistribute,
                         gxStretch::Type    aStretch,
                         gxAlign::Type      aAlign )
  : mDistribute ( aDistribute  ),
    mStretch    ( aStretch     ),
    mAlign      ( aAlign       )
{}

gxBoxLayout::gxBoxLayout( gxDistribute::Type aDistribute,
                          gxStretch::Type    aStretch,
                          gxAlign::Type      aAlign,
                          bool               aOnMajorAxis )
  : mDistribute ( aDistribute  ),
    mStretch    ( aStretch     ),
    mAlign      ( aAlign       ),
    gxLayout    ( aOnMajorAxis )
{}

void gxBoxLayout::DoLayout()
{
    gxRect iContainerBounds = mViewElement->GetInnerBounds();
    
    DoLayout( iContainerBounds, mData, mOnMajorAxis );
}

void gxBoxLayout::DoLayout( gxRect&             aContainer,
                            gxConstraints::List aConstraints,
                            bool                aOnMajorAxis  )
{

    gxDistribute( mDistribute,
                  aConstraints,
                  aContainer,
                  aOnMajorAxis );
    
    gxStretch( mStretch,
               aConstraints,
               aContainer,
               !aOnMajorAxis );
    
    gxAlign( mAlign,
             aConstraints,
             aContainer,
             !aOnMajorAxis );
}
