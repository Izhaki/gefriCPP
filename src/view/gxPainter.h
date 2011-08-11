#ifndef gxPainter_h
#define gxPainter_h

#include "core/gxObject.h"
#include "core/gxString.h"
#include "core/geometry/gxGeometry.h"
#include "view/gxTransformations.h"

#include <stack>


// Forward declaration
class gxPainterState;

typedef std::stack< gxPainterState* > StateStack;

struct gxPainterState
{
public:
  gxRect            clipArea;
  gxTransformations transformations;
  gxTransformFlags  transformEnabledFlags;
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
   * @brief Sets the translation (offset) for all drawing operations.
   *
   * As painters often draw view elements that are traversed recursively,
   * painters allow moving the painting origin so view element won't have
   * each to calculate their absolute position.
   * @param dx The amout of pixels to shift paining origin by on the X axis.
   * @param dy The amout of pixels to shift paining origin by on the Y axis.
   */
  virtual void SetTranslate(gxPix dx, gxPix dy);

  /**
   * @brief Sets the scroll value for all drawing operations.
   * @param sx The scroll value on the X axis.
   * @param sy The scroll value on the Y axis.
   */
  virtual void SetScroll(gxPix sx, gxPix sy);

  /**
   * @brief Sets the scale (zoom) for all drawing operations.
   * @param aScale The new scale
   */
  virtual void SetScale(gxScale const &aScale);

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
   * @brief Returns the current (absolute) clip rectangle
   * @return The clip rectangle
   */
  virtual gxRect GetClipRect() const = 0;

  /**
   * @brief Checks if the passed rectangle requires repainting.
   *
   * Normally this is done by checking if the rect intersects with the clipped 
   * bounds of the painting area and any damaged areas.
   * @param aRect The rect to check (which is relative, ie, not transformed)
   */
  virtual bool NeedsPainting(gxRect const &aRect) = 0;

  /**
   * @brief Sets the transform flags for this painter, allowing clients to
   * disable scale, scroll or translate.
   * 
   * As an example, view elements with absolute coordinates will disable
   * translate.
   * @param aFlags The new set of transform flags.
   */
  virtual void SetTransformFlags(gxTransformFlags aFlags); 

  // Drawing methods
  virtual void DrawRectangle(gxPix x, gxPix y,gxPix w, gxPix h) = 0;
  virtual void DrawRectangle(gxRect const &aRect) = 0;

  virtual void DrawLine(gxPix x1, gxPix y1, gxPix x2, gxPix y2, bool isHorizontal = true) = 0;
  
  virtual void DrawText(gxString &aText, gxPix x, gxPix y) = 0;
  /**
   * @brief This method is particularly to be used by rulers.
   * @param aText The text to be drawns.
   * @param x The X position.
   * @param y The Y Position.
   * @param aPadX Padding to add to the X axis; Not subject to transformations.
   * @param aPadY Padding to add to the Y axis; Not subject to transformations.
   * @param isHorizontal Whether the text to be drawn horizontally or 
   * vertically.
   */
  virtual void DrawText(gxString &aText, gxPix x, gxPix y, gxPix aPadX, gxPix aPadY, bool isHorizontal = true) = 0;
  virtual void DrawRotatedText(gxString &aText, gxPix x, gxPix y, double aAngle) = 0;
  
  /**
   * @brief Returns the size of the given text.
   * @param aText The text whose size we enquire.
   * @return The size of the given text.
   */
  virtual gxSize GetTextSize(gxString &aText) = 0;
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
   * @brief Transforms a {@link gxRect}, taking into account translate, scale
   * , etc.
   * @param aRect The rect to transform.
   */
  virtual void Transform(gxRect &aRect);

  /**
   * @brief Transfroms a {@link gxPoint).
   * @param aPoint The point to transform.
   */
  virtual void Transform(gxPoint &aPoint);

  /**
   * @brief Works out what transformations are actually neede.
   * 
   * This method will update the mNeedsX members.
   */
  void UpdateTransformationsNeeded();

  // These are for performence optimization.
  bool mNeedsTranslating;
  bool mNeedsScaling;
  bool mNeedsScrolling;

  /// The various transformations this painter applies.
  gxTransformations mTrans;

  /// Flags representing which transformation clients wish to be enabled.
  gxTransformFlags mTransformEnabledFlags;

  StateStack  mStateStack;
};

#endif // gxPainter_h