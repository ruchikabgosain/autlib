#ifndef __AUT_UTIL_ERROR_H_INCLUDED__
#define __AUT_UTIL_ERROR_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"

typedef enum autError_t
{
  AUT_EFAILURE =  0,
  AUT_ESUCCESS =  1,
  AUT_EINVAL1  = -1,
  AUT_EINVAL2  = -2,
  AUT_EINVAL3  = -3,
  AUT_EINVAL4  = -4,
  AUT_EINVAL5  = -5,
  AUT_EINVAL6  = -6,
  AUT_EINVAL7  = -7,
  AUT_EINVAL8  = -8,
  AUT_EINTERNAL= -9,
  AUT_EMALLOC  = -10,
  AUT_EMEMCPY  = -11,
  AUT_EFULL    = -12,
  AUT_ESYNTAX  = -13,
  AUT_EFOPEN   = -14
} autError_t;

char *aut_error_str(autError_t err);

#define DO_NOTHING ""

#if ((AUT_STATE_MIN > 0x0) && (AUT_STATE_MAX < AUT_STATE_T_MAX))
  #define AUT_CHECK_LIMIT_STATE(init, err) if (init < AUT_STATE_MIN || init > AUT_STATE_MAX) { return (err);}
#elif (AUT_STATE_MIN > 0x0)
  #define AUT_CHECK_LIMIT_STATE(init, err) if (init < AUT_STATE_MIN) { return (err); }
#elif (AUT_STATE_MAX < AUT_STATE_T_MAX)
  #define AUT_CHECK_LIMIT_STATE(init, err) if (init > AUT_STATE_MAX) { return (err); }
#else
  #define AUT_CHECK_LIMIT_STATE(init, err) DO_NOTHING
#endif

#if ((AUT_TRANS_COUNT_MIN > 0x0) && (AUT_TRANS_COUNT_MAX < AUT_TRANS_COUNT_T_MAX))
  #define AUT_CHECK_LIMIT_NUMTRANS(numt, err) \
    if (!numt || numt > AUT_TRANS_COUNT_MAX) { return (err); }
#elif (AUT_TRANS_COUNT_MIN > 0x0)
  #define AUT_CHECK_LIMIT_NUMTRANS(numt, err) \
    if (!numt) { return (err); }
#elif (AUT_TRANS_COUNT_MAX < AUT_TRANS_COUNT_T_MAX)
  #define AUT_CHECK_LIMIT_NUMTRANS(numt, err) \
    if (numt > AUT_TRANS_COUNT_MAX) { return (err); }
#else
  #define AUT_CHECK_LIMIT_NUMTRANS(numt, err) DO_NOTHING
#endif

#if ((AUT_STATE_COUNT_MIN > 0x0) && (AUT_STATE_COUNT_MAX < AUT_STATE_COUNT_T_MAX))
  #define AUT_CHECK_LIMIT_NUMSTATES(nums, err) \
    if ( !nums || nums > AUT_STATE_COUNT_MAX) { return (err); }
#elif (AUT_STATE_COUNT_MIN > 0x0)
  #define AUT_CHECK_LIMIT_NUMSTATES(nums, err) \
    if (!nums) { return (err); }
#elif (AUT_STATE_COUNT_MAX < AUT_STATE_COUNT_T_MAX)
  #define AUT_CHECK_LIMIT_NUMSTATES(numt, err) \
    if (numt > AUT_STATE_COUNT_T_MAX) { return (err); }
#else
  #define AUT_CHECK_LIMIT_NUMSTATES(nums, err) DO_NOTHING
#endif

#define AUT_CHECK_NULL(val, err) {  \
  if (!val) {                       \
    return err;                     \
  }                                 \
}

#ifdef __cplusplus
}
#endif

#endif /* __AUT_UTIL_ERROR_H_INCLUDED__ */