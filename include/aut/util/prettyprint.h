#ifndef __AUT_PARSE_UTIL_PRETTYPRINT_H_INCLUDED__
#define __AUT_PARSE_UTIL_PRETTYPRINT_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <aut/repr.h>

void
aut_pp_descriptor(autDescriptor_t *descriptor);

void
aut_pp_transition(autTransition_t *transition);

void
aut_pp(aut_t *aut);

#ifdef __cplusplus
}
#endif

#endif /* __AUT_PARSE_UTIL_PRETTYPRINT_H_INCLUDED__ */
