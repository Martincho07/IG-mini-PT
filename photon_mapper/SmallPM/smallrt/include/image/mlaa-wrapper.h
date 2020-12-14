#ifndef _MLAA_WRAPPER_H_
#define _MLAA_WRAPPER_H_

#include <cstdarg>
#include <cstdio>
#include <assert.h>
#include <emmintrin.h>

#ifndef _INLINE 
#define _INLINE inline
#define _UNDEF_INLINE
#endif

namespace RTTL {
  // It is an empty implementation for stand-alone app. 
  class AtomicCounter  {
  private:
    int m_counter;

  public:
    AtomicCounter() {
      m_counter = -1;
    }

    _INLINE int inc() {
      return ++m_counter;
    }
  };
};



#define max std::max
#define MLAA_AVOID_EXTERNS
#include "mlaa.hxx"
#undef max

#ifdef _UNDEF_INLINE
#undef _INLINE
#undef _UNDEF_INLINE
#endif

#endif
