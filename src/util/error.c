#ifdef __cplusplus
extern "C" {
#endif

#include <aut/util/env.h>
#include <aut/util/error.h>

char *aut_error_str(autError_t err) {
  switch(err) {
    case AUT_EFAILURE : return "AUT_EFAILURE";
    case AUT_ESUCCESS : return "AUT_ESUCCESS";
    case AUT_EINVAL1  : return "AUT_EINVAL1";
    case AUT_EINVAL2  : return "AUT_EINVAL2";
    case AUT_EINVAL3  : return "AUT_EINVAL3";
    case AUT_EINVAL4  : return "AUT_EINVAL4";
    case AUT_EINVAL5  : return "AUT_EINVAL5";
    case AUT_EINVAL6  : return "AUT_EINVAL6";
    case AUT_EINVAL7  : return "AUT_EINVAL7";
    case AUT_EINVAL8  : return "AUT_EINVAL8";
    case AUT_EINTERNAL: return "AUT_EINTERNAL";
    case AUT_EMALLOC  : return "AUT_EMALLOC";
    case AUT_EMEMCPY  : return "AUT_EMEMCPY";
    case AUT_EFULL    : return "AUT_EFULL";
    case AUT_ESYNTAX  : return "AUT_ESYNTAX";
    case AUT_EFOPEN   : return "AUT_EFOPEN";
    default: return AUT_NULL;
  }
}

#ifdef __cplusplus
}
#endif