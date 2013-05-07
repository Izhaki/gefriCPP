#ifndef gxConstraintLayout_h
#define gxConstraintLayout_h

#include "View/Layouts/gxLayout.h"
#include "View/Layouts/Constraints/gxConstraints.h"

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
     * @param aType The constraint type to set
     * @param aValue The constraint value
     */
    void SetConstraint( gxViewElement*      aLayoutee,
                        gxConstraint::Type  aType,
                        gxConstraint::Value aValue,
                        bool                aOnMajorAxis = true );
    
protected:
    gxConstraints mConstraints;
    
    /**
     * @brief Initializes the contstaineds list.
     *
     */
    virtual void Init();
    
    /**
     * @brief Applies the calculated bounds to the various view elements.
     * Called when all layout operations are completed.
     */
    virtual void Apply();
    
    /**
     * @brief Checks if the constraint type is supported by the layout
     *
     * @param aType The constraint type
     * @return True is the constraint is accepted by the layout
     */
    virtual bool IsSupportedConstraint( gxConstraint::Type aType ) = 0;
};

#endif //gxConstraintLayout_h
