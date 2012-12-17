#ifndef gxScrollManager_h
#define gxScrollManager_h

#include "core/gxObject.h"
#include "core/observable/gxObservable.h"
#include "view/gxTransformations.h"
#include "core/geometry/gxGeometry.h"

struct gxScroll
{
    /// The current scoll position.
    gxPosition mPosition;
    
    /// Represent the visible size of the viewable part of the whole.
    gxSize     mVisible;
    
    /// Represent the size of the whole area.
    gxSize     mRange;
};

/**
 * @brief Manages scroll by providing clients advance scroll modification
 * protocol and the ability to notify observers on changes.
 */
class gxScrollManager: public gxObject,
                       public virtual gxObservable
{
public:
    gxScrollManager();
    ~gxScrollManager();
    
    void SetPosition( const bool isVertical, const gxPix aScroll );
public:
    /**
     * @brief Will be called when the scroll manager needs to adjust the
     * scrollbars as either the visible part or range has changed.
     * @param aVisibleX The visible part for horizontal scrollbar
     * @param aRangeX The horizontal scroll range
     * @param aVisibleY The visible part for vertical scrollbar
     * @param aRangeY The vertical scroll range
     */
    void AdjustScrollbars( gxSize const &aVisible, gxSize const &aRange );

    /**
     * @brief Adds an observer to the observers list and notify to the added
     * observer only.
     * @param aCallback The callback to add to the observers list.
     */
    void AddObserverAndNotify( gxCallback *aCallback );
//TODO: should be private
public:
    /// The current scroll position/visible/range.
    gxScroll mScroll;
private:
    void SetPosition( gxPosition const &aScroll );
    void SetPosition( const gxPix aScrollX, const gxPix aScrollY );
    void SetPositionX( const gxPix aScrollX );
    void SetPositionY( const gxPix aScrollY );    
};

class evScroll: public evEvent
{
public:
    evScroll( const gxScrollManager* aScrollManager )
    : mScroll( aScrollManager->mScroll ) { }
    
    gxScroll mScroll;
};

#endif // gxScrollManager_h