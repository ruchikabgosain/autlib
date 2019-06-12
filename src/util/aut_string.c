#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <string.h>

#include <aut/util/string.h>

autError_t aut_strdup(char **tgt, const char *src)
{
  if ( tgt == NULL)
    return AUT_EINVAL1;
  
  if (src == NULL) {
    *tgt = NULL;
    return AUT_ESUCCESS;
  }

  size_t len = strlen(src);
#ifdef __cplusplus
  char *s = (char *) calloc(len + 1, 1);
#else
  char *s = calloc(len + 1, 1);
#endif
  AUT_CHECK_NULL(s, AUT_EMALLOC);
  s = (char *) memcpy(s, src, len);
  AUT_CHECK_NULL(s, AUT_EMEMCPY);
  *tgt = s;
  return AUT_ESUCCESS;
}

#ifdef __cplusplus
}
#endif