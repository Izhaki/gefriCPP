#ifndef gxBorderLayout_h
#define gxBorderLayout_h

#include "View/Layouts/gxConstraintLayout.h"

class gxBorderLayout : public gxConstraintLayout
{
public:
    gxBorderLayout();
    
    gxBorderLayout( bool aOnMajorAxis );
protected:
    virtual bool IsSupportedConstraint( const gxConstraintId aId );
    
    virtual void DoLayout( gxViewElement* aLayouter );
private:
    // Cache lists of the various elements;
    gxViewElement::List mCenterElements, mMajorElements, mMinorElements;
    
    /**
     * @brief Caches the center, major and minor elements into member lists
     */
    void CacheElements( gxViewElement::Iterator& aLayoutees );

    /**
     * @brief Returns the center element.
     *
     * This method will raise assertion if there isn't only one element with
     * center constraint.
     *
     * The method also makes sure the center element has flex of 1 (or above) on
     * both the major and minor axes.
     *
     * @return The center element if there's only one or NULL otherwise.
     */
    gxViewElement* GetCenterElement();

    /**
     * @brief A helper method to add the items from the second list to the end
     * of the first one.
     */
    void ConcatList( gxViewElement::List& aTo,
                     gxViewElement::List& aFrom );
};


#endif // gxBorderLayout_h
