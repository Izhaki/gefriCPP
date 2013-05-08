#ifndef gxConstraintKey_h
#define gxConstraintKey_h

struct gxConstraintKey
{
    gxConstraintKey( const gxViewElement* aLayoutee,
                     gxConstraintId       aConstraintId,
                     const bool           aOnMajorAxis = true ) :
        // Note we need the constraint key constructor to take a const layoutee
        // for const correctness, but the actual constaint list may involve
        // pushing the layoutee to another list (like border layout axis list),
        // where itteration would need to be on non-const objects, so we cast
        // the const to non-const in the initialization list.
        mLayoutee     ( const_cast< gxViewElement* >(aLayoutee) ),
        mConstraintId ( aConstraintId ),
        mOnMajorAxis  ( aOnMajorAxis )
    {}
    
    gxViewElement* mLayoutee;
    gxConstraintId mConstraintId;
    bool           mOnMajorAxis;
        
    bool operator<( const gxConstraintKey& rhs )  const
    {
        return (
                   mLayoutee < rhs.mLayoutee
               ) || (
                   mLayoutee == rhs.mLayoutee &&
                   mConstraintId < rhs.mConstraintId
               ) || (
                   mLayoutee == rhs.mLayoutee &&
                   mConstraintId == rhs.mConstraintId &&
                   mOnMajorAxis < rhs.mOnMajorAxis
               );
    }
};

#endif //gxConstraintKey_h
