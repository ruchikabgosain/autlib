#if __AUTLIB_MAJOR >= 1

#ifndef __AUT_ALGO_H_INCLUDED__
#define __AUT_ALGO_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <aut/repr/aut.h>
#include <aut/util/error.h>

typedef enum {
  AUT_ORDER_NONE            = 0x00,
  AUT_ORDER_SOURCE_ASC      = 0x01,
  AUT_ORDER_SOURCE_DESC     = 0x02,
  AUT_ORDER_TARGET_ASC      = 0x03,
  AUT_ORDER_TARGET_DESC     = 0x04,
  AUT_ORDER_ACTION_ASC      = 0x05,
  AUT_ORDER_ACTION_DESC     = 0x06,
  AUT_ORDER_ACTION_LEN_ASC  = 0x07,
  AUT_ORDER_ACTION_LEN_DESC = 0x08
} autOrder_t;

/**
 * @brief Sort an Aut
 * @param [in] aut a pointer to an Aut object
 * @param [in] an autOrder_t. Passing AUT_ORDER_NONE is effectively a no-op
 * @return An  @ref AutErr indicating the status of the operation
 */
autError_t
aut_sort(Aut *aut, autOrder_t order);

#ifdef __cplusplus
}
#endif

#endif /* __AUT_ALGO_H_INCLUDED__ */

#endif