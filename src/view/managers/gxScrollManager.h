#ifndef gxScrollManager_h
#define gxScrollManager_h
#include "core/gxObserverList.h"
{
public:
  gxScrollManager();
  ~gxScrollManager(); 

  void SetScroll(const int aScrollX, const int aScrollY);
  void SetScroll(const bool isVertical, const int aScroll);
  void SetScrollX(const int aScrollX);
  void SetScrollY(const int aScrollY);
  
  int GetScrollX() const;
  int GetScrollY() const;
  gxObserverList mObservers;
private:
  int mScrollY;