#ifndef gxAssert_wx_h
#define gxAssert_wx_h

#if defined(__cplusplus) && defined(__WXDEBUG__)
    #include <wx/debug.h>
    #define gxAssert( aCond, aMsg ) wxASSERT_MSG( aCond,      _T( aMsg ) )
    #define gxWarnIf( aCond, aMsg ) wxASSERT_MSG( !( aCond ), _T( aMsg ) )
    #define gxWarn( aMsg )          wxASSERT_MSG( false,      _T( aMsg ) )
#else
    #define gxAssert( aCond, aMsg )
    #define gxWarnIf( aCond, aMsg )
    #define gxWarn( aMsg )
#endif
  
#endif // gxAssert_wx_h