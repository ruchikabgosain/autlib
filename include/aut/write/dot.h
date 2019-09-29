#ifndef __AUT_WRITE_DOT_H_INCLUDED__
#define __AUT_WRITE_DOT_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include <aut/repr/aut.h>
#include <aut/util/error.h>

autError_t aut_write_dot(const char *path, aut_t *aut);

#ifdef __cplusplus
}
#endif

#endif /* __AUT_WRITE_AUT_H_INCLUDED__ */