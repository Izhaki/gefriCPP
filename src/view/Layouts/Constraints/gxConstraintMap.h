#ifndef gxConstraintMap_h
#define gxConstraintMap_h

#include <map>
#include "View/Layouts/Constraints/gxConstraint.h"

class gxConstraintMap
{
private:
    typedef int MapId;
public:
    virtual ~gxConstraintMap();
    
    gxConstraint* Get( gxConstraint::Type aType, bool aOnMajorAxis );
    gxConstraint* Get( MapId aId );
    
    void Add( gxConstraint::Type  aType,
              gxConstraint::Value aValue,
              bool                aOnMajorAxis = true );
private:
    typedef std::map< MapId, gxConstraint* >  ConstraintMap;
    
    ConstraintMap mConstraintMap;
    
    MapId GetMapId( gxConstraint::Type aType,
                    bool               aOnMajorAxis = true );
    
    void Add( MapId         aId,
              gxConstraint* aConstraint );    
};


#endif //gxConstraintMap_h
