#ifndef gxLayoutData_h
#define gxLayoutData_h

// Forward Dec
class gxViewElement;

#include <list>
#include "core/geometry/gxGeometry.h"
#include "View/Layouts/Constraints/gxRatio.h"
#include "View/Layouts/Constraints/gxRegion.h"


// A macro for looping all childrens (used from within the composite itself)
#define forEachConstraint( aConstraints ) \
    for ( gxConstraints::Iterator aConstraints = mConstraints.begin(); \
          aConstraints != mConstraints.end(); \
          ++aConstraints )

// A macro for looping all childrens (used from within the composite itself)
#define forEachConstraintOf( aList, aConstraints ) \
    for ( gxConstraints::Iterator aConstraints = aList.begin(); \
    aConstraints != aList.end(); \
    ++aConstraints )


/**
 * @brief A class representing extra details needed to layout view elements.
 *
 * Constraints are used by {@link gxLayout layouts}. Each constraint is
 * linked to a view element and include extra information to help the layout
 * position and size the element. For example, the initial rect of the element,
 * its (possibly rational) size, its region in a border layout, and so forth.
 */
class gxConstraints
{
public:
    gxConstraints( gxViewElement* aElement) : Element( aElement ) { }
    
    typedef std::list< gxConstraints* > List;
    typedef typename List::iterator     Iterator;
    
    // The element this constraint applies to
    gxViewElement* Element;
    
    // The initial position and size of the element
    gxRect         Rect;
    
    // The size of the element in percent or flex.
    gxRatio        Ratio;
    
    // A helper variable for used when the layout is being calculated.
    // Layouts only change the bounds of the view element when all layout
    // operations have completed. Until then, the layout used this variable to
    // store what will become the bounds of the view element once Apply() is
    // called.
    gxRect         Bounds;
    
    /**
     * @brief Sets the bounds of the element to its initial rect.
     */
    void Reset();
    
    /**
     * @brief Applies the bounds to the view element.
     */
    void Apply();
    
    // Readability methods related to Percent and Flex ratios.
    bool  IsPixels()   { return Ratio.IsEmpty(); }
    bool  IsntPixels() { return Ratio.IsntEmpty(); }
    bool  IsPercent()  { return Ratio.IsntEmpty() && Ratio.IsPercent(); }
    bool  IsFlex()     { return Ratio.IsntEmpty() && Ratio.IsFlex(); }
    gxPix GetFlex()    { return Ratio.GetFlex(); }
    gxPix GetPercent() { return Ratio.GetPercent(); }
    
    void  SetFlex   ( short aFlex    ) { Ratio.SetFlex   ( aFlex );    }
    void  SetPercent( short aPercent ) { Ratio.SetPercent( aPercent ); }
    
    gxRegion GetRegion() { return mRegion; }
    void     SetRegion( gxRegion aRegion ) { mRegion = aRegion; }
    
private:
    // The region of the element in a border layout
    gxRegion       mRegion;

};

#endif // gxLayoutData_h
