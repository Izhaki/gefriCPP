#ifndef gxStructural_h
#define gxStructural_h

#include "View/Elements/gxViewElement.h"

/**
 * @brief A view element that has no visual representation, but is inserted
 * to the view hierarchy in order to perform certain operations. 
 *
 * Structural view elements have no defined bounds and generally take the bounds
 * of their parent. They behave as transparent elements.
 *
 * Examples of structural view elements include layers, scalers, and
 * {@link gxRootViewElement root view element}.
 */
class gxStructural: public gxViewElement
{
public:
    gxStructural();
    ~gxStructural();

    /**
     * @brief Paints the view element by calling
     * {@link gxViewElement::PaintChildren() PaintChildren()}.
     *
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    void Paint( gxPainter &aPainter );

    /**
     * @brief Returns the bounds of this view element.
     *
     *  The bounds are always at origin (0,0) and has the size of the parent.
     *  This way any structural element is covering the whole of its parent.
     */
    virtual gxRect GetBounds() const;
protected:
    /**
     * @brief Paints the children of this view element.
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    virtual void PaintChildren( gxPainter &aPainter );

    // This method overrides the gxViewElement implementation to do nothing.
    // The base class translate the bounds origins to those of the current
    // object, but as structural elements always start at (0,0) no point in
    // doing that.
    virtual void Transform( gxRect           &aRect,
                            gxTransFlags &aTransFlags ) {};
};

#endif // gxStructural_h