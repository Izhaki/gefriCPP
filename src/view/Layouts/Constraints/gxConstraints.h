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
    
    void Set( gxConstraint::Type aType,
              int                aValue );
    
    // Size getter
    // TODO: merge to template method
    void Get( gxSizeConstraint*& iConstraint, bool aOnMajorAxis = true );
    void Get( gxRegionConstraint*& iConstraint );
public:
    // A couple of readability typedefs
    typedef std::list< gxConstraints* > List;
    typedef typename List::iterator     Iterator;
    
private:
    typedef int MapId;
    typedef std::map< MapId, gxConstraint* >  ConstraintMap;
    
    ConstraintMap mConstraintMap;

    gxConstraint::Type GetInternalType( gxConstraint::Type aType,
                                        bool               aOnMajorAxis = true );

    MapId TypeToMapId( gxConstraint::Type aType,
                       bool               aOnMajorAxis = true );
    
    
    gxConstraint* CreateConstraint( gxConstraint::Type aType,
                                    int                aValue );
    
    gxConstraint* GetConstraint( MapId aId );
    
    template < class Type >
    void GetConstraint( MapId aId,
                        Type& aConstraint )
    {
        aConstraint = static_cast<Type>( GetConstraint( aId ) );
    }
    
    void AddConstraint( MapId         aId,
                        gxConstraint* aConstraint );
    
};

#endif // gxLayoutData_h
