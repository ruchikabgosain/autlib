#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#include <aut/repr/descriptor.h>
#include <aut/repr/limits.h>
#include <aut/util/env.h>

/** Implements aut/repr/descriptor::aut_descriptor_create */
autError_t
aut_descriptor_create(autDescriptor_t **descriptor, autState_t initstate,
  size_t num_transitions, size_t num_states)
{
  AUT_CHECK_NULL           (descriptor,      AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE    (initstate,       AUT_EINVAL2);
  AUT_CHECK_LIMIT_NUMTRANS (num_transitions, AUT_EINVAL3);
  AUT_CHECK_LIMIT_NUMSTATES(num_states,      AUT_EINVAL4);

#ifdef __cplusplus
  *descriptor = (autDescriptor_t*) calloc( 1, sizeof(autDescriptor_t));
#else
  *descriptor = calloc( 1, sizeof(autDescriptor_t));
#endif

  AUT_CHECK_NULL(*descriptor, AUT_EMALLOC);

  (*descriptor)->initstate        = initstate;
  (*descriptor)->num_transitions  = num_transitions;
  (*descriptor)->num_states       = num_states;

  return AUT_ESUCCESS;
}

autError_t
aut_descriptor_init( autDescriptor_t *descriptor, autState_t initstate,
  size_t num_transitions, size_t num_states)
{
  AUT_CHECK_NULL           (descriptor,      AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE(initstate,       AUT_EINVAL2);
  AUT_CHECK_LIMIT_NUMTRANS (num_transitions, AUT_EINVAL3);
  AUT_CHECK_LIMIT_NUMSTATES(num_states,      AUT_EINVAL4);

  descriptor->initstate       = initstate;
  descriptor->num_transitions = num_transitions;
  descriptor->num_states      = num_states;

  return AUT_ESUCCESS;
}

/** Implements aut/repr/descriptor::aut_descriptor_new */
autError_t
aut_descriptor_new(autDescriptor_t **descriptor)
{
  AUT_CHECK_NULL(descriptor, AUT_EINVAL1);

#ifdef __cplusplus
  *descriptor = (autDescriptor_t*) calloc( 1, sizeof(autDescriptor_t));
#else
  *descriptor =  calloc( 1, sizeof(autDescriptor_t));
#endif

  AUT_CHECK_NULL(*descriptor, AUT_EMALLOC);

  (*descriptor)->initstate        = 0;
  (*descriptor)->num_transitions  = 0;
  (*descriptor)->num_states       = 0;

  return AUT_ESUCCESS;
}

/** Implements aut/repr/descriptor::aut_descriptor_destroy */
void
aut_descriptor_destroy(autDescriptor_t **descriptor)
{
  if (descriptor && *descriptor) {
    free(*descriptor);
    *descriptor = NULL;
  }
}

/** Implements aut/repr/descriptor::aut_descriptor_dup */
autError_t
aut_descriptor_dup(autDescriptor_t *src, autDescriptor_t **copy)
{
  AUT_CHECK_NULL(src, AUT_EINVAL1);
  AUT_CHECK_NULL(copy, AUT_EINVAL2);
#ifdef __cplusplus
  *copy = (autDescriptor_t*) calloc( 1, sizeof(autDescriptor_t));
#else
  *copy = calloc( 1, sizeof(autDescriptor_t));
#endif
  AUT_CHECK_NULL(*copy, AUT_EMALLOC);
  (*copy)->initstate        = src->initstate;
  (*copy)->num_transitions  = src->num_transitions;
  (*copy)->num_states       = src->num_states;
  return AUT_ESUCCESS;
}

/** Implements aut/repr/descriptor::aut_descriptor_dup2 */
autError_t
aut_descriptor_dup2(autDescriptor_t *src, autDescriptor_t *copy)
{
  AUT_CHECK_NULL(src, AUT_EINVAL1);
  AUT_CHECK_NULL(copy, AUT_EINVAL2);

  copy->initstate       = src->initstate;
  copy->num_transitions = src->num_transitions;
  copy->num_states      = src->num_states;  

  return AUT_ESUCCESS;
}


/** Implements aut/repr/descriptor::aut_descriptor_set */
autError_t
aut_descriptor_set( autDescriptor_t *descriptor, autState_t initstate,
  size_t num_transitions, size_t num_states)
{
  AUT_CHECK_NULL            (descriptor,      AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE (initstate,       AUT_EINVAL2);
  AUT_CHECK_LIMIT_NUMTRANS  (num_transitions, AUT_EINVAL3);
  AUT_CHECK_LIMIT_NUMSTATES (num_states,      AUT_EINVAL4);

  descriptor->initstate       = initstate;
  descriptor->num_transitions = num_transitions;
  descriptor->num_states      = num_states;

  return AUT_ESUCCESS;
}

AUT_FORCEINLINE autError_t
aut_descriptor_set_initstate(autDescriptor_t *descriptor, autState_t initstate)
{
  AUT_CHECK_NULL        (descriptor,      AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE (initstate,       AUT_EINVAL2);

  descriptor->initstate = initstate;

  return AUT_ESUCCESS;
}

AUT_FORCEINLINE autState_t
aut_descriptor_get_initstate(autDescriptor_t *descriptor)
{
  return descriptor->initstate;
}

AUT_FORCEINLINE autError_t
aut_descriptor_set_num_transitions(autDescriptor_t *descriptor,
  size_t num_transitions)
{
  AUT_CHECK_NULL           (descriptor,      AUT_EINVAL1);
  AUT_CHECK_LIMIT_NUMTRANS (num_transitions, AUT_EINVAL2);

  descriptor->num_transitions = num_transitions;

  return AUT_ESUCCESS;
}

AUT_FORCEINLINE size_t
aut_descriptor_get_num_transitions(autDescriptor_t *descriptor)
{
  return descriptor->num_transitions;
}

AUT_FORCEINLINE autError_t
aut_descriptor_num_transitions_inc(autDescriptor_t *descriptor)
{
  AUT_CHECK_NULL(descriptor, AUT_EINVAL1);

  if ( descriptor->num_transitions == AUT_TRANS_COUNT_MAX)
    return AUT_EFAILURE;

  descriptor->num_transitions = descriptor->num_transitions + 1;

  return AUT_ESUCCESS;
}

AUT_FORCEINLINE autError_t
aut_descriptor_set_num_states(autDescriptor_t *descriptor,
  size_t num_states)
{
  AUT_CHECK_NULL            (descriptor,      AUT_EINVAL1);
  AUT_CHECK_LIMIT_NUMSTATES (num_states,      AUT_EINVAL2);

  descriptor->num_states = num_states;

  return AUT_ESUCCESS;
}

AUT_FORCEINLINE size_t
aut_descriptor_get_num_states(autDescriptor_t *descriptor)
{
  return descriptor->num_states;
}

AUT_FORCEINLINE autError_t
aut_descriptor_num_states_inc(autDescriptor_t *descriptor)
{
  AUT_CHECK_NULL(descriptor, AUT_EINVAL1);

  if ( descriptor->num_states == AUT_STATE_COUNT_MAX)
    return AUT_EFAILURE;

  descriptor->num_states = descriptor->num_states + 1;

  return AUT_ESUCCESS;
}

#ifdef __cplusplus
}
#endif
