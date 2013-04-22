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
    
    void Set( gxConstraint::Type aType,
             int                aValue,
             bool               aOnMajorAxis = true );
    
    gxConstraint* CreateConstraint( gxConstraint::Type aType,
                                   int                aValue );
    
    void AddConstraint( MapId         aId,
                       gxConstraint* aConstraint );
private:
    typedef std::map< MapId, gxConstraint* >  ConstraintMap;
    
    ConstraintMap mConstraintMap;
    
    gxConstraint::Type GetInternalType( gxConstraint::Type aType );
    
    MapId TypeToMapId( gxConstraint::Type aType,
                      bool               aOnMajorAxis = true );
};


#endif //gxConstraintMap_h
