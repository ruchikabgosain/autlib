#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <aut/repr/limits.h>
#include <aut/repr/transition.h>
#include <aut/util/error.h>
#include <aut/util/string.h>
#include <aut/util/env.h>

autError_t
aut_transition_create(autTransition_t **transition,
  autState_t source, autState_t target, const char *action)
{
  AUT_CHECK_NULL           (transition,     AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE    (source,         AUT_EINVAL2);
  AUT_CHECK_LIMIT_STATE    (target,         AUT_EINVAL3);

#ifdef __cplusplus
  *transition = (autTransition_t *) calloc( sizeof(autTransition_t), 1);
#else
  *transition = calloc( sizeof(autTransition_t), 1);
#endif

  AUT_CHECK_NULL(*transition, AUT_EMALLOC);

  (*transition)->source = source;
  (*transition)->target = target;
  (*transition)->action = (char *) action;

  return AUT_ESUCCESS;  
  // return aut_strdup( &(*transition)->action, action) == AUT_EINVAL2?
  //   AUT_EINVAL4 : AUT_ESUCCESS;
}

autError_t
aut_transition_init( autTransition_t *transition,
autState_t source, autState_t target, const char *action)
{
  AUT_CHECK_NULL           (transition,     AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE    (source,         AUT_EINVAL2);
  AUT_CHECK_LIMIT_STATE    (target,         AUT_EINVAL3);
  transition->source = source;
  transition->target = target;
  transition->action = (char*) action;

  return AUT_ESUCCESS;
  // return aut_strdup( &transition->action, action) == AUT_EINVAL2?
  //   AUT_EINVAL4 : AUT_ESUCCESS;
}

autError_t
aut_transition_new(autTransition_t **transition)
{
  AUT_CHECK_NULL(transition, AUT_EINVAL1);
#ifdef __cplusplus
  *transition = (autTransition_t*) calloc( sizeof(autTransition_t), 1);
#else
  *transition = calloc( sizeof( autTransition_t), 1);
#endif
  AUT_CHECK_NULL(transition, AUT_EMALLOC);
  (*transition)->source = 0;
  (*transition)->target = 0;
#ifdef __cplusplus
  (*transition)->action = nullptr;
#else
  (*transition)->action = NULL;
#endif
  return AUT_ESUCCESS;
}

void
aut_transition_destroy( autTransition_t **transition)
{
  if ( transition && *transition) {
    free((*transition)->action);    
    free(*transition);
    *transition = NULL;
  }
}

autError_t
aut_transition_dup( autTransition_t *orig, autTransition_t **copy)
{
  AUT_CHECK_NULL(orig, AUT_EINVAL1);
  AUT_CHECK_NULL(copy, AUT_EINVAL2);
#ifdef __cplusplus
  *copy = (autTransition_t*) malloc( sizeof(autTransition_t));
#else
  *copy = malloc( sizeof(autTransition_t));
#endif
  AUT_CHECK_NULL(*copy, AUT_EMALLOC);
  (*copy)->source = orig->source;
  (*copy)->target = orig->target;
  if ( aut_strdup( &(*copy)->action, orig->action) != AUT_ESUCCESS)
    return AUT_EINVAL1;
  return AUT_ESUCCESS;
}

autError_t
aut_transition_dup2( autTransition_t *orig, autTransition_t *copy)
{
  AUT_CHECK_NULL(orig, AUT_EINVAL1);
  AUT_CHECK_NULL(copy, AUT_EINVAL2);
  copy->source = orig->source;
  copy->target = orig->target;
  // if ( copy->action)
  //   free(copy->action); //PROBLEM IF copy on stack
  char *action_dup;
  if ( aut_strdup(&action_dup, orig->action) != AUT_ESUCCESS)
    return AUT_EINVAL1;
  copy->action = action_dup;
  if ( copy->action == NULL)
    return AUT_EFAILURE;
  return AUT_ESUCCESS;
}

autError_t
aut_transition_set( autTransition_t *transition, 
  autState_t source, autState_t target, const char *action )
{
  AUT_CHECK_NULL            (transition,  AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE     (source,      AUT_EINVAL2);
  AUT_CHECK_LIMIT_STATE     (target,      AUT_EINVAL3);
  autError_t err;
  transition->source = source;
  transition->target = target;
  transition->action = (char *) action;
  // if ( (err = aut_strdup(&transition->action, action)) != AUT_ESUCCESS)
  //   return err;
  return AUT_ESUCCESS;
}

AUT_FORCEINLINE autError_t
aut_transition_set_source( autTransition_t *transition, autState_t source)
{
  AUT_CHECK_NULL        (transition,   AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE (source,       AUT_EINVAL2);
  transition->source = source;
  return AUT_ESUCCESS;
}

AUT_FORCEINLINE autState_t
aut_transition_get_source(autTransition_t *t)
{
  return t->source;
}

AUT_FORCEINLINE autError_t
aut_transition_set_target( autTransition_t *transition, autState_t target)
{
  AUT_CHECK_NULL        (transition,   AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE (target,       AUT_EINVAL2);
  transition->target = target;
  return AUT_ESUCCESS;
}

AUT_FORCEINLINE autState_t
aut_transition_get_target(autTransition_t *t)
{
  return t->target;
}

AUT_FORCEINLINE autError_t
aut_transition_set_action( autTransition_t *transition, const char *action)
{
  AUT_CHECK_NULL        (transition,   AUT_EINVAL1);
  free(transition->action);
  transition->action = (char *) action;
  return AUT_ESUCCESS;
}

AUT_FORCEINLINE autError_t
aut_transition_get_action( autTransition_t *transition, char **action)
{
  AUT_CHECK_NULL        (transition,  AUT_EINVAL1);
  AUT_CHECK_NULL        (action,      AUT_EINVAL2);
  *action = transition->action;
  return AUT_ESUCCESS;
}

autError_t
aut_transition_get_action_dup( autTransition_t *transition, char **action)
{
  AUT_CHECK_NULL (transition, AUT_EINVAL1);
  AUT_CHECK_NULL (action,     AUT_EINVAL2);
  return aut_strdup(action, transition->action);
}

#ifdef __cplusplus
}
#endif
