#ifndef __AUT_READ_AUT_H_INCLUDED__
#define __AUT_READ_AUT_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <aut/repr/aut.h>
#include <aut/util/error.h>

autError_t aut_read(const char *path, aut_t **aut);

#ifdef __cplusplus
}
#endif

#endif /* __AUT_READ_AUT_H_INCLUDED__ */