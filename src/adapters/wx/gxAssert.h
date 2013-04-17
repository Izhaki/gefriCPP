#ifndef gxAssert_wx_h
#define gxAssert_wx_h

// Notice that gxAssert uses an opposite condition to wx.
// gxAssert will generate assertion if the condition is true.
#if defined(__cplusplus) && defined(__WXDEBUG__)
    #include <wx/debug.h>
    #define gxAssert(cond, msg) wxASSERT_MSG(!(cond), _T(msg))
#else
    #define gxAssert(cond, msg)
#endif
  
#endif // gxAssert_wx_h