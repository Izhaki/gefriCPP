#ifndef gxLayoutData_h
#define gxLayoutData_h

// Forward Dec
class gxViewElement;

#include <list>
#include <map>
#include "core/geometry/gxGeometry.h"
#include "core/gxString.h"

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

// A list of all possible constraint IDs
#define gxFlexConstraintId   1
#define gxRegionConstraintId 2

typedef short ConstriantId;

class gxConstraintBase
{
public:
    virtual ~gxConstraintBase() {}
};

template< class Type >
class gxConstraint : public gxConstraintBase
{
public:
    gxConstraint( Type aValue ) :
        mValue( aValue )
    {}
    
    Type GetValue()
    {
        return mValue;
    }
    
    virtual ~gxConstraint() {}
protected:
    Type mValue;
};

// TODO
#include "View/Layouts/Constraints/gxRatioConstraint.h"
#include "View/Layouts/Constraints/gxRegionConstraint.h"

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
class gxConstraints: virtual public gxAbstractRatioConstraint
{
protected:
    typedef std::map< ConstriantId, gxConstraintBase* >  ConstraintMap;
private:
    ConstraintMap mConstraintMap;
    
    gxConstraintBase* GetConstraint( ConstriantId aId );
public:
    gxConstraints( gxViewElement* aElement) : mElement( aElement ) { }
    
    // Just typedefs to help iteration
    // TODO - not needed?
    typedef std::list< gxConstraints* > List;
    typedef typename List::iterator     Iterator;
    
    // The element this constraint applies to
    gxViewElement* mElement;
    
    // The initial position and size of the element
//!    gxRect         Rect;
        
    // A helper variable for used when the layout is being calculated.
    // Layouts only change the bounds of the view element when all layout
    // operations have completed. Until then, the layout used this variable to
    // store what will become the bounds of the view element once Apply() is
    // called.
    gxRect         Bounds;
    
    void Set( gxString aConstraintName,
              int      aValue );
    
    void Set( gxRegion aRegion );
    gxRegion GetRegion();
    
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
