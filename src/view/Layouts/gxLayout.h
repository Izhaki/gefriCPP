#ifndef gxLayout_h
#define gxLayout_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"

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
    void SetRect( gxViewElement* aViewElement,
                  gxRect         aRect );

    /**
     * @brief Sets the size constraint of the given view element in percetages.
     *
     * If the element is not yet in the list of constraints, it will be added.
     */
    void SetPercent( gxViewElement* aViewElement,
                     short          aPercent );

    /**
     * @brief Sets the size constraint of the given view element in flex units.
     *
     * If the element is not yet in the list of constraints, it will be added.
     */
    void SetFlex( gxViewElement* aViewElement,
                  short          aFlex );
        
    // A helper class to find elements in the data list.
    class ElementFinder
    {
    public:
        ElementFinder( gxViewElement* aElement ) : mElement( aElement ) {}
        bool operator() ( const gxConstraints* aData ) const
        {
            return aData->Element == mElement;
        }
    private:
        gxViewElement* mElement;
    };
    
protected:    
    gxViewElement*      mViewElement;
    gxConstraints::List mData;
    bool                mOnMajorAxis;
    
        
    gxConstraints* GetDataOf( gxViewElement* aElement );

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
    void SortElements();
    
    /**
     * @brief Performs the actual layout. An abstract method that subclasses
     * will implement.
     *
     */
    virtual void DoLayout() = 0;

    /**
     * @brief Applies the calculated bounds to the various view elements.
     * Called when all layout operations are completed.
     */
    void Apply();
};

#endif //gxLayout_h
