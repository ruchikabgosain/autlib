#ifndef __AUT_REPR_ACTION_H_INCLUDED__
#define __AUT_REPR_ACTION_H_INCLUDED__

#ifdef __cplusplus
extern "C"
{
#endif

#include <aut/repr/limits.h>

#define AUT_ACTION_EMPTY ""

#ifdef __cplusplus
  #define AUT_ACTION_NONINIT nullptr
#else
  #define AUT_ACTION_NONINIT NULL
#endif

/**
 * @brief Represents an action
 */
typedef char *AutAction;

#ifdef __cplusplus
}
#endif

#endif /* __AUT_REPR_ACTION_H_INCLUDED__ */
