#ifndef gxConstraintKey_h
#define gxConstraintKey_h

struct gxConstraintKey
{
    gxConstraintKey( const gxViewElement*     aLayoutee,
                     const gxConstraint::Type aConstraintType,
                     const bool               aOnMajorAxis = true ) :
        // Note we need the constraint key constructor to take a const layoutee
        // for const correctness, but the actual constaint list may involve
        // pushing the layoutee to another list (like border layout axis list),
        // where itteration would need to be on non-const objects, so we cast
        // the const to non-const in the initialization list.
        mLayoutee( const_cast< gxViewElement* >(aLayoutee) ),
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

#endif //gxConstraintKey_h
