#ifndef gxScrollManager_h
#define gxScrollManager_h

#include "core/gxObject.h"
#include "core/gxObserverList.h"
#include "view/gxTransformations.h"
#include "core/geometry/gxGeometry.h"

/**
 * @brief Manages scroll by providing clients advance scroll modification
 * protocol and the ability to notify observers on changes.
 */
class gxScrollManager: public gxObject
{
public:
  gxScrollManager();
  ~gxScrollManager(); 

  void SetScroll(const int aScrollX, const int aScrollY);
  void SetScroll(const bool isVertical, const int aScroll);
  void SetScrollX(const int aScrollX);
  void SetScrollY(const int aScrollY);
  
  /**
   * @brief Will be called when the scroll manager needs to adjust the
   * scrollbars as either the visible part or range has changed.
   * @param aVisibleX The visible part for horizontal scrollbar
   * @param aRangeX The horizontal scroll range
   * @param aVisibleY The visible part for vertical scrollbar
   * @param aRangeY The vertical scroll range
   */
  void AdjustScrollbars(int aVisibleX, int aRangeX, int aVisibleY, int aRangeY);
  
  int GetScrollX() const { return mScroll.X; }
  int GetScrollY() const { return mScroll.Y; }
  gxScroll GetScroll() const { return mScroll; }

  int GetVisibleX() const { return mVisible.X; }
  int GetVisibleY() const { return mVisible.Y; }
  gxSize GetVisible() const { return mVisible; }

  int GetRangeX() const { return mRange.X; }
  int GetRangeY() const { return mRange.Y; }
  gxSize GetRange() const { return mRange; }

  /**
   * @brief Adds an observer to the observers list and notify to the added
   * observer only.
   * @param aCallback The callback to add to the observers list.
   */
  void AddObserverAndNotify(gxCallback *aCallback);

  gxObserverList mObservers;
private:
  /// The current scoll position.
  gxScroll mScroll;

  /// Represent the visible size of the viewable part of the whole.
  gxSize mVisible;
  
  /// Represent the size of the whole area.
  gxSize mRange;
};

/**
 * @brief A notification object to inform observers of scroll position changes.
 */
class gxScrollPositionChangedNotification: public gxNotification
{
public:
  gxScrollPositionChangedNotification(const gxScrollManager* aScrollManager)
    : mScroll(aScrollManager->GetScroll()) { }

  gxScroll mScroll;
};

/**
 * @brief A notification object to inform observers of scroll range changes.
 */
class gxScrollRangeChangedNotification: public gxNotification
{
public:
  gxScrollRangeChangedNotification(const gxScrollManager* aScrollManager)
    : mScroll( aScrollManager->GetScroll() ),
      mVisible( aScrollManager->GetVisible() ),
      mRange( aScrollManager->GetRange() ) { }

  gxScroll mScroll;
  gxSize   mVisible;
  gxSize   mRange;
};

#endif // gxScrollManager_h