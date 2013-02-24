#ifndef gxLine_h
#define gxLine_h

#include "View/Elements/Visual/shapes/gxShape.h"

/**
 * @brief A line.
 */
class gxLine: public gxShape
{
public:
    gxLine()
      : mFrom( 400, 0 ),
        mTo  ( 400, 100 ),
        gxShape( gxRect( gxPoint( 400, 0 ), gxPoint( 400, 100 ) ) )
    { }
    
    gxLine( const gxPoint &aStart, const gxPoint &aEnd )
      : mFrom( aStart ),
        mTo  ( aEnd ),
        gxShape( gxRect( aStart, aEnd ) )
    { }
    
    gxLine( const gxRect &aBounds )
      : mFrom( aBounds.GetTopLeft() ),
        mTo  ( aBounds.GetBottomRight() ),
        gxShape( aBounds ) {}
    
    virtual gxRect GetBounds() const;    
    
protected:
    virtual void PaintShape( gxPainter &aPainter );
    
    gxPoint mFrom;
    gxPoint mTo;
};

#endif // gxLine_h
