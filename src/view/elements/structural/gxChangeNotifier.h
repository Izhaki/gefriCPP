#ifndef gxChangeNotifier_h
#define gxChangeNotifier_h

#include "View/Elements/Structural/gxStructural.h"
#include "core/observer/gxSubject.h"

/**
 * @brief A view element that scrolls all its children.
 *
 * Scrollers are inserted into the hierarchy of of view elements to facilitate
 * scrolling.
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
