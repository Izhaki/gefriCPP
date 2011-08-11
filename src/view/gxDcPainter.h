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

  /**
   * @brief Returns the current (absolute) clip rectangle of the DC
   * @return The dc clip rectangle
   */
  virtual gxRect GetClipRect() const;

  virtual bool NeedsPainting(gxRect const &aRect);

  void DrawRectangle(int x, int y, int w, int h);
  void DrawRectangle(gxRect const &aRect);

  void DrawLine(int x1, int y1, int x2, int y2, bool isHorizontal = true);
  
  void DrawText(gxString &aText, int x, int y);
  void DrawText(gxString  &aText, int x, int y, int aPadX, int aPadY, bool isHorizontal = true);
  void DrawRotatedText(gxString &aText, int x, int y, double aAngle);

  virtual gxSize GetTextSize(gxString &aText);
protected:
  virtual void IntersectClipArea(gxRect const &aRect);
private:
  /// The painting DC
  gxPaintDC *mDc;
  gxRects mDamagedRects;
};

#endif // gxDcPainter_h
