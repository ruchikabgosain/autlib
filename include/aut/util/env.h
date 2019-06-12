#ifndef __AUT_UTIL_ENV_H_INCLUDED__
#define __AUT_UTIL_ENV_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/* Check uint32_t, uint64_t, uintptr_t exist */
#ifndef UINT64_MAX
  #error Required type uint64_t is not supported
#endif
#ifndef UINT32_MAX
  #error Required type uint32_t is not supported
#endif
#ifndef UINTPTR_MAX
  #error Required type uintptr_t is not supported
#endif

/* Check if 32 or 64 bit machine */
#if UINTPTR_MAX == 0xffffffff
  #define AUT_64BIT 0
#elif UINTPTR_MAX == 0xffffffffffffffff
  #define AUT_64BIT 1
#else
  #error "Unsupported Architecture"
#endif

/* Compiler Macros. We only support GCC, Clang, MSVC */
#define AUT_CLANG      (defined(__clang__))
#define AUT_MSVC       (defined(_MSC_VER))
#define AUT_GCC        (defined(__GNUC__) && !defined(__clang__))

#define INLINE inline

/* Compiler portable force inline */
#if AUT_CLANG
  #define AUT_FORCEINLINE __attribute__((always_inline)) INLINE
#elif AUT_GCC
  #define AUT_FORCEINLINE __attribute__((always_inline)) INLINE
#elif AUT_MSCVC
  #define AUT_FORCEINLINE __forceinline
#else
  #error Unsupported Compiler
#endif

/* C/C++ portable null macro */
#ifdef __cplusplus
  #define AUT_NULL nullptr
#else
  #include <stdio.h>
  #define AUT_NULL NULL
#endif

/* autlib version */
#define __AUTLIB_MAJOR 0
#define __AUTLIB_MINOR 1

#ifdef __cplusplus
}
#endif

#endif /* __AUT_UTIL_ENV_H_INCLUDED__ */
