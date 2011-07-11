#ifndef gxDcPainter_h
#define gxDcPainter_h

#include "core/gxPaintDC.h"
#include "view/gxPainter.h"

/**
 * @brief A painter that paints on a control DC.
 */
class gxDcPainter: public gxPainter
{
public:
  gxDcPainter(gxPaintDC *aDc, gxRects const &aDamagedRects);

  virtual void SetAbsoluteClipArea(gxRect const &aRect);

  virtual bool NeedsPainting(gxRect const &aRect);

  void DrawRectangle(int x, int y, int w, int h);
protected:
  virtual void IntersectClipArea(gxRect const &aRect);
  /**
   * @brief Returns the current (absolute) clip rectangle of the DC
   * @return The dc clip rectangle
   */
  virtual gxRect GetClipRect();
private:
  /// The painting DC
  gxPaintDC *mDc;
  gxRects mDamagedRects;
};

#endif // gxDcPainter_h