#ifndef gxZoomManager_h
#define gxZoomManager_h

#include "core/gxObject.h"
#include "core/observer/gxSubject.h"
#include "View/gxTransformations.h"

/**
 * @brief Manages zoom by providing clients advance zoom modification protocol
 * and the ability to notify observers on changes.
 */
class gxZoomManager: public gxObject,
                     public virtual gxSubject
{
public:
    gxZoomManager();
    ~gxZoomManager();

    // Events definition
    gxDefineBoundEvent( evZoomChanged,
                        const gxScale*,
                        &mZoom )
    
    /**
     * @brief Returns the current zoom.
     * @return The current zoom.
     */
    gxScale GetZoom() const;
  
    /**
     * @brief Sets the Zoom to the given values.
     * @param aZoomV The vertical zoom factor.
     * @param aZoomH The horizontal zoom factor.
     */
    void SetZoom( const float aZoomH,
                  const float aZoomV );

    /**
     * @brief A convinience method for setting both the vertical and horizontal
     * zoom to the same value.
     * @param aZoom Both the vertical and horizontal zoom factor.
     */
    void SetZoom( const float aZoom );

    /**
     * @brief Multiply the current zoom by the given multiplier.
     * @param aMultiplierV The vertical zoom multiplier.
     * @param aMultiplierH The horizontal zoom multiplier.
     */
    void MultiplyZoom( const float aMultiplierH,
                       const float aMultiplierV );

    /**
     * @brief A convinience method for multiplying both the horizontal and
     * vertical  zoom by the same multiplier.
     * @param aMultiplier Both the vertical and horizontal multiplier.
     */
    void MultiplyZoom( const float aMultiplier );
  
private:
    gxScale mZoom;
};


#endif // gxZoomManager_h