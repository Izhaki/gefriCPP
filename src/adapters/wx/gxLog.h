#ifndef gxLog_wx_h
#define gxLog_wx_h

#include <wx/log.h>

#if defined(__cplusplus) && defined(__WXDEBUG__)
    #include "core/geometry/gxGeometry.h"
    static void gxLogRect(const wchar_t* msg, gxRect rect)
    {
        wxLogDebug(_T("%s: %i, %i, %i, %i"), msg, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
    }

    #define gxLog( aDebug ) wxLogDebug( aDebug)
#else
    #define gxLogRect( aMsg, aRect )
    #define gxLod( aMsg )
#endif
  
#endif // gxLog_wx_h