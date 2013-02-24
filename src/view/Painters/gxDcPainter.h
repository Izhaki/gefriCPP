#ifndef gxDcPainter_h
#define gxDcPainter_h

#include "core/gxPaintDC.h"
#include "View/Painters/gxPainter.h"

/**
 * @brief A painter that paints on a control DC.
 */
class gxDcPainter: public gxPainter
{
public:
    gxDcPainter( gxPaintDC *aDc,
                 gxRects const &aDamagedRects );

    virtual void SetAbsoluteClipArea( gxRect const &aRect );

    /**
     * @brief Returns the current (absolute) clip rectangle of the DC
     * @return The dc clip rectangle
     */
    virtual gxRect GetClipRect() const;

    virtual bool NeedsPainting( gxRect const &aRect );

    void DrawRectangle( gxPix aX,
                        gxPix aY,
                        gxPix aW,
                        gxPix aH );
    
    void DrawRectangle( gxRect const &aRect );

    void DrawLine( gxPix x1,
                   gxPix y1,
                   gxPix x2,
                   gxPix y2,
                   bool  isHorizontal = true );
  
    void DrawText( gxString &aText,
                   gxPix    aX,
                   gxPix    aY);
    
    void DrawText( gxString &aText,
                   gxPix    aX,
                   gxPix    aY,
                   gxPix    aPadX,
                   gxPix    aPadY,
                   bool     isHorizontal = true );
    
    void DrawRotatedText( gxString &aText,
                          gxPix  aX,
                          gxPix  aY,
                          double aAngle);

    virtual gxSize GetTextSize( gxString &aText );
protected:
    virtual void IntersectClipArea( gxRect const &aRect );
private:
    /// The painting DC
    gxPaintDC *mDc;
    gxRects   mDamagedRects;
};

#endif // gxDcPainter_h
