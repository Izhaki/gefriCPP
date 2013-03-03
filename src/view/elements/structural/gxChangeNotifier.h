#ifndef gxChangeNotifier_h
#define gxChangeNotifier_h

#include "View/Elements/Structural/gxStructural.h"
#include "core/observer/gxSubject.h"

/**
 * @brief A view element thtat fires notification whenever its ancestor has
 * changed.
 *
 * Used before anchors were structural elements, but no longer needed really.
 */
class gxChangeNotifier: public gxStructural,
                        public virtual gxSubject
{
public:
    // Events definition
    gxDefineEvent( evAnsectorChanged, bool )

protected:
    virtual void OnAncestorChanged(  bool aDeleted = false  )
    {
        Fire( evAnsectorChanged, aDeleted );
    }
};

#endif // gxChangeNotifier_h
