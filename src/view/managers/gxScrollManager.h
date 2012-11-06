#ifndef gxScrollManager_h
#define gxScrollManager_h

#include "core/gxObject.h"
#include "core/observable/gxObservable.h"
#include "view/gxTransformations.h"
#include "core/geometry/gxGeometry.h"

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

    void SetScroll( gxScroll const &aScroll );
    void SetScroll( const gxPix aScrollX, const gxPix aScrollY );
    void SetScroll( const bool isVertical, const gxPix aScroll );
    void SetScrollX( const gxPix aScrollX );
    void SetScrollY( const gxPix aScrollY );
  
    /**
     * @brief Will be called when the scroll manager needs to adjust the
     * scrollbars as either the visible part or range has changed.
     * @param aVisibleX The visible part for horizontal scrollbar
     * @param aRangeX The horizontal scroll range
     * @param aVisibleY The visible part for vertical scrollbar
     * @param aRangeY The vertical scroll range
     */
    void AdjustScrollbars( gxSize const &aVisible, gxSize const &aRange );
  
    gxPix GetScrollX() const { return mScroll.X; }
    gxPix GetScrollY() const { return mScroll.Y; }
    gxScroll GetScroll() const { return mScroll; }

    gxPix GetVisibleX() const { return mVisible.X; }
    gxPix GetVisibleY() const { return mVisible.Y; }
    gxSize GetVisible() const { return mVisible; }

    gxPix GetRangeX() const { return mRange.X; }
    gxPix GetRangeY() const { return mRange.Y; }
    gxSize GetRange() const { return mRange; }

    /**
     * @brief Adds an observer to the observers list and notify to the added
     * observer only.
     * @param aCallback The callback to add to the observers list.
     */
    void AddObserverAndNotify( gxCallback *aCallback );
private:
    /// The current scoll position.
    gxScroll mScroll;

    /// Represent the visible size of the viewable part of the whole.
    gxSize mVisible;
  
    /// Represent the size of the whole area.
    gxSize mRange;
};

/**
 * @brief An event to inform observers of scroll position changes.
 */
class evScrollPosition: public evEvent
{
public:
    evScrollPosition( const gxScrollManager* aScrollManager )
      : mScroll(aScrollManager->GetScroll()) { }

    gxScroll mScroll;
};

/**
 * @brief An event to inform observers of scroll range changes.
 */
class evScrollRange: public evEvent
{
public:
    evScrollRange( const gxScrollManager* aScrollManager )
    : mScroll( aScrollManager->GetScroll() ),
      mVisible( aScrollManager->GetVisible() ),
      mRange( aScrollManager->GetRange() ) { }

    gxScroll mScroll;
    gxSize   mVisible;
    gxSize   mRange;
};

#endif // gxScrollManager_h