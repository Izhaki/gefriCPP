#ifndef gxRuler_h
#define gxRuler_h

#include "View/elements/Visual/gxVisual.h"
#include "core/observer/gxObserver.h"
#include "View/Managers/gxZoomManager.h"
#include "View/Managers/gxScrollManager.h"
#include "View/DivProvider/gxDivProvider.h"

/**
 * @brief A ruler view element.
 * 
 * Rulers work together with {@link gxDivProvider div providers} - who provide
 * the ruler with the divisions to be displayed.
 * 
 * Per the protocol of {@link gxDivProvider div providers}, a ruler can display
 * 3 types of divisions:
 * - Block - which is a full line length next to which a label is displayed.
 * - Key - a division with a line length longer than normal.
 * - Normal - a normal division (shortest line length).
 */
class gxRuler: public gxVisual
{
    gxDeclareObserver( gxRuler )
public:
    /**
     * @brief The ruler's constructor.
     * @param aBounds The bounds of the ruler.
     * @param aDivProvider The {@link gxDivProvider div provider} providing
     * the divisions for this ruler.
     */
    gxRuler( const gxRect  &aBounds,
             gxDivProvider *aDivProvider );

    ~gxRuler();

    /**
     * @brief Sets the {@link gxZoomManager zoom manager} for this ruler.
     * @param aZoomManager The new {@link gxZoomManager zoom manager}.
    */
    void SetZoomManager( gxZoomManager *aZoomManager );

    /**
     * @brief Sets the {@link gxScrollManager scroll manager} for this ruler.
     * @param aScrollManager The new {@link gxScrollManager scroll manager}.
     */
    void SetScrollManager( gxScrollManager *aScrollManager );

    /**
     * @brief A handler method for scroll events from the
     * {@link gxScrollManager scroll manager}.
     * 
     * @param aScroll The new scroll.
     */
    void OnScrollChanged( const gxScroll *aScroll );

    /**
     * @brief A handler method for zoom change notifications from the
     * {@link gxZoomManager zoom manager}.
     * @param aZoom The new zoom.
     */
    void OnZoomChanged( const gxScale *aZoom );
    
    virtual void SetBounds( const gxRect &aNewBounds );

protected:
    void PaintSelf( gxPainter &aPainter );

    /**
     * @brief Calculates the miminum block size in pixel.
     * 
     * This is done based on the largest text to be displayed and the text
     * portion of a block.
     */
    virtual void CalcMinBlockSize();

    gxZoomManager *mZoomManager;
    gxScrollManager *mScrollManager;

    // Whether or not the scroller is horizontal
    bool mIsHorizontal;

    virtual void DoValidate();
protected:
    /**
     * @brief Returns the visible size of the ruler.
     * 
     * The visible size is either the bounds size after scaling or the parent
     * size.
     * @return The visible size in pixels. 
     */
    gxPix GetMyVisibleSize();

    /**
     * @brief Sets the scale this ruler represents.
     * @param aScale The new scale
     */
    virtual void SetScale( const float aScale );

    /// The scale the ruler represents
    float mScale;

    /// The first pixel to be displayed by the ruler.
    gxPix mStartPixel;
  
    /// How much of the cell is dedicated for text. A value of 0.5 means the
    /// block size will be twice as big as the largest text.
    float mBlockTextRatio;
  
    gxDivProvider *mDivProvider;
};

#endif // gxRuler_h