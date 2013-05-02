#ifndef gxLayout_h
#define gxLayout_h

#include "core/gxObject.h"
#include "core/geometry/gxGeometry.h"
#include "core/gxString.h"

// Forward Declarations
class gxViewElement;

#include "View/Layouts/Constraints/gxConstrained.h"

/**
 * @brief A base class for various layouts.
 *
 * Layouts are composed into view elements so to layout their decendents.
 * 
 * Each layout contains a list of constraineds, each includes a view elements
 * and some additional data to help the layout perform its task.
 * 
 * Layouts don't modify view elements whilst the various layout operations are
 * being performed. Instead, they work on temp bounds that are part of the
 * constraineds data. When all layout operations are completed, the layout then
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
    
protected:
    bool                mOnMajorAxis;
    
    enum LayoutStatus {
        Valid,
        InProgress,
        Invalid,
    } mLayoutStatus;
        
    /**
     * @brief Performs the actual layout. An abstract method that subclasses
     * will implement.
     */
    virtual void DoLayout( gxViewElement* aLayouter ) = 0;
    
    // TODO: what's up with these?
    virtual void Init();
    virtual void Apply();
};

#endif //gxLayout_h
