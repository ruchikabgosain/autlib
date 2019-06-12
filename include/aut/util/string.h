#ifndef __AUT_UTIL_STRING_H_INCLUDED__
#define __AUT_UTIL_STRING_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif


#include <aut/repr/limits.h>
#include <aut/util/error.h>

#define TO_STR(x) #x

autError_t aut_strdup(char **tgt, const char *src);

#ifdef __cplusplus
}
#endif

#endif /* __AUT_UTIL_STRING_H_INCLUDED__ */