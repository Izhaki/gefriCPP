#ifndef gxLine_h
#define gxLine_h

#include "View/Elements/Visual/shapes/gxShape.h"

/**
 * @brief A line.
 *
 * This shape will draw a line from its top-left position and its bottom-right
 * position.
 */
class gxLine: public gxShape
{
public:
    gxLine() {}
    gxLine( const gxPoint &aStart, const gxPoint &aEnd )
      : gxShape( gxRect( aStart, aEnd ) )  {}
    gxLine( const gxRect &aBounds )
      : gxShape( aBounds ) {}
    
protected:
    virtual void PaintShape( gxPainter &aPainter );
};

#endif // gxLine_h
