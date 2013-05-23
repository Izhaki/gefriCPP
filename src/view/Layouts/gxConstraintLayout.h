#ifndef gxConstraintLayout_h
#define gxConstraintLayout_h

#include "View/Layouts/gxLayout.h"
#include "View/Layouts/Constraints/gxConstraints.h"


/**
 * @brief Base class for the layouts that allow layoutees to have constraints.
 */
class gxConstraintLayout : public gxLayout
{
public:
    gxConstraintLayout();
    gxConstraintLayout( bool aOnMajorAxis );
    
    ~gxConstraintLayout();
    
    /**
     * @brief Sets a constraint for the given view element.
     *
     * @param aViewElement The view element for which the constraints is set
     * @param aConstraint The constraint to set
     * @param aOnMajorAxis Whether or not the constraint is on the major axis
     */
    template < typename ConstraintType >
    void SetConstraint( gxViewElement* aLayoutee,
                        ConstraintType aConstraint,
                        bool           aOnMajorAxis = true )
    {
        // Warn if the layout does not accepts the provided constraint type
        gxAssert( IsSupportedConstraint( gxTypeId( ConstraintType ) ) , "Constraint type is not accepted by this layout" );
        
        mConstraints.Set( aLayoutee, aConstraint, aOnMajorAxis );
        
        // Now invalidate the element
        aLayoutee->Invalidate();
    }
    
protected:
    gxConstraints mConstraints;
    
    virtual void Init();
    
    virtual void Apply();
    
    /**
     * @brief Checks if the constraint type is supported by the layout
     *
     * @param aType The constraint type
     * @return True is the constraint is accepted by the layout
     */
    virtual bool IsSupportedConstraint( const gxConstraintId aId ) = 0;
};

#endif //gxConstraintLayout_h
