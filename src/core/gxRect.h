#ifndef gxRect_h
#define gxRect_h

#include <vector>
// forward decleration (for gxRectVector)
class gxRect;

typedef std::vector< gxRect > gxRects;
typedef gxRects::iterator gxRectsIterator;

#include "adapters/wx/gxRect.h"

#endif // gxRect_h