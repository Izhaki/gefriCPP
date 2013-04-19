#ifndef gxLayout_h
#define gxLayout_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"
#include "core/gxString.h"

#include "core/gxLog.h"

// Forward Declarations
class gxViewElement;

#include "View/Layouts/Constraints/gxConstraints.h"

/**
 * @brief A base class for various layouts.
 *
 * Layouts are composed into view elements so to layout their decendents.
 * 
 * Each layout contains a list of constraints, each includes a view elements
 * and some additional data to help the layout perform its task.
 * 
 * Layouts don't modify view elements whilst the various layout operations are
 * being performed. Instead, they work on temp bounds that are part of the
 * constraints data. When all layout operations are completed, the layout then
 * applies these temp bounds to the view elements.
 */
class gxLayout : public gxObject
{
public:
    gxLayout();
    gxLayout( bool aOnMajorAxis );
    
    ~gxLayout();
        
    /**
     * @brief Performs the layouting.
     * @param aLayouter The parent view element whose children are being laid 
     * out.
     */
    void Layout( gxViewElement* aLayouter );

    /**
     * @brief Invalidates the layout if the view element is part of it
     */    
    void Invalidate( gxViewElement* aLayoutee );
    
    /**
     * @brief Adds the view element to the constraints list.
     */
    void Add( gxViewElement* aLayoutee );

    /**
     * @brief Sets a constraint for the given view element.
     *
     * @param aViewElement The view element for which the constraints is set
     * @param aType The constraint type to set
     * @param aValue The constraint value
     */
    void SetConstraint( gxViewElement*      aLayoutee,
                        gxConstraint::Type  aType,
                        gxConstraint::Value aValue );
    
    // A helper class to find elements in the data list.
    // TODO: ElementFinder or LayouteeFinder
    class ElementFinder
    {
    public:
        ElementFinder( gxViewElement* aElement ) : mElement( aElement ) {}
        bool operator() ( const gxConstraints* aConstraints ) const
        {
            return aConstraints->mLayoutee == mElement;
        }
    private:
        gxViewElement* mElement;
    };
    
protected:    
    gxConstraints::List mConstraints;
    bool                mOnMajorAxis;
    
    enum LayoutStatus {
        Valid,
        InProgress,
        Invalid,
    } mLayoutStatus;
    
    /**
     * @brief Finds the constraints of the provided view element.
     *
     * @param aViewElement The view element the constraints of which we're 
     * after.
     * @return The constraints of the provided view element, or NULL if none was
     * found.
     */
    gxConstraints* FindConstraints( gxViewElement* aLayoutee );
    
    /**
     * @brief Gets the constraints for the provided view element, or create
     * new constraints if no such exit.
     *
     * @param aViewElement The view element for which we retrieve the 
     * constraints.
     * @return The constraints of the provided view element.
     */
    gxConstraints* GetConstraints( gxViewElement* aLayoutee );

    /**
     * @brief Checks if the constraint type is supported by the layout
     *
     * @param aType The constraint type
     * @return True is the constraint is accepted by the layout
     */
    virtual bool IsSupportedConstraint( gxConstraint::Type aType ) = 0;
    
    /**
     * @brief Performs the actual layout. An abstract method that subclasses
     * will implement.
     */
    virtual void DoLayout( gxViewElement* aLayouter ) = 0;
    
    /**
     * @brief Initialize the contstaint list, by sorting all view elements to
     * be laid out and applying the initial constraint rect.
     *
     */
    void Init();
    
    /**
     * @brief Sorts the constraint list based on the elements' index.
     *
     */
    void SortConstraints();
    
    /**
     * @brief Applies the calculated bounds to the various view elements.
     * Called when all layout operations are completed.
     */
    void Apply();
};

#endif //gxLayout_h
