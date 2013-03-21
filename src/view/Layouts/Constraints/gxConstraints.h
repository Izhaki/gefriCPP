#ifndef gxLayoutData_h
#define gxLayoutData_h

// Forward Dec
class gxViewElement;

#include <list>
#include "core/geometry/gxGeometry.h"
#include "View/Layouts/Constraints/gxRatioConstraint.h"
#include "View/Layouts/Constraints/gxRegionConstraint.h"

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
 * linked to a view element and includes extra information to help the layout
 * position and size the element.
 *
 * By means of multiple inheritance, this class interface includes abstract
 * getters and setters of all possible constraints (to save memory, these
 * abstract constraints do not include any member variables). Individual layouts
 * will pick and mix the implemented constraints (with member variables)
 * related to them.
 */
class gxConstraints: virtual public gxAbstractRegionConstraint,
                     virtual public gxAbstractRatioConstraint
{
public:
    gxConstraints( gxViewElement* aElement) : Element( aElement ) { }
    
    typedef std::list< gxConstraints* > List;
    typedef typename List::iterator     Iterator;
    
    // The element this constraint applies to
    gxViewElement* Element;
    
    // The initial position and size of the element
    gxRect         Rect;
        
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
};

#endif // gxLayoutData_h
