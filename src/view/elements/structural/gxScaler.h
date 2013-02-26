#ifndef gxScaler_h
#define gxScaler_h

#include "View/Elements/Structural/gxStructural.h"
#include "core/observer/gxObserver.h"
#include "View/Managers/gxZoomManager.h"
#include "View/gxTransformations.h"

/**
 * @brief A view element that scales (zoom) all its children.
 * 
 * Scalers are inserted into the hierarchy of of view elements to facilitate
 * zooming.
 * 
 * This class provides a very simply protocol for setting the scale 
 * (@link gxScaler::SetScale SetScale), but is intendent to be used with
 * @link gxZoomManager gxZoomManager} which provide additional methods for zoom
 * manipulation.
 */
class gxScaler: public gxStructural
{
    gxDeclareObserver( gxScaler )
public:
    gxScaler();
    gxScaler( gxZoomManager *aZoomManager );
    ~gxScaler();

    /**
     * @brief Sets the {@link gxZoomManager zoom manager} for this scaler.
     * @param aZoomManager The new {@link gxZoomManager zoom manager}.
     */
    void SetZoomManager( gxZoomManager *aZoomManager );
  
    /**
     * @brief Sets the scale.
     * @param aScale The new scale
     */
    void SetScale( gxScale const &aScale );

    /**
     * @brief A handler method for zoom change notifications from the
     * {@link gxZoomManager zoom manager}.
     * @param aZoom The new zoom.
     */
    void OnZoomChanged( const gxScale *aZoom );

    /**
     * @brief Paints the view element by scaling the painter then calling
     * {@link gxViewElement::PaintChildren() PaintChildren()}.
     * 
     * @param aPainter The {@link gxPainter painter} to be used for drawing.
     */
    void Paint( gxPainter &aPainter );

protected:
    virtual void Transform( gxRect &aRect );

    gxZoomManager *mZoomManager;
private:
    gxScale mScale;
};

#endif // gxScaler_h