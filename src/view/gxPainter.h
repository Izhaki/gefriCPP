#ifndef gxPainter_h
#define gxPainter_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"

#include <stack>

// Forward declaration
class gxPainterState;

typedef std::stack< gxPainterState* > StateStack;

struct gxPainterState
{
public:
  int dx, dy;     // The current translation (offset)
  float sx, sy;  // The current scale (zoom)
  gxRect clipArea;
};

/**
 * @brief Painters are used to draw on various system-dependent canvases or
 * device-contexts.
 *
 * Part of this class is abstract and needs to be implemented by descendants.
 *
 * {@link gxViewElement View elements} use painters to draw themselves.
 *
 * Painters have a state (translation, cliparea, pen, etc.) which can be pushed
 * and popped. This allows an efficient painting of the view elements hierarchy.
 *
 * This class also takes care of any transformations (translation, scaling).
 */
class gxPainter: public gxObject
{
public:
  gxPainter();
  /**
   * @brief Stores the state of the painter in a stack.  
   */
  virtual void PushState();

  /**
   * @brief Pops the state of the painter from stack.  
   */
  virtual void PopState();	

  /**
   * @brief Restores the last state on the stack without popping it.  
   */
  virtual void RestoreState();

  /**
   * @brief Sets the translation (offset) for all drawing operation.
   *
   * As painters often draw view elements that are traversed recursively,
   * painters allow moving the painting origin so view element won't have
   * each to calculate their absolute position.
   * @param dx The amout of pixels to shift paining origin by on the X axis.
   * @param dy The amout of pixels to shift paining origin by on the Y axis.
   */
  virtual void SetTranslate(int dx, int dy) ;

  /**
   * @brief Sets the scale (zoom) for all drawing operations.
   * @param sx The X axis scale.
   * @param sy The Y axis scale.
   */
  virtual void SetScale(float sx, float sy);

  /**
   * @brief Sets the clip rect for drawing while intersecting with existing
   * clip areas.
   *
   * {@link gxViewElement View elements} call this so their children are
   * clipped when painted.
   *
   *  No drawing will occur outside the given area.
   * @param aRect The clip rectangle (which is relative, ie, not transformed)
   */
  virtual void SetClipArea(gxRect const &aRect);

  /**
   * @brief Sets the absolute clip rect for drawing (without intersecting with 
   * any existing clip areas and without any transformations). 
   *
   * Largly used by {@link gxPainter::RestoreState RestoreState}.
   * No drawing will occur outside the given area.
   * @param aRect The absolute coordinates of the clip rectangle.
   */
  virtual void SetAbsoluteClipArea(gxRect const &aRect) = 0;

  /**
   * @brief Checks if the passed rectangle requires repainting.
   *
   * Normally this is done by checking if the rect intersects with the clipped 
   * bounds of the painting area and any damaged areas.
   * @param aRect The rect to check (which is relative, ie, not transformed)
   */
  virtual bool NeedsPainting(gxRect const &aRect) = 0;

  // Drawing methods
  virtual void DrawRectangle(int x, int y, int w, int h) = 0;

protected:
  /**
   * @brief Performs state restoration.  
   */
  virtual void RestoreState(gxPainterState *aState);

  /**
   * @brief Intersects the current clip area with a new rectangle.
   * @param aRect The absolute coordinates of the rect to intersect.
   */
  virtual void IntersectClipArea(gxRect const &aRect) = 0;

  /**
   * @brief Returns the current (absolute) clip rectangle
   * @return The clip rectangle
   */
  virtual gxRect GetClipRect() = 0;

  /**
   * @brief Transforms a {@link gxRect}, taking into account translate, scale
   * , etc.
   * @param aRect The rect to transform.
   */
  virtual void Transform(gxRect &aRect);

  int mTranslateX;
  int mTranslateY;
  
  float mScaleX;
  float mScaleY;

  // These two are for performence optimization.
  bool mNeedsTranslating;
  bool mNeedsScaling;

  StateStack  mStateStack;
};

#endif // gxPainter_h