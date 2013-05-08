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
    
    
    template < typename ConstraintType >
    void Get( const gxViewElement*  aLayoutee,
              ConstraintType&       aConstraint,
              const bool            aOnMajorAxis = true ) const
    {
        gxConstraintKey iKey( aLayoutee, gxTypeId( ConstraintType ), aOnMajorAxis );
        aConstraint = static_cast<ConstraintType>( Get( iKey ) );
    }
    
    Map Get( gxConstraintId aId );
    
    // Helper methods
    
    /**
     * @brief Returns the region of that provided view element.
     * @return The region type.
     */
    gxLayoutRegion::Type GetRegion( gxViewElement* aLayoutee );
    
    /**
     * @brief Returns the flex constraint of the given layoutee.
     * @return The flex value or 0 if none is found
     */
    int GetFlex( gxViewElement* aLayoutee,
                 bool           aOnMajorAxis );
protected:
    Map mConstraints;
    
    void Set( gxConstraintKey& aKey,
              gxConstraint*    aConstraint );
    
    gxConstraint* Get( const gxConstraintKey& aKey ) const;
};


#endif // gxConstraints_h
