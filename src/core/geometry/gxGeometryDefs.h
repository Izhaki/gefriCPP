#ifndef gxGeometryDefs_h
#define gxGeometryDefs_h

#include <math.h>

// gxPix defines the data type of coordinates.
// Currently the view layer is using integer coordinates.
// But we might want it to change in the future to float coordinates.
typedef int gxPix;

enum {  gxDefaultCoord = -1 };

enum gxOrientation
{
  gxHORIZONTAL              = 0x0004,
  gxVERTICAL                = 0x0008,

  gxBOTH                    = gxVERTICAL | gxHORIZONTAL
};

#define gxMax(a,b) (((a) > (b)) ? (a) : (b))
#define gxMin(a,b) (((a) < (b)) ? (a) : (b))

#define gxFloor(a) (int)floor(a)
#define gxCeil(a) (int)ceil(a)

#endif // gxGeometryDefs_h