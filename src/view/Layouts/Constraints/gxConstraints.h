#ifndef gxConstraints_h
#define gxConstraints_h

#include "View/Elements/gxViewElement.h"
#include "View/Layouts/Constraints/gxConstraint.h"
#include <map>

struct gxConstraintKey
{
    gxConstraintKey( gxViewElement*     aLayoutee,
                     gxConstraint::Type aConstraintType,
                     bool               aOnMajorAxis ) :
        mLayoutee       ( aLayoutee ),
        mConstraintType ( aConstraintType ),
        mOnMajorAxis    ( aOnMajorAxis )
    {}
    
    gxViewElement*     mLayoutee;
    gxConstraint::Type mConstraintType;
    bool               mOnMajorAxis;
    
    bool operator<( const gxConstraintKey& rhs )  const
    {
        return (
                   mLayoutee < rhs.mLayoutee
               ) || (
                   mLayoutee == rhs.mLayoutee &&
                   mConstraintType < rhs.mConstraintType
               ) || (
                   mLayoutee == rhs.mLayoutee &&
                   mConstraintType == rhs.mConstraintType &&
                   mOnMajorAxis < rhs.mOnMajorAxis
               );
    }
};

class gxConstraints
{
public:    
    ~gxConstraints();
    
    void Set( gxViewElement* aLayoutee,
              gxConstraint*  aConstraint,
              bool           aOnMajorAxis = true );
protected:
    typedef std::map< gxConstraintKey, gxConstraint* > Constraints;
    Constraints mConstraints;
    
    void Set( gxConstraintKey& aKey,
              gxConstraint*    aConstraint );
    
    gxConstraint* Get( gxConstraintKey& aKey );
};


#endif // gxConstraints_h
