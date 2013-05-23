#ifndef gxConstraints_h
#define gxConstraints_h

#include "View/Elements/gxViewElement.h"
#include "View/Layouts/Constraints/gxConstraint.h"
#include "View/Layouts/Constraints/gxSizeConstraint.h"
#include "View/Layouts/Constraints/gxRegionConstraint.h"
#include "View/Layouts/Constraints/gxConstraintKey.h"
#include <map>

// A macro for iterating all constraints
#define forEachConstraint( aList, aConstraint ) \
    for ( gxConstraints::Iterator aConstraint = aList.begin(); \
          aConstraint != aList.end(); \
          ++aConstraint )

/**
 * @brief A class that maps view elements to their constraints.
 *
 * Constraint are stored in a map where the (constraint) key includes:
 *
 * - The view element that has the constraint.
 * - The constraint id.
 * - Whether the constraint was set for the major or minor axis.
 */
class gxConstraints
{
public:
    typedef std::map< gxConstraintKey, gxConstraint* > Map;
    typedef typename Map::iterator                     Iterator;
    typedef typename Map::const_iterator               ConstIterator;
public:    
    ~gxConstraints();
    
    /**
     * @brief Sets a constraint for the given view element.
     *
     * @param aViewElement The view element for which the constraints is set
     * @param aConstraint The constraint to set
     * @param aOnMajorAxis Whether the constraint is on the major or minor axis.
     */    
    template < typename ConstraintType >
    void Set( gxViewElement* aLayoutee,
              ConstraintType aConstraint,
              bool           aOnMajorAxis = true )
    {
        gxConstraintKey iKey( aLayoutee, gxTypeId( ConstraintType ), aOnMajorAxis );
        Set( iKey, aConstraint );
    }
    
    /**
     * @brief Returns a view element constraint.
     *
     * @param aLayoutee The view element for which the constraints is set.
     * @param aConstraint The constraint type.
     * @param aOnMajorAxis Optional parameter to determine whether the
     *         constraint is on the major or minor axis. Defaults to true.
     */
    template < typename ConstraintType >
    void Get( const gxViewElement*  aLayoutee,
              ConstraintType&       aConstraint,
              const bool            aOnMajorAxis = true ) const
    {
        gxConstraintKey iKey( aLayoutee, gxTypeId( ConstraintType ), aOnMajorAxis );
        aConstraint = static_cast<ConstraintType>( Get( iKey ) );
    }

    /**
     * @brief Returns a filtered map of constraints, all with the same type.
     *
     * @param aId The constraint id.
     */
    Map Get( gxConstraintId aId );
    
    // Helper methods
    
    /**
     * @brief Returns the region of the provided view element.
     *
     * @param aLayoutee The view element.
     * @return The region type.
     */
    gxLayoutRegion::Type GetRegion( gxViewElement* aLayoutee );
    
    /**
     * @brief Returns the flex constraint of the given view element.
     *
     * @param aLayoutee The view element.
     * @param aOnMajorAxis Determines whether the return the constraint of the
     * major or minor axis.
     * @return The flex value or 0 if none is found
     */
    int GetFlex( gxViewElement* aLayoutee,
                 bool           aOnMajorAxis );
protected:
    // The constraints map
    Map mConstraints;
    
    /**
     * @brief Gets a constraint based on the given constraint key.
     *
     * @param aKey The key of the constraint we're after.
     * @param aConstraint The constraint to fill with the mapped constraint.
     */
    void Set( gxConstraintKey& aKey,
              gxConstraint*    aConstraint );

    /**
     * @brief Returns a constraint based on a constraint key.
     */
    gxConstraint* Get( const gxConstraintKey& aKey ) const;
};


#endif // gxConstraints_h
