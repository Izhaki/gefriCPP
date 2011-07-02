#ifndef gxGeometryDefs_h#define gxGeometryDefs_h

typedef int gxCoord;

enum {  gxDefaultCoord = -1 };

enum gxOrientation
{
  gxHORIZONTAL              = 0x0004,
  gxVERTICAL                = 0x0008,

  gxBOTH                    = gxVERTICAL | gxHORIZONTAL
};

#define gxMax(a,b)            (((a) > (b)) ? (a) : (b))
#define gxMin(a,b)            (((a) < (b)) ? (a) : (b))

#endif // gxGeometryDefs_h