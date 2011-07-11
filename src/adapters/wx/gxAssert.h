#ifndef gxAssert_wx_h
#define gxAssert_wx_h

// Notice that gxASSERT uses an opposite condition to wx.
// gxASSERT will generate assertion if the condition is true.
#if defined(__cplusplus) && defined(__WXDEBUG__)
  #define gxASSERT(cond, msg) wxASSERT_MSG(!(cond), _T(msg))
#else
  #define gxASSERT(cond, msg)
#endif
  
#endif // gxAssert_wx_h