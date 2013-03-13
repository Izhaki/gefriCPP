#ifndef gxVisual_h
#define gxVisual_h

#include "View/Elements/gxViewElement.h"

/**
 * @brief A view element that has visual representation and defined bounds,
 * like shapes.
 */
class gxVisual: public gxViewElement
{
public:
    gxVisual();
    gxVisual( const gxRect &aBounds );
    ~gxVisual();

    /**
     * @brief Paints the view element, by calling {@link
     * gxViewElement::PaintSelf() PaintSelf()}, {@link
     * gxViewElement::PaintChildren() PaintChildren()} and then
     * {@link gxViewElement::PaintBorder() PaintBorder()}
     *
     * As part of the default painting mechanism, visual view elements clip the
     * painting of their children to their bounds.
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    void Paint( gxPainter &aPainter );
    
    /**
     * @brief Repaints the view element making its bounds dirty.
     */
    virtual void Repaint();

    /**
     * @brief Returns the bounds of this view element.
     */
    gxRect GetBounds() const;

    /**
     * @brief Sets new bounds to this view element.
     * @param aNewBounds The new bounds
     */
    virtual void SetBounds( const gxRect &aNewBounds );
  
    // TODO: Docs
    virtual void GetDescendantsBounds( gxRect &aBounds );
protected:
    /**
     * @brief Paints graphics related to this view element.
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    virtual void PaintSelf( gxPainter &aPainter ) {}
    /**
     * @brief Paints the children of this view element.
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    virtual void PaintChildren( gxPainter &aPainter );

    /**
     * @brief Paints the border of this view element.
     *
     * As children might overpaint any borders painted by {@link
     * gxViewElement::PaintSelf() PaintSelf()}, this method
     * is called after {@link gxViewElement::PaintChildren() PaintChildren()}
     * to paint any borders of the view element.
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    virtual void PaintBorder( gxPainter &aPainter ) {};

    /**
     * @brief Translates (moves) the element.
     * @param aDelta The X/Y delta of pixels.
     */
    void Translate( gxPoint aDelta );

    /// The bounds of this view element
    gxRect mBounds;
};

#endif // gxVisual_h