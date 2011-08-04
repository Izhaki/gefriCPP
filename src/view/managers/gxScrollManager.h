#ifndef gxScrollManager_h
#define gxScrollManager_h

#include "core/gxObject.h"
#include "core/gxObserverList.h"

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
  
  int GetScrollX() const { return mScrollX; }
  int GetScrollY() const { return mScrollY; }
  int GetVisibleX() const { return mVisibleX; }
  int GetRangeX() const { return mRangeX; }
  int GetVisibleY() const { return mVisibleY; }
  int GetRangeY() const { return mRangeY; }

  /**
   * @brief Adds an observer to the observers list and notify to the added
   * observer only.
   * @param aCallback The callback to add to the observers list.
   */
  void AddObserverAndNotify(gxCallback *aCallback);

  gxObserverList mObservers;
private:
  int mScrollX;
  int mScrollY;
  
  int mVisibleX;
  int mRangeX;
  int mVisibleY;
  int mRangeY;
};

/**
 * @brief A notification object to inform observers of scroll position changes.
 */
class gxScrollPositionChangedNotification: public gxNotification
{
public:
  gxScrollPositionChangedNotification(const gxScrollManager* aScrollManager)
    : scrollX(aScrollManager->GetScrollX()),
      scrollY(aScrollManager->GetScrollY()) { }
  int scrollX;
  int scrollY;
};

/**
 * @brief A notification object to inform observers of scroll range changes.
 */
class gxScrollRangeChangedNotification: public gxNotification
{
public:
  gxScrollRangeChangedNotification(const gxScrollManager* aScrollManager)
    : scrollX(aScrollManager->GetScrollX()), scrollY(aScrollManager->GetScrollY()),
      visibleX(aScrollManager->GetVisibleX()), rangeX(aScrollManager->GetRangeX()),
      visibleY(aScrollManager->GetVisibleY()), rangeY(aScrollManager->GetRangeY()) { }

  int scrollX;
  int scrollY;
  int visibleX;
  int rangeX;
  int visibleY;
  int rangeY;
};

#endif // gxScrollManager_h