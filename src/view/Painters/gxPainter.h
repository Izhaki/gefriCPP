#ifndef gxPainter_h
#define gxPainter_h

#include "core/gxObject.h"
#include "core/gxString.h"
#include "core/geometry/gxGeometry.h"
#include "View/gxTransformations.h"

#include <stack>


// Forward declaration
class gxPainterState;

typedef std::stack< gxPainterState* > StateStack;

struct gxPainterState
{
public:
    gxRect            clipArea;
    gxTransformations transformations;
    bool              relative;
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
     * @param aDelta The X/Y pixels offset to shift painting origin by.
     */
    virtual void SetTranslate( gxPoint aDelta );

    /**
     * @brief Sets the scroll value for all drawing operations.
     * @param aScrollPosition The X/Y scroll position
     */
    virtual void SetScroll( gxPoint aScroll );

    /**
     * @brief Sets the scale (zoom) for all drawing operations.
     * @param aScale The new scale
     */
    virtual void SetScale( gxScale const &aScale );

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
    virtual void SetClipArea( gxRect const &aRect );

    /**
     * @brief Sets the absolute clip rect for drawing (without intersecting with
     * any existing clip areas and without any transformations).
     *
     * Largly used by {@link gxPainter::RestoreState RestoreState}.
     * No drawing will occur outside the given area.
     * @param aRect The absolute coordinates of the clip rectangle.
     */
    virtual void SetAbsoluteClipArea( gxRect const &aRect ) = 0;

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
    virtual bool NeedsPainting( gxRect const &aRect ) = 0;

    // Drawing methods
    
    // Rectangles
    void DrawRectangle( gxPix x,
                        gxPix y,
                        gxPix w,
                        gxPix h );
    
    void DrawRectangle( gxRect aRect );

    // Lines
    void DrawLine( gxPix x1,
                   gxPix y1,
                   gxPix x2,
                   gxPix y2 );
    
    void DrawLine( gxPoint aFrom,
                   gxPoint aTo );
    
    void DrawLine( gxRect aRect );
    
    // Text
    void DrawText( gxString &aText,
                   gxPix    aX,
                   gxPix    aY,
                   double   aAngle = 0 );
        
    /**
    * @brief This method is particularly to be used by rulers.
    * @param aText The text to be drawn.
    * @param x The X position.
    * @param y The Y Position.
    * @param aPadX Padding to add to the X axis; Not subject to transformations.
    * @param aPadY Padding to add to the Y axis; Not subject to transformations.
    * @param isHorizontal Whether the text to be drawn horizontally or 
    * vertically.
    */
    void DrawText( gxString &aText,
                   gxPix    aX,
                   gxPix    aY,
                   gxPix    aPadX,
                   gxPix    aPadY,
                   bool     isHorizontal = true );
    
    // Abstract drawing methods.
    // These should be implemented by subclasses.
    virtual void DoDrawRectangle( gxRect const &aRect ) = 0;
    
    virtual void DoDrawLine( gxPoint &aFrom,
                             gxPoint &aTo ) = 0;
    
    virtual void DoDrawText( gxString &aText,
                             gxPix    &aX,
                             gxPix    &aY,
                             double   aAngle = 0 ) = 0;
    
    /**
    * @brief Returns the size of the given text.
    * @param aText The text whose size we enquire.
    * @return The size of the given text.
    */
    virtual gxSize GetTextSize( gxString &aText ) = 0;
    
    /**
     * @brief Returns whether or not the painter is using a relative rendering
     * mode. In relative mode, all parent transformations are applied.
     * @return True if in realtive rendering mode.
     */
    bool IsRelative();
    
    void SetRelative( bool aRelative );
protected:
    /**
    * @brief Performs state restoration.  
    */
    virtual void RestoreState( gxPainterState *aState );

    /**
    * @brief Intersects the current clip area with a new rectangle.
    * @param aRect The absolute coordinates of the rect to intersect.
    */
    virtual void IntersectClipArea( gxRect const &aRect ) = 0;

    /**
    * @brief Transforms a {@link gxRect}, taking into account translate, scale
    * , etc.
    * @param aRect The rect to transform.
    */
    virtual void Transform( gxRect &aRect );

    /**
    * @brief Transfroms a {@link gxPoint).
    * @param aPoint The point to transform.
    */
    virtual void Transform( gxPoint &aPoint );

    bool TranslateNeeded();
    bool ScaleNeeded();
    bool ScrollNeeded();
    
    /// The various transformations this painter applies.
    gxTransformations mTrans;

    StateStack        mStateStack;
    
    /// Whether or not painting is based on relative positioning (absolute
    /// positioning otherwise.
    bool              mRelative;
};

#endif // gxPainter_h