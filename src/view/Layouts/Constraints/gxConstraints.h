#ifndef gxLayoutData_h
#define gxLayoutData_h

// Forward Dec
class gxViewElement;

#include <list>
#include <map>
#include "core/geometry/gxGeometry.h"
#include "core/gxString.h"

// A macro for looping all childrens (used from within the constraints class)
#define forEachConstraint( aConstraints ) \
    for ( gxConstraints::Iterator aConstraints = mConstraints.begin(); \
          aConstraints != mConstraints.end(); \
          ++aConstraints )

// A macro for looping all childrens (used from outside the constraints class)
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

enum gxConstraintType
{
    gcPixels,
    gcPercent,
    gcFlex,
    gcRegion,
    gcSplit,
    gcCollapse,
    gcLocked,
    gcResizable,
    gcSpan,
    gcAlign,
    
    // Internal Constraints
    // TODO, can't we just store X/Y ? Can the map key be a pair?
    // Or alternatively have one map for major, one for minor?
    gcSizeX,
    gcSizeY,
    gcAlignX,
    gcAlignY,
    gcSpanX,
    gcSpanY
};

#include "View/Layouts/Constraints/gxConstraint.h"
#include "View/Layouts/Constraints/gxSizeConstraint.h"
#include "View/Layouts/Constraints/gxRegionConstraint.h"

class gxConstraints
{
public:
    gxConstraints( gxViewElement* aElement) : mElement( aElement ) { }
    
    // The element this constraint applies to
    gxViewElement* mElement;
            
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
    
public:
    // Getters and Setters
    
    void Set( gxConstraintType aType,
              int              aValue );
    
    // Size getter
    // TODO: merge to template method
    void Get( gxSizeConstraint*& iConstraint, bool aOnMajorAxis = true );
    void Get( gxRegionConstraint*& iConstraint );
public:
    // A couple of readability typedefs
    typedef std::list< gxConstraints* > List;
    typedef typename List::iterator     Iterator;
    
private:
    typedef std::map< gxConstraintType, gxConstraint* >  ConstraintMap;
    
    ConstraintMap mConstraintMap;
    
    gxConstraint* GetConstraint( gxConstraintType aType );
    
    template < class Type >
    void GetConstraint( gxConstraintType aType,
                        Type&            aConstraint )
    {
        aConstraint = static_cast<Type>( GetConstraint( aType ) );
    }
    
    void AddConstraint( gxConstraintType aType,
                        gxConstraint*    aConstraint );
    
    gxConstraintType GetInternalType( gxConstraintType aType,
                                      bool             aOnMajorAxis = true );
    
};

#endif // gxLayoutData_h
