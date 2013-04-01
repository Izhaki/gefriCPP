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
     * @brief Sets the view element for which this layout apply. Typically it
     * is the parent view element, and its children are the ones being laid out.
     */
    void SetViewElement( gxViewElement* aViewElement );
    
    /**
     * @brief Performs the layouting.
     */
    void Layout();
    
    void Invalidate( gxViewElement* aViewElement );
    
    
    // Constraint setters
    
    /**
     * @brief Adds the view element to the constraints list.
     */
    void Add( gxViewElement* aViewElement );

    /**
     * @brief Sets the initial rect constraints used for layouting for the
     * given element.
     *
     * If the element is not yet in the list of constraints, it will be added.
     */
//!    void SetRect( gxViewElement* aViewElement,
//!                  gxRect         aRect );

    /**
     * @brief Sets the size constraint of the given view element in percetages.
     *
     * If the element is not yet in the list of constraints, it will be added.
     */
    // TODO: given we have RatioConstraint, does SetPercent really belong to
    // gxLayout? Would all layouts have this? Or shall we move this to the
    // individual layouts that do? And if we do move it, shouldn't we create
    // an interface?
    void SetPercent( gxViewElement* aViewElement,
                     short          aPercent );

    /**
     * @brief Sets the size constraint of the given view element in flex units.
     *
     * If the element is not yet in the list of constraints, it will be added.
     */
    void SetFlex( gxViewElement* aViewElement,
                  short          aFlex );
    
    void InvalidateElement( gxViewElement* aViewElement );
    
    // For Constraints that don't have a unique value type
    template< typename Type>
    void SetConstraint( gxViewElement* aViewElement,
                        gxString       aConstraintName,
                        Type           aValue)
    {
        gxConstraints* iConstraints = GetConstraints( aViewElement );        
        iConstraints->Set( aConstraintName, aValue );
        InvalidateElement( aViewElement );
    }

    // For Constraints that have a unique value type
    template< typename Type>
    void SetConstraint( gxViewElement* aViewElement,
                       Type            aValue)
    {
        gxConstraints* iConstraints = GetConstraints( aViewElement );
        iConstraints->Set( aValue );
        InvalidateElement( aViewElement );
    }
    
    // A helper class to find elements in the data list.
    class ElementFinder
    {
    public:
        ElementFinder( gxViewElement* aElement ) : mElement( aElement ) {}
        bool operator() ( const gxConstraints* aConstraints ) const
        {
            return aConstraints->mElement == mElement;
        }
    private:
        gxViewElement* mElement;
    };
    
protected:    
    gxViewElement*      mViewElement;
    gxConstraints::List mConstraints;
    bool                mOnMajorAxis;
    
    enum LayoutStatus {
        Valid,
        InProgress,
        Invalid,
    } mLayoutStatus;

    
    virtual gxConstraints* CreateConstraints( gxViewElement* aElement ) = 0;
    
    /**
     * @brief Finds the constraints of the provided view element.
     *
     * @return The constraints of the provided view element, or NULL if none was
     * found.
     */
    gxConstraints* FindConstraints( gxViewElement* aElement );
    
    /**
     * @brief Gets the constraints for the provided view element, or create
     * new constraints if no such exit.
     *
     * @return The constraints of the provided view element.
     */
    gxConstraints* GetConstraints( gxViewElement* aElement );

    /**
     * @brief Performs the actual layout. An abstract method that subclasses
     * will implement.
     */
    virtual void DoLayout() = 0;
    
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
