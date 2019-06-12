#ifdef __cplusplus
extern "C"
{
#endif

#include "_parser_.h"
#include "_scanner_.h"
#include <aut/read.h>
#include <aut/util/error.h>

autError_t aut_read(const char *path, aut_t **aut)
{
  AUT_CHECK_NULL(path, AUT_EINVAL1);
  AUT_CHECK_NULL(aut,  AUT_EINVAL2);

  FILE *fp;

  if ( (fp = fopen(path, "r")) == AUT_NULL)
    return AUT_EFOPEN;

  yyscan_t scanner;
  autError_t err = AUT_ESUCCESS;

  yylex_init(&scanner);
  yyset_in(fp, scanner);
  yyparse(scanner, aut, &err);
  yylex_destroy(scanner);

  fclose(fp);
  
  return err;
}

#ifdef __cplusplus
}
#endif