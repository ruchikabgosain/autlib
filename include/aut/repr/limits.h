#ifndef __AUT_REPR_LIMITS_H_INCLUDED__
#define __AUT_REPR_LIMITS_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <aut/util/env.h>

#define AUT_STATE_T             uint32_t
#define AUT_STATE_T_SZ          0x04
#define AUT_STATE_T_MAX         0xFFFFFFFF
#define AUT_STATE_RESERVED      0x01
#define AUT_STATE_MIN           0x00
#define AUT_STATE_MAX           0xFFFFFFFE
#define AUT_STATE_NONE          0xFFFFFFFF
#define AUT_STATE_COUNT_T       AUT_STATE_T
#define AUT_STATE_COUNT_T_MAX   AUT_STATE_T_MAX
#define AUT_STATE_COUNT_MIN     0x1
#define AUT_STATE_COUNT_MAX     AUT_STATE_MAX + 1
////////////////////////////////////////////////////
#define AUT_ACTION_T            char *
#define AUT_ACTION_NULL_ALLOWED 0x0
////////////////////////////////////////////////////
#define AUT_TRANS_COUNT_T       size_t
#if AUT_64BIT
  #define AUT_TRANS_COUNT_SZ    0x08
  #define AUT_TRANS_COUNT_T_MAX 0xFFFFFFFFFFFFFFFF
#else
  #define AUT_TRANS_COUNT_SZ    0x04
  #define AUT_TRANS_COUNT_T_MAX 0xFFFFFFFF
#endif
#define AUT_TRANS_COUNT_MIN     0x01
#define AUT_TRANS_COUNT_MAX     AUT_TRANS_COUNT_T_MAX

#ifdef __cplusplus
}
#endif

#endif /* __AUT_REPR_LIMITS_H_INCLUDED__ */
