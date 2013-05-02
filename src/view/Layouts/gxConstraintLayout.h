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

    void SetConstraint( gxViewElement* aLayoutee,
                        gxConstraint*  aConstraint,
                        bool           aOnMajorAxis = true );
    
    /**
     * @brief Adds the view element to the constraineds list.
     */
    //TODO: Delete
    //!
    void Add( gxViewElement* aLayoutee );
    
    
    // A helper class to find elements in the data list.
    // TODO: ElementFinder or LayouteeFinder
    // TODO: protected?
    class ElementFinder
    {
    public:
        ElementFinder( gxViewElement* aElement ) : mElement( aElement ) {}
        bool operator() ( const gxConstrained* aConstrained ) const
        {
            return aConstrained->mLayoutee == mElement;
        }
    private:
        gxViewElement* mElement;
    };
protected:
    gxConstrained::List mConstraineds;
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
     * @brief Finds the constrained of the provided view element.
     *
     * @param aLayoutee The view element the constrained of which we're
     * after.
     * @return The constrained of the provided view element, or NULL if none was
     * found.
     */
    gxConstrained* FindConstrained( gxViewElement* aLayoutee );
    
    /**
     * @brief Gets the constrained for the provided view element, or creates
     * new constrained if no such exits.
     *
     * @param aLayoutee The view element for which we retrieve the
     * constrained.
     * @return The constrained of the provided view element.
     */
    gxConstrained* GetConstrained( gxViewElement* aLayoutee );
    
    /**
     * @brief Sorts the constraineds list based on the elements' index.
     *
     */
    void SortConstraineds();
    
    /**
     * @brief Checks if the constraint type is supported by the layout
     *
     * @param aType The constraint type
     * @return True is the constraint is accepted by the layout
     */
    virtual bool IsSupportedConstraint( gxConstraint::Type aType ) = 0;
};

#endif //gxConstraintLayout_h
