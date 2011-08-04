#ifndef gxFlags_h
#define gxFlags_h

#define gx8Flags char
#define gx16Flags short int
#define gx32Flags int

template <class TClass>
class gxFlags
{
public:
  gxFlags()
    : mFlags(0)
    { }
  
  gxFlags(const TClass aFlags)
    : mFlags(aFlags)
    { }

  void Set(const TClass aFlags)
  {
    mFlags |= aFlags;
  }

  void Unset(const TClass aFlags)
  {
    mFlags &= ~aFlags;
  }

  bool IsSet(const TClass aFlags)
  {
    return ( mFlags & aFlags );
  }
  
  bool IsntSet(const TClass aFlags)
  {
    return !(IsSet(aFlags));
  }

private:
  TClass mFlags;
};

#endif // gxFlags_h